//
// Created by pache on 11/05/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_MENUPRINTS_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_MENUPRINTS_H

#include "../logic/struct.h"

#define WIDTH 81
#define COL_WIDTH 27// 81/3 = 27

void printTextCentered(char *text, int width);

void printHeader(int time, int nCaixas, int nCaixasTotal, float vendas);

void printCashiers(int page, FilaCaixa *lista, int nCaixasTotal);

void printLogs();

void printFooter(int opcao);

int escolherOpcaoMenuPrincipal(int numMin, int numMax);

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_MENUPRINTS_H