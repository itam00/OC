#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include "C:\Users\Alan\Desktop\UNS\Organizacion de Computadoras\proyecto orga github\OC\TDALista\lista.h"


#define ARB_OPERACION_INVALIDA      10
#define ARB_POSICION_INVALIDA       11
#define ARB_ERROR_MEMORIA           12

struct nodo{
    tElemento elemento;
    struct nodo * padre;
    tLista hijos;
};

struct arbol{
    struct nodo * raiz;
};

typedef struct nodo * tNodo;
typedef struct arbol * tArbol;


/**
Inicializa un ?bol vac?.
Una referencia al ?bol creado es referenciado en *A.
**/
extern void crear_arbol(tArbol * a);

/**
Crea la ra? de A.
Si A no es vac?, finaliza indicando ARB_OPERACION_INVALIDA.
**/
extern void crear_raiz(tArbol a, tElemento e);

/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo r?ulo es E.
 Si NH es NULL, el nuevo nodo se agrega como ?ltimo hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
extern tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e);

/**
 Elimina el nodo N de A.
 El elemento almacenado en el ?bol es eliminado mediante la funci? fEliminar parametrizada.
 Si N es la ra? de A, y tiene un s?o hijo, este pasa a ser la nueva ra? del ?bol.
 Si N es la ra? de A, y a su vez tiene m? de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la ra? de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posici? que ocupa N en la lista de hijos de su padre.
**/
extern void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento));

/**
 Destruye el ?bol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el ?bol son eliminados mediante la funci? fEliminar parametrizada.
**/
extern void a_destruir(tArbol * a, void (*fEliminar)(tElemento));

/**
Recupera y retorna el elemento del nodo N.
*/
extern tElemento a_recuperar(tArbol a, tNodo n);

/**
Recupera y retorna el nodo correspondiente a la ra? de A.
**/
extern tNodo a_raiz(tArbol a);

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
extern tLista a_hijos(tArbol a, tNodo n);



#endif // ARBOL_H_INCLUDED
