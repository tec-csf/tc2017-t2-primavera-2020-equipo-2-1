// C++ program to insert a node in AVL tree  
#include <iostream>
using namespace std; 
  
// An AVL tree node  
template <class T>
class Nodo{
	public:
        T value;
        Nodo<T> *right;
        Nodo<T> *left;
        int height; 
        
        Nodo(){
            value=NULL;
            right=NULL;
            left=NULL;
            height=1; 
        }
        
        Nodo(T val){
            value=val;
            right=NULL;
            left=NULL;
            height=1; 
        }

        ~Nodo();
}; 

template <class T>
class AVL{
    public:
        Nodo<T> *raiz = NULL;
        // A utility function to get the  
        // height of the tree  
        int height(Nodo<T> *nodo)  
        {  
            if (nodo == NULL)  
                return 0;  
            return nodo->height;  
        }  
        
        // A utility function to get maximum 
        // of two integers  
        int max(int a, int b)  
        {  
            return (a > b)? a : b;  
        }  
        
        // A utility function to right 
        // rotate subtree rooted with y  
        // See the diagram given above.  
        Nodo<T> *rightRotate(Nodo<T> *y)  
        {  
            Nodo<T> *x = y->left;  
            Nodo<T> *T2 = x->right;  
        
            // Perform rotation  
            x->right = y;  
            y->left = T2;  
        
            // Update heights  
            y->height = max(height(y->left), height(y->right)) + 1;  
            x->height = max(height(x->left), height(x->right)) + 1;  
        
            // Return new root  
            return x;  
        }  
        
        // A utility function to left  
        // rotate subtree rooted with x  
        // See the diagram given above.  
        Nodo<T> *leftRotate(Nodo<T> *x)  
        {  
            Nodo<T> *y = x->right;  
            Nodo<T> *T2 = y->left;  
        
            // Perform rotation  
            y->left = x;  
            x->right = T2;  
        
            // Update heights  
            x->height = max(height(x->left), height(x->right)) + 1;  
            y->height = max(height(y->left), height(y->right)) + 1;  
        
            // Return new root  
            return y;  
        }  
        
        // Get Balance factor of node N  
        int getBalance(Nodo<T> *N)  
        {  
            if (N == NULL)  
                return 0;  
            return height(N->left) - height(N->right);  
        }  
        

        Nodo<T>* insert(int value){
            return insertAux(raiz, value); 
        }
        // Recursive function to insert a value 
        // in the subtree rooted with node and 
        // returns the new root of the subtree.  
        Nodo<T>* insertAux(Nodo<T>* node, int value)  
        {  
            /* 1. Perform the normal BST insertion */
            if (node == NULL){
                Nodo<T>* nodo_insertado = new Nodo<T>(value);
                return(nodo_insertado);  
            }
            if (value < node->value)  
                node->left = insertAux(node->left, value);  
            else if (value > node->value)  
                node->right = insertAux(node->right, value);  
            else // Equal values are not allowed in BST  
                return node;  
        
            /* 2. Update height of this ancestor node */
            node->height = 1 + max(height(node->left), height(node->right));  
        
            /* 3. Get the balance factor of this ancestor  
                node to check whether this node became  
                unbalanced */
            int balance = getBalance(node);  
        
            // If this node becomes unbalanced, then  
            // there are 4 cases  
        
            // Left Left Case  
            if (balance > 1 && value < node->left->value)  
                return rightRotate(node);  
        
            // Right Right Case  
            if (balance < -1 && value > node->right->value)  
                return leftRotate(node);  
        
            // Left Right Case  
            if (balance > 1 && value > node->left->value)  
            {  
                node->left = leftRotate(node->left);  
                return rightRotate(node);  
            }  
        
            // Right Left Case  
            if (balance < -1 && value < node->right->value)  
            {  
                node->right = rightRotate(node->right);  
                return leftRotate(node);  
            }  
        
            /* return the (unchanged) node pointer */
            return node;  
        }  
        
        void preOrder(){
            preOrderAux(raiz);
        }
        // A utility function to print preorder  
        // traversal of the tree.  
        // The function also prints height  
        // of every node  
        void preOrderAux(Nodo<T> *raiz)  
        {  
            if(raiz != NULL)  
            {  
                cout << raiz->value << " . ";  
                preOrderAux(raiz->left);  
                preOrderAux(raiz->right);  
            }  
        }
};  
  
// Driver Code 
int main()  
{  
    AVL<int> arbol;  
      
    /* Constructing tree given in  
    the above figure */
    arbol.insert(10);  
    arbol.insert(20);  
    arbol.insert(30);  
    arbol.insert(40);  
    arbol.insert(50);  
    arbol.insert(25);  

    cout << "Preorder traversal of the "
            "constructed AVL tree is \n";  
    arbol.preOrder();  
      
    return 0;  
} 