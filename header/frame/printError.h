//
// Created by pache on 06/05/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_PRINTERROR_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_PRINTERROR_H

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD          "\x1b[1m"

//Funções para dar print de algum erro ou aviso

void printError(char *message);

void printWarning(char *mensagem);

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_PRINTERROR_H