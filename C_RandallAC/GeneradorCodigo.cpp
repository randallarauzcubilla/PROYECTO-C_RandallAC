#include "pch.h"
#include "GeneradorCodigo.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_NOMBRE 50

GeneradorCodigo::GeneradorCodigo() : cabeza(nullptr), cola(nullptr), cabezaFueraMain(nullptr), colaFueraMain(nullptr) {
    agregar("int main() {", false);
}

GeneradorCodigo::~GeneradorCodigo() {
    limpiar();
}

bool GeneradorCodigo::contiene(const char* texto) {
    NodoCodigo* actual = cabeza;
    while (actual != nullptr) {
        if (strcmp(actual->linea, texto) == 0)
            return true;
        actual = actual->siguiente;
    }

    NodoCodigo* actualFuera = cabezaFueraMain;
    while (actualFuera != nullptr) {
        if (strcmp(actualFuera->linea, texto) == 0)
            return true;
        actualFuera = actualFuera->siguiente;
    }

    return false;
}

void GeneradorCodigo::agregar(const char* instruccionCpp, bool indentar) {
    char lineaFinal[MAX_LINEA_GENERADOR] = { 0 };

    if (indentar) {
        snprintf(lineaFinal, MAX_LINEA_GENERADOR, "    %s", instruccionCpp);
    }
    else {
        strncpy(lineaFinal, instruccionCpp, MAX_LINEA_GENERADOR - 1);
        lineaFinal[MAX_LINEA_GENERADOR - 1] = '\0';
    }

    NodoCodigo* nuevoNodo = new NodoCodigo;
    strncpy(nuevoNodo->linea, lineaFinal, MAX_LINEA_GENERADOR - 1);
    nuevoNodo->linea[MAX_LINEA_GENERADOR - 1] = '\0';
    nuevoNodo->siguiente = nullptr;

    if (cabeza == nullptr) {
        cabeza = cola = nuevoNodo;
    }
    else {
        cola->siguiente = nuevoNodo;
        cola = nuevoNodo;
    }
}

void GeneradorCodigo::finalizar() {
    if (!contiene("}")) {
        agregar("return 0;", true);
        agregar("}", true);
    }
}

void GeneradorCodigo::imprimirCodigo() {
    NodoCodigo* actualFuera = cabezaFueraMain;
    while (actualFuera != nullptr) {
        std::cout << actualFuera->linea << std::endl;
        actualFuera = actualFuera->siguiente;
    }

    NodoCodigo* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->linea << std::endl;
        actual = actual->siguiente;
    }
}

void GeneradorCodigo::limpiar() {
    NodoCodigo* actual = cabeza;
    while (actual != nullptr) {
        NodoCodigo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = cola = nullptr;

    NodoCodigo* actualFuera = cabezaFueraMain;
    while (actualFuera != nullptr) {
        NodoCodigo* siguiente = actualFuera->siguiente;
        delete actualFuera;
        actualFuera = siguiente;
    }
    cabezaFueraMain = colaFueraMain = nullptr;
}


void GeneradorCodigo::generarLlamadaFuncion(const char* nombre, const char* parametrosRaw, char* llamadaCpp) {
    strcpy(llamadaCpp, nombre);
    strcat(llamadaCpp, "(");

    if (parametrosRaw[0] != '\0') {
        char copia[MAX_LINEA_GENERADOR];
        strcpy(copia, parametrosRaw);
        char* token = strtok(copia, ",");

        while (token != NULL) {
            char tipo[MAX_NOMBRE] = { 0 };
            sscanf_s(token, "%49s", tipo, (unsigned)_countof(tipo));

            // Convertir a minúscula
            for (int i = 0; tipo[i]; ++i) tipo[i] = tolower(tipo[i]);

            if (strcmp(tipo, "entero") == 0) strcat(llamadaCpp, "0, ");
            else if (strcmp(tipo, "decimal") == 0) strcat(llamadaCpp, "0.0, ");
            else if (strcmp(tipo, "caracter") == 0) strcat(llamadaCpp, "' ', ");
            else if (strcmp(tipo, "booleana") == 0 || strcmp(tipo, "boolean") == 0) strcat(llamadaCpp, "false, ");

            token = strtok(NULL, ",");
        }

        size_t len = strlen(llamadaCpp);
        if (len >= 2) llamadaCpp[len - 2] = '\0';  // quitar última coma
    }

    strcat(llamadaCpp, ");");
}

void GeneradorCodigo::agregarFueraMain(const char* instruccionCpp) {
    if (contiene(instruccionCpp)) return;

    NodoCodigo* nuevoNodo = new NodoCodigo;
    strncpy(nuevoNodo->linea, instruccionCpp, MAX_LINEA_GENERADOR - 1);
    nuevoNodo->linea[MAX_LINEA_GENERADOR - 1] = '\0';
    nuevoNodo->siguiente = nullptr;

    if (colaFueraMain != nullptr) {
        colaFueraMain->siguiente = nuevoNodo;
        colaFueraMain = nuevoNodo;
    }
    else {
        cabezaFueraMain = colaFueraMain = nuevoNodo;
    }
}

void GeneradorCodigo::generarArchivo(const char* nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir archivo para escribir: " << nombreArchivo << std::endl;
        return;
    }
    archivo << "#include <iostream>\n";
    archivo << "using namespace std;\n\n";
    // Primero imprimir funciones fuera del main
    NodoCodigo* actualFuera = cabezaFueraMain;
    while (actualFuera != nullptr) {
        archivo << actualFuera->linea << std::endl;
        actualFuera = actualFuera->siguiente;
    }

    // Luego imprimir el main y su contenido
    NodoCodigo* actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->linea << std::endl;
        actual = actual->siguiente;
    }

    archivo.close();
}