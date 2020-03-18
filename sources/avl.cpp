#include <iostream> // cin y cout
#include <cstdlib>  // rand() y srand()
#include <fstream>  // archivos
#include <string>   // suAVLr()
#include <cstdio>   // printf()
#include <ctime>    // time() [para rands] y clock()
#include <stack>
#include <vector>

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
        Nodo<T> *raiz;
        
        AVL(){
            raiz=NULL;
        }

        ~AVL(); 

        int altura(Nodo<T> *N)  
        {  
            if (N == NULL)  
                return 0;  
            return N->height;  
        }  

        int mayor(int a, int b)  
        {  
            return (a > b)? a : b;  
        } 

        int factor_balanceo(Nodo<T> *N)  
        {  
            if (N == NULL)  
                return 0;  
            return altura(N->right) - altura(N->left);  
        }  

        void rotacion_simple_izquierda(Nodo<T> *pivote){
            Node *pivote_right = pivote->right;  
            Node *new_pivote_right = pivote_right->left;  
        
            // Perform rotation  
            pivote_right->left = pivote;  
            pivote->right = new_pivote_right;  
        
            // Update heights  
            pivote->height = max(altura(pivote->left), altura(pivote->right)) + 1;  
            pivote_right->height = max(altura(pivote_right->left), altura(pivote_right->right)) + 1;  
        }

        void insertar(T value){
            Nodo<T> *nuevo=new Nodo<T>(value);
            Nodo<T> *nodo_pivote; 

            if(raiz==NULL){
                raiz=nuevo;
            }else{
                Nodo<T> *temp=raiz;
                while(temp!=NULL){
                    if(factor_balanceo(temp) != 0){
                        nodo_pivote=temp; 
                    }
                    if(temp->value==value){
                        return;
                    }
                    else if(value<temp->value){
                        if(temp->left==NULL){
                            temp->left=nuevo;
                            return;
                        }else{
                            temp=temp->left;
                        }
                    }
                    else if(value>temp->value){
                        if(temp->right==NULL){
                            temp->right=nuevo;
                            return;
                        }else{
                            temp=temp->right;
                        }
                    }
                }
            }


        }
        

        /*
        void inorden(){
                inordenAux(raiz);
                cout<<endl;
        }
        
        void inordenAux(Nodo<T> *actual){
            if(actual==NULL){
                return;
            }
            inordenAux(actual->left);
            cout<<actual->value<<", ";
            inordenAux(actual->right);
        }

        void preorden(){
            preordenAux(raiz);
            cout<<endl; 
        }

        void preordenAux(Nodo<T> *actual){
            if(actual==NULL){
                return; 
            }
            cout<<actual->value<<", ";
            preordenAux(actual->left);
            preordenAux(actual->right);
        }

        void postorden(){
            postordenAux(raiz);
            cout<<endl; 
        }

        void postordenAux(Nodo<T> *actual){
            if(actual==NULL){
                return; 
            }
            postordenAux(actual->left);
            postordenAux(actual->right);
            cout<<actual->value<<", ";
        }*/
};

int main(){
	AVL<int> b;
}