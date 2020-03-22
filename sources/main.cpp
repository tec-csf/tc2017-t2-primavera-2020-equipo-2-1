#include <iostream>
#include <chrono>
#include <cstdio>
#include <string>
#include "avl.cpp"
#include "BTree.cpp"

using namespace std;
using namespace std::chrono;

void insertar_n_elementos(AVL<int> *avl, BTree<int> *b, int* array, int num){
    auto inicio=high_resolution_clock::now();
    for (int i=0; i<num; ++i)
        avl->insertar(array[i]);
    auto fin=high_resolution_clock::now();
    auto duracion_avl=fin-inicio;
    int d_avl =duration_cast<milliseconds>(duracion_avl).count();

    inicio=high_resolution_clock::now();
    for (int i=0; i<num; ++i)
        b->insertar(array[i]);
    fin=high_resolution_clock::now();
    auto duracion_b=fin-inicio;
    int d_b =duration_cast<milliseconds>(duracion_b).count();

    printf(" |  %-14s | %-4d miliseg %14s| \n", "AVL", d_avl, " ");
    printf(" %s\n", "|-----------------------------------------------|");
    printf(" |  %-14s | %-4d miliseg %14s| \n", "B", d_b, " ");
    printf(" %s\n", "|-----------------------------------------------|");
}

void buscar_elementos(AVL<int> *avl, BTree<int> *b, int value){
    auto inicio=high_resolution_clock::now();
    avl->buscar(value);
    auto fin=high_resolution_clock::now();
    auto duracion_avl=fin-inicio;
    string busqueda_avl = ((avl->buscar(value) != value)? "NO ENCONTRADO" : "ENCONTRADO");

    inicio=high_resolution_clock::now();
    b->buscar(value);
    fin=high_resolution_clock::now();
    auto duracion_b=fin-inicio;
    string busqueda_b = ((b->buscar(value) != value)? "NO ENCONTRADO" : "ENCONTRADO");

    int d_avl = duration_cast<microseconds>(duracion_avl).count();
    int d_b = duration_cast<microseconds>(duracion_b).count();

    printf(" |  %-14d | ", value);
    printf("%-15s", busqueda_avl.c_str());
    // cout<<busqueda_avl;
    printf(" | %-2d microseg %-6s | ", d_avl, " ");
    // cout<<busqueda_b;
    printf("%-15s", busqueda_b.c_str());

    printf(" | %-3d microseg %-5s | \n", d_b, " ");
    printf(" %s\n", "|-----------------------------------------------------------------------------------------------|");
}

void eliminar_elementos(AVL<int> *avl, BTree<int> *b, int value){
    auto inicio=high_resolution_clock::now();
    avl->eliminar(value);
    auto fin=high_resolution_clock::now();
    auto duracion_avl=fin-inicio;

    inicio=high_resolution_clock::now();
    b->eliminar(value);
    fin=high_resolution_clock::now();
    auto duracion_b=fin-inicio;

    int d_avl = duration_cast<microseconds>(duracion_avl).count();
    int d_b = duration_cast<microseconds>(duracion_b).count();

    printf(" |  %-14d | %-3d microseg %-7s | %-4d microseg %-7s | \n", value, d_avl, " ", d_b, " ");
    printf(" %s\n", "|----------------------------------------------------------------|");
}

int main(){
    cout<<"\n\n\n\t\t-----INICIO PROGRAMA-----\n\n\n";

    int numero_elementos, grado_B, rango;
    int elementos_prueba[10];
    cout<<" Ingrese la cantidad de elementos a ingresar a los arboles: ";
    cin>>numero_elementos;
    cout<<endl;

    int elementos_aleatorios[numero_elementos];
    grado_B = numero_elementos/100000+5; // Variar el grado del arbol B en medida que crece su contenido
    grado_B = (grado_B > 20? 20 : grado_B);
    rango = numero_elementos*3; // Para evitar mucho elementos repetidos (los cuales no se incluyen en un AVL)

    AVL<int> avl;
    BTree<int> b(grado_B);

    for (int i=0; i<numero_elementos; ++i)
    {
        elementos_aleatorios[i] = (rand()%rango)+1;
    }

    printf(" %s\n", "_________________________________________________");
    printf(" |%15s %-6d %-23s | \n", "INSERTAR", numero_elementos, "ELEMENTOS");
    printf(" %s\n", "|-----------------------------------------------|");
    insertar_n_elementos(&avl, &b, elementos_aleatorios, numero_elementos);
    cout<<endl;

    cout<<endl<<" Los siguientes 10 elementos seran buscados y posteriormente eliminados de cada arbol: "<<endl;
    cout<<'\t';
    for (int i=0; i<10; ++i){
        elementos_prueba[i] = (rand()%rango)+1;
        cout<<elementos_prueba[i]<<" ";
    }
    cout<<endl;

    printf("%s\n", " _________________________________________________________________________________________________");
    printf(" |%47s %-47s| \n", "BUSCAR", " ");
    printf(" %s\n", "|-----------------------------------------------------------------------------------------------|");
    printf(" |  %-14s | %-36s | %-36s | \n", "Valor", "AVL", "Arbol B");
    printf(" %s\n", "|-----------------------------------------------------------------------------------------------|");
    printf(" |%-16s | %-15s | %-18s | %-15s | %-18s | \n", "", "Estado", "Tiempo", "Estado", "Tiempo");
    printf(" %s\n", "|-----------------------------------------------------------------------------------------------|");
    for (int i=0; i<10; ++i){
        buscar_elementos(&avl, &b, elementos_prueba[i]);
    }

    cout<<endl;

    printf("%s\n", " __________________________________________________________________");
    printf(" |%33s %-29s | \n", "ELIMINAR", " ");
    printf(" %s\n", "|----------------------------------------------------------------|");
    printf(" |  %-14s | %-20s | %-21s | \n", "Valor", "AVL", "Arbol B" );
    printf(" %s\n", "|----------------------------------------------------------------|");
    printf(" |  %-14s | %-20s | %-21s | \n", "", "Tiempo", "Tiempo" );
    printf(" %s\n", "|----------------------------------------------------------------|");
    for (int i=0; i<10; ++i){
        eliminar_elementos(&avl, &b, elementos_prueba[i]);
    }

    cout<<endl;

    cout<<"\n\n\t\t-----PROGRAMA FINALIZADO-----\n\n";

    return 0;
}
