//
// Created by pache on 13/05/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_SIMULATIONCONTROL_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_SIMULATIONCONTROL_H

#include "struct.h"

void startSimulation(int *time, FilaCaixa *filaCaixa, int *totalCaixasAbertas, float *vendas, Dados config, Fila *clientesEmCompras, int *clienteAtivos, Cliente *clientes, int numClientes, Produto *produtos, int numTotalProdutos, Funcionario *funcionarios, int totalFuncionarios);

int summonClient(Cliente *clientes, int numClientes, Produto *produtos, int numTotalProdutos, Fila *clientesEmCompras, int *tempo);

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_SIMULATIONCONTROL_H