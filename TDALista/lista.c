#include "lista.h"
#include <stdio.h>
#include <stdlib.h>


/**
 Inicializa una lista vacía.
 Una referencia a la lista creada es referenciada en *L.
**/

void crear_lista(tLista* l){
    *l = (struct celda*)malloc(sizeof(struct celda));
    if((*l)==NULL){
        exit(LST_ERROR_MEMORIA);
    }
    (*l)->elemento = NULL;
    (*l)->siguiente = NULL;
}

/**
 Recupera y retorna la primera posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_primera(tLista l){

    tPosicion p = (tPosicion)l;
    return p;
}

 /**
 Recupera y retorna la última posición de L.
 Si L es vacía, primera(L) = ultima(L) = fin(L).
**/
tPosicion l_ultima(tLista l){
    tPosicion ultima = (tPosicion)l->siguiente;
    tPosicion indirecta = (tPosicion)l;
    while(ultima->siguiente!=NULL){
        indirecta = ultima;
        ultima = ultima->siguiente;
    }
    return indirecta;
}

/**
 Destruye la lista L, elimininando cada una de sus celdas. Los elementos almacenados en las celdas son eliminados mediante la función fEliminar parametrizada.
**/

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
    *l = NULL;

}



/**
 Inserta el elemento E, en la posición P, en L.
 Con L = A,B,C,D y la posición P direccionando C, luego:
 L' = A,B,E,C,D
**/
void l_insertar(tLista l, tPosicion p, tElemento e){

    if(p==NULL){
        exit(LST_POSICION_INVALIDA);
    }
    tPosicion nueva= (struct celda*)(malloc(sizeof(struct celda)));
    if(nueva==NULL){
        exit(LST_ERROR_MEMORIA);
    }
    nueva->siguiente=p->siguiente;
    nueva->elemento= e;
    p->siguiente=nueva;
}

/**
 Elimina la celda P de L. El elemento almacenado en la posición P es eliminado mediante la función fEliminar parametrizada.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento)){
    if (p== NULL || p->siguiente == NULL){
        exit(LST_POSICION_INVALIDA);
    }
    fEliminar(p->siguiente->elemento);
    struct celda* aux;
    aux=p->siguiente;
    p->siguiente=p->siguiente->siguiente;
    aux->siguiente=NULL;
    free(aux);


}

/**
 Recupera y retorna el elemento en la posición P.
 Si P es fin(L), finaliza indicando LST_POSICION_INVALIDA.
**/
tElemento l_recuperar(tLista l, tPosicion p){

    if(p==NULL){
        exit(LST_POSICION_INVALIDA);
    }
    if (p->siguiente == NULL){
        exit(LST_ELEMENTO_NULO);
    }
    return p->siguiente->elemento;
}

/**
 Recupera y retorna la posición siguiente a P en L.
 Si P es fin(L), finaliza indicando LST_NO_EXISTE_SIGUIENTE.
**/
tPosicion l_siguiente(tLista l, tPosicion p){
    if(p==NULL){
        exit(LST_POSICION_INVALIDA);
    }
    if (p->siguiente == NULL){
        exit(LST_NO_EXISTE_SIGUIENTE);
    }
    return p->siguiente;

}

/**
 Recupera y retorna la posición anterior a P en L.
 Si P es primera(L), finaliza indicando LST_NO_EXISTE_ANTERIOR.
**/
tPosicion l_anterior(tLista l, tPosicion p){
    if(p==NULL){
        exit(LST_POSICION_INVALIDA);
    }
    if (p==l){
        exit(LST_NO_EXISTE_ANTERIOR);
    }
    tPosicion pos= l;
    while( pos!=NULL && pos->siguiente != p){
        pos=pos->siguiente;
    }

    if(pos->siguiente==NULL){
        exit(LST_POSICION_INVALIDA);
    }
    return pos;


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
