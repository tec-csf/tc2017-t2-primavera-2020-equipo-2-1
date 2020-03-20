#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;
class arbolB{
public:
    int cont=0;
    struct nodo{
        char clave[5];
        int apuntador;
    }reg;
    FILE *file;
    void crearFile(char* name){
        file = fopen(name, "r+b");          // Este modo permite leer y escribir
         if(!file) {
            file = fopen(name, "w+b");
        }
    }
    void leerFile(){
        rewind(file);
        string s="34";
        while(fread(&reg, sizeof(struct nodo), 1, file)){
        cout<<reg.clave<<"\t";
        }
        cout<<endl;
        long nBytes = ftell(file); // Tamaño en bytes
        long nRegistros = ftell(file)/sizeof(struct nodo); // Tamaño en registros
    }
    void insertar(){
    long nRegistros = ftell(file)/sizeof(struct nodo);
    cout<<nRegistros<<endl;
    fgets(reg.clave,5,stdin);
    for(int i = strlen(reg.clave)-1; i && reg.clave[i] < ' '; i--){
      reg.clave[i] = 0;
    }
    while(!feof(file)){
    cout<<(reg.clave)<<endl;
    if (reg.clave=="23"){
    cout<<"hola"<<endl;
    }
    }
    fseek(file, 0, SEEK_END);
    fwrite(&reg, sizeof(struct nodo), 1, file);
    
        
    }

    
};
   struct nodo
    {
        char clave[5];
        int apuntador;
    };


int main(){
    /*arbolB a;
    struct nodo reg;
    FILE *file;
   file = fopen("t.dat", "r+b");          // Este modo permite leer y escribir
   if(!file) {
    file = fopen("t.dat", "w+b");
    } // si el fichero no existe, lo crea.
    fgets(reg.clave,10,stdin);
   for(int i = strlen(reg.clave)-1; i && reg.clave[i] < ' '; i--)
      reg.clave[i] = 0;
    reg.apuntador=0;
    fseek(file, 0, SEEK_END);
    fwrite(&reg, sizeof(struct nodo), 1, file);
    rewind(file);
    cout<<endl; 
    while(fread(&reg, sizeof(struct nodo), 1, file)){
        if(atoi(reg.clave)>atoi(fgets(reg.clave,10,stdin))){
            string path;
            char str[12];
            sprintf(str, "%d", 0);
            path=str;
            file = fopen(str, "r+b");          // Este modo permite leer y escribir
             if(!file) {
             file = fopen(str, "w+b");
             }
             fwrite(&reg, sizeof(struct nodo), 1, file);
        }
        cout<<reg.clave<<"\t";
    }
    fclose(file);
    cout<<endl;*/
    arbolB a;
    a.crearFile("nombre");
    a.insertar();
    a.leerFile();
    return 0;

}