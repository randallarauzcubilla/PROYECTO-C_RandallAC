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
    for (int i = 0; i < MAX_ENTRADAS; ++i) {
        const char* trad = diccionario[i].traduccionCpp;

        // Solo reemplazar si la traducción es una palabra clave semántica
        if (strcmp(trad, "crear") == 0 || strcmp(trad, "int") == 0 ||
            strcmp(trad, "float") == 0 || strcmp(trad, "char") == 0 ||
            strcmp(trad, "bool") == 0) {
            while (contienePalabra(lineaSemantica, diccionario[i].palabraNatural)) {
                reemplazarPalabra(lineaSemantica, diccionario[i].palabraNatural, trad);
            }
        }
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
    // Si no reconoce la instrucción
    snprintf(lineaSalida, MAX_LINEA, "// Instrucción no reconocida: %s", lineaEntrada);
}