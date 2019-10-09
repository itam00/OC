#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"



int main()
{
    int a=1,b=2,c=3,x;
    int* pa,pb,pc;
    tNodo aux;
    pa = &a;
    pb = &b;
    pc = &c;
    tArbol arbol;
    crear_arbol(&arbol);
    crear_raiz(arbol,pa);
    int* elem = (int*)a_recuperar(arbol,a_raiz(arbol));
    printf("el nodo raiz es: %d",*elem);

return(0);

}


