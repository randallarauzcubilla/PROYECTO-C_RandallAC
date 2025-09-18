#include "pch.h"
#include "ParserNatural.h"
#include "DiccionarioManual.h"
#include <cstring>
#include <cstdio>
#include <cctype>
#include <stdlib.h>

#define MAX_NOMBRE 50
#define MAX_VALOR 50

ParserNatural::ParserNatural() {}

bool ParserNatural::contienePalabra(const char* linea, const char* palabra) {
    return strstr(linea, palabra) != nullptr;
}

void ParserNatural::reemplazarPalabra(char* linea, const char* buscar, const char* reemplazar) {
    char buffer[MAX_LINEA];
    char* pos = strstr(linea, buscar);
    if (pos == nullptr) return;

    int index = pos - linea;
    strncpy(buffer, linea, index);
    buffer[index] = '\0';

    strcat(buffer, reemplazar);
    strcat(buffer, pos + strlen(buscar));

    strcpy(linea, buffer);
}

void convertirMinusculas(char* linea) {
    for (int i = 0; linea[i]; i++) {
        linea[i] = (char)tolower(linea[i]);
    }
}

void ParserNatural::parseLinea(const char* lineaEntrada, char* lineaSalida) {
    char linea[MAX_LINEA];
    strncpy(linea, lineaEntrada, MAX_LINEA);
    linea[MAX_LINEA - 1] = '\0';

    // Copia para análisis semántico
    char lineaSemantica[MAX_LINEA];
    strncpy(lineaSemantica, linea, MAX_LINEA);
    lineaSemantica[MAX_LINEA - 1] = '\0';

    convertirMinusculas(lineaSemantica);

    // Reemplazar solo palabras clave semánticas (no estructurales)
    EntradaDiccionario* actual = diccionario;
    while (actual != nullptr) {
        const char* trad = actual->traduccionCpp;

        if (strcmp(trad, "crear") == 0 || strcmp(trad, "int") == 0 ||
            strcmp(trad, "float") == 0 || strcmp(trad, "char") == 0 ||
            strcmp(trad, "bool") == 0) {

            NodoPalabra* nodo = actual->listaPalabras;
            while (nodo != nullptr) {
                while (contienePalabra(lineaSemantica, nodo->palabraNatural)) {
                    reemplazarPalabra(lineaSemantica, nodo->palabraNatural, trad);
                }
                nodo = nodo->siguiente;
            }
        }
        actual = actual->siguiente;
    }

    //  Declaración: "crear variable float temperatura"
    if (strstr(lineaSemantica, "crear")) {
        const char* tipo = nullptr;
        if (strstr(lineaSemantica, "int")) tipo = "int";
        else if (strstr(lineaSemantica, "float")) tipo = "float";
        else if (strstr(lineaSemantica, "char")) tipo = "char";
        else if (strstr(lineaSemantica, "bool")) tipo = "bool";

        if (tipo == nullptr) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: tipo de variable no reconocido");
            return;
        }

        // Buscar el nombre después del tipo
        char nombre[MAX_NOMBRE] = { 0 };
        const char* p = strstr(lineaSemantica, "llamada ");
        if (p) {
            p += strlen("llamada ");
            sscanf_s(p, "%49s", nombre, (unsigned)_countof(nombre));
        }
        else {
            // Si no hay "llamada", buscar después del tipo
            p = strstr(lineaSemantica, tipo);
            if (p) {
                p += strlen(tipo);
                sscanf_s(p, "%49s", nombre, (unsigned)_countof(nombre));
            }
        }

        if (nombre[0] == '\0') {
            snprintf(lineaSalida, MAX_LINEA, "// Error: declaracion incompleta o ambigua");
            return;
        }

        snprintf(lineaSalida, MAX_LINEA, "%s %s;", tipo, nombre);
        return;
    }

    //  Asignación: "asignar 25.5 a temperatura"
    if (strstr(lineaSemantica, "asignar") && strstr(lineaSemantica, " a ")) {
        char expresion[MAX_VALOR] = { 0 };
        char nombre[MAX_NOMBRE] = { 0 };

        const char* p = strstr(lineaSemantica, "asignar ");
        if (p) {
            p += strlen("asignar ");
            const char* hasta = strstr(p, " a ");
            if (hasta) {
                size_t len = hasta - p;
                strncpy(expresion, p, len);
                expresion[len] = '\0';
            }
        }

        p = strstr(lineaSemantica, " a ");
        if (p) {
            p += strlen(" a ");
            sscanf_s(p, "%49s", nombre, (unsigned)_countof(nombre));
        }

        if (expresion[0] == '\0' || nombre[0] == '\0') {
            snprintf(lineaSalida, MAX_LINEA, "// Error: asignación incompleta o ambigua");
            return;
        }

        snprintf(lineaSalida, MAX_LINEA, "%s = %s;", nombre, expresion);
        return;
    }

    //  Mostrar: "mostrar temperatura"
    if (strstr(lineaSemantica, "mostrar")) {
        const char* p = strstr(lineaSemantica, "mostrar ");
        char nombre[MAX_NOMBRE] = { 0 };
        if (p) {
            p += strlen("mostrar ");
            sscanf_s(p, "%49s", nombre, (unsigned)_countof(nombre));
            if (nombre[0] == '\0') {
                snprintf(lineaSalida, MAX_LINEA, "// Error: instruccion de impresion incompleta");
                return;
            }
            snprintf(lineaSalida, MAX_LINEA, "cout << %s << endl;", nombre);
            return;
        }
    }

    // Operación: "sumar 5 y 3"
    if (strstr(lineaSemantica, "sumar") && strstr(lineaSemantica, " y ")) {
        char a[MAX_VALOR] = { 0 };
        char b[MAX_VALOR] = { 0 };
        const char* p = strstr(lineaSemantica, "sumar ");
        if (p) {
            p += strlen("sumar ");
            sscanf_s(p, "%49s y %49s", a, (unsigned)_countof(a), b, (unsigned)_countof(b));
            snprintf(lineaSalida, MAX_LINEA, "int resultado = %s + %s;", a, b);
            return;
        }
    }

    if (strncmp(lineaSemantica, "agrega un comentario que diga", 29) == 0) {
        const char* texto = lineaSemantica + 30;  // salta el prefijo
        snprintf(lineaSalida, MAX_LINEA, "// %s", texto);
        return;
    }

    if (strstr(lineaSemantica, "si") && strstr(lineaSemantica, "mostrar")) {
        char variable[MAX_NOMBRE] = { 0 };
        char operador[MAX_VALOR] = { 0 };
        char valor[MAX_VALOR] = { 0 };
        char accion[MAX_NOMBRE] = { 0 };

        sscanf_s(lineaSemantica, "si %49s es %49s %49s mostrar %49s",
            variable, (unsigned)_countof(variable),
            operador, (unsigned)_countof(operador),
            valor, (unsigned)_countof(valor),
            accion, (unsigned)_countof(accion));

        const char* opCpp = buscarTraduccion(operador);
        if (!opCpp) opCpp = operador;

        snprintf(lineaSalida, MAX_LINEA,
            "if (%s %s %s) {\n    cout << %s << endl;\n}",
            variable, opCpp, valor, accion);
        return;
    }

    if (strstr(lineaSemantica, "repetir") && strstr(lineaSemantica, "veces")) {
        int veces = 0;
        char accion[MAX_NOMBRE] = { 0 };

        sscanf_s(lineaSemantica, "repetir %d veces mostrar %49s",
            &veces, accion, (unsigned)_countof(accion));

        snprintf(lineaSalida, MAX_LINEA,
            "for (int i = 0; i < %d; i++) {\n    cout << %s << endl;\n}",
            veces, accion);
        return;
    }

    if (strstr(lineaSemantica, "definir funcion llamada")) {
        char nombre[MAX_NOMBRE] = { 0 };
        const char* p = strstr(lineaSemantica, "llamada ");
        if (p) {
            p += strlen("llamada ");
            sscanf_s(p, "%49s", nombre, (unsigned)_countof(nombre));
            snprintf(lineaSalida, MAX_LINEA,
                "void %s() {\n    // cuerpo de la función\n}", nombre);
            return;
        }
    }

    // Si no reconoce la instrucción
    snprintf(lineaSalida, MAX_LINEA, "// Instrucción no reconocida: %s", lineaEntrada);
}