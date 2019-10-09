#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
void insertarEntero(tLista l, tPosicion p,int x);
void imprimirAscendente(tLista lista);
void imprimirDescendente(tLista lista);
void fEliminar(tElemento elem);

int* copiarEntero(int* e);
tLista copiarLista(tLista lista, tElemento (*copiar)(tElemento));


void iniciarTester(){
//creando a la lista
    tLista lista;
    crear_lista(&lista);
    int a = l_longitud(lista);
    printf("tamaño de la lista: %i",a);

    //probando insercion de elementos
    printf("\ninsertando 10 elementos: \n");
    tPosicion p = l_primera(lista);
    for(int i=0;i<10;i++){
        insertarEntero(lista,p,i);
        p = l_siguiente(lista,p);
    }
    printf("Lista en orden ascendente: ");
    imprimirAscendente(lista);
    printf("\ncopiando lista...: \n\n");

    tLista nueva = copiarLista(lista,&copiarEntero);

    printf("Nueva lista en orden ascendente: ");
    imprimirAscendente(nueva);


    /*


    printf("Lista en orden ascendente: ");
    imprimirAscendente(lista);
    int x= l_longitud(lista);
    printf("\nLongitud de la lista: %d\n",x);
    printf("\nLista en orden descendente: ");
    imprimirDescendente(lista);


    //probando eliminacion de elementos
    printf("\nEliminando 5 elementos: \n");
    p = l_primera(lista);
    for(int i=0;i<10;i++){
        p = l_primera(lista);
        l_eliminar(lista,p,fEliminar);
    }

    x= l_longitud(lista);
    printf("\nLongitud de la lista: %d\n",x);
    printf("\nelementos de la lista en orden ascendente: ");
    imprimirAscendente(lista);

    //volviendo a completar la lista

    printf("\nVolviendo a completar la lista\n");
    for(int i=4;i>=0;i--){
        p= l_primera(lista);
        insertarEntero(lista,p,i);
    }
    printf("lista completa: ");
    imprimirAscendente(lista);
    printf("\n");

    //eliminando un elemento en el medio

    printf("Eliminando un elemento en medio de la lista");
    p=l_siguiente(lista,p);

    l_eliminar(lista,p,fEliminar);

    printf("\n");


    imprimirAscendente(lista);

    //destruccion de la lista


    l_destruir(&lista,fEliminar);
    printf("\n");
    //si se intenta acceder a la lista explota todo
    //imprimirAscendente(lista);
    printf("lista eliminada");
    //l_primera(lista);


    */}

void imprimirAscendente(tLista lista){

    tPosicion p = l_primera(lista);
    int longitud = l_longitud(lista);
    while(p!=l_fin(lista)){
        int* x = (int*) l_recuperar(lista,p);
        p = l_siguiente(lista,p);
        printf("%d - ",*x);
    }

}
void imprimirDescendente(tLista lista){

    tPosicion p = l_ultima(lista);
    int longitud = l_longitud(lista);

    for(int i=0;i<longitud;i++){
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

tLista copiarLista(tLista lista,tElemento(*copiar)(tElemento elem)){
    tLista nueva;
    crear_lista(&nueva);
    tPosicion aux;
    tElemento original,copia;

    aux = l_primera(lista);
    while(aux!=l_fin(lista)){
        original = l_recuperar(lista,aux);
        copia = copiar(original);
        l_insertar(nueva,l_fin(nueva),copia);
        aux = l_siguiente(lista,aux);
    }
    return nueva;
}

int* copiarEntero(int* e){
    int* nuevo = (int*)malloc(sizeof(int));
    *nuevo = *e;
    return nuevo;
}
