//
// Created by pache on 06/05/2026.
//

#include "../../header/logic/dataManager.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../header/logic/errorlogs.h"
#include "../../header/frame/printError.h"
#include "../../header/logic/init.h"
#include "../../header/logic/queueManager.h"

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
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (buffer[0] == '\n') continue;
        sscanf(buffer, "%d %[^[] [%[^]]] %[^\t] %f %f %f",
            &lista[i].id,
            nome,
            marca,
            pesoDescricao,
            &lista[i].price,
            &lista[i].purchaseTime,
            &lista[i].cashierTime
            );

        lista[i].name = malloc(strlen(nome) + 1);
        lista[i].brand = malloc(strlen(marca) + 1);
        lista[i].weight = malloc(strlen(pesoDescricao) + 1);

        if (lista[i].name == NULL || lista[i].brand == NULL) {
            createLog("ERROR", "Memória insuficiente para alocar produtos!");
            free(lista);
            fclose(f);
            return NULL;
        }

        strcpy(lista[i].name, nome);
        strcpy(lista[i].brand, marca);
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
        if (buffer[0] == '\n') continue;
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
        if (buffer[0] == '\n') continue;
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
        lista[i].tempoChegadaLoja = 0.0;
        lista[i].tempoChegadaFila = 0.0;
        lista[i].tempoPassarProdutos = 2.0;
        lista[i].tempoPegarProdutos = 0.0;
        lista[i].totalProdutos = 0;
        lista[i].custoTotalProdutos = 0;
        lista[i].produtos = NULL;

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

int saveSimulationHistory(int tempo, int clientesAtendidos, int produtosVendidos, float tempoMedio, float vendas, int nProdutosOferecidos, float valorProdutosOferecidos, int clientProb) {
    FILE *f = fopen(SIMULATIONHISTORY_PATH, "a");

    if (!f) {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char data_hora[20];
    strftime(data_hora, sizeof(data_hora), "%d-%m-%Y-%H:%M:%S", t);

    fprintf(f, "%s; %d; %d; %d; %.2f; %.2f; %d; %.2f; %d\n", data_hora, tempo, clientesAtendidos, produtosVendidos, tempoMedio/clientesAtendidos, vendas, nProdutosOferecidos, valorProdutosOferecidos, clientProb);

    fclose(f);
    return 1;
}

int readSimulationHistory() {
    FILE *f = fopen(SIMULATIONHISTORY_PATH, "r");
    if (!f) {
        // Error in file opening
        printf("Can't open file\n");
        return 0;
    }
    system("cls");
    printf("\n");
    printf("============================================================================================================================\n");
    printf("|                                                HISTORICO DE SIMULACOES                                                   |\n");
    printf("============================================================================================================================\n");
    printf("| %-12s | %-8s | %-12s | %-12s | %-12s | %-10s | %-12s | %-12s | %-12s\n",
           "Data", "Tempo", "Clientes", "Produtos", "Tempo Medio", "Vendas ($)", "Prod. Ofer.", "Valor Ofer.", "Prob. Cliente");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");

    char buffer[1024];

    int row = 0;

    while (fgets(buffer,sizeof(buffer), f) != NULL) {
        if (buffer[0] == '\n') continue;
        //Se for colocado uma linha com os nomes da colunas
        /*if (row == 1)
            continue;*/
        char data[20];
        int tempo;
        int clientesAtendidos;
        int produtosVendidos;
        float tempoMedio;
        float vendas;
        int nProdutosOferecidos;
        float valorProdutosOferecidos;
        int clientProb;

        sscanf(buffer, "%[^;]; %d; %d; %d; %f; %f; %d; %f; %d",
        data,
        &tempo,
        &clientesAtendidos,
        &produtosVendidos,
        &tempoMedio,
        &vendas,
        &nProdutosOferecidos,
        &valorProdutosOferecidos,
        &clientProb
        );

        printf("| %-12s | %8d | %12d | %12d | %12.2f | %10.2f | %12d | %12.2f | %12d |\n",
                   data,
                   tempo,
                   clientesAtendidos,
                   produtosVendidos,
                   tempoMedio,
                   vendas,
                   nProdutosOferecidos,
                   valorProdutosOferecidos,
                   clientProb);
        row++;
    }

    if (row > 0) {
        printf("  Total de registos carregados: %d\n", row);
    } else {
        printf("  Nenhum registo de simulacao encontrado no ficheiro.\n");
    }
    printf("\n");

    // Close the file
    fclose(f);

    printf("Enter para continuar...");
    scanf("%*c");
    scanf("%*c");
    return 1;
}

int saveSimulationState(int tempo, float vendas, FilaCaixa *fila_caixa, int nCaixas) {
    FILE *f = fopen(SIMULATIONDATA_PATH, "w");
    if (!f) {
        createLog("ERROR", "Nao foi possivel abrir/criar o ficheiro db/dados.txt para guardar o estado.");
        return 0;
    }

    fprintf(f, "TEMPO: %d\n", tempo);
    fprintf(f, "VENDAS: %.2f\n", vendas);
    fprintf(f, "TOTAL_CAIXAS: %d\n", nCaixas);

    for (int i = 0; i < nCaixas; i++) {
        //Guardar estado, totalClientes atendidos e total produtos vendidos
        fprintf(f, "Caixa%d: %d, %d, %d\n", i + 1, fila_caixa[i].cashier->state, fila_caixa[i].cashier->totalClientesAtendidos, fila_caixa[i].cashier->totalProdutosVendidos);
        fprintf(f, "%d\n", fila_caixa[i].fila->numClients); // Número de clientes na fila

        // 3. Guardar os clientes que estão dentro desta fila
        ListaCliente *atual = fila_caixa[i].fila->head;
        while (atual != NULL) {
            // Guardamos o id e o número de produtos de cada um, e o tempo que chegou á fila
            fprintf(f, "P%d: %d, %f\n", atual->client->id, atual->client->totalProdutos, atual->client->tempoChegadaFila);
            atual = atual->prev;
        }
    }
    fclose(f);
    return 1;
}

int readSimulationState(FilaCaixa *filaCaixas, int *totalCaixasAbertas, Cliente *clientes, int numClientes, Produto *produtos, int numTotalProdutos, Funcionario *funcionarios, int totalFuncionarios, int *tempoGlobal, float *vendasGlobais) {
    FILE *f = fopen(SIMULATIONDATA_PATH, "r");
    if (!f) {
        createLog("WARNING", "Nao foi possivel abrir/criar o ficheiro db/dados.txt para guardar o estado.");
        return 0;
    }

    char buffer[TAMANHO_LINHA];
    int totalCaixasArquivo = 0;
    *totalCaixasAbertas = 0;

    if (fgets(buffer, sizeof(buffer), f)) sscanf(buffer, "TEMPO: %d", tempoGlobal);
    if (fgets(buffer, sizeof(buffer), f)) sscanf(buffer, "VENDAS: %f", vendasGlobais);
    if (fgets(buffer, sizeof(buffer), f)) sscanf(buffer, "TOTAL_CAIXAS: %d", &totalCaixasArquivo);

    for (int i = 0; i < totalCaixasArquivo; i++) {
        int idCaixa, estadoCaixa, clientesAtendidos, produtosVendidos = 0;

        if (fgets(buffer, sizeof(buffer), f)) {
            sscanf(buffer, "Caixa%d: %d, %d, %d", &idCaixa, &estadoCaixa, &clientesAtendidos, &produtosVendidos);

            int index = idCaixa - 1;

            filaCaixas[index].cashier->state = estadoCaixa;
            filaCaixas[index].cashier->totalClientesAtendidos = clientesAtendidos;
            filaCaixas[index].cashier->totalProdutosVendidos = produtosVendidos;

            if (estadoCaixa == 1) {
                *filaCaixas[index].cashier->resp = generateFuncionario(funcionarios, totalFuncionarios);
                (*totalCaixasAbertas)++;
            }

            int numClientesFila = 0;
            if (fgets(buffer, sizeof(buffer), f)) {
                sscanf(buffer, "%d", &numClientesFila);
            }

            for (int c = 0; c < numClientesFila; c++) {
                int idCliente;
                int nProdutos;
                float tempoChegadaFila;

                if (fgets(buffer, sizeof(buffer), f)) {
                    sscanf(buffer, "P%d: %d, %f", &idCliente, &nProdutos, &tempoChegadaFila);

                    Cliente *clientLido = malloc(sizeof(Cliente));

                    for (int j = 0; j < numClientes; j++) {
                        if (clientes[j].id == idCliente) {
                            *clientLido = clientes[j];
                        }
                    }
                    if (clientLido->id != idCliente) {
                        free(clientLido);
                        return 0;
                    }

                    clientLido->totalProdutos = nProdutos;
                    clientLido->produtos = generateProductList(produtos, numTotalProdutos, &clientLido->totalProdutos);
                    clientLido->tempoChegadaFila = tempoChegadaFila;
                    //calculo de tempo a pegar nos produtos e custo total
                    for (int p = 0; p < clientLido->totalProdutos; p++) {
                        clientLido->tempoPegarProdutos += clientLido->produtos[p].purchaseTime/60;
                        clientLido->custoTotalProdutos += clientLido->produtos[p].price;
                    }
                    //Calculo de tempo a passar os produtos na caixa
                    for (int p = 0; p < clientLido->totalProdutos; p++) {
                        clientLido->tempoPassarProdutos += clientLido->produtos[p].cashierTime /60;
                    }
                    addToQueue(clientLido, filaCaixas[index].fila);
                }
            }
        }
    }
    return 1;
}
