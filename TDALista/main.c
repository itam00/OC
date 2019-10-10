#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"
void removerLista();

int main()
{
    char a='A',b='B',c='C',x;
    char *pa,*pb,*pc,*elem;
    tNodo aux;
    pa = &a;
    pb = &b;
    pc = &c;
    tArbol arbol;
    crear_arbol(&arbol);
    crear_raiz(arbol,pa);

    elem = (char*)a_recuperar(arbol,a_raiz(arbol));

    aux = a_insertar(arbol,a_raiz(arbol),NULL,pb);

    aux = a_insertar(arbol,a_raiz(arbol),NULL,pc);

    imprimirArbol(arbol);
    /*printf("el nodo raiz es: %c",*elem);

    elem = (char*)a_recuperar(arbol,aux);

    printf("\nEl hijo de la raiz es: %c",*elem);*/

return(0);

}

void imprimirArbol(tArbol arbol){
    tLista lista,hijos;
    crear_lista(&lista);
    tNodo nodo = a_raiz(arbol),fin;

    l_insertar(lista,l_primera(lista),nodo);
    l_insertar(lista,l_primera(lista),NULL);
    char *c;

    while(l_longitud(lista)>1){
        printf("%d",l_longitud(lista));
        nodo = l_recuperar(lista,l_ultima(lista));
        l_eliminar(lista,l_ultima(lista),removerLista);

        c = (char*)a_recuperar(arbol,nodo);
        printf("%c  -  ", *c);


        //se insertan los hijos del nodo
        hijos = a_hijos(arbol,nodo);
        nodo = l_primera(hijos);
    printf("hola");
        printf("%d  -  ", l_longitud(hijos));
        while(nodo!=l_fin(hijos)){
            nodo= l_siguiente(hijos,nodo);
            l_insertar(lista,l_primera(lista),nodo);

        }

        nodo = l_recuperar(lista,l_ultima(lista));


        if(nodo == NULL){
            l_eliminar(lista,l_ultima(lista),removerLista);
            l_insertar(lista,l_primera(lista),NULL);
            printf("\n");
        }


    }
}
void removerLista(tElemento t){}

