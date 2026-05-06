//
// Created by pache on 07/04/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_STRUCT_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_STRUCT_H

typedef struct {
    int id;
    char name[50];
    char brand[50];
    int weight;
    float price;
    float purchaseTime;
    float cashierTime;
}Produto;

typedef struct {
    int id;
    char name[50];
}Cliente;

typedef struct {
    int id;
    char name[50];
}Funcionario;

typedef struct {
    int id;
}ListaCaixa;

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_STRUCT_H