#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arbol.h"
#include "ia.h"

void humanoVsHumano(char jugador1[50],char jugador2[50],int jugadorInicial);
void humanoVsMaquina(char jugador1[50],int jugadorInicial);
void MaquinaVsMaquina(int jugadorInicial);
int esTerminal(tTablero t);
int verificarGanador(tTablero e);
void imprimirTablero(tTablero tablero);

/**
Refleja una partida de Ta-Te-Ti.
**/
int main(){
    int modo=0;
    int jugadorInicial=0;
    printf("TA-TE-TI\n");
    char jugador1[50];
    char jugador2[50];
    int jugarDenuevo = 1;

    while(jugarDenuevo){

        while(modo!=1 && modo!=2 && modo!=3){
            printf("\nSeleccione un modo para comenzar:\n");
            printf("1: Humano vs Humano\n2: Humano vs Maquina\n3: Maquina vs Maquina\n");
            scanf("%i",&modo);
        }

        while(jugadorInicial<1 || jugadorInicial>3){
            printf("\nSeleccione quien empieza:\n");
            printf("\n1: jugador1\n2: jugador2/Maquina \n3: random\n");
            scanf("%i",&jugadorInicial);
        }

        switch(jugadorInicial){
            case 1:
                jugadorInicial = PART_JUGADOR_1;
                break;
            case 2:
                jugadorInicial = PART_JUGADOR_2;
                break;
            case 3:
                jugadorInicial = PART_JUGADOR_RANDOM;
                break;
        }

        if(modo == 1){
            printf("Ingrese el nombre del jugador 1: (sin espacios)\n");
            scanf("%s",jugador1);
            printf("\nIngrese el nombre del jugador 2: (sin espacios)\n");
            scanf("%s",jugador2);
            printf("\n");
            humanoVsHumano(jugador1,jugador2,jugadorInicial);
        }
        else
            if (modo==2){
            printf("Ingrese el nombre del jugador 1: (sin espacios)\n");
            scanf("%s",jugador1);
            humanoVsMaquina(jugador1,jugadorInicial);
            printf("\n");
            }
            else{
                MaquinaVsMaquina(jugadorInicial);
                printf("\n");
            }
        printf("\n\nDesea volver a jugar?...\n");
        printf("0: NO   Otro numero: SI\n");
        scanf("%i",&jugarDenuevo);
    }

}
/**
Refleja el modo de juego Humano vs Humano.
**/
void humanoVsHumano(char jugador1[50],char jugador2[50],int jugadorInicial){
    int fil,col;
    tPartida partida;
    nueva_partida(&partida,PART_MODO_USUARIO_VS_USUARIO,jugadorInicial,jugador1,jugador2);

    while(partida->estado==PART_EN_JUEGO){
        imprimirTablero(partida->tablero);
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

    imprimirTablero(partida->tablero);
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
    finalizar_partida(&partida);
}

/**
Refleja el modo de juego Humano vs Maquina.
**/
void humanoVsMaquina(char jugador1[50],int jugadorInicial){
    int fil,col,valido;
    tPartida partida;
    nueva_partida(&partida,PART_MODO_USUARIO_VS_AGENTE_IA,jugadorInicial,jugador1,"Maquina");

    while(partida->estado==PART_EN_JUEGO){
        imprimirTablero(partida->tablero);

        if(partida->turno_de==PART_JUGADOR_1){
            printf("Turno de %s",partida->nombre_jugador_1);
            valido=PART_SIN_MOVIMIENTO;
            while(valido!=PART_MOVIMIENTO_OK){
                printf("\nIngrese la fila (0-2): ");
                scanf("%i",&fil);
                printf("\nIngrese la columna (0-2): ");
                scanf("%i",&col);
                valido=nuevo_movimiento(partida,fil,col);
                printf("\n\n");
            }
        }
        else{
            printf("Turno de %s",partida->nombre_jugador_2);
            tBusquedaAdversaria b;
            crear_busqueda_adversaria(&b,partida);
            proximo_movimiento(b,&fil,&col);
            nuevo_movimiento(partida,fil,col);
            destruir_busqueda_adversaria(&b);
        }
        partida->estado = verificarGanador(partida->tablero);
    }

    imprimirTablero(partida->tablero);
    switch(partida->estado){
    case PART_EMPATE:
        printf("\nHubo un empate");
        break;
    case PART_GANA_JUGADOR_1:
        printf("\nGana %s",partida->nombre_jugador_1);
        break;
    case PART_GANA_JUGADOR_2:
        printf("\nGana la maquinola");
        break;
    }
    finalizar_partida(&partida);
}
/**
Refleja el modo de juego Maquina vs Maquina.
**/

void MaquinaVsMaquina(int jugadorInicial){
    int fil,col;
    tPartida partida;
    tBusquedaAdversaria b;
    nueva_partida(&partida,PART_MODO_USUARIO_VS_AGENTE_IA,jugadorInicial,"Maquina A","Maquina B");

    while(partida->estado==PART_EN_JUEGO){
        imprimirTablero(partida->tablero);
        printf("Turno de %s",partida->nombre_jugador_2);
        crear_busqueda_adversaria(&b,partida);
        proximo_movimiento(b,&fil,&col);
        nuevo_movimiento(partida,fil,col);
        partida->estado = verificarGanador(partida->tablero);
        destruir_busqueda_adversaria(&b);
    }

    imprimirTablero(partida->tablero);
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

/**
Devuelve 1 si el tablero es terminal (esta lleno) y 0
en caso contrario.
*/
int esTerminal(tTablero t){
    int ocupadas=1;
    for(int i=0;i<3 && ocupadas;i++){
        for(int j=0;j<3 && ocupadas;j++){
            ocupadas = t->grilla[i][j] != 0;
        }
    }
    return ocupadas;
}
/**
Devuelve 1 PART_EMPATE si hubo embate, PART_GANA_JUGADOR_1 si gan�
el jugador 1, PART_GANA_JUGADOR_2 si gan� el jugador 2 y PART_EN_JUEGO
en cualquier otro caso.
**/

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

/**
Imprime el tablero mostrando la ubicaci�n de las fichas en la grilla.
*/

void imprimirTablero(tTablero tablero){
    printf("\n  0   1   2");
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
        printf("%i",i);

        printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c\n",206,205,205,205,206,205,205,205,206,205,205,205,206);
    }
}
