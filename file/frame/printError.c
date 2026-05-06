//
// Created by pache on 06/05/2026.
//

#include <stdio.h>
#include "../../header/frame/printError.h"

#include <stdlib.h>
#include <string.h>

void printError(char *mensagem) {
    int tamanho = strlen(mensagem) + 10;
    system("cls");
    printf("\n");
    printf(ANSI_COLOR_RED);
    for (int i = 0; i < tamanho; i++) printf("-");
    printf("\n"ANSI_COLOR_RESET);

    printf(ANSI_BOLD ANSI_COLOR_RED "  [ERRO] " ANSI_COLOR_RESET);
    printf("%s\n", mensagem);

    printf(ANSI_COLOR_RED);
    for (int i = 0; i < tamanho; i++) printf("-");
    printf("\n"ANSI_COLOR_RESET);

    printf("\n" ANSI_COLOR_CYAN "  > Pressione [ENTER] para continuar..." ANSI_COLOR_RESET "\n");
    scanf("%*c");
}

void printWarning(char *mensagem) {
    system("cls");
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "  [AVISO] " ANSI_COLOR_RESET "%s\n", mensagem);
    scanf("%*c");
}