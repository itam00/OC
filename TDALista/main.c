#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void insertarEntero(tLista l, tPosicion p,int x);
void imprimirAscendente(tLista lista);
void imprimirDescendente(tLista lista);
void fEliminar(tElemento elem);

int main()
{
    tLista lista;
    crear_lista(&lista);

    //probando insercion de elementos
    tPosicion p = l_primera(lista);
    for(int i=0;i<10;i++){
        insertarEntero(lista,p,i);
        p = l_siguiente(lista,p);
    }

    int x= l_longitud(lista);
    printf("Longitud de la lista: %d\n",x);
    printf("Lista en orden ascendente: ");
    imprimirAscendente(lista);
    printf("\nLista en orden descendente: ");
    imprimirDescendente(lista);


    //probando eliminacion de elementos
    /*p = l_primera(lista);
    tPosicion aux;
    for(int i=0;i<5;i++){
        p = l_primera(lista);
        l_eliminar(lista,p,fEliminar);
    }

    x= l_longitud(lista);
    printf("Longitud de la lista: %d\n",x);
    printf("\nEliminando 5 elementos: \n");
    imprimirAscendente(lista);*/


    //destruccion de la lista


    l_destruir(&lista,fEliminar);
    printf("\n");
    //si se intenta acceder a la lista explota todo
    //imprimirAscendente(lista);
    printf("lista eliminada");


}



void imprimirAscendente(tLista lista){

    tPosicion p = l_primera(lista);
    for(int i=0;i<10;i++){
        int* x = (int*) l_recuperar(lista,p);
        p = l_siguiente(lista,p);
        printf("%d - ",*x);
    }
}
void imprimirDescendente(tLista lista){

    tPosicion p = l_ultima(lista);
    for(int i=0;i<10;i++){
        int* x = (int*) l_recuperar(lista,p);
        printf("%d - ",*x);
        if(p!=l_primera(lista))
            p = l_anterior(lista,p);
    }
}

void insertarEntero(tLista l,tPosicion p, int x){
    int* e = (int*) malloc(sizeof(int));
    *e= x;
    tElemento elem = e;
    l_insertar(l,p,elem);
}

void fEliminar(tElemento elem){
    free(elem);
}
