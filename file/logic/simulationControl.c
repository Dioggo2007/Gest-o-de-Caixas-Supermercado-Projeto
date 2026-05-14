//
// Created by pache on 13/05/2026.
//

#include <windows.h>

#include "../../header/logic/simulationControl.h"
#include "../../header/frame/menuPrints.h"

#include <stdio.h>

void startSimulation(int *time, int velSec, FilaCaixa *filaCaixa, int *totalCaixasAbertas, float *vendas, Dados config) {
    int endTime = 0;
    printf("Quanto tempo quer que a simulação em minutos(cada min é 1 seg)?\n");
    scanf("%d", &endTime);
    endTime += *time;

    while (*time <= endTime) {
        system("cls");
        printf("endTime: %d, time:%d, velSec: %d\n", endTime, *time, velSec);

        printHeader(*time, *totalCaixasAbertas, config.N_CAIXAS, *vendas);

        *time += velSec;
        Sleep(velSec*1000);
    }
    return;
}
