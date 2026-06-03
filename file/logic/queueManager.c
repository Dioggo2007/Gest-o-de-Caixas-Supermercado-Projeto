//
// Created by pache on 07/05/2026.
//

#include "../../header/logic/queueManager.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../header/logic/errorlogs.h"

//Resposta: 1: Correu tudo bem; 0: Erro
int addToQueue(Cliente *client, Fila *fila) {
    ListaCliente *novo = (ListaCliente*)malloc(sizeof(ListaCliente));
    if (novo == NULL) {
        createLog("ERROR", "Memória insuficiente para alocar cliente novo na lista!");
        return 0;
    }

    novo->client = client;
    novo->next = fila->tail;
    novo->prev = NULL;

    if (fila->numClients == 0) {
        fila->head = novo;
    } else {
        fila->tail->prev = novo;
    }

    fila->tail = novo;
    fila->numClients++;

    return 1;
}

int removeFromQueue(Fila *fila) {
    if (fila->numClients == 0 || fila->head == NULL) return 0;

    ListaCliente *listaRemove = fila->head;
    fila->head = listaRemove->prev;
    if (fila->head == NULL) fila->tail = NULL;
    else fila->head->next = NULL;
    fila->numClients--;

    free(listaRemove);
    return 1;
}

int removeSpecificClient(Fila *fila, int idCliente) {
    if (fila->numClients == 0 || fila->head == NULL) return 0;

    ListaCliente *listaRemove = fila->head;
    while (listaRemove != NULL) {
        if (listaRemove->client->id == idCliente) {
            //Se for primeiro
            if (listaRemove == fila->head) {
                fila->head = fila->head->prev;
            }else if (listaRemove == fila->tail) { //Se for ultimo
                listaRemove->next->prev = NULL;
            }else{ //Se tiver no meio
                listaRemove->prev->next = listaRemove->next;
                listaRemove->next->prev = listaRemove->prev;
            }

            fila->numClients--;
            free(listaRemove);
            return 1;
        }
        listaRemove = listaRemove->prev;
    }
    return 0;
}

int removeLastFromQueue(Fila *fila) {
    if (fila->numClients == 0 || fila->tail == NULL) return 0;
    printf("%d", fila->numClients);
    ListaCliente *listaRemove = fila->tail;
    fila->tail = listaRemove->next;
    if (fila->tail == NULL) fila->head = NULL;
    else fila->tail->prev = NULL;
    fila->numClients--;

    free(listaRemove);
    return 1;
}

