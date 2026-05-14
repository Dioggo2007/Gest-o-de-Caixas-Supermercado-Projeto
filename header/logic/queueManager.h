//
// Created by pache on 07/05/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_QUEUEMANAGER_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_QUEUEMANAGER_H
#include "struct.h"

//Adicionar Cliente ao fim da fila
int addToQueue(Cliente *client, Fila *fila);

//Remover Cliente da lista
int removeFromQueue(Cliente *client, Fila *fila);

int queueSize(FilaCaixa caixa);

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_QUEUEMANAGER_H