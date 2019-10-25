#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ia.h"
#include "arbol.h"
#include "partida.h"
#include "lista.h"


/**
Inicializa una nueva partida, indicando:
 - Modo de partida (Usuario vs. Usuario o Usuario vs. Agente IA).
 - Jugador que comienza la partida (Jugador 1, Jugador 2, o elección al azar).
 - Nombre que representa al Jugador 1.
 - Nombre que representa al Jugador 2.
**/
void nueva_partida(tPartida * p, int modo_partida, int comienza, char * j1_nombre, char * j2_nombre){
    (*p)=(struct partida*)(malloc(sizeof(struct partida)));
    (*p)->modo_partida=modo_partida;
    if(comienza!= PART_JUGADOR_RANDOM){
        (*p)->turno_de=comienza;
    }
    else{
        (*p)->turno_de=PART_JUGADOR_1;
    }

    strcpy((*p)->nombre_jugador_1,j1_nombre);
    strcpy((*p)->nombre_jugador_1,j2_nombre);
    (*p)->tablero=(struct tablero*)malloc(sizeof(struct tablero));
    for(int i=0;i<3;i++){
        for(int j=0;i<3;j++){
            (*p)->tablero->grilla[i][j] = 0;
        }
    }
}

/**
Actualiza, si corresponde, el estado de la partida considerando que el jugador al que le corresponde jugar, decide hacerlo en la posición indicada (X,Y).
En caso de que el movimiento a dicha posición sea posible, retorna PART_MOVIMIENTO_OK; en caso contrario, retorna PART_MOVIMIENTO_ERROR.
Las posiciones (X,Y) deben corresponderse al rango [0-2]; X representa el número de fila, mientras Y el número de columna.
**/
int nuevo_movimiento(tPartida p, int mov_x, int mov_y){
    int toReturn = PART_MOVIMIENTO_ERROR;
    if(!(mov_x>2 || mov_y>2 || p->tablero->grilla[mov_x][mov_y] !=0)){//si no es movimiento invalido (es movimiento valido)
        p->tablero->grilla[mov_x][mov_y] = p->turno_de;

        if(p->turno_de == PART_JUGADOR_1){
            p->turno_de = PART_JUGADOR_2;
        }
        else{
            p->turno_de = PART_JUGADOR_1;
        }
        toReturn = PART_MOVIMIENTO_OK;
    }
    return toReturn;
}


/**
Finaliza la partida referenciada por P, liberando toda la memoria utilizada.
**/

void finalizar_partida(tPartida * p){
    free((*p)->tablero);
    free((*p));
    (*p)=NULL;
}
