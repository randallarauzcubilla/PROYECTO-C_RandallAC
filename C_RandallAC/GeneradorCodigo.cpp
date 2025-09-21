#include "pch.h"
#include "GeneradorCodigo.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#define _CRT_SECURE_NO_WARNINGS

GeneradorCodigo::GeneradorCodigo() : cabeza(nullptr), cola(nullptr) {
    agregar("#include <iostream>", false);
    agregar("using namespace std;", false);
    agregar("int main() {", false);
}

GeneradorCodigo::~GeneradorCodigo() {
    limpiar();
}

bool GeneradorCodigo::contiene(const char* texto) {
    NodoCodigo* actual = cabeza;
    while (actual != nullptr) {
        if (strstr(actual->linea, texto) != nullptr)
            return true;
        actual = actual->siguiente;
    }
    return false;
}

void GeneradorCodigo::agregar(const char* instruccionCpp, bool indentar) {
    char lineaFinal[MAX_LINEA] = { 0 };

    if (indentar) {
        snprintf(lineaFinal, MAX_LINEA, "    %s", instruccionCpp);
    }
    else {
        strncpy(lineaFinal, instruccionCpp, MAX_LINEA - 1);
        lineaFinal[MAX_LINEA - 1] = '\0';
    }

    NodoCodigo* nuevoNodo = new NodoCodigo;
    strncpy(nuevoNodo->linea, lineaFinal, MAX_LINEA - 1);
    nuevoNodo->linea[MAX_LINEA - 1] = '\0';
    nuevoNodo->siguiente = nullptr;

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    }
    else {
        cola->siguiente = nuevoNodo;
        cola = nuevoNodo;
    }
}

void GeneradorCodigo::finalizar() {
    agregar("return 0;", true);
    agregar("}",true);
}


void GeneradorCodigo::imprimirCodigo() {
    NodoCodigo* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->linea << std::endl;
        actual = actual->siguiente;
    }
}

void GeneradorCodigo::generarArchivo(const char* nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir archivo para escribir: " << nombreArchivo << std::endl;
        return;
    }

    NodoCodigo* actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->linea << std::endl;
        actual = actual->siguiente;
    }

    archivo.close();
}

void GeneradorCodigo::limpiar() {
    NodoCodigo* actual = cabeza;
    while (actual != nullptr) {
        NodoCodigo* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
}

void GeneradorCodigo::agregarFueraMain(const char* instruccionCpp) {
    NodoCodigo* nuevoNodo = new NodoCodigo;
    strncpy(nuevoNodo->linea, instruccionCpp, MAX_LINEA - 1);
    nuevoNodo->linea[MAX_LINEA - 1] = '\0';
    nuevoNodo->siguiente = cabeza;  // Insertar al inicio
    cabeza = nuevoNodo;
}