#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;
struct nodo{
    int clave;
    int numero;
}reg;
int main(){
    FILE *f;
    int n;
    f=fopen("test.txt","w+b");
    n=getc(stdin);
    putc(n,f);

}