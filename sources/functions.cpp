#include <iostream> // cin y cout
#include <cstdlib>  // rand() y srand()
#include <fstream>  // archivos
#include <string>   // substr()
#include <cstdio>   // printf()
#include <ctime>    // time() [para rands] y clock()
#include <stack>
#include <vector>

#include "functions.hpp"
using namespace std;

// Aquí van las funciones de hpp, pero ya con código
//CONSTRUCTORES
Arbol::Arbol()
{
    a = new int;
}

// Class::Class(string new_name, int val);
//   : name(new_name), var(val) {}

// Destructor
Arbol::~Arbol()
{
    delete a;
}


void Arbol::agregar(int valor)
{
    cout << "Agregando " << valor << "\n";
}


void Arbol::eliminar(int valor)
{
    cout << "Eliminando " << valor << "\n";
}


void Arbol::buscar(int valor)
{
    cout << "Buscando " << valor << "\n";
}
