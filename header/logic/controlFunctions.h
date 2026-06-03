//
// Created by pache on 31/05/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_CONTROLFUNCTIONS_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_CONTROLFUNCTIONS_H

#include "struct.h"
#include "../frame/menuPrints.h"
#include  "init.h"

//Funções para clientes
void searchClientId(Fila *clientesEmCompra, FilaCaixa *fila_caixa, Dados config);
void searchClientName(Fila *clientesEmCompra, FilaCaixa *fila_caixa, Dados config);

//Funções para Caixas
void calcularEstatisticasCaixas(FilaCaixa *filaCaixas, int nCaixas);
void changeWorker(FilaCaixa *fila_caixa, int nCaixas, Funcionario *funcionarios, int totalFuncionarios);
void changeCashierState(FilaCaixa *fila_caixa, int nCaixas, Funcionario *funcionarios, int totalFuncionarios);

void calcularMemoria(int totalProdutos, int totalClientes, int totalFuncionarios, int totalCaixas, Fila *corredor);

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_CONTROLFUNCTIONS_H