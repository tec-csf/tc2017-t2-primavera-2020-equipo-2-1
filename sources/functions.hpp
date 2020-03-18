#include <iostream> // cin y cout
#include <cstdlib>  // rand() y srand()
#include <fstream>  // archivos
#include <string>   // substr()
#include <cstdio>   // printf()
#include <ctime>    // time() [para rands] y clock()
#include <stack>
#include <vector>

using namespace std;

class Arbol
{
    // variables (todo estos son privados)
    int* a;

    // method declaration (definition will be made in cpp)
    public:
        // CONSTRUCTORES
        Arbol();
        // Name(string new_name, int val);

        // Destructor (SOLO UNO)
        ~Arbol();

        /* Agrega nodo con valor establecido en su lugar correcto
        *
        * @param &valor: valor del nodo a agregar.
        */
        void agregar(int valor);


        /* Elimina nodo con valor establecido en su lugar correcto
        *
        * @param &valor: valor del nodo a eliminar.
        */
        void eliminar(int valor);


        /* Buscar nodo con valor establecido en su lugar correcto
        *
        * @param &valor: valor del nodo a buscar.
        */
        void buscar(int valor);

    protected:

    private:

};
