//
// Created by pache on 06/05/2026.
//

#include "../../header/logic/dataManager.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../header/logic/struct.h"

int countLines(const char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) return -1;

    int linhas = 0;
    char buffer[TAMANHO_LINHA];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (buffer[0] != '\n') linhas++; // Evita contar linhas vazias
    }
    fclose(f);
    return linhas;
}

int readProductData(Produto **lista, int *totalProdutos) {
    int linhas = countLines(PRODUTOS_PATH);
    if (linhas <= 0) {
        printf("Erro: Nenhum produto encontrado!\n");
        return 0;
    }

    FILE *f = fopen(PRODUTOS_PATH, "r");
    if (f == NULL) return 0;

    //Alocar memoria
    *lista = (Produto *)malloc(linhas * sizeof(Produto));
    if (*lista == NULL)
    {
        printf("Erro: Memória insuficiente para alocar produtos\n");
        scanf("%*c");
        fclose(f);
        return 0;
    }

    // Ler os produtos
    char buffer[TAMANHO_LINHA];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        sscanf(buffer, "%d %[^[] [%[^]]] %d gr %f %f %f",
            &(*lista)[i].id,
            (*lista)[i].name,
            (*lista)[i].brand,
            &(*lista)[i].weight,
            &(*lista)[i].price,
            &(*lista)[i].purchaseTime,
            &(*lista)[i].cashierTime
            );
        i++;
    }
    *totalProdutos = linhas;
    fclose(f);
    return 1;
}

int readFuncionario(Funcionario **lista, int *totalFuncionarios) {
    int linhas = countLines(FUNCIONARIOS_PATH);
    if (linhas <= 0) {
        printf("Erro: Nenhum produto encontrado!\n");
        return 0;
    }

    FILE *f = fopen(FUNCIONARIOS_PATH, "r");
    if (f == NULL) return 0;

    //Alocar memoria
    *lista = (Funcionario *)malloc(linhas * sizeof(Funcionario));
    if (*lista == NULL)
    {
        printf("Erro: Memória insuficiente para alocar funcionarios\n");
        scanf("%*c");
        fclose(f);
        return 0;
    }

    // Ler os produtos
    char buffer[TAMANHO_LINHA];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        sscanf(buffer, "%d %[^\n]",
            &(*lista)[i].id,
            (*lista)[i].name
            );
        i++;
    }
    *totalFuncionarios = linhas;
    fclose(f);
    return 1;
}

int readClient(Cliente **lista, int *totalClientes) {
    int linhas = countLines(CLIENTES_PATH);
    if (linhas <= 0) {
        printf("Erro: Nenhum produto encontrado!\n");
        return 0;
    }

    FILE *f = fopen(CLIENTES_PATH, "r");
    if (f == NULL) return 0;

    //Alocar memoria
    *lista = (Cliente *)malloc(linhas * sizeof(Cliente));
    if (*lista == NULL)
    {
        printf("Erro: Memória insuficiente para alocar Clientes\n");
        scanf("%*c");
        fclose(f);
        return 0;
    }

    // Ler os produtos
    char buffer[TAMANHO_LINHA];
    int i = 0;
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        sscanf(buffer, "%d %[^\n]",
            &(*lista)[i].id,
            (*lista)[i].name
            );
        i++;
    }
    *totalClientes = linhas;
    fclose(f);
    return 1;
}
