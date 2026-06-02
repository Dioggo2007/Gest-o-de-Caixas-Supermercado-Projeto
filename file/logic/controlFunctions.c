//
// Created by pache on 31/05/2026.
//

#include "../../header/logic/controlFunctions.h"

#include <stdio.h>
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