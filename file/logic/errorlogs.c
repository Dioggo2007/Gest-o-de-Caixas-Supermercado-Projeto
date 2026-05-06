//
// Created by pache on 06/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../../header/logic/errorlogs.h"

void createLog(char *nivel, char *mensagem){
    char *path = "db/errorlog.txt";

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char data_hora[20];
    strftime(data_hora, sizeof(data_hora), "%d-%m-%Y-%H:%M:%S", t);

    FILE *logFile = fopen(path, "a");

    if (logFile == NULL)
    {
        printf("[SISTEMA] Erro ao aceder ou criar o ficheiro de logs. Verifique se a pasta 'db' existe.\n");
        scanf("%*c");
        return;
    }

    fprintf(logFile, "[%s] [%s] %s\n", data_hora, nivel, mensagem);
    fclose(logFile);
}
