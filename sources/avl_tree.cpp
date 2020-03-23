#include <iostream>
using namespace std;

// Clase Nodo_AVL, contiene la altura de cada nodo (un mínimo de 1)
template <class T>
class Nodo_AVL
{
	public:
        T value;
        Nodo_AVL<T>* right;
        Nodo_AVL<T>* left;
        int height;

        // CONSTRUCTORES
        Nodo_AVL<T>()
        {
            value = NULL;
            right = NULL;
            left = NULL;
            height = 1;
        }

        Nodo_AVL<T>(T val)
        {
            value=val;
            right=NULL;
            left=NULL;
            height=1;
        }

        // DESTRUCTOR
        ~Nodo_AVL()
        {
            delete this;
        }
};

//Clase AVL
template <class T>
class AVL
{
    public:
        /* Función auxiliar para no tener que
         * estar colocando la raíz en cada llamada.
				 * @param value: valor genérico que tendrá el nodo creado,
 				 * 							para su posterior inserción.
         */
        void insertar(T value)
        {
            raiz = insertAux(raiz, value);
        }


        /* Función de insertar (implementada recursivamente).
				 * @param* node: apuntador al nodo que se está insertando.
				 * @param value: valor genérico que tendrá el nodo insertado.
				 */
        Nodo_AVL<T>* insertAux(Nodo_AVL<T>* node, T value)
        {
            //Se inserta el nodo de manera recursiva
            if (node == NULL){
                Nodo_AVL<T>* nodo_insertado = new Nodo_AVL<T>(value);
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

        /* Función auxiliar para no tener que
        * estar colocando la raíz en cada llamada.
				* @param value: valor genérico que tendrá el nodo creado,
				* 							para su posterior búsqueda y luego eliminación.
        */
        void eliminar(T value)
        {
            raiz = eliminarAux(raiz, value);
        }


        /* Función de eliminar (implementada recursivamente).
				 * @param* node: apuntador al nodo que se está eliminando.
				 * @param value: valor genérico que se comparará al nodo a eliminar.
				 */
        Nodo_AVL<T>* eliminarAux(Nodo_AVL<T>* node, T value)
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
                // Nodo_AVL con 0 o 1 sucesor
                if((node->left == NULL) || (node->right == NULL)){
                    Nodo_AVL<T> *temp = node->left ? node->left : node->right;
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
                    Nodo_AVL<T>* temp = nodo_sucesor(node);
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


        /* Función auxiliar para no tener que
         * estar colocando la raíz en cada llamada.
				 * @param value: valor genérico que tendrá el nodo creado,
 				* 							para su posterior búsqueda.
         */
        T buscar(T value)
        {
            return buscarAux(raiz, value);
        }


        /* Función de buscar (implementada recursivamente).
				 * @param* node: apuntador al nodo que se está buscando.
				 * @param value: valor genérico que se comparará al nodo buscado.
				 */
        T buscarAux(Nodo_AVL<T>* node, T value)
        {
            if (node == NULL)
                return NULL;
            if (value < node->value)
                return buscarAux(node->left, value);
            else if (value > node->value)
                return buscarAux(node->right, value);
            else
                return node->value;
        }


        // Impresión 'inOrder'.
        void inOrder()
        {
            inOrderAux(raiz);
            cout<<endl;
        }


        // Función auxiliar para la impresión 'inOrder'.
        void inOrderAux(Nodo_AVL<T> *raiz)
        {
            if(raiz != NULL)
            {
                inOrderAux(raiz->left);
                cout << raiz->value << " ";
                inOrderAux(raiz->right);
            }
        }


        //Impresión 'preOrder'.
        void preOrder()
        {
            preOrderAux(raiz);
            cout<<endl;
        }


        // Función auxiliar para la impresión 'preOrder'.
        void preOrderAux(Nodo_AVL<T> *raiz)
        {
            if(raiz != NULL)
            {
                cout << raiz->value << " ";
                preOrderAux(raiz->left);
                preOrderAux(raiz->right);
            }
        }

    private:
        Nodo_AVL<T> *raiz = NULL;

        // Regresa la altura de cada nodo.
        int height(Nodo_AVL<T> *nodo)
        {
            if (nodo == NULL)
                return 0;
            return nodo->height;
        }


        /* Encuentra la altura máxima entre 2 enteros,
         * utilizada para actualizar las alturas de los
         * nodos correctamente y conocer su factor de balanceo.
				 * @param a, b: enteros a comparar.
         */
        int max(int a, int b)
        {
            return (a > b)? a : b;
        }


        /* Rotación a la derecha (simple).
				 * @param* pivote: apuntador a nodo que será usado como "pivote".
				 */
        Nodo_AVL<T> *rotacion_simple_derecha(Nodo_AVL<T>* pivote)
        {
            Nodo_AVL<T> *pivote_left = pivote->left;
            Nodo_AVL<T> *new_pivote_left = pivote_left->right;

            // Rotación
            pivote_left->right = pivote;
            pivote->left = new_pivote_left;

            // Update heights
            pivote->height = max(height(pivote->left), height(pivote->right)) + 1;
            pivote_left->height = max(height(pivote_left->left), height(pivote_left->right)) + 1;

            // Nueva raiz (lo que se encontraba a la izquierda del pivote)
            return pivote_left;
        }


				/* Rotación a la derecha (doble).
				 * @param* pivote: apuntador a nodo que será usado como "pivote".
				 */
        Nodo_AVL<T> *rotacion_doble_derecha(Nodo_AVL<T> *pivote)
        {
            pivote->left = rotacion_simple_izquierda(pivote->left);
            return rotacion_simple_derecha(pivote);
        }


				/* Rotación a la izquierda (simple).
				 * @param* pivote: apuntador a nodo que será usado como "pivote".
				 */
        Nodo_AVL<T> *rotacion_simple_izquierda(Nodo_AVL<T> *pivote)
        {
            Nodo_AVL<T> *pivote_right = pivote->right;
            Nodo_AVL<T> *new_pivote_right = pivote_right->left;

            // Rotación
            pivote_right->left = pivote;
            pivote->right = new_pivote_right;

            // Actualización de alturas
            pivote->height = max(height(pivote->left), height(pivote->right)) + 1;
            pivote_right->height = max(height(pivote_right->left), height(pivote_right->right)) + 1;

            // Nueva raiz (lo que se encontraba a la derecha del pivote)
            return pivote_right;
        }


				/* Rotación a la izquierda (doble).
				 * @param* pivote: apuntador a nodo que será usado como "pivote".
				 */
        Nodo_AVL<T> *rotacion_doble_izquierda(Nodo_AVL<T> *pivote)
        {
            pivote->right = rotacion_simple_derecha(pivote->right);
            return rotacion_simple_izquierda(pivote);
        }


        /* Regresa un número que indica el
         * factor de balanceo del nodo N.
				 * @param* node: apuntador al nodo a analizar.
         */
        int obtener_factor_balanceo(Nodo_AVL<T> *node)
        {
            if (node == NULL)
                return 0;
            return height(node->right) - height(node->left);
        }


        /* Obtiene el valor del nodo sucesor
				 * factor de balanceo del nodo N.
				 * @param* node: apuntador al nodo a analizar.
				 */
        Nodo_AVL<T>* nodo_sucesor(Nodo_AVL<T>* node)
        {
            Nodo_AVL<T>* current = node->right;

            while (current->left != NULL)
                current = current->left;

            return current;
        }
};
