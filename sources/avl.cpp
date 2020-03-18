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

        ~Nodo();
}; 

//Clase AVL
template <class T>
class AVL{
    public:
        Nodo<T> *raiz = NULL;
        
        //Regresar la altura de cada nodo
        int height(Nodo<T> *nodo)  
        {  
            if (nodo == NULL)  
                return 0;  
            return nodo->height;  
        }  
        
        /*Encontrar l altura mazima entre 2 enteros, utilizada para actualizar 
        las alturas de los nodos correctamente y conocer su factor de balanceo */
        int max(int a, int b)  
        {  
            return (a > b)? a : b;  
        }  
        
        //Rotaciones a la derecha
        Nodo<T> *rotacion_simple_derecha(Nodo<T> *pivote)  
        {  
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
        Nodo<T> *rotacion_simple_izquierda(Nodo<T> *pivote)  
        {  
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
        int obtener_factor_balanceo(Nodo<T> *N)  
        {  
            if (N == NULL)  
                return 0;  
            return height(N->left) - height(N->right);  
        }  
        
        //Función auxiliar para no tener que esta colocando la raíz en cada llamad
        Nodo<T>* insertar(int value){
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
            if (factor_balanceo > 1){  
                if (value > node->left->value)  // Caso en que se requiere una rotación doble
                    return rotacion_doble_derecha(node); 
                return rotacion_simple_derecha(node);  
            }
            // El arbol se encuentra cargado hacia la derecha
            if (factor_balanceo < -1 && value > node->right->value){  
                if (factor_balanceo < -1 && value < node->right->value)  // Caso en que se requiere una rotación doble
                    return rotacion_doble_izquierda(node);  
                return rotacion_simple_izquierda(node);  
            }

            //En caso de no requerir rotaciones
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
};  
  
// Driver Code 
int main()  
{  
    AVL<int> arbol;  
      
    /* Constructing tree given in  
    the above figure */
    arbol.insertar(10);  
    arbol.insertar(20);  
    arbol.insertar(30);  
    arbol.insertar(40);  
    arbol.insertar(50);  
    arbol.insertar(25);  

    cout << "Arbol inOrden:\n";  
    arbol.inOrder();  
      
    return 0;  
} 