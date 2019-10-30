#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void eliminarQuitarLista(tElemento nodo);
void destruirAux( void (*fEliminar)(tElemento),tNodo nodo);
void aux_sub_arbol();
/**
Inicializa un árbol vacío.
Una referencia al árbol creado es referenciado en *A.
**/
 void crear_arbol(tArbol * a){
    *a= (struct arbol*)(malloc(sizeof(struct arbol)));
    (*a)->raiz=NULL;
}

/**
Crea la raíz de A.
Si A no es vacío, finaliza indicando ARB_OPERACION_INVALIDA.
**/
void crear_raiz(tArbol a, tElemento e){
    if ((a->raiz)!=NULL)
        exit(ARB_OPERACION_INVALIDA);
    a->raiz= (struct nodo*)malloc(sizeof(struct nodo));
    tLista lista;
    crear_lista(&lista);
    a->raiz->hijos=lista;
    a->raiz->elemento=e;
    a->raiz->padre=NULL;
}
/**
Recupera y retorna el elemento del nodo N.
*/
tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento;
}

/**
Recupera y retorna el nodo correspondiente a la raíz de A.
**/
tNodo a_raiz(tArbol a){
    return (tNodo)(a->raiz);
}

/**
 Obtiene y retorna una lista con los nodos hijos de N en A.
**/
tLista a_hijos(tArbol a, tNodo n){
    return n->hijos;
}
/**
 Inserta y retorna un nuevo nodo en A.
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo rótulo es E.
 Si NH es NULL, el nuevo nodo se agrega como último hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    tLista hermanos = np->hijos;
    tLista nueva;
    tPosicion aux;
    tNodo nuevo;

    if(nh == NULL)
    {
        aux = l_fin(hermanos);
        nuevo = (struct nodo*)malloc(sizeof(struct nodo));
        l_insertar(hermanos,aux, nuevo);

    }
    else{
        aux = l_primera(hermanos);
        int cant = l_longitud(hermanos), encontrado;
        encontrado = l_recuperar(hermanos,aux)==nh;
        for(int i=0;i<cant && !encontrado;i++){
            aux = aux->siguiente;
            encontrado = l_recuperar(hermanos,aux)==nh;
        }
        if(!encontrado){
            exit(ARB_OPERACION_INVALIDA);
        }
        nuevo = (tNodo) malloc(sizeof(struct nodo));
        l_insertar(hermanos,aux,nuevo);
    }

    crear_lista(&nueva);
    nuevo->hijos = nueva;
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
            l_eliminar(hijos,l_primera(hijos),&eliminarQuitarLista);
            aux->padre = NULL;
            a->raiz = aux;

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

        //se busca la posicion del nodo en la lista de su padre para poder agregar los hijos del nodo a eliminar
        encontrado = l_recuperar(hermanos,posNodo) == n;

        while(posNodo!=l_fin(hermanos) && !encontrado){
            posNodo = l_siguiente(hermanos,posNodo);
            encontrado = l_recuperar(hermanos,posNodo) == n;
        }

        //se cambian los hijos del nodo a la lista de su padre
        posHijo = l_primera(hijos);
        while(posHijo!=l_fin(hijos)){
            aux = l_recuperar(hijos,posHijo);
            aux->padre = n->padre;  //se cambia de padre
            l_insertar(hermanos,posNodo,aux); // se agrega a la lista del padre d n
            posHijo = l_siguiente(hijos,posHijo);
            posNodo = l_siguiente(hermanos,posNodo);
        }

        //Se elimina completamente el nodo que debe ser eliminado
        l_eliminar(hermanos,posNodo,eliminarQuitarLista); //se elimina de la lista de sus hermanos
        l_destruir(&hijos,eliminarQuitarLista); //se elimina la lista de hijos
        n->padre = NULL;
        fEliminar(n->elemento);
    }

}

/**
Funcion auxiliar usaba para poder quitar los nodos de la listas sin eliminarlos, para poder seguir
usandolos.
**/

void eliminarQuitarLista(tElemento nodo){
}

/**
 Destruye el árbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el árbol son eliminados mediante la función fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
    tNodo raiz = (*a)->raiz;
    destruirAux(eliminarQuitarLista,raiz);
    free(*a);
    *a = NULL;
}

/**
Funcion auxiliar usada para destruir la lista de manera recursiva.
**/
void destruirAux(void (*fEliminar)(tElemento),tNodo nodo){
    tLista hijos = nodo->hijos;
    tPosicion hijo = l_primera(hijos);
    if(hijo!=l_fin(hijos)){
        while(hijo!=l_fin(hijos)){
            destruirAux(*fEliminar,l_recuperar(hijos,hijo));
            hijo = l_siguiente(hijos,hijo);
        }
    }
    else{
        nodo->padre = NULL;
        l_destruir(&hijos,eliminarQuitarLista);    //no deberia tener ningun hijo
        fEliminar(nodo->elemento);
        free(nodo);
    }
}

/**
 Inicializa un nuevo árbol en *SA.
 El nuevo árbol en *SA se compone de los nodos del subárbol de A a partir de N.
 El subarbol de A a partir de N debe ser eliminado de A.
**/

void a_sub_arbol(tArbol a, tNodo n, tArbol * sa){
    crear_arbol(sa);
    (*sa)->raiz=n;
    if (n==a->raiz){
        a->raiz=NULL;
        (*sa)->raiz=n;
    }
    else{
        tNodo padre= n->padre;
        tPosicion actual= l_primera(padre->hijos);
        int encontre=0;
        while (actual != l_fin(padre->hijos) && !encontre){
            if ( (tNodo)l_recuperar(padre->hijos,actual) == n)
                encontre=1;
            else
                actual=l_siguiente(padre->hijos,actual);
        }
        l_eliminar(padre->hijos,actual,&aux_sub_arbol);
        n->padre=NULL;
    }
}


/**funcion auxiliar para poder quitar los nodos de la lista de hijos de un nodo
en el arbol sin eliminarlos.
**/
void aux_sub_arbol(){
}

