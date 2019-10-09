#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"
#include "lista.h"

void eliminarQuitarLista(tElemento nodo);
void destruirAux(tArbol a, void (*fEliminar)(tElemento),tNodo nodo);
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
Recupera y retorna el elemento del nodo N.
*/
tElemento a_recuperar(tArbol a, tNodo n){
    return n->elemento;
}

/**
Recupera y retorna el nodo correspondiente a la ra�z de A.
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
 El nuevo nodo se agrega en A como hijo de NP, hermano izquierdo de NH, y cuyo r�tulo es E.
 Si NH es NULL, el nuevo nodo se agrega como �ltimo hijo de NP.
 Si NH no corresponde a un nodo hijo de NP, finaliza indicando ARB_POSICION_INVALIDA.
 NP direcciona al nodo padre, mientras NH al nodo hermano derecho del nuevo nodo a insertar.
**/
tNodo a_insertar(tArbol a, tNodo np, tNodo nh, tElemento e){
    tLista hermanos = np->hijos;
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
 El elemento almacenado en el �rbol es eliminado mediante la funci�n fEliminar parametrizada.
 Si N es la ra�z de A, y tiene un s�lo hijo, este pasa a ser la nueva ra�z del �rbol.
 Si N es la ra�z de A, y a su vez tiene m�s de un hijo, finaliza retornando ARB_OPERACION_INVALIDA.
 Si N no es la ra�z de A y tiene hijos, estos pasan a ser hijos del padre de N, en el mismo orden y a partir de la posici�n que ocupa N en la lista de hijos de su padre.
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
        for(int i=0;i<cantHermanos&& !encontrado;i++){
            posNodo = l_siguiente(hermanos,posNodo);
            encontrado = l_recuperar(hermanos,posNodo) == n;
        }

        //se cambian los hijos del nodo a la lista de su padre
        posHijo = l_primera(hijos);
        for(int i=0;i<cantHijos;i++){
            aux = l_recuperar(hijos,posHijo);
            aux->padre = n->padre;  //se cambia de padre
            l_insertar(hermanos,posNodo,l_recuperar(hijos,posHijo)); // se agrega a la lista del padre d n
            posHijo = l_siguiente(hijos,posHijo);
        }

        //Se elimina completamente el nodo que debe ser eliminado
        l_eliminar(hermanos,posNodo,eliminarQuitarLista); //se elimina de la lista de sus hermanos
        l_destruir(&hijos,&eliminarQuitarLista); //se elimina la lista de hijos
        n->padre = NULL;
        fEliminar(n->elemento);
    }

}

void eliminarQuitarLista(tElemento nodo){
}

/**
 Destruye el �rbol A, eliminando cada uno de sus nodos.
 Los elementos almacenados en el �rbol son eliminados mediante la funci�n fEliminar parametrizada.
**/
void a_destruir(tArbol * a, void (*fEliminar)(tElemento)){
    destruirAux((*a),fEliminar,a_raiz((*a)));
}
void destruirAux(tArbol a, void (*fEliminar)(tElemento),tNodo nodo){
    tLista hijos = nodo->hijos;
    tPosicion hijo = l_primera(hijos);
    if(hijo!=NULL){
        while(hijo!=l_fin(hijos)){
            destruirAux(a,fEliminar,l_recuperar(hijos,hijo));
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
Recupera y retorna el elemento del nodo N.
*/

/*int pertenece(tArbol a,tNodo n){
    while(n->padre!=NULL){
        n = n->padre;
    }
    if(n == a_raiz())
        return 0;
    else
        return 1;
}*/