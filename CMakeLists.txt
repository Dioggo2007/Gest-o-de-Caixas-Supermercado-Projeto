cmake_minimum_required(VERSION 4.0)
project(Gest_o_de_Caixas_Supermercado_Projeto C)

set(CMAKE_C_STANDARD 11)

add_executable(Gest_o_de_Caixas_Supermercado_Projeto main.c
        header/logic/struct.h
        file/logic/dataManager.c
        header/logic/dataManager.h
        db/
        file/logic/errorlogs.c
        header/logic/errorlogs.h
        file/frame/printError.c
        header/frame/printError.h
        file/logic/queueManager.c
        header/logic/queueManager.h
        file/logic/init.c
        header/logic/init.h
        file/frame/menuPrints.c
        header/frame/menuPrints.h
        file/logic/simulationControl.c
        header/logic/simulationControl.h)
