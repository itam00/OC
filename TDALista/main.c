#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"
void removerLista();
void imprimirArbol(tArbol a);
tNodo nodob;
int main()
{
   char a='A',b='B',c='C',d = 'D',e='E',f='F',g='G',h='H',i='I',j='J',k='K',l='L',m='M';
    char *pa,*pb,*pc,*pd,*pe,*pf,*pg,*ph,*pi,*pj,*pk,*pl,*pm;
    tNodo aux,elim,hermano;
    pa = &a;
    pb = &b;
    pc = &c;
    pd = &d;
    pe = &e;
    pf = &f;
    pg = &g;
    ph = &h;
    pi = &i;
    pj = &j;
    pk = &k;
    pl = &l;
    pm = &m;

    printf("creando arbol: \n");

    tArbol arbol;
    crear_arbol(&arbol);
    crear_raiz(arbol,pa);

    printf("agregando nodos al arbol...\n");


    aux = a_insertar(arbol,a_raiz(arbol),NULL,pb);
    elim = aux;

    hermano =a_insertar(arbol,aux,NULL,pd);
    aux = a_insertar(arbol,aux,hermano,pe);
    a_insertar(arbol,aux,NULL,pi);

    aux = a_insertar(arbol,a_raiz(arbol),NULL,pc);
    //elim = aux;

    a_insertar(arbol,aux,NULL,pf);
    a_insertar(arbol,aux,NULL,pg);
    aux = a_insertar(arbol,aux,NULL,ph);
    a_insertar(arbol,aux,NULL,pj);

    nodob = aux;
    imprimirArbol(arbol);

    char* elem = a_recuperar(arbol,elim);
    printf("Eliminando el nodo: %c\n",*elem);

    a_eliminar(arbol,elim,removerLista);

    imprimirArbol(arbol);
    printf("\n\nDestruyendo el arbol...\n");
    a_destruir(&arbol,removerLista);
    if(arbol == NULL){
        printf("El arbol fue eliminado");
    }

    printf("\n\ncreando un nuevo arbol...\n");
    crear_arbol(&arbol);
    crear_raiz(arbol,pf);

    printf("\ninsertando nuevos elmentos en el arbol..\n");

    aux = a_insertar(arbol,a_raiz(arbol),NULL,pg);
    elim = a_raiz(arbol);

    a_insertar(arbol,aux,NULL,ph);
    a_insertar(arbol,aux,NULL,pi);

    imprimirArbol(arbol);

    elem = a_recuperar(arbol,elim);
    printf("\nEliminando el nodo: %c\n",*elem);

    a_eliminar(arbol,elim,removerLista);
    imprimirArbol(arbol);

    printf("\n\ninsertando nuevos elementos en la raiz..\n");
    a_insertar(arbol,a_raiz(arbol),NULL,pj);
    a_insertar(arbol,a_raiz(arbol),NULL,pk);
    imprimirArbol(arbol);


return(0);

}

void imprimirArbol(tArbol arbol){
    tLista lista,hijos;
    crear_lista(&lista);
    tPosicion pos;
    tNodo nodo = a_raiz(arbol),padre;

    l_insertar(lista,l_primera(lista),nodo);
    l_insertar(lista,l_primera(lista),NULL);
    char *c,*p;

    while(l_longitud(lista)>1){

        nodo = l_recuperar(lista,l_ultima(lista));
        l_eliminar(lista,l_ultima(lista),&removerLista);

        c = (char*)a_recuperar(arbol,nodo);

        //verificacion de que realmente son sus padres
        padre = nodo->padre;
        if(padre!=NULL){
            p = (char*)a_recuperar(arbol,padre);
            printf("%c<--",*p);
        }
        printf("(%c)   ", *c);



        //se insertan los hijos del nodo
        hijos = a_hijos(arbol,nodo);
        pos = l_primera(hijos);
        while(pos!=l_fin(hijos)){
            nodo = l_recuperar(hijos,pos);
            l_insertar(lista,l_primera(lista),nodo);
            pos= l_siguiente(hijos,pos);
        }

        nodo = l_recuperar(lista,l_ultima(lista));

        //se marca el fin del cada nivel
        if(nodo == NULL){
            l_eliminar(lista,l_ultima(lista),&removerLista);
            l_insertar(lista,l_primera(lista),NULL);
            printf("\n");
        }


    }
}
void removerLista(tElemento t){}



