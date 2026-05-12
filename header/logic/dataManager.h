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
#define CONFIG_PATH "db/config.txt"
#define TAMANHO_LINHA 100

//Função util para contar linhas e diminuir linhas de codigo repetidas
int countLines(const char *path);

// Ler e carregar os produtos do ficheiro produtos.txt
// Retorna lista se sucesso, NULL se erro
Produto *readProductData(int *totalProdutos);

// Ler e carregar os produtos do ficheiro produtos.txt
// Retorna 1 se sucesso, 0 se erro
Funcionario *readFuncionario(int *totalFuncionarios);

// Ler e carregar os produtos do ficheiro produtos.txt
// Retorna 1 se sucesso, 0 se erro
Cliente *readClient(int *totalClientes);

// Ler e carregar os dados de configuração do ficheiro config.txt
// Retorna 1 se sucesso, 0 se erro
Dados readConfig();

// Escrever novos dados de configuração no ficheiro config.txt
// Retorna 1 se sucesso, 0 se erro
int writeConfig(Dados *config);

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_DATAMANAGER_H