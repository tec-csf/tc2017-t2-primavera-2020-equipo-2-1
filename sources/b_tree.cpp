#include<iostream>
#include <stdio.h>
using namespace std;

template<class T>
class BTreeNode
{
    public:
        int pos = -1;
        int numero_elementos;
        int hoja; //1 = hoja

        /* Se actualizan los valores de un nodo
         * dependiendo de lo que hay en el archivo
         * de manera que se pueda accesar a su información
         * con mayor facilidad.
         */
        void read(FILE *file, int p)
        {
            fseek (file , p*sizeof(int) , SEEK_SET);
            fread(&pos, sizeof(int), 1, file);
            fread(&numero_elementos, sizeof(int), 1, file);
            fread(&hoja, sizeof(int), 1, file);
            pos = pos/sizeof(int);
        }
};

template <class T>
class BTree
{

    public:
        /* Constructor de la clase 'BTree'
         * en donde se establece el orden que habrá
         * de seguir el arbol y los nodos.
         */
        BTree(int orden)
        {
            this->orden = orden;
            max = 2*orden-1;
        }

        // Destructor
        ~BTree()
        {
            fclose(file);
        }


        /* Inserción de elementos en el arbol B,
         * depende de que el árbol tenga elementos,
         * su raíz este llena o incompleta para poder ingresar valores.
         */
        void insertar(T value)
        {
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


        /* Encuentra un valor dado dentro de la estructura del árbol.
         * Función auxiliar de 'buscarAux' para evitar llamara al nodo raiz.
         */
        T buscar(T value)
        {
            return buscarAux(root.pos, value);
        }


        /* Se elimina el valor establecido dentro del nodo dado.
         * Función auxiliar de 'remover' que se encarga de cambiar
         * la raiz en caso de que la raíz actual se quede sin elementos.
         */
        void eliminar(T value)
        {
            if (root.pos == -1)
                return;

            remover(root.pos, value);

            root.read(file, root.pos);
            if (root.numero_elementos == 0){
                if(root.hoja == 1)
                    root.pos = -1; //El arbol se convierte en vacío
                else  {
                    actualizar_numero_elementos(-1, root.pos); //Se identifica que la raíz antigua deja de ser un nodo
                    root.read(file, apuntador(root.pos, 0)); //La raiz ahora es el primer apuntador de la raiz vieja
                }
            }
        }


        /* Se recorre el arbol en orden. Función auxiliar
         * de 'recorrerAux' para evitar llamara al nodo raiz.
         */
        void recorrer()
        {
            cout<<"Impresión de los valores en orden: "<<endl;
            recorrerAux(root.pos);
            cout<<endl;
        }


        /* Imprime una 'version grafica'
         * del arbol para ser analizada.
         */
        void imprimirNumeros()
        {
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

    private:
        int orden, max;
        BTreeNode<T> root;
        FILE *file = fopen ("nodos.bin", "w+");

        /* Dependiendo del orden asignado al arbol
         * se crea un espacio vacio en el archivo
         * en la ultima posición disponible, regresando
         * esa misma posición para ser utilizada como 'apuntador'.
         */
        int crear_nodo(int hoja)
        {
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


        /* Se obtiene el valor en un indice del nodo
         * utilizando su posición para calcular
         * la posición del elemento buscado.
         */
        T valor(int nodo, int index)
        {
            T valor;
            fseek (file, (nodo+index+3)*sizeof(T), SEEK_SET);
            fread(&valor, sizeof(T), 1, file);
            return valor;
        }


        /* Se obtiene el apuntador hacia otro nodo
         * utilizando su indice junto con la posición
         *  del nodo para localizar el valor en el archivo.
         */
        int apuntador(int nodo, int index)
        {
            int apuntador;
            fseek (file, (nodo+index+max+3)*sizeof(T), SEEK_SET);
            fread(&apuntador, sizeof(int), 1, file);
            return apuntador;
        }


        // Se sobreescribe un valor en una posición dada de un nodo.
        void escribir_valor(T value, int nodo, int index)
        {
            fseek (file, (nodo+index+3)*sizeof(T), SEEK_SET);
            fwrite (&value, sizeof(T), 1, file);
        }


        // Se sobreescribe un apuntador en una posición dada de un nodo.
        void escribir_apuntador(int apuntador, int nodo, int index)
        {
            fseek (file, (nodo+index+max+3)*sizeof(T), SEEK_SET);
            fwrite (&apuntador, sizeof(int), 1, file);
        }


        // Se actualiza el número de elementos dentro del achivo.
        void actualizar_numero_elementos(int num, int nodo)
        {
            fseek (file, (nodo+1)*sizeof(int), SEEK_SET);
            fwrite (&num, sizeof(int), 1, file);
        }


        // Se recorre el arbol en orden.
        void recorrerAux(int node_pos)
        {
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


        // Función para encontrar un valor dentro de la estructura del árbol.
        T buscarAux(int node_pos, T value)
        {
            BTreeNode<T> node;
            node.read(file, node_pos);

            int i = 0;
            while (i < node.numero_elementos && value > valor(node.pos, i))
                i++;

            if (valor(node.pos, i) == value)
                return valor(node.pos, i);
            if (node.hoja == 1)
                return NULL;

            return buscarAux(apuntador(node.pos, i), value);
        }


        /* Función para insertar en casos donde el nodo aún no se completa.
         *
         * @param node_pos:
         */
        void insertar_a_nodo_incompleto(int node_pos, T value)
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


        /* Se divide un nodo dado, reasignando
         * valores y llaves entre los nodos resultantes.
         */
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


        /* Se elimina el valor establecido dentro del nodo dado.
        *
        * @param node_pos:
        */
        void remover(int node_pos, T value)
        {
            BTreeNode<T> node;
            node.read(file, node_pos);

            int index = 0;
            while (index<node.numero_elementos && valor(node.pos, index) < value) //Se identifica la posición del valor a eliminar
                ++index;

            if (index < node.numero_elementos && valor(node.pos, index) == value){ //El valor se encunetra en este nodo
                if (node.hoja == 1) //Se determina si se está eliminando de una hoja o no
                    remover_de_hoja(node.pos, index);
                else
                    remover_de_no_hoja(node.pos, index);
            } else {
                if (node.hoja == 1)
                    return; //El elemento no se encuentra, no se realiza ninguna operacion

                BTreeNode<T> index_node;
                index_node.read(file, apuntador(node.pos, index));
                bool flag = ((index == node.numero_elementos)? true : false); //El valor se encunetra en el último elemento de este nodo

                if (index_node.numero_elementos < orden)
                    llenar(node.pos, index); //Se llena el nodo hijo izquierdo en caso de tener numero de elementos que el orden establecido

                node.read(file, node.pos);
                if (flag && index > node.numero_elementos)
                    remover(apuntador(node.pos, index-1), value); //Al haberse llenado el nodo hijo izquierdo, se elimina el valor buscado de el
                else
                    remover(apuntador(node.pos, index), value);  //Se remueve el valor buscado del hijo derecho.
            }
        }


        /* Remueve el valor buscado en un nodo
         * que no posee hijos (o nodo hoja).
         *
         * @param node_pos:
         */
        void remover_de_hoja (int node_pos, int index)
        {
            BTreeNode<T> node;
            node.read(file, node_pos);

            for (int i=index+1; i<node.numero_elementos; ++i) //Se mueven todos los elementos un lugara hacia atrás, eliminando el valor
                escribir_valor(valor(node.pos, i), node.pos, i-1);

            actualizar_numero_elementos(node.numero_elementos-1, node.pos); //Se reduce el número de elementos del nodo hoja
        }


        /* Remueve el valor buscado en un nodo que posee hijos.
         *
         * @param node_pos:
         */
        void remover_de_no_hoja(int node_pos, int index)
        {
            BTreeNode<T> node, test_node_1, test_node_2;
            node.read(file, node_pos);

            int value = valor(node.pos, index); //Se obtiene el valor buscado

            test_node_1.read(file, apuntador(node.pos, index));
            test_node_2.read(file, apuntador(node.pos, index+1));
            //Se obtiene el numero de elementos en los sucesores y predecesores para determinar que método utilizar
            if (test_node_1.numero_elementos >= orden){
                int predecesor = obtener_predecesor(node.pos, index);
                escribir_valor(predecesor, node.pos, index); //Se reemplaza con el predecesor
                remover(test_node_1.pos, predecesor); //Se elimina el predecesor en el hijo izquierdo
            } else if (test_node_2.numero_elementos >= orden){
                int sucesor = obtener_sucesor(node.pos, index);
                escribir_valor(sucesor, node.pos, index); //Se reemplaza con el sucesor
                remover(test_node_2.pos, sucesor); //Se elimina el sucesor en el hijo derecho
            } else { //Si el numero de elementos de ammbos hijos es menor al orden se unen ambos hijos.
                merge(node.pos, index);
                remover(apuntador(node.pos, index), value); //Se remueve el valor del nodo resultante
            }
        }


        /* Obtiene el elemento predecesor (mayor de los menores).
         *
         * @param node_pos:
         */
        int obtener_predecesor(int node_pos, int index)
        {
            BTreeNode<T> node;
            node.read(file, apuntador(node_pos, index));

            while (node.hoja != 1) //Se desplaza por los valores extremos derechos mientras no se encuentre en una hoja
                node.read(file, apuntador(node.pos, node.numero_elementos));

            return valor(node.pos, node.numero_elementos-1); //Regresa el predecesor (mayor de los menores)
        }


        /* Obtiene el elemento sucesor (menor de los mayores).
         *
         * @param node_pos:
         */
        int obtener_sucesor(int node_pos, int index)
        {
            BTreeNode<T> node;
            node.read(file, apuntador(node_pos, index+1));

            while (node.hoja != 1) //Se desplaza por los valores extremos izquierdos mientras no esté en una hoja
                node.read(file, apuntador(node.pos, 0));

            return valor(node.pos, 0); //Regresa el sucesor (menor de los mayores)
        }


        /* Llena un nodo que se ha quedado con menos elementos
         * que los establecidos por el orden utilizando valores
         * pertenecientes a uno de sus nodos hermanos.
         *
         * @param node_pos:
         */
        void llenar(int node_pos, int index)
        {
            BTreeNode<T> node, previous, next;
            //Se obtiene el nodo anterior y el siguiente
            node.read(file, node_pos);
            previous.read(file, apuntador(node.pos, index-1));
            next.read(file, apuntador(node.pos, index+1));

            //Se transfieren elementos del nodo con más elementos al nodo con menos elementos
            if (index != 0 && previous.numero_elementos >= orden)
                tomar_anterior(node.pos, index);
            else if (index != node.numero_elementos && next.numero_elementos >= orden)
                tomar_siguiente(node.pos, index);
            else { //Se realiza un merge entre nodos hermanos
                if (index != node.numero_elementos)
                    merge(node.pos, index);
                else
                    merge(node.pos, index-1);
            }
        }


        /* Se transfiere un valor del nodo hijo izquierdo al nodo actual.
        *
        * @param node_pos:
        */
        void tomar_anterior(int pos_node, int index)
        {
            BTreeNode<T> node, child, sibling;
            node.read(file, pos_node);
            child.read(file, apuntador(node.pos, index));
            sibling.read(file, apuntador(node.pos, index-1));

            for (int i=child.numero_elementos-1; i>=0; --i) //Se desplazan hacia la derecha los elementos del nodo hijo
                escribir_valor(valor(child.pos, i), child.pos, i+1);

            if (child.hoja != 1){ //Se recorren los apuntadores en caso de no haber sido un nodo hijo
                for (int i=child.numero_elementos; i>=0; --i)
                    escribir_apuntador(apuntador(child.pos, i), child.pos, i+1);
            }

            escribir_valor(valor(node.pos, index-1), child.pos, 0); //Se coloca el elemento del indice en el nodo actual en el nodo hijo

            if (child.hoja != 1) //Se recorre el último apuntador del nodo hermano del hijo  al nodo hijo
                escribir_apuntador(apuntador(sibling.pos, sibling.numero_elementos), child.pos, 0);

            //El último elemento del nodo hermano del hijo se coloca en el padre
            escribir_valor(valor(sibling.pos, sibling.numero_elementos-1), node.pos, index-1);

            //Se actualiza el numero de elementos tanto en el hijo como en su hermano
            actualizar_numero_elementos(child.numero_elementos+1, child.pos);
            actualizar_numero_elementos(sibling.numero_elementos-1, sibling.pos);
        }


        /* Se transfiere un valor del nodo hijo derecho al nodo actual.
        *
        * @param node_pos:
        */
        void tomar_siguiente(int node_pos, int index)
        {
            BTreeNode<T> node, child, sibling;
            node.read(file, node_pos);
            child.read(file, apuntador(node.pos, index));
            sibling.read(file, apuntador(node.pos, index+1));

            //El elemento en el indice se vuelve el ultimo elemento del hijo
            escribir_valor(valor(node.pos, index), child.pos, child.numero_elementos);

            if (child.hoja != 1) //Se transfiere el primer apuntador del nodo hermano al último del nodo hijo
                escribir_apuntador(apuntador(sibling.pos, 0), child.pos, child.numero_elementos+1);

            escribir_valor(valor(sibling.pos, 0), node.pos, index); //Se transifere valor entre nodo hermano y nodo hijo

            for (int i=1; i<sibling.numero_elementos; ++i) //Se recorren hacia la izquierda los elementos en el nodo hermano
                escribir_valor(valor(sibling.pos, i), sibling.pos, i-1);

            if (sibling.hoja != 1){ //Se recorren hacia la izquierda los apuntadores en el nodo hermano
                for (int i=1; i<=sibling.numero_elementos; ++i)
                    escribir_apuntador(apuntador(sibling.pos, i), sibling.pos, i-1);
            }

            //Se actualiza el numero de elementos tanto en el hijo como en su hermano
            actualizar_numero_elementos(child.numero_elementos+1, child.pos);
            actualizar_numero_elementos(sibling.numero_elementos-1, sibling.pos);
        }


        /* Se unen los elementos de 2 nodos hijos de un nodo dado,
        dejando un solo nodo y eliminando el otro como resultado.
        *
        * @param node_pos:
        */
        void merge(int node_pos, int index)
        {
            BTreeNode<T> node, child, sibling;
            node.read(file, node_pos);
            child.read(file, apuntador(node.pos, index));
            sibling.read(file, apuntador(node.pos, index+1));

            //Se transfiere el elemento en cuestión del nodo actual al hijo
            escribir_valor(valor(node.pos, index), child.pos, orden-1);

            //Se copian los elementos y apuntadores del nodo hermano al hijo
            for (int i=0; i<sibling.numero_elementos; ++i)
                escribir_valor(valor(sibling.pos, i), child.pos, i+orden);
            if (child.hoja != 1) {
                for(int i=0; i<=sibling.numero_elementos; ++i)
                    escribir_apuntador(apuntador(sibling.pos, i), child.pos, i+orden);
            }

            //Se dezplazan los elementos y apuntadores en el nodo padre una posición
            for (int i=index+1; i<node.numero_elementos; ++i)
                escribir_valor(valor(node.pos, i), node.pos, i-1);
            for (int i=index+2; i<=node.numero_elementos; ++i)
                escribir_apuntador(apuntador(node.pos, i), node.pos, i-1);

            //Se actualiza el numero de elementos en el nodo hijo (nodo resultante) y el padre, y se descarta el nodo hermano
            actualizar_numero_elementos(child.numero_elementos+sibling.numero_elementos+1, child.pos);
            actualizar_numero_elementos(node.numero_elementos-1, node.pos);
            actualizar_numero_elementos(-1, sibling.pos);
        }
};
