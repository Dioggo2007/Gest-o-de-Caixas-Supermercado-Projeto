//
// Created by pache on 13/05/2026.
//

#include <windows.h>

#include "../../header/logic/simulationControl.h"

#include <math.h>

#include "../../header/frame/menuPrints.h"
#include "../../header/logic/init.h"
#include "../../header/logic/queueManager.h"
#include "../../header/logic/dataManager.h"

#include <stdio.h>

void startSimulation(int *time, FilaCaixa *filaCaixa, int *totalCaixasAbertas, float *vendas, Dados config, Fila *clientesEmCompras, int *clienteAtivos, Cliente *clientes, int numClientes, Produto *produtos, int numTotalProdutos, Funcionario *funcionarios, int totalFuncionarios) {
    int endTime = 0;
    int velSec = 1;

    //possibilidade de ser probabilidade maior que 100%
    int clientProb = 0;

    //Desenpenho
    int duracao = 0;
    int totalClientesCaixas = 0; //Total de Clientes nas Filas da Caixa
    float mediaClientesCaixas = 0; //Media de Clientes nas filas das Caixas
    int nProdutosOferecidos = 0;
    float valorProdutosOferecidos = 0.0;
    int vendasIniciais = *vendas;

    //Valores para guardar
    int totalClientesAtendidos = 0;
    int totalProdutosVendidos = 0;
    float somaTempoEspera = 0;

    printf("Quanto tempo quer que a simulação dure em minutos(cada min é 1 seg)?\n");
    scanf("%d", &duracao);
    printf("Qual a velocidade quer que a simulação corra (x alterações por segundo)?\n");
    scanf("%d", &velSec);
    printf("Qual a probabilidade que quer que o cliente apareca a cada segundo?\n");
    scanf("%d", &clientProb);
    endTime = duracao + *time;

    for (int i = 0; i < *totalCaixasAbertas; i++) {
        if (filaCaixa[i].cashier->state)
            totalClientesCaixas += filaCaixa[i].fila->numClients;
    }

    int n;

    while (*time < endTime) {
        system("cls");
        //lógica da simulação



        for (int i = 0; i < velSec; i++) {
            if (*time >= endTime) break;

            int clientesAGerar = clientProb / 100;
            int restoProb = clientProb % 100;

            //Gerar os clientes com 100% de probabilidade
            for(int k = 0; k < clientesAGerar; k++) {
                if (!summonClient(clientes, numClientes, produtos, numTotalProdutos, clientesEmCompras, time))
                    break;
                (*clienteAtivos)++;
            }

            //Gerar cliente com a probabilidade restante
            n = rand() % 100;
            if (n < restoProb) {
                if (!summonClient(clientes, numClientes, produtos, numTotalProdutos, clientesEmCompras, time))
                    break;
                (*clienteAtivos)++;
            }

            //Ler todos os clientes a fazer compras
            ListaCliente *atual = clientesEmCompras->head;
            while (atual != NULL) {
                //Se ja passou o tempo de pegar os produtos
                if ((float)*time - atual->client->tempoChegadaLoja >= atual->client->tempoPegarProdutos) {

                    //Remover da fila da loja
                    if (atual->next) atual->next->prev = atual->prev;
                    else clientesEmCompras->head = atual->prev;
                    if (atual->prev) atual->prev->next = atual->next;
                    else clientesEmCompras->tail = atual->next;
                    clientesEmCompras->numClients--;

                    //Encontrar caixa aberta com menos pessoas e dentro do limite de pessoas
                    int melhorCaixa = -1;
                    int menorFila = 9999;
                    for (int c = 0; c < config.N_CAIXAS; c++) {
                        if (filaCaixa[c].cashier->state == 1 && filaCaixa[c].fila->numClients < menorFila && filaCaixa[c].fila->numClients < config.MAX_FILA) {
                            menorFila = filaCaixa[c].fila->numClients;
                            melhorCaixa = c;
                        }
                    }
                    if (melhorCaixa != -1) {
                        addToQueue(atual->client, filaCaixa[melhorCaixa].fila);
                        atual->client->tempoChegadaFila = (float)*time;
                        totalClientesCaixas++;
                    }
                }
                atual = atual->next;
            }
            //Ler dados das Caixas

            //Calcular media de cliente nas caixas
            if (totalClientesCaixas != 0) {
                mediaClientesCaixas = (float)totalClientesCaixas / (float)*totalCaixasAbertas;
            }

            //LOGICA DE ABRIR CAIXA
            //Se media for >= maxima que uma caixa pode ter
            if (mediaClientesCaixas >= (float)config.MAX_FILA && *totalCaixasAbertas < config.N_CAIXAS) {
                //Encontrar caixa com mais clientes
                int caixaMaisCheia = 0;
                int maiorFila = 0;
                for (int c = 0; c < config.N_CAIXAS; c++) {
                    if (filaCaixa[c].cashier->state == 1 && filaCaixa[c].fila->numClients > maiorFila) {
                        maiorFila = filaCaixa[c].fila->numClients;
                        caixaMaisCheia = c;
                    }
                }
                /*printf("Encontrado caixa comm amsi clientes %d", caixaMaisCheia);*/
                for (int c = 0; c < config.N_CAIXAS; c++) {
                    if (filaCaixa[c].cashier->state == 0) {
                        filaCaixa[c].cashier->state = 1; // Abre a primeira caixa fechada que encontrar
                        *filaCaixa[c].cashier->resp = generateFuncionario(funcionarios, totalFuncionarios);
                        (*totalCaixasAbertas)++;
                        /*printf("Caixa %d aberta", c);*/
                        //Transferir metade dos clientes no fim da fila para a caixa nova
                        int pessoasAMover = maiorFila / 2;
                        for (int p = 0; p < pessoasAMover; p++) {
                            /*printf("%d", p);*/
                            Cliente *clienteMovido = filaCaixa[caixaMaisCheia].fila->tail->client;
                            removeLastFromQueue(filaCaixa[caixaMaisCheia].fila);
                            /*printf("numclientes na caixa cheia %d", filaCaixa[caixaMaisCheia].fila->numClients);*/
                            if (clienteMovido != NULL) {
                                // Como ele vai para uma fila nova, entra normalmente pela ponta
                                addToQueue(clienteMovido, filaCaixa[c].fila);
                            }
                        }
                        break;
                    }
                }
            }

            //Se media for < minimo que uma caixa pode ter e o numero total de caixas abertas seja maior que 1
            if (mediaClientesCaixas < (float)config.MIN_FILA && *totalCaixasAbertas > 1) {

                //Procurar caixa aberta com menos clientes
                int caixaParaFechar = -1;
                int menorQuantidade = 9999;
                for (int c = 0; c < config.N_CAIXAS; c++) {
                    if (filaCaixa[c].cashier->state == 1 && filaCaixa[c].fila-> numClients < menorQuantidade) {
                        menorQuantidade = filaCaixa[c].fila->numClients;
                        caixaParaFechar = c;
                    }
                }
                //Se encontrado fechar a caixa
                if (caixaParaFechar != -1) {
                    filaCaixa[caixaParaFechar].cashier->state = 0;
                    /*filaCaixa[caixaParaFechar].cashier->resp = NULL;*/
                    (*totalCaixasAbertas)--;

                    //Mudar os Cliente da filas
                    while (filaCaixa[caixaParaFechar].fila->numClients > 0) {
                        Cliente *clienteDeslocado = filaCaixa[caixaParaFechar].fila->head->client;
                        removeFromQueue(filaCaixa[caixaParaFechar].fila);

                        // Procurar a melhor caixa aberta para ele
                        int melhorCaixaNova = -1;
                        int menorFilaNova = 9999;
                        for(int c = 0; c < config.N_CAIXAS; c++) {
                            if(filaCaixa[c].cashier->state == 1 && filaCaixa[c].fila->numClients < menorFilaNova) {
                                menorFilaNova = filaCaixa[c].fila->numClients;
                                melhorCaixaNova = c;
                            }
                        }

                        if (melhorCaixaNova != -1) {
                            addToQueue(clienteDeslocado, filaCaixa[melhorCaixaNova].fila);
                        }
                    }
                }
            }

            //Ler clientes na frente da fila das caixas
            for (int c = 0; c < config.N_CAIXAS; c++) {
                if (filaCaixa[c].cashier->state == 1 && filaCaixa[c].fila->head != NULL) {
                    Cliente *clientEmFila = filaCaixa[c].fila->head->client;
                    clientEmFila->tempoPassarProdutos -= 1.0;

                    //Se ja passou o tempo de passar os produtos
                    if (clientEmFila->tempoPassarProdutos <= 0.0) {
                        //O cliente vai sair

                        //Guardar desempenho

                        filaCaixa[c].cashier->totalClientesAtendidos++;
                        filaCaixa[c].cashier->totalProdutosVendidos += clientEmFila->totalProdutos;

                        totalClientesAtendidos++;
                        totalProdutosVendidos += clientEmFila->totalProdutos;
                        somaTempoEspera += (float)*time - clientEmFila->tempoChegadaFila;

                        /*printf("Cliente %s saiu!", clientEmFila->name);*/

                        //Verificar se ficou muito tempo á espera
                        if ((float)*time - clientEmFila->tempoChegadaFila >= (float)config.MAX_ESPERA) {
                            //oferecer 1 produto(mais barato)
                            int nP = 0;
                            float precoP = 999;
                            //Procurar produto mais barato
                            for (int p = 0; p < clientEmFila->totalProdutos; p++) {
                                if (clientEmFila->produtos[p].price < precoP) {
                                    precoP = clientEmFila->produtos[p].price;
                                    nP = p;
                                }
                            }
                            clientEmFila->custoTotalProdutos -= precoP;
                            valorProdutosOferecidos += precoP;
                            nProdutosOferecidos++;
                            /*printf("O cliente %s, levou o produto %s de graça!", clientEmFila->name, clientEmFila->produtos[nP].name);*/
                        }

                        removeFromQueue(filaCaixa[c].fila);
                        *vendas += clientEmFila->custoTotalProdutos;
                        (*clienteAtivos)--;
                        totalClientesCaixas--;

                        free(clientEmFila->produtos);
                        free(clientEmFila);
                    }


                }
            }


            *time += 1;
        }

        /*printf("endTime: %d, time:%d, velSec: %d\n", endTime, *time, velSec);
        printf("Clientes ativos: %d", *clienteAtivos);*/
        printHeader(*time, *totalCaixasAbertas, config.N_CAIXAS, *vendas);
        for(int c = 1; c <= ceil(config.N_CAIXAS / 3.0); c++) {
            printCashiers(c, filaCaixa, config.N_CAIXAS);
        }

        printf("Clientes em compras: %d", clientesEmCompras->numClients);

        /*scanf("%*c");
        scanf("%*c");*/

        Sleep(1000);
    }

    saveSimulationHistory(*time, totalClientesAtendidos, totalProdutosVendidos, somaTempoEspera, *vendas - vendasIniciais, nProdutosOferecidos, valorProdutosOferecidos, clientProb);
    saveSimulationState(*time, *vendas, filaCaixa, config.N_CAIXAS);

    printf("\n\nSimulação terminada! Dados guardados no ficheiro 'historial_simulacoes.csv'.\n");
    Sleep(2000);

    return;
}

int summonClient(Cliente *clientes, int numClientes, Produto *produtos, int numTotalProdutos, Fila *clientesEmCompras, int *tempo) {
    Cliente *novoCliente = malloc(sizeof(Cliente));
    *novoCliente = generateCliente(clientes, numClientes, produtos, numTotalProdutos);
    novoCliente->tempoChegadaLoja = (float)*tempo;

    /*printf("id: %d\n", novoCliente->id);
    printf("nome: %s\n", novoCliente->name);
    printf("tempoChegadaLoja: %.2f\n", novoCliente->tempoChegadaLoja);
    printf("tempoChegadaFila: %.2f\n", novoCliente->tempoChegadaFila);
    printf("tempoEstimadoSaida: %.2f\n", novoCliente->tempoEstimadoSaida);
    printf("totalProdutos: %d\n", novoCliente->totalProdutos);*/

    //Dá return de 0 se der erro
    return addToQueue(novoCliente, clientesEmCompras);

    /*ListaCliente *novoClienteLista = malloc(sizeof(ListaCliente));
    novoClienteLista->client = novoCliente;
    if (clientesEmCompras->numClients == 0) {
        clientesEmCompras->numClients = 1;
        clientesEmCompras->head = novoClienteLista;
        clientesEmCompras->tail = novoClienteLista;
    }else {
        clientesEmCompras->numClients += 1;
        novoClienteLista->next = clientesEmCompras->tail;
        clientesEmCompras->tail->prev = novoClienteLista;
        clientesEmCompras->tail = novoClienteLista;
    }*/
}


