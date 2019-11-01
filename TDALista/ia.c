#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "arbol.h"
#include "ia.h"

// Prototipos de funciones auxiliares.
static void ejecutar_min_max(tBusquedaAdversaria b);
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min);
static int valor_utilidad(tEstado e, int jugador_max);
static tLista estados_sucesores(tEstado e, int ficha_jugador);
static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y);
static tEstado clonar_estado(tEstado e);
static void eliminarQuitarDeLista(tElemento estado);
static int tableroLleno(tEstado estado);
void destruirEstado(tElemento e);


static int min(int x, int y){
    if (x<y)
        return x;
    else
        return y;
}
static int max(int x, int y){
    if (x>y)
        return x;
    else
        return y;
}


void crear_busqueda_adversaria(tBusquedaAdversaria * b, tPartida p){
    int i, j;
    tEstado estado;
    srand (time(NULL));

    (*b) = (tBusquedaAdversaria) malloc(sizeof(struct busqueda_adversaria));
    if ((*b) == NULL) exit(IA_ERROR_MEMORIA);

    estado = (tEstado) malloc(sizeof(struct estado));
    if (estado == NULL) exit(IA_ERROR_MEMORIA);

    // Se clona el estado del tablero de la partida, al estado inicial de la búsqueda adversaria.
    for(i=0; i<3; i++){
        for(j=0; j<3; j++){
            estado->grilla[i][j] = p->tablero->grilla[i][j];
        }
    }

	// Se asume que el estado de la partida es PART_EN_JUEGO por lo que, la utilidad del estado
	// inicialmente es IA_NO_TERMINO
    estado->utilidad = IA_NO_TERMINO;

    // Inicializa los valores que representarán a los jugadores MAX y MIN respectivamente.
    (*b)->jugador_max = p->turno_de;
    (*b)->jugador_min = (p->turno_de == PART_JUGADOR_1) ? PART_JUGADOR_2 : PART_JUGADOR_1;

    // Inicializa un árbol para la búsqueda adversaria inicialmente vacío.
    crear_arbol(&((*b)->arbol_busqueda));

    // Inicializa la raíz del árbol de búsqueda con el estado del tablero T.
    crear_raiz((*b)->arbol_busqueda, estado);

    // Ejecuta algoritmo Min-Max con podas Alpha-Beta.
    ejecutar_min_max((*b));
}

/**
Indica cual sera el proximo movimiento de la IA haciendo uso de los punteros x e y.
*/
void proximo_movimiento(tBusquedaAdversaria b, int * x, int * y){
    int mayor=IA_INFINITO_NEG;
    tArbol arbol= b->arbol_busqueda; //tArbol arbol=arbol;
    tNodo raiz= a_raiz(arbol);
    tEstado estadoActual = (tEstado) a_recuperar(arbol,raiz);
    tEstado estadoProximo;
    tLista listaHijos= a_hijos(arbol,raiz);
    tPosicion actual=l_primera(listaHijos);
    tNodo hijoActual;
    tEstado estadoHijoActual;
    while (actual!=l_fin(listaHijos) && mayor!=IA_GANA_MAX){
        hijoActual=(tNodo)l_recuperar(listaHijos,actual);
        estadoHijoActual=(tEstado)a_recuperar(arbol,hijoActual);

        if (estadoHijoActual->utilidad>mayor){
            mayor=estadoHijoActual->utilidad;
            estadoProximo=estadoHijoActual;
        }
        actual= l_siguiente(listaHijos,actual);
    }
    diferencia_estados(estadoActual,estadoProximo,x,y);
}


/**
Finaliza la busqueda binaria B, liberando toda la memoria utilizada.
**/
void destruir_busqueda_adversaria(tBusquedaAdversaria * b){
    a_destruir(&(*b)->arbol_busqueda,destruirEstado);
    free(*b);
    b=NULL;
}

// ===============================================================================================================
// FUNCIONES Y PROCEDEMIENTOS AUXILIARES
// ===============================================================================================================

/**
Ordena la ejecución del algoritmo Min-Max para la generación del árbol de búsqueda adversaria, considerando como
estado inicial el estado de la partida almacenado en el árbol almacenado en B.
**/
static void ejecutar_min_max(tBusquedaAdversaria b){
    tArbol a = b->arbol_busqueda;
    tNodo r = a_raiz(a);
    int jugador_max = b->jugador_max;
    int jugador_min = b->jugador_min;
    crear_sucesores_min_max(a, r, 1, IA_INFINITO_NEG, IA_INFINITO_POS, jugador_max, jugador_min);
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Implementa la estrategia del algoritmo Min-Max con podas Alpha-Beta, a partir del estado almacenado en N.
- A referencia al árbol de búsqueda adversaria.
- N referencia al nodo a partir del cual se construye el subárbol de búsqueda adversaria.
- ES_MAX indica si N representa un nodo MAX en el árbol de búsqueda adversaria.
- ALPHA y BETA indican sendos valores correspondientes a los nodos ancestros a N en el árbol de búsqueda A.
- JUGADOR_MAX y JUGADOR_MIN indican las fichas con las que juegan los respectivos jugadores.
**/
static void crear_sucesores_min_max(tArbol a, tNodo n, int es_max, int alpha, int beta, int jugador_max, int jugador_min){
    tEstado estado= (tEstado)(n->elemento);
    int mejor_valor_sucesores;
    tLista listaSucesores;
    tPosicion actual;
    tNodo nodoNuevo;
    tEstado estado_sucesor;
    int valor_sucesor;
    valor_sucesor=0;

    estado->utilidad=valor_utilidad(estado,jugador_max);

    if (estado->utilidad == IA_NO_TERMINO){

        if (es_max){
            mejor_valor_sucesores= IA_INFINITO_NEG;
            listaSucesores=estados_sucesores(estado,jugador_max);
            actual= l_primera(listaSucesores);
            while (beta>alpha && actual!=l_fin(listaSucesores)){
                estado_sucesor= (tEstado) l_recuperar(listaSucesores,actual);
                nodoNuevo= a_insertar(a,n,NULL,estado_sucesor);
                crear_sucesores_min_max(a,nodoNuevo,0,alpha,beta,jugador_max,jugador_min);
                valor_sucesor= estado_sucesor->utilidad;
                alpha= max(alpha,mejor_valor_sucesores);
                mejor_valor_sucesores= max(mejor_valor_sucesores,estado_sucesor->utilidad);


                actual = l_siguiente(listaSucesores,actual);

            }
            estado->utilidad=mejor_valor_sucesores;
        }
        else{
            mejor_valor_sucesores=IA_INFINITO_POS;
            listaSucesores=estados_sucesores(estado,jugador_min);
            actual= l_primera(listaSucesores);
            while (beta>alpha && actual!=l_fin(listaSucesores)){
                estado_sucesor= (tEstado) l_recuperar(listaSucesores,actual);
                nodoNuevo= a_insertar(a,n,NULL,estado_sucesor);
                crear_sucesores_min_max(a,nodoNuevo,1,alpha,beta,jugador_max,jugador_min);
                valor_sucesor= estado_sucesor->utilidad;
                mejor_valor_sucesores= min(mejor_valor_sucesores,estado_sucesor->utilidad);
                alpha= min(alpha,mejor_valor_sucesores);

                actual = l_siguiente(listaSucesores,actual);
            }

            estado->utilidad=mejor_valor_sucesores;
        }

        //se eliminan completamente los estados que no seran utilizados ya que no fueorn insertados en el arbol
        while(actual!=l_fin(listaSucesores)){
            l_eliminar(listaSucesores,l_ultima(listaSucesores),&destruirEstado);
        }
        //Se quitan los estados de la lista que si fueron usados y se destruye la lista
        l_destruir(&listaSucesores,eliminarQuitarDeLista);
    }
}
/**
Operacion auxiliar usada para quitar un estado de un lista sin eliminarlo
**/
void eliminarQuitarDeLista(tElemento estado){
}

/**
Operacin auxiliar usada para eliminar un elemento
**/
void destruirEstado(tElemento e){
    free(e);
}


/* Operacion auxiliar que determina si el "tablero" esta completamente ocupado
por fichas de cualquiera de los dos jugadores.
*/
int tableroLleno(tEstado estado){
    int ocupadas=1;
    for(int i=0;i<3 && ocupadas;i++){
        for(int j=0;j<3 && ocupadas;j++){
            ocupadas = estado->grilla[i][j] != 0;
        }
    }
    return ocupadas;
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa el valor de utilidad correspondiente al estado E, y la ficha correspondiente al JUGADOR_MAX, retornado:
- IA_GANA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX ganó la partida.
- IA_EMPATA_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX empató la partida.
- IA_PIERDE_MAX si el estado E refleja una jugada en el que el JUGADOR_MAX perdió la partida.
- IA_NO_TERMINO en caso contrario.
**/

static int valor_utilidad(tEstado e, int jugador_max){
    int tateti=0,toReturn,fichaGanador;

    for(int i=0;i<3&& !tateti;i++){
        fichaGanador = e->grilla[i][i];
        tateti = fichaGanador!=0 && e->grilla[i][0] == e->grilla[i][1] && e->grilla[i][1] == e->grilla[i][2];
    }
    for(int i=0;i<3&& !tateti;i++){
        fichaGanador = e->grilla[i][i];
        tateti = fichaGanador!=0 && e->grilla[0][i] == e->grilla[1][i] && e->grilla[1][i] == e->grilla[2][i];
    }
    if(!tateti){
        fichaGanador = e->grilla[0][0];
        tateti = fichaGanador!=0 && e->grilla[0][0] == e->grilla[1][1] && e->grilla[1][1] == e->grilla[2][2];
    }
    if(!tateti){
        fichaGanador = e->grilla[2][0];
        tateti = fichaGanador!=0 && e->grilla[2][0] == e->grilla[1][1] && e->grilla[1][1] == e->grilla[0][2];
    }
    if(tateti){
        if(fichaGanador == jugador_max){
            toReturn = IA_GANA_MAX;
        }
        else{
            toReturn = IA_PIERDE_MAX;
        }
    }
    else{
        if(tableroLleno(e)){
            toReturn = IA_EMPATA_MAX;
        }
        else{
            toReturn = IA_NO_TERMINO;
        }
    }
    return toReturn;


}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Computa y retorna una lista con aquellos estados que representan estados sucesores al estado E.
Un estado sucesor corresponde a la clonación del estado E, junto con la incorporación de un nuevo movimiento
realizado por el jugador cuya ficha es FICHA_JUGADOR por sobre una posición que se encuentra libre en el estado E.
La lista de estados sucesores se debe ordenar de forma aleatoria, de forma tal que una doble invocación de la función
estados_sucesores(estado, ficha) retornaría dos listas L1 y L2 tal que:
- L1 y L2 tienen exactamente los mismos estados sucesores de ESTADO a partir de jugar FICHA.
- El orden de los estado en L1 posiblemente sea diferente al orden de los estados en L2.
**/
static tLista estados_sucesores(tEstado e, int ficha_jugador){
    tLista lista;
    crear_lista(&lista);
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(e->grilla[i][j]==0){
                tEstado nuevo = clonar_estado(e);
                nuevo->grilla[i][j] = ficha_jugador;
                if(rand()%2){ //numero random entre 0 y 1 los cuales definiran el orden de los elementos en la lista
                    l_insertar(lista,l_primera(lista),nuevo);
                }
                else{
                    l_insertar(lista,l_fin(lista),nuevo);
                }
            }
        }
    }
    return lista;
}

/**
>>>>>  A IMPLEMENTAR   <<<<<
Inicializa y retorna un nuevo estado que resulta de la clonación del estado E.
Para esto copia en el estado a retornar los valores actuales de la grilla del estado E, como su valor
de utilidad.
**/
static tEstado clonar_estado(tEstado e){
    tEstado nuevo= (tEstado)(malloc(sizeof(struct estado)));
    for (int i=0; i<3;i++)
        for( int j=0; j<3; j++)
            nuevo->grilla[i][j]= e->grilla[i][j];
    nuevo->utilidad=e->utilidad;
    return nuevo;
}

/**
Computa la diferencia existente entre dos estados.
Se asume que entre ambos existe sólo una posición en el que la ficha del estado anterior y nuevo difiere.
La posición en la que los estados difiere, es retornada en los parámetros *X e *Y.
**/

static void diferencia_estados(tEstado anterior, tEstado nuevo, int * x, int * y){
    int i,j, hallado = 0;
    for(i=0; i<3 && !hallado; i++){
        for(j=0; j<3 && !hallado; j++){
            if (anterior->grilla[i][j] != nuevo->grilla[i][j]){
                *x = i;
                *y = j;
                hallado = 1;
            }
        }
    }
}

