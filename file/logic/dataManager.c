//
// Created by pache on 06/05/2026.
//

#include "../../header/logic/dataManager.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../header/logic/errorlogs.h"
#include "../../header/frame/printError.h"

#include "../../header/logic/struct.h"

int countLines(const char *path) {
    FILE *f = fopen(path, "r");
    if (f == NULL) return -1;

    int linhas = 0;
    char buffer[TAMANHO_LINHA];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (buffer[0] != '\n') linhas++;
    }
    fclose(f);
    return linhas;
}

Produto *readProductData(int *totalProdutos) {
    int linhas = countLines(PRODUTOS_PATH);
    if (linhas <= 0) {
        createLog("ERROR", "Nenhum produto encontrado no ficheiro txt");
        /*printf("Erro: Nenhum produto encontrado!\n");
        printf("%*c");*/
        return 0;
    }

    FILE *f = fopen(PRODUTOS_PATH, "r");
    if (f == NULL) {
        createLog("ERROR", "Não foi possivel abrir o ficheiro dos Produtos!");
        return NULL;
    }

    //Alocar memoria
    Produto *lista = (Produto *)malloc(linhas * sizeof(Produto));

    if (lista == NULL)
    {
        createLog("ERROR", "Memória insuficiente para alocar produtos!");
        /*printf("Erro: Memória insuficiente para alocar produtos!\n");
        scanf("%*c");*/
        free(lista);
        fclose(f);
        return NULL;
    }

    // Ler os produtos


    //AVISO PESO LER ATE UMA LETRA EXCLUINDO O X PEGAR NO TIPO DE PESO E DEPOIS OS FLOATS
    char buffer[TAMANHO_LINHA];
    int i = 0;
    char nome[TAMANHO_LINHA];
    char marca[TAMANHO_LINHA];
    char pesoDescricao[TAMANHO_LINHA];
    char tipoPeso[TAMANHO_LINHA];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        sscanf(buffer, "%d %[^[] [%[^]]] %[^a-wy-zA-WY-Z] %[^0-9] %f %f %f",
            &lista[i].id,
            nome,
            marca,
            pesoDescricao,
            tipoPeso,
            &lista[i].price,
            &lista[i].purchaseTime,
            &lista[i].cashierTime
            );

        lista[i].name = malloc(strlen(nome) + 1);
        lista[i].brand = malloc(strlen(marca) + 1);
        lista[i].weight = malloc(strlen(pesoDescricao) + strlen(tipoPeso) + 1);

        if (lista[i].name == NULL || lista[i].brand == NULL) {
            createLog("ERROR", "Memória insuficiente para alocar produtos!");
            free(lista);
            fclose(f);
            return NULL;
        }

        strcpy(lista[i].name, nome);
        strcpy(lista[i].brand, marca);
        strcat(pesoDescricao, tipoPeso);
        strcpy(lista[i].weight, pesoDescricao);

        i++;
    }
    *totalProdutos = linhas;
    fclose(f);
    return lista;
}

Funcionario *readFuncionario(int *totalFuncionarios) {
    int linhas = countLines(FUNCIONARIOS_PATH);
    if (linhas <= 0) {
        createLog("ERROR", "Nenhum funcionario encontrado no ficheiro txt");
        /*printf("Erro: Nenhum funcionario encontrado!\n");
        printf("%*c");*/
        return NULL;
    }

    FILE *f = fopen(FUNCIONARIOS_PATH, "r");
    if (f == NULL) {
        createLog("ERROR", "Não foi possivel abrir o ficheiro de funcionarios!");
        return NULL;
    }

    //Alocar memoria
    Funcionario *lista = (Funcionario *)malloc(linhas * sizeof(Funcionario));
    if (lista == NULL)
    {
        createLog("ERROR", "Memória insuficiente para alocar funcionarios!");
        /*printf("Erro: Memória insuficiente para alocar funcionarios!\n");
        scanf("%*c");*/
        fclose(f);
        free(lista);
        return NULL;
    }

    // Ler os produtos
    char buffer[TAMANHO_LINHA];
    int i = 0;
    char nome[TAMANHO_LINHA];

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        sscanf(buffer, "%d %[^\n]",
            &lista[i].id,
            nome
            );
        lista[i].name = malloc(strlen(nome) + 1);
        if (lista[i].name == NULL) {
            createLog("ERROR", "Memória insuficiente para alocar funcionarios!");
            fclose(f);
            free(lista);
            return NULL;
        }

        strcpy(lista[i].name, nome);

        i++;
    }
    *totalFuncionarios = linhas;
    fclose(f);
    return lista;
}

Cliente *readClient(int *totalClientes) {
    int linhas = countLines(CLIENTES_PATH);
    if (linhas <= 0) {
        createLog("ERROR", "Nenhum cliente encontrado no ficheiro txt");
        /*printf("Erro: Nenhum cliente encontrado!\n");
        printf("%*c");*/
        return 0;
    }

    FILE *f = fopen(CLIENTES_PATH, "r");
    if (f == NULL) {
        createLog("ERROR", "Não foi possivel abrir o ficheiro de clientes!");
        return 0;
    }

    //Alocar memoria
    Cliente *lista = (Cliente *)malloc(linhas * sizeof(Cliente));
    if (lista == NULL)
    {
        createLog("ERROR", "Memória insuficiente para alocar clientes");
        /*printf("Erro: Memória insuficiente para alocar clientes\n");
        scanf("%*c");*/
        fclose(f);
        free(lista);
        return 0;
    }

    // Ler os produtos
    char buffer[TAMANHO_LINHA];
    int i = 0;
    char nome[TAMANHO_LINHA];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        sscanf(buffer, "%d %[^\n]",
            &lista[i].id,
            nome
            );

        lista[i].name = malloc(strlen(nome) + 1);
        if (lista[i].name == NULL) {
            createLog("ERROR", "Memória insuficiente para alocar Clientes!");
            fclose(f);
            free(lista);
            return NULL;
        }

        strcpy(lista[i].name, nome);

        i++;
    }
    *totalClientes = linhas;
    fclose(f);
    return lista;
}

Dados readConfig() {
    Dados dados;
    dados.MAX_ESPERA = 120;
    dados.N_CAIXAS = 6;
    dados.TEMPO_ATENDIMENTO = 6;
    dados.MAX_PRECO = 40;
    dados.MAX_FILA = 7;
    dados.MIN_FILA = 3;

    int linhas = countLines(CONFIG_PATH);
    if (linhas <= 0) {
        createLog("WARNING", "Está vazio ou não foi encontrado o ficheiro txt de configurações ficheiro txt!");
        printError("Erro ao ler o ficheiro de configuração! Ira ser criado um novo com configurações padrão");
        scanf("%*c");
        return dados;
    }
    FILE *f = fopen(CONFIG_PATH, "r");
    if (f == NULL) {
        createLog("WARNING", "Não foi possivel abrir o ficheiro de configurações!");
        printError("Erro ao ler o ficheiro de configuração! Ira ser criado um novo com configurações padrão");
        scanf("%*c");
        return dados;
    }

    char label[50];
    int value;

    while (fscanf(f, "%s %d", label, &value) != EOF) {
        if (strcmp(label, "MAX_ESPERA") == 0) {
            dados.MAX_ESPERA = value;
        } else if (strcmp(label, "N_CAIXAS") == 0) {
            dados.N_CAIXAS = value;
        } else if ( strcmp(label, "TEMPO_ATENDIMENTO_PRODUTO") == 0) {
            dados.TEMPO_ATENDIMENTO = value;
        } else if (strcmp(label, "MAX_PRECO") == 0) {
            dados.MAX_PRECO = value;
        } else if (strcmp(label, "MAX_FILA") == 0) {
            dados.MAX_FILA = value;
        } else if (strcmp(label, "MIN_FILA") == 0) {
            dados.MIN_FILA = value;
        }
    }

    fclose(f);
    return dados;
}