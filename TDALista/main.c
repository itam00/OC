#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"
#include "ia.h"

int main(){
    int modo;

    printf("TA-TE-TI\n");
    char jugador1[50];
    while(modo!=1 || modo!=2){
        printf("\nSeleccione un modo para comenzar:\n");
        printf("1: Humano vs Humano\n2: Humano vs Maquina\n");
        scanf("%i",&modo);
        if(modo == 1){
            int jugador2[50];
            printf("Ingrese el nombre del jugador 1:");
            scanf("%s",jugador1);
            printf("\nIngrese el nombre del jugador 2:");
            scanf("%s",jugador2);
            printf("\n");
            humanoVsHumano(jugador1,jugador2);
        }
        else{
            printf("Ingrese el nombre del jugador 1:");
            scanf("%s",jugador1);
            humanoVsMaquina(jugador1);
            printf("\n");
        }

    }

}



void humanoVsHumano(char jugador1[50],char jugador2[50]){
    int fil,col;
    tPartida partida;
    nueva_partida(&partida,PART_MODO_USUARIO_VS_USUARIO,PART_JUGADOR_1,jugador1,jugador2);
    while(partida->estado==PART_EN_JUEGO){
        mostrarEstado(partida->tablero);
        printf("Turno de ");
        if(partida->turno_de==PART_JUGADOR_1){
            printf("%s",partida->nombre_jugador_1);
        }
        else{
            printf("%s",partida->nombre_jugador_2);
        }
        printf("\nIngrese la fila (0-2): ");
        scanf("%i",&fil);
        printf("\nIngrese la columna (0-2): ");
        scanf("%i",&col);
        nuevo_movimiento(partida,fil,col);
        printf("\n\n");
        partida->estado = verificarGanador(partida->tablero);
    }

    mostrarEstado(partida->tablero);
    switch(partida->estado){
    case PART_EMPATE:
        printf("\nHubo un empate");
        break;
    case PART_GANA_JUGADOR_1:
        printf("\nGana %s",partida->nombre_jugador_1);
        break;
    case PART_GANA_JUGADOR_2:
        printf("\nGana %s",partida->nombre_jugador_2);
        break;
    }
}

    void humanoVsMaquina(char jugador1[50]){
        int fil,col;
        tPartida partida;
        nueva_partida(&partida,PART_MODO_USUARIO_VS_AGENTE_IA,PART_JUGADOR_1,jugador1,"maquina");
        while(partida->estado==PART_EN_JUEGO){
            mostrarEstado(partida->tablero);
            printf("Turno de %s",partida->nombre_jugador_1);
            printf("\nIngrese la fila (0-2): ");
            scanf("%i",&fil);
            printf("\nIngrese la columna (0-2): ");
            scanf("%i",&col);
            nuevo_movimiento(partida,fil,col);
            printf("\n\n");
            partida->estado = verificarGanador(partida->tablero);
            if (partida->estado==PART_EN_JUEGO){
                printf("Juega la MAQUINOLA");
                tBusquedaAdversaria b;
                crear_busqueda_adversaria(&b,partida);
                proximo_movimiento(b,&fil,&col);
                nuevo_movimiento(partida,fil,col);
            }
        }

        mostrarEstado(partida->tablero);
        switch(partida->estado){
        case PART_EMPATE:
            printf("\nHubo un empate");
            break;
        case PART_GANA_JUGADOR_1:
            printf("\nGana %s",partida->nombre_jugador_1);
            break;
        case PART_GANA_JUGADOR_2:
            printf("\nGana la maquina");
            break;
        }
    }

int esTerminal(tTablero t){
    int ocupadas=1;
    for(int i=0;i<3 && ocupadas;i++){
        for(int j=0;j<3 && ocupadas;j++){
            ocupadas = t->grilla[i][j] != 0;
        }
    }
    return ocupadas;
}

int verificarGanador(tTablero e){
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
        tateti = fichaGanador!= 0 && e->grilla[0][0] == e->grilla[1][1] && e->grilla[1][1] == e->grilla[2][2];
    }
    if(!tateti){
        fichaGanador = e->grilla[2][0];
        tateti = fichaGanador!= 0 && e->grilla[2][0] == e->grilla[1][1] && e->grilla[1][1] == e->grilla[0][2];
    }
    if(tateti){
        if(fichaGanador == PART_JUGADOR_1){
            toReturn = PART_GANA_JUGADOR_1;
        }
        else{
            toReturn = PART_GANA_JUGADOR_2;
        }
    }
    else{
        if(esTerminal(e)){
            toReturn = PART_EMPATE;
        }
        else{
            toReturn = PART_EN_JUEGO;
        }
    }
    return toReturn;


}



void mostrarEstado(tTablero tablero){
    printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c\n",206,205,205,205,206,205,205,205,206,205,205,205,206);
    for(int i=0;i<3;i++){
            printf("%c",186);
        for(int j=0;j<3;j++){
            int ficha = tablero->grilla[i][j];
            switch(ficha){
                case PART_JUGADOR_1:
                    printf(" X ");
                    break;
                case PART_JUGADOR_2:
                    printf(" O ");
                    break;
                default:
                    printf("   ");
            }
            printf("%c",186);
        }
        printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c\n",206,205,205,205,206,205,205,205,206,205,205,205,206);
    }
}
