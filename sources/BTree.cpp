#include<iostream> 
#include <stdio.h>
using namespace std; 

template<class T>
class BTreeNode{
    public: 
        int pos = -1; 
        int numero_elementos; 
        int hoja; //1 = hoja

        /*Se actualizan los valores de un nodo dependiendo de lo que hay 
        en el archivo de manera que se pueda accesar a su información con 
        mayor facilidad */
        void read(FILE *file, int p){
            fseek (file , p*sizeof(int) , SEEK_SET);
            fread(&pos, sizeof(int), 1, file);
            fread(&numero_elementos, sizeof(int), 1, file);
            fread(&hoja, sizeof(int), 1, file); 
            pos = pos/sizeof(int);
        }
};
  
template <class T>
class BTree{
    private:
        int orden, max; 
        BTreeNode<T> root; 
        FILE *file = fopen ("nodos.bin", "w+");

    public: 
        BTree(int orden){
            this->orden = orden; 
            max = 2*orden-1; 
        }
        ~BTree(){
            fclose(file);
        }

        /* Dependiendo del orden asignado al arbol se crea un espacio vacio 
        en el archivo en la ultima posición disponible, regresando esa misma
        posición para ser utilizada como 'apuntador'*/
        int crear_nodo(int hoja){
            int numero_elementos = 0; 
            int pos;
            int none = NULL; 
            
            fseek (file, 0, SEEK_END);
            pos = ftell(file);
            fwrite (&pos, sizeof(int), 1, file);
            fwrite (&numero_elementos, sizeof(int), 1, file);
            fwrite (&hoja, sizeof(int), 1, file);
            
            for(int i = 0; i<(2*max+1); i++){
                fwrite (&none, sizeof(int), 1, file);
            }

            return pos/sizeof(int); 
        }

        /* Se obtiene el valor en un indice del nodo utilizando su posición
        para calcular la posición del elemento buscado*/ 
        T valor(int nodo, int index){
            T valor; 
            fseek (file, (nodo+index+3)*sizeof(T), SEEK_SET);
            fread(&valor, sizeof(T), 1, file);
            return valor; 
        }

        /* Se obtiene el apuntador hacia otro nodo utilizando su indice junto
        con la posición del nodo para localizar el valor en el archivo*/
        int apuntador(int nodo, int index){
            int apuntador; 
            fseek (file, (nodo+index+max+3)*sizeof(T), SEEK_SET);
            fread(&apuntador, sizeof(int), 1, file);
            return apuntador; 
        }

        /* Se sobre escribe un valor en una posición dada de un nodo */
        void escribir_valor(T value, int nodo, int index){
            fseek (file, (nodo+index+3)*sizeof(T), SEEK_SET);
            fwrite (&value, sizeof(T), 1, file);
        }

        /* Se sobre escribe un apuntadoe en una posición dada de un nodo */
        void escribir_apuntador(int apuntador, int nodo, int index){
            fseek (file, (nodo+index+max+3)*sizeof(T), SEEK_SET);
            fwrite (&apuntador, sizeof(int), 1, file);
        }

        /*Se actualiza el numero de elementos dentro del achivo*/
        void actualizar_numero_elementos(int num, int nodo){
            fseek (file, (nodo+1)*sizeof(int), SEEK_SET);
            fwrite (&num, sizeof(int), 1, file);
        }

        /* Función auxiliar de recorres para evitar llamara al nodo raiz */
        void recorrer(){
            cout<<"Impresión de los valores en orden: "<<endl;
            recorrerAux(root.pos);
            cout<<endl;
        }   
        /* Se recorre el arbol en orden */ 
        void recorrerAux(int node_pos){ 
            BTreeNode<T> node; 
            node.read(file, node_pos);

            int i; 
            for (i = 0; i < node.numero_elementos; i++) 
            {
                if (node.hoja != 1) 
                    recorrerAux(apuntador(node.pos, i));
                cout << " " << valor(node.pos, i); 
            } 
        
            if (node.hoja != 1) 
                recorrerAux(apuntador(node.pos, i));
        } 

        /* Inserción de elementos en el arbol B, depende de que el arbol tenga
        elementos, su raiz este llena o incompleta para poder ingresar valores */
        void insertar(int value){ 
            if (root.pos == -1){ //Caso en el que el arbol se encuentra vacío 
                crear_nodo(1); 
                escribir_valor(value, 0, 0); 
                root.read(file, 0); 
                actualizar_numero_elementos(root.numero_elementos+1, root.pos); 
                root.read(file, root.pos); 
            } else { 
                if (root.numero_elementos == max){ //la raíz esta llena
                    //Se crea un nuevo nodo y se coloca un apuntador hacia la vieja raiz
                    int posicion_nueva_raiz = crear_nodo(0);
                    escribir_apuntador(root.pos, posicion_nueva_raiz, 0); 

                    dividir(0, posicion_nueva_raiz, root.pos); //División de la raíz previa
        
                    int i = 0; 
                    if (valor(posicion_nueva_raiz, i) < value) 
                        i++; 
                    insertar_a_nodo_incompleto(apuntador(posicion_nueva_raiz, i), value);
        
                    root.read(file, posicion_nueva_raiz); //Se actualiza la raiz
                } 
                else { // La raiz no esta llena
                    insertar_a_nodo_incompleto(root.pos, value);
                    root.read(file, root.pos);
                }
            } 
        } 
        
        /* Función para insertar en casos donde el nodo aún no se completa */
        void insertar_a_nodo_incompleto(int node_pos, int value) 
        { 
            BTreeNode<T> node; 
            node.read(file, node_pos);
            int i = node.numero_elementos - 1;
        
            if (node.hoja == 1){ 
                while (i >= 0 && valor(node.pos, i) > value) {//Se recorren los valores y coloca el nuevo valor 
                    escribir_valor(valor(node.pos, i), node.pos, i+1); 
                    i--; 
                } 
        
                escribir_valor(value, node.pos, i+1); 
                actualizar_numero_elementos(node.numero_elementos+1, node.pos);
            } else { //El nodo analizado no es hoja
                while (i >= 0 && valor(node.pos, i) > value) //Encontrar posición para nodo hijo
                    i--; 

                BTreeNode<T> child; 
                child.read(file, apuntador(node.pos, i+1)); 

                if (child.numero_elementos == 2*orden-1){   //El nodo hijo está lleno, se debe dividir    
                    dividir(i+1, node.pos, child.pos); 
        
                    if (valor(node.pos, i+1) < value) 
                        i++; 
                } 
                insertar_a_nodo_incompleto(apuntador(node.pos, i+1), value); 
            }
        } 
        
        /*Se divide un nodo dado, reasignando valores y llaves entre los nodos resultantes */
        void dividir(int i, int nodo_original, int nodo_dividido) 
        { 
            BTreeNode<T> original, dividido; 
            original.read(file, nodo_original); 
            dividido.read(file, nodo_dividido);
            int posicion_nuevo = crear_nodo(dividido.hoja);
            actualizar_numero_elementos(orden-1, posicion_nuevo);       
            
            for (int j = 0; j < orden-1; j++) 
                escribir_valor(valor(dividido.pos, j+orden), posicion_nuevo, j);
        
            if (dividido.hoja != 1){ 
                for (int j = 0; j < orden; j++) 
                    escribir_apuntador(apuntador(dividido.pos, j+orden), posicion_nuevo, j);
            }
        
            actualizar_numero_elementos(orden-1, dividido.pos); 

            for (int j = original.numero_elementos; j >= i+1; j--) 
                escribir_apuntador(apuntador(original.pos, j), original.pos, j+1); 
        
            escribir_apuntador(posicion_nuevo, original.pos, i+1);
        
            for (int j = original.numero_elementos-1; j >= i; j--) 
                escribir_valor(valor(original.pos, j), original.pos, j+1); 
        
            escribir_valor(valor(dividido.pos, orden-1), original.pos, i);
        
            actualizar_numero_elementos(original.numero_elementos+1, original.pos); 
        } 

        /*Imprime una 'version grafica' del arbol para ser analizada */
        void imprimirNumeros(){
            int last, temp;
            fseek (file, 0, SEEK_END);
            last = ftell(file);
            rewind(file);

            cout<<"Orden: "<<orden<<", Raiz: "<<root.pos<<" (multiplicar por 4 o sizeof(int))"<<endl;
            cout<<"Indices por nodo: \n\t0\tPosicion en el archivo\n\t1\tCantidad de elementos en el nodo\n\t2\tHoja (1) o No Hoja(0)\n\t";
            cout<<"3-"<<max+2<<"\tValores\n\t"<<max+3<<"-"<<2*max+3<<"\tApuntadores (multiplicar por 4 o sizeof(int))"<<endl;
            for (int i=1; i<=last/sizeof(int); i++){
                fread(&temp, sizeof(int), 1, file);
                cout<<temp<<" "; 
                if (i%(2*max+4) == 0)
                    cout<<"|";
            }
            cout<<endl;
        }
};

int main(){
    BTree<int> t(3); 

    t.insertar(10); 
    t.insertar(20); 
    t.insertar(5); 
    t.insertar(6); 
    t.insertar(12); 
    t.insertar(30); 
    t.insertar(7); 
    t.insertar(17);
    t.insertar(8);
    t.insertar(19);
    t.insertar(31);
    t.insertar(1);
    t.insertar(2);
    t.insertar(40);
    t.insertar(45);
    t.insertar(35);
    t.insertar(32);
    t.insertar(50);
    t.insertar(51);
    t.insertar(55);
    t.insertar(60);
    t.insertar(70);

    t.recorrer(); 

    cout<<endl; 
    t.imprimirNumeros();

    return 0; 
}