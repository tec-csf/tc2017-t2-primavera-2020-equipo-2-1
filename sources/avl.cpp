#include <iostream>
using namespace std; 
  
// Clase Nodo, contiene la altura de cada nodo (un mínimo de 1)
template <class T>
class Nodo{
	public:
        T value;
        Nodo<T> *right;
        Nodo<T> *left;
        int height; 
        
        Nodo<T>(){
            value=NULL;
            right=NULL;
            left=NULL;
            height=1; 
        }
        
        Nodo<T>(T val){
            value=val;
            right=NULL;
            left=NULL;
            height=1; 
        }

        ~Nodo(){
            delete this; 
        };
}; 

//Clase AVL
template <class T>
class AVL{
    public:
        Nodo<T> *raiz = NULL;
        
        //Regresar la altura de cada nodo
        int height(Nodo<T> *nodo){  
            if (nodo == NULL)  
                return 0;  
            return nodo->height;  
        }  
        
        /*Encontrar l altura mazima entre 2 enteros, utilizada para actualizar 
        las alturas de los nodos correctamente y conocer su factor de balanceo */
        int max(int a, int b){  
            return (a > b)? a : b;  
        }  
        
        //Rotaciones a la derecha
        Nodo<T> *rotacion_simple_derecha(Nodo<T> *pivote){  
            Nodo<T> *pivote_left = pivote->left;  
            Nodo<T> *new_pivote_left = pivote_left->right;  
        
            // Rotación 
            pivote_left->right = pivote;  
            pivote->left = new_pivote_left;  
        
            // Update heights  
            pivote->height = max(height(pivote->left), height(pivote->right)) + 1;  
            pivote_left->height = max(height(pivote_left->left), height(pivote_left->right)) + 1;  
        
            // Nueva raiz (lo que se encontraba a la izquierda del pivote)   
            return pivote_left;  
        }  
        Nodo<T> *rotacion_doble_derecha(Nodo<T> *pivote){
            pivote->left = rotacion_simple_izquierda(pivote->left);  
            return rotacion_simple_derecha(pivote);  
        }
        
        //Rotaciones a la izquierda
        Nodo<T> *rotacion_simple_izquierda(Nodo<T> *pivote){  
            Nodo<T> *pivote_right = pivote->right;  
            Nodo<T> *new_pivote_right = pivote_right->left;  

            // Rotación
            pivote_right->left = pivote;  
            pivote->right = new_pivote_right;  
        
            // Actualización de alturas
            pivote->height = max(height(pivote->left), height(pivote->right)) + 1;  
            pivote_right->height = max(height(pivote_right->left), height(pivote_right->right)) + 1;  
        
            // Nueva raiz (lo que se encontraba a la derecha del pivote)  
            return pivote_right;  
        }  
        Nodo<T> *rotacion_doble_izquierda(Nodo<T> *pivote){
            pivote->right = rotacion_simple_derecha(pivote->right);  
            return rotacion_simple_izquierda(pivote);  
        }
        
        // Get Balance factor of node N  
        int obtener_factor_balanceo(Nodo<T> *node){  
            if (node == NULL)  
                return 0;  
            return height(node->right) - height(node->left);  
        }  

        //Función para obtener el valor del nodo sucesor
        Nodo<T> *nodo_sucesor(Nodo<T>* node){  
            Nodo<T>* current = node->right;  
        
            while (current->left != NULL)  
                current = current->left;  
        
            return current;  
        }  
        
        //Función auxiliar para no tener que esta colocando la raíz en cada llamad
        void insertar(int value){
            raiz = insertAux(raiz, value); 
        }
        //Función de insertar implementada recursivamente
        Nodo<T>* insertAux(Nodo<T>* node, int value)  
        {  
            //Se inserta el nodo de manera recursiva
            if (node == NULL){
                Nodo<T>* nodo_insertado = new Nodo<T>(value);
                return(nodo_insertado);  
            }
            if (value < node->value)  
                node->left = insertAux(node->left, value);  
            else if (value > node->value)  
                node->right = insertAux(node->right, value);  
            else 
                return node;  
        
            //Se actualiza la altura de cada nodo
            node->height = 1 + max(height(node->left), height(node->right));  
        
            //Se obtiene el factor de balanceo de cada nodo para determinar si es necesario realizar una rotación 
            int factor_balanceo = obtener_factor_balanceo(node);  
        
            // El arbol se encuentra cargado hacia la izquierda
            if (factor_balanceo < -1){  
                if (value > node->left->value)  // Caso en que se requiere una rotación doble (se forma una escuadra)
                    return rotacion_doble_derecha(node); 
                return rotacion_simple_derecha(node);  
            }
            // El arbol se encuentra cargado hacia la derecha
            if (factor_balanceo > 1){  
                if (value < node->right->value)  // Caso en que se requiere una rotación doble
                    return rotacion_doble_izquierda(node);  
                return rotacion_simple_izquierda(node);  
            }

            //En caso de no requerir rotaciones
            return node;  
        }  
        
        //Función auxiliar para no tener que esta colocando la raíz en cada llamada
        void eliminar(int value){
            raiz = eliminarAux(raiz, value); 
        }
        //Función de eliminar implementada recursivamente
        Nodo<T>* eliminarAux(Nodo<T>* node, int value)  
        {  
            if (node == NULL)  //El elemento a eliminar no se encuentra en el árbol 
                return node;  
        
            /* Se reccore el arbol (ya sea hacia la derecha o la izquierda) 
            comparando con el valor del nodo actual hasta encontrar el valor*/
            if (value < node->value)  
                node->left = eliminarAux(node->left, value);  
            else if( value > node->value )  
                node->right = eliminarAux(node->right, value);  
            else //Se encuentra el valor buscado
            {  
                // Nodo con 0 o 1 sucesor
                if((node->left == NULL) || (node->right == NULL)){  
                    Nodo<T> *temp = node->left ? node->left : node->right;  
                    // Se trata de un nodo sin sucesores 
                    if (temp == NULL) {  
                        temp = node;  
                        node = NULL;  
                    }  
                    else // Solo existe un sucesor
                        *node = *temp; 

                    free(temp);  //Se libera el espacio utilizado
                }  
                else{  
                    /*Se obtiene el nodo sucesor y se almacena en un nodo 
                    temporal copiado al nodo deseado*/
                    Nodo<T>* temp = nodo_sucesor(node);  
                    node->value = temp->value;  
                    // Se elimina el nodo sucesor
                    node->right = eliminarAux(node->right, temp->value);  
                }  
            }  
        
            // Se sale del método si el arbol únicamente contaba con un elemento 
            if (node == NULL)  
                return node;  
        
            // Se actualiza la altura del nodo en cuestion
            node->height = 1 + max(height(node->left), height(node->right));  
        
            // Se obtiene el factor de balanceo del nodo en cuestion
            int factor_balanceo = obtener_factor_balanceo(node);  
        
            // El arbol se encuentra cargado hacia la izquierda
            if (factor_balanceo < -1){  
                if (obtener_factor_balanceo(node->left) > 0)  // Caso en que se requiere una rotación doble (se forma una escuadra)
                    return rotacion_doble_derecha(node); 
                return rotacion_simple_derecha(node);  
            }
            // El arbol se encuentra cargado hacia la derecha
            if (factor_balanceo > 1){  
                if (obtener_factor_balanceo(node->right) < 0)  // Caso en que se requiere una rotación doble
                    return rotacion_doble_izquierda(node);  
                return rotacion_simple_izquierda(node);  
            }
        
            return node;  
        }  
        
        //Impresión 'inOrder'
        void inOrder(){
            inOrderAux(raiz);
        }
        void inOrderAux(Nodo<T> *raiz)  
        {  
            if(raiz != NULL)  
            {  
                inOrderAux(raiz->left); 
                cout << raiz->value << " ";   
                inOrderAux(raiz->right);  
            }  
        }

        //Impresión 'preOrder'
        void preOrder(){
            preOrderAux(raiz);
        }
        void preOrderAux(Nodo<T> *raiz)  
        {  
            if(raiz != NULL)  
            {  
                cout << raiz->value << " ";  
                preOrderAux(raiz->left);  
                preOrderAux(raiz->right);  
            }  
        }  
};  
  
int main()  
{  
    AVL<int> arbol;  
      
    //Valores de prueba
    arbol.insertar(9);  
    arbol.insertar(5);  
    arbol.insertar(10);  
    arbol.insertar(0);  
    arbol.insertar(6);  
    arbol.insertar(11);
    arbol.insertar(-1); 
    arbol.insertar(1); 
    arbol.insertar(2);

    cout << "Arbol en orden previo a eliminación de 10:\n";  
    arbol.inOrder(); 
    cout << "\nArbol en pre orden previo a eliminación de 10:\n";  
    arbol.preOrder();   

    arbol.eliminar(10);

    cout << "\nArbol en orden despues de eliminar 10:\n";  
    arbol.inOrder(); 
    cout << "\nArbol en pre orden despues de eliminar 10:\n";  
    arbol.preOrder(); 
      
    return 0;  
} 