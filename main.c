#include <stdio.h>
#include "header/logic/struct.h"
#include "header/logic/dataManager.h"
#include "header/frame/printError.h"
#include "header/frame/menuPrints.h"
#include "header/logic/init.h"
#include "header/logic/simulationControl.h"

#include <time.h>

#include "header/logic/controlFunctions.h"
#ifdef _WIN32
#include <windows.h>
#endif



int main(void) {
    #ifdef _WIN32
        SetConsoleOutputCP(65001); // Define a consola para UTF-8
    #endif

    srand(time(NULL));

    //Inicializar as variaveis principais
    int totalProdutos = 0;
    Produto *produtos = readProductData(&totalProdutos);
    if (produtos == NULL) {
        printError("Erro ao ler os produtos do ficheiro! Verifique o ficheiro de logs.");
        return 0;
    }

    int totalClientes = 0;
    Cliente *clientes = readClient(&totalClientes);
    if (clientes == NULL) {
        printError("Erro ao ler os clientes do ficheiro! Verifique o ficheiro de logs.");
        return 0;
    }

    int totalFuncionarios = 0;
    Funcionario *funcionarios = readFuncionario(&totalFuncionarios);
    if (funcionarios == NULL) {
        printError("Erro ao ler os funcionarios do ficheiro! Verifique o ficheiro de logs.");
        return 0;
    }

    int totalCaixasAbertas = 1;
    Dados config = readConfig();

    float vendas = 0;

    int page = 1;

    int tempo = 0;
    int clienteAtivos = 0;
    Fila *clientesEmCompra = createShoppingClientList();

    int sair = 1;

    //Inicializar as caixas com as filas
    FilaCaixa *filaCaixas = createFilaCaixa(config.N_CAIXAS);
    if (filaCaixas == NULL) {
        printError("Erro ao inicializar as Caixas! Verifique o ficheiro de logs.");
        return 0;
    }
    filaCaixas[0].cashier->state = 1;
    *filaCaixas[0].cashier->resp = generateFuncionario(funcionarios, totalFuncionarios);

    int d = 0;
    printf("Pretende ler os dados da simulação anterior('1' se sim)?");
    scanf("%d", &d);
    if (d == 1)
        readSimulationState(filaCaixas, &totalCaixasAbertas, clientes, totalClientes, produtos, totalProdutos, funcionarios, totalFuncionarios, &tempo, &vendas);

    do {
        system("cls");

        printHeader(tempo, totalCaixasAbertas, config.N_CAIXAS, vendas);
        printCashiers(page, filaCaixas, config.N_CAIXAS);

        switch (escolherOpcaoMenuPrincipal(0, printFooter(0))) {
            case 1://Simulação
                system("cls");
                printHeader(tempo, totalCaixasAbertas, config.N_CAIXAS, vendas);
                printCashiers(page, filaCaixas, config.N_CAIXAS);
                switch (escolherOpcaoMenuPrincipal(0, printFooter(1))) {
                    case 1:
                        system("cls");
                        startSimulation(&tempo, filaCaixas, &totalCaixasAbertas, &vendas, config, clientesEmCompra, &clienteAtivos, clientes, totalClientes, produtos, totalProdutos, funcionarios, totalFuncionarios);
                    default:
                        break;
                }
                break;
            case 2://Caixas
                system("cls");
                printHeader(tempo, totalCaixasAbertas, config.N_CAIXAS, vendas);
                printCashiers(page, filaCaixas, config.N_CAIXAS);
                switch (escolherOpcaoMenuPrincipal(0, printFooter(2))) {
                    case 3:
                        printCashierClients(filaCaixas, config.N_CAIXAS);
                        break;
                    default:
                        break;
                }
                break;
            case 3://Cliente
                system("cls");
                printHeader(tempo, totalCaixasAbertas, config.N_CAIXAS, vendas);
                printCashiers(page, filaCaixas, config.N_CAIXAS);
                switch (escolherOpcaoMenuPrincipal(0, printFooter(3))) {
                    case 1:
                        searchClientName(clientesEmCompra, filaCaixas, config);
                        break;
                    case 2:
                        searchClientId(clientesEmCompra, filaCaixas, config);
                        break;
                    default:
                        break;
                }
                break;
            case 4://Outras
                system("cls");
                printHeader(tempo, totalCaixasAbertas, config.N_CAIXAS, vendas);
                printCashiers(page, filaCaixas, config.N_CAIXAS);
                switch (escolherOpcaoMenuPrincipal(0, printFooter(4))) {
                    case 1:
                        readSimulationHistory();
                        break;
                    default:
                        break;
                }
                break;
            case 5:
                sair = 0;
            default:
                break;
        }

    }while (sair != 0);
    /*printf("Config:");
    printf("MAX_ESPERA %d\n", config.MAX_FILA);
    printf("N_CAIXAS = %d\n", config.N_CAIXAS);
    printf("TEMPO_ATENDIMENTO %d\n", config.TEMPO_ATENDIMENTO);
    printf("MAX_PRECO = %d\n", config.MAX_PRECO);
    printf("MAX_FILA %d\n", config.MAX_FILA);
    printf("MIN_FILA = %d\n", config.MIN_FILA);*/

    /*for (int i = 0; i < 10; i++) {
        printf("Funcionario %d:\n", i + 1);
        printf("id: %d\n", funcionarios[i].id);
        printf("nome: %s\n", funcionarios[i].name);
    }*/
    /*for (int i = 0; i < 10; i++) {
        Cliente randomCliente = generateCliente(clientes, totalClientes, produtos, totalProdutos);
        printf("Cliente %d:\n", i + 1);
        printf("id: %d\n", randomCliente.id);
        printf("nome: %s\n", randomCliente.name);
        printf("tempoChegadaFila: %f\n", randomCliente.tempoChegadaFila);
        printf("tempoEstimadoSaida: %f\n", randomCliente.tempoEstimadoSaida);
        printf("totalProdutos: %d\n", randomCliente.totalProdutos);
    }*/

    /*int nProdutos;
    Produto *listaProdutos = generateProductList(produtos, totalProdutos, &nProdutos);*/
    for (int i = 0; i < 11; i++) {
        printf("Produto %d:\n", i + 1);
        printf("id: %d\n", produtos[i].id);
        printf("nome: %s\n", produtos[i].name);
        printf("brand: %s\n", produtos[i].brand);
        printf("weight: %s\n", produtos[i].weight);
        printf("price: %.2f\n", (produtos[i].price == 0.00) ? 10000000 : produtos[i].price);
        printf("purchaseTime: %.2f\n", (produtos[i].purchaseTime == 0.00) ? 10000000 : produtos[i].purchaseTime);
        printf("cashierTime: %.2f\n", (produtos[i].cashierTime == 0.00) ? 10000000 : produtos[i].cashierTime);
    }

    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].name) free(produtos[i].name);
        if (produtos[i].brand) free(produtos[i].brand);
        if (produtos[i].weight) free(produtos[i].weight);
    }
    free(produtos);

    for (int i = 0; i < totalClientes; i++) {
        free(clientes[i].name);
        if (clientes[i].produtos != NULL)
            free(clientes[i].produtos);
    }
    free(clientes);

    for(int i = 0; i < totalFuncionarios; i++) {
        free(funcionarios[i].name);
    }
    free(funcionarios);

    scanf("%*c");
    scanf("%*c");

    return 0;
}