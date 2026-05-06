cmake_minimum_required(VERSION 4.0)
project(Gest_o_de_Caixas_Supermercado_Projeto C)

set(CMAKE_C_STANDARD 11)

add_executable(Gest_o_de_Caixas_Supermercado_Projeto main.c
        header/logic/struct.h
        file/logic/dataManager.c
        header/logic/dataManager.h
        db/)
