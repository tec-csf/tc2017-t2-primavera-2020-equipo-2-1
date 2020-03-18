// EJEMPLO QUE OBTIENE EL TIEMPO EN HACER OPERACIONES DE PUNTO 'A' A 'B'
#include <iostream> // cin y cout
#include <cstdlib>  // rand() y srand()
#include <ctime>    // clock() y time() [para rands]

using namespace std;

int main ()
{
    cout << "\n\n\n\n\t\t-----INICIO PROGRAMA-----\n\n\n\n\n";

    float x,y;
  	clock_t time_req;

  	time_req = clock(); // Aqui se guarda el tiempo en ese momento

    srand((int)time(0));
  	int i = 0;

    while(i++ < 10000)
    {
  		  int r = (rand() % 1000) + 1; // (0 - 999) + 1 == (1 - 1000)
  		  // cout << r << " ";
  	}

    time_req = clock() - time_req; // Aqui se guarda el tiempo en ese momento

    cout << "Generar 10,000 numeros aleatorios tomó: ";
    cout << (float)time_req/CLOCKS_PER_SEC << " segundos.\n" << endl;
    cout << "\n\n\t\t-----FIN PROGRAMA-----\n\n";
    return 0;
}
