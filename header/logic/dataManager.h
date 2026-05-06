//
// Created by pache on 06/05/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_DATAMANAGER_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_DATAMANAGER_H

#include <stdio.h>

#include "struct.h"

#define PRODUTOS_PATH "db/produtos.txt"
#define FUNCIONARIOS_PATH "db/funcionarios.txt"
#define CLIENTES_PATH "db/clientes.txt"
#define TAMANHO_LINHA 100

int countLines(const char *path);

// Ler e carregar os produtos do ficheiro produtos.txt
// Retorna 1 se sucesso, 0 se erro
int readProductData(Produto **lista, int *totalProdutos);

// Ler e carregar os produtos do ficheiro produtos.txt
// Retorna 1 se sucesso, 0 se erro
int readFuncionario(Funcionario **lista, int *totalFuncionarios);

// Ler e carregar os produtos do ficheiro produtos.txt
// Retorna 1 se sucesso, 0 se erro
int readClient(Cliente **lista, int *totalClientes);


#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_DATAMANAGER_H