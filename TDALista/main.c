#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"
void removerLista();
void imprimirArbol(tArbol arbol);
int main()
{
   char a='A',b='B',c='C',d = 'D',e='E',f='F',g='G',h='H',i='I',j='J';
	tNodo raizsub;
    char *pa,*pb,*pc,*pd,*pe,*pf,*pg,*ph,*pi, *pj;
    tNodo aux,elim;
    pa = &a;
    pb = &b;
    pc = &c;
    pd = &d;
    pe = &e;
    pf = &f;
    pg = &g;
    ph = &h;
    pi = &i;
    pj =&j;

    tArbol arbol;
    crear_arbol(&arbol);
    crear_raiz(arbol,pa);
    char* letra=(char*)(a_recuperar(arbol,a_raiz(arbol)));
    printf(" El elemento guardado en la raiz es: %c \n",*letra);


    aux = a_insertar(arbol,a_raiz(arbol),NULL,pb);

    a_insertar(arbol,aux,NULL,pd);
    a_insertar(arbol,aux,NULL,pe);

    aux = a_insertar(arbol,a_raiz(arbol),NULL,pc);
    elim = aux;

    a_insertar(arbol,aux,NULL,pf);
    tNodo hermano=a_insertar(arbol,aux,NULL,pg);
    a_insertar(arbol,aux,hermano,pj);
    aux = a_insertar(arbol,aux,NULL,ph);
    a_insertar(arbol,aux,NULL,pi);
    a_insertar(arbol, aux, NULL,pc);

    raizsub = aux;
    imprimirArbol(arbol);

    a_eliminar(arbol,elim,removerLista);

    imprimirArbol(arbol);

    tArbol sub;
    a_sub_arbol(arbol,raizsub,&sub);
    imprimirArbol(sub);
    printf ("Los hijos del nodo h son: \n");

    tLista hijos= raizsub->hijos;
    char* caracter;
    tNodo recuperado;
    tPosicion actual= l_primera(hijos);
    while (actual!=l_fin(hijos)){
        recuperado= (tNodo)l_recuperar(hijos,actual);
        caracter=a_recuperar(sub,recuperado);
        printf("%c \n",*caracter);
        actual=l_siguiente(hijos,actual);
    }

    a_destruir(&arbol,removerLista);


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



