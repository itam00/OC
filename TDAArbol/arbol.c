#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"

/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo rótulo es E.
 Si NH es NULL, el nuevo nodo se agrega como último hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    tLista hermanos = np->hijos;
    tPosicion aux;
    tNodo nuevo;
    if(nh == NULL)
    {
        aux = l_ultima(hermanos);
        nuevo = (struct nodo*)malloc(sizeof(struct nodo));
        l_insertar(hermanos,aux, nuevo);
    }
    else{
        aux = l_primera(hermanos);
        int cant = l_longitud(hermanos), encontrado = 0;
        for(int i=0;i<cant && !encontrado;i++){
            aux = aux->siguiente;
            encontrado = l_recuperar(hermanos,aux)!=nh;
        }
        if(!encontrado){
            exit(ARB_OPERACION_INVALIDA);
        }
        nuevo = (tNodo) malloc(sizeof(struct nodo));
        l_insertar(hermanos,aux,nuevo);
    }
    nuevo->elemento = e;
    nuevo->padre = np;
    return nuevo;
}

/**
 Elimina el nodo N de A.
 El elemento almacenado en el árbol es eliminado mediante la función fEliminar parametrizada.
 Si N es la raíz de A, y tiene un sólo hijo, este pasa a ser la nueva raíz del árbol.
 Si N es la raíz de A, y a su vez tiene más de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la raíz de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posición que ocupa N en la lista de hijos de su padre.
**/
void a_eliminar(tArbol a, tNodo n, void (*fEliminar)(tElemento)){
    tNodo padre = n->padre,aux;
    tLista hijos = n->hijos;
    int cantHijos = l_longitud(hijos);
    if(padre == NULL){
        if(cantHijos==1){
            aux = l_recuperar(hijos,l_primera(hijos));
            aux->padre = NULL;
            a->raiz = aux;//COMO QUITO LOS NODOS DE LA LISTA SIN ELIMINARLOS??
            fEliminar(n->elemento);
            free(n);
        }
        else{
            exit(ARB_OPERACION_INVALIDA);
        }
    }
    else{
        tLista hermanos = padre->hijos;
        tPosicion posNodo= l_primera(hermanos),posHijo;
        int cantHermanos = l_longitud(hermanos),encontrado = 0;

        encontrado = l_recuperar(hermanos,posNodo) == n;
        for(int i=0;i<cantHermanos&& !encontrado;i++){
            posNodo = l_siguiente(hermanos,posNodo);
            encontrado = l_recuperar(hermanos,posNodo) == n;
        }

        posHijo = l_primera(hijos);
        for(int i=0;i<cantHijos;i++){
            l_insertar(hermanos,posNodo,l_recuperar(hijos,posHijo));
            posHijo = l_siguiente(hijos,posHijo);
        }

        l_eliminar(hermanos,posNodo,fEliminar);


    }

}

void fEliminar(tElemento t){
}
/**
Recupera y retorna el elemento del nodo N.
*/
tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento;
}
/*int pertenece(tArbol a,tNodo n){
    while(n->padre!=NULL){
        n = n->padre;
    }
    if(n == a_raiz())
        return 0;
    else
        return 1;
}*/
