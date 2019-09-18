#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void crear_lista(tLista* l){
    *l = (struct celda*)malloc(sizeof(struct celda));
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}


tPosicion l_primera(tLista l){
    tPosicion p = (tPosicion)l;
    return p;
}

tPosicion l_ultima(tLista l){
    tPosicion ultima = (tPosicion)l->siguiente;
    tPosicion indirecta = (tPosicion)l;
    while(ultima->siguiente!=NULL){
        indirecta = ultima;
        ultima = ultima->siguiente;
    }
    return indirecta;
}

void l_destruir(tLista* l,void (*fEliminar)(tElemento)){
    tPosicion aEliminar=(tPosicion)*l;
    tPosicion siguiente;
    tElemento elem;

    do{
        siguiente = aEliminar->siguiente;
        elem = aEliminar->elemento;
        fEliminar(elem);
        aEliminar->siguiente=NULL;
        free(aEliminar);
        aEliminar = siguiente;

    }while(siguiente!=NULL);
    /*tPosicion primera=(tPosicion)*l;
    tPosicion aEliminar = primera->siguiente;
    tElemento elem;

    while(aEliminar!=NULL){
        elem = aEliminar->elemento;
        fEliminar(elem);
        primera->siguiente = aEliminar->siguiente;
        aEliminar->siguiente = NULL;
        free(aEliminar);
        aEliminar = primera->siguiente;
    }
    primera->siguiente=NULL;
    elem = primera->elemento;
    fEliminar(elem);
    free(primera);*/
}



/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e){
    struct celda* nueva= (struct celda*)(malloc(sizeof(struct celda)));
    nueva->siguiente=p->siguiente;
    nueva->elemento= e;
    p->siguiente=nueva;
}

/**
 Elimina la celda P de L. El elemento almacenado en la posición P es eliminado mediante la función fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){
    if (p->siguiente != NULL){
        (fEliminar(p->siguiente->elemento));
        struct celda* aux;
        aux=p->siguiente;
        p->siguiente=p->siguiente->siguiente;
        aux->siguiente=NULL;
        free(aux);
    }
}

/**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p){
    if (p->siguiente != NULL){
        return p->siguiente->elemento;
    }
    else
        exit(1);
}

/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p){
    if (p->siguiente != NULL){
        return p->siguiente;
    }
    else
        exit(2);
}

/**
 Recupera y retorna la posición anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
tPosicion l_anterior(tLista l, tPosicion p){
    if (p!=l){
        tPosicion pos= l;
        while( pos->siguiente != p){
            pos=pos->siguiente;
        }
        return pos;
    }
    else
        exit(4);
}

 /**
 Recupera y retorna la posición fin de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_fin(tLista l){
    tPosicion pos= l;
    while (pos->siguiente != NULL)
        pos=pos->siguiente;
    return pos;
}

/**
 Retorna la longitud actual de la lista.
**/
int l_longitud(tLista l){
     tPosicion pos=l;
     int contador=0;
     while (pos->siguiente != NULL){
        contador++;
        pos=pos->siguiente;
     }
     return contador;
}


