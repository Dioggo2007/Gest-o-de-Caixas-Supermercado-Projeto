//
// Created by pache on 31/05/2026.
//

#include "../../header/logic/controlFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void searchClientId(Fila *clientesEmCompra, FilaCaixa *fila_caixa, Dados config) {
    int id;
    printf("Insira o id do cliente: ");
    scanf("%d", &id);

    if (clientesEmCompra->numClients != 0) {
        ListaCliente *cltTemp = clientesEmCompra->head;
        int i = 0;

        while (cltTemp != NULL) {
            printf("%d", i);
            if (cltTemp->client->id == id) {
                printClient(cltTemp->client, i + 1);
                printf("\nEnter para continuar...");
                scanf("%*c");
                scanf("%*c");
                return;
            }
            cltTemp = cltTemp->prev;
            i++;
        }
    }

    // Pesquisa nas filas das caixas
    for (int i = 0; i < config.N_CAIXAS; i++) {
        if (fila_caixa[i].fila->numClients != 0) {
            printf("%d", i);
            ListaCliente *cltTemp = fila_caixa[i].fila->head;
            int p = 0;

            while (cltTemp != NULL) {
                printf("%d", p);
                if (cltTemp->client->id == id) {
                    printClient(cltTemp->client, p + 1);
                    printf("\nEnter para continuar...");
                    scanf("%*c");
                    scanf("%*c");
                    return;
                }
                cltTemp = cltTemp->prev;
                p++;
            }
        }
    }

    printf("\nCliente não encontrado!");
    scanf("%*c");
    scanf("%*c");
}

void searchClientName(Fila *clientesEmCompra, FilaCaixa *fila_caixa, Dados config) {
    char name[100];
    printf("Insira o nome (ou parte do nome) do cliente: ");
    // ^\n ignora "\n"
    scanf(" %[^\n]", name);

    int encontrado = 0;

    if (clientesEmCompra->numClients != 0) {
        ListaCliente *cltTemp = clientesEmCompra->head;
        int i = 0;

        while (cltTemp != NULL) {
            if (strstr(cltTemp->client->name, name) != NULL) {
                printClient(cltTemp->client, -1);
                encontrado = 1;
            }
            cltTemp = cltTemp->prev;
            i++;
        }
    }

    for (int i = 0; i < config.N_CAIXAS; i++) {
        if (fila_caixa[i].fila->numClients != 0) {
            ListaCliente *cltTemp = fila_caixa[i].fila->head;
            int p = 0;

            while (cltTemp != NULL) {
                if (strstr(cltTemp->client->name, name) != NULL) {
                    printClient(cltTemp->client, p + 1);
                    encontrado = 1;
                }
                cltTemp = cltTemp->prev;
                p++;
            }
        }
    }

    if (encontrado == 0) {
        printf("\nNenhum cliente encontrado com a palavra '%s' no nome!\n", name);
    }

    printf("\nPressione ENTER para continuar...");
    scanf("%*c");
    scanf("%*c");
}

void calcularEstatisticasCaixas(FilaCaixa *filaCaixas, int nCaixas) {
    int maxPessoas = -1;
    int idCaixaMaxPessoas = -1;

    int maxProdutos = -1;
    int idCaixaMaxProdutos = -1;

    for (int i = 0; i < nCaixas; i++) {
        //Caixa que atendeu mais pessoas
        if (filaCaixas[i].cashier->totalClientesAtendidos > maxPessoas) {
            maxPessoas = filaCaixas[i].cashier->totalClientesAtendidos;
            idCaixaMaxPessoas = filaCaixas[i].cashier->id;
        }
        //Caixa que vendeu mais produtos
        if (filaCaixas[i].cashier->totalProdutosVendidos > maxProdutos) {
            maxProdutos = filaCaixas[i].cashier->totalProdutosVendidos;
            idCaixaMaxProdutos = filaCaixas[i].cashier->id;
        }
    }

    printf("\n=== ESTATISTICAS GLOBAIS DAS CAIXAS ===\n");
    if (maxPessoas > -1) {
        printf(" -> Caixa com MAIS clientes atendidos: Caixa %d (%d pessoas)\n", idCaixaMaxPessoas, maxPessoas);
        printf(" -> Caixa com MAIS produtos vendidos: Caixa %d (%d produtos)\n", idCaixaMaxProdutos, maxProdutos);
    } else {
        printf(" -> Nenhuma caixa realizou atendimentos ainda.\n");
    }
    printf("=======================================\n");
}

void changeWorker(FilaCaixa *fila_caixa, int nCaixas, Funcionario *funcionarios, int totalFuncionarios) {
    system("cls");
    int nCaixa;
    printf("Qual caixa quer mudar o cliente? ");
    scanf("%d", &nCaixa);
    if (nCaixa < nCaixas && nCaixas > 0)
        *fila_caixa[nCaixa - 1].cashier->resp = generateFuncionario(funcionarios, totalFuncionarios);
}

void changeCashierState(FilaCaixa *fila_caixa, int nCaixas, Funcionario *funcionarios, int totalFuncionarios) {
    system("cls");
    int nCaixa;
    printf("Qual caixa quer mudar o estado? ");
    scanf("%d", &nCaixa);
    if (nCaixa < nCaixas && nCaixas > 0)
        fila_caixa[nCaixa - 1].cashier->state = (fila_caixa[nCaixa - 1].cashier->state == 1 ? 0 : 1);
    *fila_caixa[nCaixa - 1].cashier->resp = generateFuncionario(funcionarios, totalFuncionarios);
}

void calcularMemoria(int totalProdutos, int totalClientes, int totalFuncionarios, int totalCaixas, Fila *corredor) {
    system("cls");
    int memProdutos = totalProdutos * sizeof(Produto);
    int memClientes = totalClientes * sizeof(Cliente);
    int memFuncionarios = totalFuncionarios * sizeof(Funcionario);
    int memCaixas = totalCaixas * (sizeof(Caixa) + sizeof(Fila));

    int memAtivos = corredor->numClients * (sizeof(ListaCliente) + sizeof(Cliente));

    int totalUtilizado = memProdutos + memClientes + memFuncionarios + memCaixas + memAtivos;


    printf("\n=== GESTAO DE MEMORIA ===\n");
    printf(" -> Memoria Total Utilizada: %d bytes (%.2f KB)\n", totalUtilizado, (float)totalUtilizado / 1024.0);
    printf("=========================\n");
    printf("Enter para continuar...");
    scanf("%*c");
    scanf("%*c");
}