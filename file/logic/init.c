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
        caixa->resp = malloc(sizeof(Funcionario));

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
    /*printf("numProd: %d\n", numProd);
    printf("numTotalProdutos: %d\n", numTotalProdutos);*/


    for (int i = 0; i < numProd; i++) {
        int n = rand() % numTotalProdutos;
        listaProdutos[i] = produtos[n];
        /*listaProdutos[i].id = produtos[n].id;*/
        /*listaProdutos[i].name = strdup(produtos[n].name);
        listaProdutos[i].brand = strdup(produtos[n].brand);
        listaProdutos[i].weight = produtos[n].weight;
        listaProdutos[i].price = produtos[n].price;
        listaProdutos[i].purchaseTime = produtos[n].purchaseTime;
        listaProdutos[i].cashierTime = produtos[n].cashierTime;*/
    }
    *nProdutos = numProd;
    return listaProdutos;
}

Cliente generateCliente(Cliente *clientes, int numClientes, Produto *produtos, int numTotalProdutos) {
    int numCliente = (rand() % numClientes);
    Cliente cliente = clientes[numCliente];
    cliente.produtos = generateProductList(produtos, numTotalProdutos, &cliente.totalProdutos);
    /*for (int i = 0; i < cliente.totalProdutos; i++) {
        printf("Produto %d do cliente %d:\n", i + 1, cliente.id);
        printf("id: %d\n", cliente.produtos[i].id);
        printf("nome: %s\n", cliente.produtos[i].name);
        printf("brand: %s\n", cliente.produtos[i].brand);
        printf("weight: %s\n", cliente.produtos[i].weight);
        printf("price: %.2f\n", (cliente.produtos[i].price == 0.00) ? 10000000 : cliente.produtos[i].price);
        printf("purchaseTime: %.2f\n", (cliente.produtos[i].purchaseTime == 0.00) ? 10000000 : cliente.produtos[i].purchaseTime);
        printf("cashierTime: %.2f\n", (cliente.produtos[i].cashierTime == 0.00) ? 10000000 : cliente.produtos[i].cashierTime);
    }*/
    //calculo de tempo a pegar nos produtos e custo total
    for (int i = 0; i < cliente.totalProdutos; i++) {
        /*printf("Tempo chegada calculo %d %f", i, cliente.tempoChegadaFila);*/
        cliente.tempoPegarProdutos += cliente.produtos[i].purchaseTime/60;
        cliente.custoTotalProdutos += cliente.produtos[i].price;
    }

    //Calculo de tempo a passar os produtos na caixa
    for (int i = 0; i < cliente.totalProdutos; i++) {
        cliente.tempoPassarProdutos += cliente.produtos[i].cashierTime /60;
    }

    return cliente;
}

Funcionario generateFuncionario(Funcionario *funcionarios, int numFuncionarios) {
    int numFuncionario = (rand() % numFuncionarios);
    Funcionario funcionario = funcionarios[numFuncionario];
    return funcionario;
}

Fila *createShoppingClientList() {
    Fila *listaCliente = (Fila *)malloc(sizeof(Fila));
    if (listaCliente == NULL) {
        createLog("ERROR", "Memória insuficiente para alocar lista de clientes em compras!");
        return NULL;
    }
    listaCliente->numClients = 0;
    listaCliente->head = NULL;
    listaCliente->tail = NULL;

    return listaCliente;
}