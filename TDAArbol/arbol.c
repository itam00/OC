#include "arbol.h"
#include "C:\Users\Alan\Desktop\UNS\Organizacion de Computadoras\proyecto orga github\OC\TDALista\lista.h"
#include <stdio.h>
#include <stdlib.h>

/**
Inicializa un �rbol vac�o.
Una referencia al �rbol creado es referenciado en *A.
**/
extern void crear_arbol(tArbol * a){
    *a= (struct arbol*)(malloc(sizeof(struct arbol)));
    (*a)->raiz=NULL;
}

/**
Crea la ra�z de A.
Si A no es vac�o, finaliza indicando ARB_OPERACION_INVALIDA.
**/
extern void crear_raiz(tArbol a, tElemento e){
    if ((a->raiz)!=NULL)
        exit(ARB_OPERACION_INVALIDA);
    a->raiz= (struct nodo*)(malloc(sizeof(struct nodo*)));
    tLista* lista= (tLista*)malloc(sizeof(tLista*));
    crear_lista(lista);
    a->raiz->hijos=*lista;
    a->raiz->elemento=e;
    a->raiz->padre=NULL;

}

/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo r�tulo es E.
 Si NH es NULL, el nuevo nodo se agrega como �ltimo hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
extern tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e);

/**
 Elimina el nodo N de A.
 El elemento almacenado en el �rbol es eliminado mediante la funci�n fEliminar parametrizada.
 Si N es la ra�z de A, y tiene un s�lo hijo, este pasa a ser la nueva ra�z del �rbol.
 Si N es la ra�z de A, y a su vez tiene m�s de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la ra�z de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posici�n que ocupa N en la lista de hijos de su padre.
**/
extern void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento));

/**
 Destruye el �rbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el �rbol son eliminados mediante la funci�n fEliminar parametrizada.
**/
extern void a_destruir(tArbol * a, void (*fEliminar)(tElemento));

/**
Recupera y retorna el elemento del nodo N.
*/
extern tElemento a_recuperar(tArbol a, tNodo n){
    /*tElemento toreturn;
    if (n==a->raiz)
        toreturn= a->raiz->elemento;
    else{
        for (int i=0; i<l_longitud(a->raiz->hijos);i++){

        }
    }
    */
    return n->elemento;
}

/**
Recupera y retorna el nodo correspondiente a la ra�z de A.
**/
extern tNodo a_raiz(tArbol a){
    return (tNodo)(a->raiz);
}

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
extern tLista a_hijos(tArbol a, tNodo n){
    tLista* toreturn= (tLista*)(malloc(sizeof(tLista*)));
    crear_lista(toreturn);
    tLista hijos=n->hijos;
    if (l_longitud(hijos)>0){
        tPosicion actual= l_primera(hijos);
        tPosicion aCopiar=l_primera(*toreturn);
        while (actual!=l_fin(hijos)){
            l_insertar(*toreturn,aCopiar,l_recuperar(hijos,actual));
            actual=l_siguiente(hijos,actual);
            aCopiar=l_siguiente(*toreturn,aCopiar);
        }
    }
    return *toreturn;
}

/**
 Inicializa un nuevo �rbol en *SA.
 El nuevo �rbol en *SA se compone de los nodos del sub�rbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/
extern void a_sub_arbol(tArbol a, tNodo n, tArbol * sa);

