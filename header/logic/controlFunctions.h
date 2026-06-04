//
// Created by pache on 31/05/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_CONTROLFUNCTIONS_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_CONTROLFUNCTIONS_H

#include "struct.h"
#include "../frame/menuPrints.h"
#include  "init.h"

//Funções Simulador
void clearSimulation(int *time, FilaCaixa *fila_caixa, int *totalCaixasAbertas ,float *vendas, Dados config, Fila *clientes_corredor, int *clienteAtivos, Funcionario *funcionarios, int totalFuncionarios);

//Funções para clientes
void searchClientId(Fila *clientesEmCompra, FilaCaixa *fila_caixa, Dados config);
void searchClientName(Fila *clientesEmCompra, FilaCaixa *fila_caixa, Dados config);

//Funções para Caixas
void calcularEstatisticasCaixas(FilaCaixa *filaCaixas, int nCaixas);
void changeWorker(FilaCaixa *fila_caixa, int nCaixas, Funcionario *funcionarios, int totalFuncionarios);
void changeCashierState(FilaCaixa *fila_caixa, int nCaixas, Funcionario *funcionarios, int totalFuncionarios);

//Funções para CLientes

void addClient(Cliente *clientes, int numClientes, Produto *produtos, int totalProdutos, Fila *clientes_corredor, FilaCaixa *fila_caixas, Dados config, int tempo);
void removeClient(FilaCaixa *fila_caixa, int nCaixas, Fila *clientes_corredor);

void calcularMemoria(int totalProdutos, int totalClientes, int totalFuncionarios, int totalCaixas, Fila *corredor);



#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_CONTROLFUNCTIONS_H