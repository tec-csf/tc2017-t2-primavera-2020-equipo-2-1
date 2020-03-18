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


int main()
{
    cout << "\n\n\n\n\t\t-----INICIO PROGRAMA-----\n\n\n\n\n";

    int choice;

    cout << "Árboles" << '\n';
    cout << "¿Qué tipo de árbol quieres?" << '\n';
    cout << "\t 1. AVL (Memoria Interna)" << '\n';
    cout << "\t 2. B (Memoria Externa)" << '\n';
    cout << "\n Tu opción [1-2]: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
        char option;

        case 1:
        {
        Arbol* avl = new Arbol;

        cout << "Árboles AVL" << '\n';
        cout << "Se ha generado un arbol con tamaño 10 aleatoriamente." << '\n';
        cout << "¿Qué quieres hacer con tu árbol?" << '\n';
        cout << "\t a. Agregar nodo" << '\n';
        cout << "\t b. Eliminar nodo" << '\n';
        cout << "\t c. Buscar nodo" << '\n';
        cout << "\n Tu opción [a-c]: ";
        cin >> option;
        cout << endl;

        switch (option)
        {
            case 'a':
            avl->agregar(4);
            break;

            case 'b':
            avl->eliminar(4);
            break;

            case 'c':
            avl->buscar(4);
            break;
        }
        avl->~Arbol(); // PARA QUE NO HAYA FUGAS!!
        break;
        }
        case 2:
        {
        Arbol* b = new Arbol;

        cout << "\nÁrboles B" << '\n';
        cout << "Se ha generado un arbol con tamaño 10 aleatoriamente." << '\n';
        cout << "¿Qué quieres hacer con tu árbol?" << '\n';
        cout << "\t a. Agregar nodo" << '\n';
        cout << "\t b. Eliminar nodo" << '\n';
        cout << "\t c. Buscar nodo" << '\n';
        cout << "\nTu opción [a-c]: ";
        cin >> option;
        cout << endl;

        switch (option)
        {
            case 'a':
            b->agregar(4);
            break;

            case 'b':
            b->eliminar(4);
            break;

            case 'c':
            b->buscar(4);
            break;
        }
        b->~Arbol();
        break;
      }
    }
    cout << "\n\n\t\t-----FIN PROGRAMA-----\n\n";
}
