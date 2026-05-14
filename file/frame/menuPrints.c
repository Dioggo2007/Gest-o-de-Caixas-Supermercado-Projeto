//
// Created by pache on 11/05/2026.
//

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "../../header/frame/menuPrints.h"
#include "../../header/logic/struct.h"


void printTextCentered(char *text, int width) {

    int len = strlen(text);

    int padding = (width - len) / 2;

    for(int i = 0; i < padding; i++)
        printf(" ");

    printf("%s", text);

    for(int i = 0; i < padding; i++)
        printf(" ");
}

void printHeader(int time, int nCaixasAbertas, int nCaixasTotal, float vendas) {
    printf("=================================================================================\n");
    printTextCentered("Sistema de Gestão de Caixas", WIDTH);printf("\n");
    printf("=================================================================================\n");

    /*"   Tempo:[%d minutos]     |       Caixas %d/%d        |       Vendas: %2.f €     \n"*/
    char buffer[50];
    sprintf(buffer, "Tempo:[%d minutos]", time);
    printTextCentered(buffer, COL_WIDTH - 1);
    printf("|");
    sprintf(buffer, "Caixas %d/%d", nCaixasAbertas, nCaixasTotal);
    printTextCentered(buffer, COL_WIDTH);
    printf("|");
    sprintf(buffer, "Vendas: %2.f €", vendas);
    printTextCentered(buffer, COL_WIDTH - 1);
    printf("\n");
}

void printCashiers(int page, FilaCaixa *lista, int nCaixasTotal) {
    printf("---------------------------------------------------------------------------------\n");
    int numMin = (page - 1) * 3;

    int numMax = page * 3 - 1;
    if (numMax > nCaixasTotal - 1) {
        numMax = nCaixasTotal - 1;
    }
    for (int i = numMin; i <= numMax; i++) {

        char buffer[50];

        sprintf(buffer,
                "Caixa %d [%s]",
                lista[i].cashier->id,
                lista[i].cashier->state ? "Aberto" : "Fechado");
        //Se nao for o ultimo ou se for o primeiro e só for 1 para dar print
        if (i != numMax || i == numMin)
            printf(" %-*s| ", COL_WIDTH - 2, buffer);
        else
            printf("%-*s", COL_WIDTH, buffer);
    }
    printf("\n");

    // Operadores
    for (int i = numMin; i <= numMax; i++) {
        char buffer[50];
        if (lista[i].cashier->state == 0)
            sprintf(buffer, "Op: %-21s", "-----");
        else
            sprintf(buffer,"Op: %-21s",
                   lista[i].cashier->resp->name);

        //Se nao for o ultimo ou se for o primeiro e só for 1 para dar print
        if (i != numMax || i == numMin)
            printf(" %-*s| ", COL_WIDTH - 2, buffer);
        else
            printf("%-*s", COL_WIDTH, buffer);
    }
    printf("\n");

    for (int i = numMin; i <= numMax; i++) {
        char buffer[50];
        sprintf(buffer,"Clientes: %-15d",
               lista[i].fila->numClients);

        //Se nao for o ultimo ou se for o primeiro e só for 1 para dar print
        if (i != numMax || i == numMin)
            printf(" %-*s| ", COL_WIDTH - 2, buffer);
        else
            printf("%-*s", COL_WIDTH, buffer);
    }

    printf("\n");
}

void printLogs() {
    printf("---------------------------------------------------------------------------------\n");

}

void printFooter(int opcao) {
    /*[1]Simulação | [2]Caixas | [3]Clientes | [4]Outros*/
    /*Iniciar Simulação   | Abrir/Fechar Caixa | Procurar Cliente  | Historico
     * Pausar Simulação   | Mudar Funcionario  | Adicionar Cliente | Utilização de memoria
     * Acelarar Simulação | Mostrar Clientes   | Remover Cliente   | Configurações
     * Reiniciar Simulação|
     */
    printf("---------------------------------------------------------------------------------\n");
    switch (opcao) {
        case 0:
            printf("Opções: [1]Simulação | [2]Caixas | [3]Clientes | [4]Outros");
            break;
        case 1:
            printf("Opções: [1]Iniciar Simulação | [2]Acelarar Simulação | [3]Reiniciar Simulação");
            break;
        case 2:
            printf("Opções: [1]Abrir/Fechar Caixa | [2]Mudar Funcionario | [3]Mostrar Clientes");
            break;
        case 3:
            printf("Opções: [1]Procurar Cliente | [2]Adicionar Cliente | [3] Remover Cliente");
            break;
        case 4:
            printf("Opções: [1]Historico | [2]Utilização de Memoria | [3]Configurações");
            break;
        default:
            printf("Opções: [1]Simulação | [2]Caixas | [3]Clientes | [4]Outros");
            break;
    }
    printf("\n");
}

int escolherOpcaoMenuPrincipal(int numMin, int numMax)
{
    int opcao;
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    if (opcao < numMin || opcao > numMax)
    {
        system("cls");
        printf("Opção inválida. Tente novamente.\n");
        while (getchar() != '\n');
        scanf("%*c"); // Limpar o buffer do teclado

        return -1;
    }
    return opcao;
}