//
// Created by pache on 07/05/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_INIT_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_INIT_H

#include "struct.h"

FilaCaixa *createFilaCaixa(int numCaixas);

Produto *generateProductList(Produto *produtos, int numTotalProdutos, int *nProdutos);

Cliente generateCliente(Cliente *clientes, int numClientes, Produto *produtos, int numTotalProdutos);

Funcionario generateFuncionario(Funcionario *funcionarios, int numFuncionarios);

Fila *createShoppingClientList();

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_INIT_H