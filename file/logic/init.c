//
// Created by pache on 07/05/2026.
//

#include "../../header/logic/init.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../header/logic/errorlogs.h"

FilaCaixa *createFilaCaixa(int numCaixas) {
    FilaCaixa *filaCaixa = malloc(sizeof(FilaCaixa) * numCaixas);
    if (filaCaixa == NULL) {
        createLog("ERROR", "Memória insuficiente para alocar as Caixas!");
        free(filaCaixa);
        return NULL;
    }

    for (int i = 0; i < numCaixas; i++) {
        Caixa *caixa = malloc(sizeof(Caixa));
        Fila *fila = malloc(sizeof(Fila));

        if (caixa == NULL || fila == NULL) {
            createLog("ERROR", "Memória insuficiente para alocar as Caixas!");
            free(fila);free(caixa);free(filaCaixa);
            return NULL;
        }

        caixa->id = i+1;
        caixa->state = 0;
        caixa->resp = NULL;

        fila->numClients = 0;
        fila->head = fila->tail = NULL;

        filaCaixa[i].fila = fila;
        filaCaixa[i].cashier = caixa;
    }

    return filaCaixa;
}

Produto *generateProductList(Produto *produtos, int numTotalProdutos, int *nProdutos) {
    Produto *listaProdutos;
    int numProd = (rand() % 10) + 1;

    listaProdutos = malloc(sizeof(Produto) * numProd);

    if (listaProdutos == NULL) {
        createLog("ERROR", "Memória insuficiente para alocar lista de produtos!");
        return NULL;
    }
    printf("numProd: %d\n", numProd);
    printf("numTotalProdutos: %d\n", numTotalProdutos);

    //DUVIDA PERGUNTAR PROFESSOR
    for (int i = 0; i < numProd; i++) {
        int n = rand() % numTotalProdutos;
        printf("aleatorio %d: ", n);
        listaProdutos[i] = produtos[n];
        /*listaProdutos[i].id = produtos[n].id;
        listaProdutos[i].name = strdup(produtos[n].name);
        listaProdutos[i].brand = strdup(produtos[n].brand);
        listaProdutos[i].weight = produtos[n].weight;
        listaProdutos[i].price = produtos[n].price;
        listaProdutos[i].purchaseTime = produtos[n].purchaseTime;
        listaProdutos[i].cashierTime = produtos[n].cashierTime;*/
    }
    *nProdutos = numProd;
    return listaProdutos;
}