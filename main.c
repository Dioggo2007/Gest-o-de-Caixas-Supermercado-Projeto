#include <stdio.h>
#include "header/logic/struct.h"
#include "header/logic/dataManager.h"

#ifdef _WIN32
#include <windows.h>
#endif



int main(void) {
    #ifdef _WIN32
        SetConsoleOutputCP(65001); // Define a consola para UTF-8
    #endif

    //Inicializar as variaveis principais
    Produto *produtos;
    int totalProdutos = 0;
    Cliente *clientes;
    int totalClientes = 0;
    Funcionario *funcionarios;
    int totalFuncionarios = 0;

    if (!readProductData(&produtos, &totalProdutos)) {
        printf("Erro ao ler os produtos do ficheiro.");
        scanf("%*c");
        return 0;
    }

    if (!readFuncionario(&funcionarios, &totalFuncionarios)) {
        printf("Erro ao ler os funcionarios do ficheiro.");
        scanf("%*c");
        return 0;
    }

    if (!readClient(&clientes, &totalClientes)) {
        printf("Erro ao ler os clientes do ficheiro.");
        scanf("%*c");
        return 0;
    }
    for (int i = 0; i < 10; i++) {
        printf("Funcionario %d:\n", i + 1);
        printf("id: %d\n", funcionarios[i].id);
        printf("nome: %s\n", funcionarios[i].name);
    }
    for (int i = 0; i < 10; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("id: %d\n", clientes[i].id);
        printf("nome: %s\n", clientes[i].name);
    }
    for (int i = 0; i < 10; i++) {
        printf("Produto %d:\n", i + 1);
        printf("id: %d\n", produtos[i].id);
        printf("nome: %s\n", produtos[i].name);
        printf("brand: %s\n", produtos[i].brand);
        printf("weight: %d\n", produtos[i].weight);
        printf("price: %.2f\n", produtos[i].price);
        printf("purchaseTime: %.2f\n", produtos[i].purchaseTime);
        printf("cashierTime: %.2f\n", produtos[i].cashierTime);
    }

    scanf("%*c");
    return 0;
}