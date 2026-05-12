//
// Created by pache on 06/05/2026.
//

#ifndef GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_ERRORLOGS_H
#define GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_ERRORLOGS_H

//Criar um ficheiro ou adicionar ao ficheiro uma linha de erro ou aviso(ERROR/WARNING)
void createLog(char *nivel, char *mensagem);

/*
 * Exemplos:
 * createLog("ERROR", "Nenhum produto encontrado no ficheiro txt");
 * createLog("ERROR", "Memória insuficiente para alocar produtos!");
 * createLog("WARNING", "Não foi possivel abrir o ficheiro de configurações!");
 */

#endif //GEST_O_DE_CAIXAS_SUPERMERCADO_PROJETO_ERRORLOGS_H