//
// Created by pache on 07/04/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_STRUCT_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_STRUCT_H

typedef struct {
    int id;
    char *name;
    char *brand;
    char *weight;
    float price;
    float purchaseTime;
    float cashierTime;
}Produto;

typedef struct {
    int id;
    char *name;
    float tempoChegadaFila;//Tempo que demorou a pegar nos produtos da loja
    float tempoEstimadoSaida;//Calculos dos
} Cliente;

typedef struct {
    int id;
    char *name;
}Funcionario;

typedef struct {
    int id;
    int state; // 1: Aberto; 0: Fechado
    Funcionario *resp;
}Caixa;

typedef struct clientList { // "No" dos Clientes
    Cliente *client;
    struct clientList *next;
    struct clientList *prev;
}ListaCliente;

typedef struct {
    int numClients;
    ListaCliente *head;
    ListaCliente *tail;
} Fila;

typedef struct { //Hashing, ordenar pela caixa
    Caixa *cashier;
    Fila *fila;
}FilaCaixa;

typedef struct {
    int MAX_ESPERA;
    int N_CAIXAS;
    int TEMPO_ATENDIMENTO;
    int MAX_PRECO;
    int MAX_FILA;
    int MIN_FILA;
}Dados;

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_STRUCT_H