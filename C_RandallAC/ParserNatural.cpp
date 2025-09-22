#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include "ParserNatural.h"
#include "GeneradorCodigo.h"
#include "DiccionarioManual.h"
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <stdlib.h>
#include <regex> //Reemplace solo cuando aparece como palabra aislada, no dentro de otras palabras. USO PARA DELIMITADOR DE PALABRA!
#define MAX_NOMBRE 50
#define MAX_VALOR 50

int contadorInt = 1;
int contadorFloat = 1;
int contadorChar = 1;
int contadorBool = 1;
bool esperandoElse = false;
using namespace System;
using namespace std;
ParserNatural parser;
ParserNatural::ParserNatural() {}

bool ParserNatural::contienePalabra(const char* linea, const char* palabra) {
    return strstr(linea, palabra) != nullptr;
}

void ParserNatural::reemplazarTodas(char* linea, const char* buscar, const char* reemplazar) {
    std::string str(linea);
    std::string patron = "\\b" + std::string(buscar) + "\\b";  // solo palabras completas para evitar reemplazos erroneos
    std::regex re(patron);
    str = std::regex_replace(str, re, reemplazar);

    strncpy_s(linea, MAX_LINEA, str.c_str(), MAX_LINEA - 1);
    linea[MAX_LINEA - 1] = '\0';
}

void insertarEspaciosOperadores(char* linea) {
    const char* ops[] = { ">=", "<=", "==", "!=", ">", "<" };
    for (int i = 0; i < 6; ++i) {
        std::string str(linea);
        std::string op = ops[i];
        std::string conEspacios = " " + op + " ";
        size_t pos = 0;
        while ((pos = str.find(op, pos)) != std::string::npos) {
            // Evitar duplicar espacios si ya existen
            bool antesEspacio = (pos > 0 && str[pos - 1] == ' ');
            bool despuesEspacio = (pos + op.size() < str.size() && str[pos + op.size()] == ' ');
            if (!antesEspacio || !despuesEspacio) {
                str.replace(pos, op.size(), conEspacios);
                pos += conEspacios.size();
            }
            else {
                pos += op.size();
            }
        }
        strncpy_s(linea, MAX_LINEA, str.c_str(), MAX_LINEA - 1);
        linea[MAX_LINEA - 1] = '\0';
    }
}

void ParserNatural::traducirLinea(char* linea) {
    EntradaDiccionario* actual = diccionario;
    while (actual != nullptr) {
        const char* traduccion = actual->traduccionCpp;
        NodoPalabra* nodo = actual->listaPalabras;
        while (nodo != nullptr) {
            reemplazarTodas(linea, nodo->palabraNatural, traduccion);
            nodo = nodo->siguiente;
        }
        actual = actual->siguiente;
    }
}

void convertirMinusculas(char* linea) {
    for (int i = 0; linea[i]; i++) {
        linea[i] = (char)tolower(linea[i]);
    }
}


void ParserNatural::parseLinea(const char* lineaEntrada, char* lineaSalida, GeneradorCodigo* generador) {
    char linea[MAX_LINEA];
    strncpy(linea, lineaEntrada, MAX_LINEA);
    linea[MAX_LINEA - 1] = '\0';

    // Copia para análisis semántico
    char lineaSemantica[MAX_LINEA];
    strncpy(lineaSemantica, linea, MAX_LINEA);
    lineaSemantica[MAX_LINEA - 1] = '\0';

    convertirMinusculas(lineaSemantica);

    // Reemplazar solo palabras clave semánticas (no estructurales) / Reemplazar todas las palabras del diccionario sin filtrar
    EntradaDiccionario* actual = diccionario;
    while (actual != nullptr) {
        const char* trad = actual->traduccionCpp;
        NodoPalabra* nodo = actual->listaPalabras;
        while (nodo != nullptr) {
            parser.reemplazarTodas(lineaSemantica, nodo->palabraNatural, trad);  
            nodo = nodo->siguiente;
        }
        actual = actual->siguiente;
    }
    //std::cout << "Semantica: " << lineaSemantica << std::endl;
    if (lineaEntrada[0] == '\0' || strlen(lineaEntrada) < 2) {
        snprintf(lineaSalida, MAX_LINEA, "");
        return;
    }


    if ((strstr(lineaEntrada, "crear lista") || strstr(lineaEntrada, "crear arreglo")) && strstr(lineaEntrada, "con")) {
        esperandoElse = false;
        char tipo[MAX_NOMBRE] = { 0 };
        char nombre[MAX_NOMBRE] = "lista"; // por defecto
        const char* llamadaPos = strstr(lineaEntrada, "llamada ");
        if (llamadaPos) {
            llamadaPos += strlen("llamada ");
            sscanf_s(llamadaPos, "%49s", nombre, (unsigned)_countof(nombre));
        }

        int cantidad = 0;

        // Detectar tipo
        if (strstr(lineaEntrada, "números") || strstr(lineaEntrada, "enteros")) {
            strcpy_s(tipo, "int");
            if (!llamadaPos) snprintf(nombre, MAX_NOMBRE, "listaNumeros%d", contadorInt++);
        }
        else if (strstr(lineaEntrada, "decimales") || strstr(lineaEntrada, "decimal")) {
            strcpy_s(tipo, "float");
            if (!llamadaPos) snprintf(nombre, MAX_NOMBRE, "listaDecimales%d", contadorFloat++);
        }
        else if (strstr(lineaEntrada, "letras") || strstr(lineaEntrada, "caracteres")) {
            strcpy_s(tipo, "char");
            if (!llamadaPos) snprintf(nombre, MAX_NOMBRE, "arregloLetras%d", contadorChar++);
        }
        else if (strstr(lineaEntrada, "booleana") || strstr(lineaEntrada, "booleano")) {
            strcpy_s(tipo, "bool");
            if (!llamadaPos) snprintf(nombre, MAX_NOMBRE, "listaBooleana%d", contadorBool++);
        }
        else {
            snprintf(lineaSalida, MAX_LINEA, "// Error: tipo no reconocido");
            return;
        }

        // Extraer cantidad
        const char* conPos = strstr(lineaEntrada, "con");
        if (conPos) {
            while (*conPos && !isdigit(*conPos)) ++conPos;
            sscanf_s(conPos, "%d", &cantidad);
        }

        if (cantidad <= 0) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: cantidad inválida");
            return;
        }

        snprintf(lineaSalida, MAX_LINEA, "%s %s[%d];", tipo, nombre, cantidad);
        return;
    }

    if (strstr(lineaEntrada, "agrega un comentario que diga")) {
        const char* p = strstr(lineaEntrada, "agrega un comentario que diga");
        if (p) {
            p += strlen("agrega un comentario que diga ");
            snprintf(lineaSalida, MAX_LINEA, "// %s", p);
            return;
        }
    }

    if (strstr(lineaEntrada, "funcion") || strstr(lineaEntrada, "función")) {
        esperandoElse = false;
        char tipoRetorno[MAX_NOMBRE] = "void";
        char nombreFuncion[MAX_NOMBRE] = { 0 };
        char parametrosRaw[MAX_LINEA] = { 0 };
        char parametrosCpp[MAX_LINEA] = { 0 };
        char cuerpoCpp[MAX_LINEA] = { 0 };
        char nombreParam1[MAX_NOMBRE] = { 0 };
        char nombreParam2[MAX_NOMBRE] = { 0 };
        int contadorParams = 0;

        // Tipo de retorno
        if (strstr(lineaEntrada, "entera") || strstr(lineaEntrada, "entero") || strstr(lineaSemantica, "int"))
            strcpy(tipoRetorno, "int");
        else if (strstr(lineaEntrada, "decimal") || strstr(lineaEntrada, "flotante") || strstr(lineaSemantica, "float"))
            strcpy(tipoRetorno, "float");
        else if (strstr(lineaEntrada, "booleana") || strstr(lineaEntrada, "boolean") || strstr(lineaSemantica, "bool"))
            strcpy(tipoRetorno, "bool");
        else if (strstr(lineaEntrada, "caracter") || strstr(lineaSemantica, "char"))
            strcpy(tipoRetorno, "char");

        // Nombre de función
        const char* inicioNombre = strstr(lineaEntrada, "llamada ");
        if (!inicioNombre) inicioNombre = strstr(lineaEntrada, "llamado ");
        if (inicioNombre) {
            inicioNombre += strlen("llamada ");
            sscanf_s(inicioNombre, "%49s", nombreFuncion, (unsigned)_countof(nombreFuncion));
        }
        else {
            const char* tipoPos = strstr(lineaSemantica, tipoRetorno);
            if (tipoPos) {
                tipoPos += strlen(tipoRetorno);
                while (*tipoPos == ' ') ++tipoPos;
                sscanf_s(tipoPos, "%49s", nombreFuncion, (unsigned)_countof(nombreFuncion));
            }
        }

        if (nombreFuncion[0] == '\0') {
            snprintf(lineaSalida, MAX_LINEA, "// Error: No se encontró nombre de función");
            return;
        }

        // Parámetros
        const char* inicioParams = strstr(lineaEntrada, "reciba");
        if (!inicioParams) inicioParams = strstr(lineaEntrada, "con parametros");
        if (!inicioParams) inicioParams = strstr(lineaEntrada, "con");

        if (inicioParams) {
            if (strstr(lineaEntrada, "reciba"))
                inicioParams += strlen("reciba");
            else if (strstr(lineaEntrada, "con parametros"))
                inicioParams += strlen("con parametros");
            else
                inicioParams += strlen("con");

            while (*inicioParams == ' ') ++inicioParams;

            parametrosCpp[0] = '\0';
            parametrosRaw[0] = '\0';

            char copiaParams[MAX_LINEA];
            strncpy_s(copiaParams, inicioParams, _TRUNCATE);
            char* token = strtok(copiaParams, ",");

            while (token != NULL) {
                while (*token == ' ') ++token;
                char tipoOriginal[MAX_NOMBRE] = { 0 };
                char tipoTraducido[MAX_NOMBRE] = { 0 };
                char nombre[MAX_NOMBRE] = { 0 };
                sscanf_s(token, "%49s %49s", tipoOriginal, (unsigned)_countof(tipoOriginal), nombre, (unsigned)_countof(nombre));

                if (strcmp(tipoOriginal, "entero") == 0) strcpy(tipoTraducido, "int");
                else if (strcmp(tipoOriginal, "decimal") == 0) strcpy(tipoTraducido, "float");
                else if (strcmp(tipoOriginal, "caracter") == 0) strcpy(tipoTraducido, "char");
                else if (strcmp(tipoOriginal, "booleana") == 0 || strcmp(tipoOriginal, "boolean") == 0) strcpy(tipoTraducido, "bool");
                else strcpy(tipoTraducido, tipoOriginal);

                if (tipoTraducido[0] != '\0' && nombre[0] != '\0') {
                    strcat(parametrosCpp, tipoTraducido);
                    strcat(parametrosCpp, " ");
                    strcat(parametrosCpp, nombre);
                    strcat(parametrosCpp, ", ");

                    strcat(parametrosRaw, tipoOriginal);
                    strcat(parametrosRaw, " ");
                    strcat(parametrosRaw, nombre);
                    strcat(parametrosRaw, ", ");

                    if (contadorParams == 0)
                        strcpy(nombreParam1, nombre);
                    else if (contadorParams == 1)
                        strcpy(nombreParam2, nombre);
                    contadorParams++;
                }

                token = strtok(NULL, ",");
            }

            size_t lenCpp = strlen(parametrosCpp);
            if (lenCpp >= 2) parametrosCpp[lenCpp - 2] = '\0';

            size_t lenRaw = strlen(parametrosRaw);
            if (lenRaw >= 2) parametrosRaw[lenRaw - 2] = '\0';
        }

        // Cuerpo
        const char* retorno = strstr(lineaEntrada, "retorne");
        if (retorno) {
            retorno += strlen("retorne");
            while (*retorno == ' ') ++retorno;
            snprintf(cuerpoCpp, MAX_LINEA, "    return %s;", retorno);
        }
        else {
            if (strcmp(nombreFuncion, "sumar") == 0 && nombreParam1[0] != '\0' && nombreParam2[0] != '\0')
                snprintf(cuerpoCpp, MAX_LINEA, "    return %s + %s;", nombreParam1, nombreParam2);
            else if (strcmp(nombreFuncion, "restar") == 0 && nombreParam1[0] != '\0' && nombreParam2[0] != '\0')
                snprintf(cuerpoCpp, MAX_LINEA, "    return %s - %s;", nombreParam1, nombreParam2);
            else if (strcmp(nombreFuncion, "promedio") == 0 && nombreParam1[0] != '\0' && nombreParam2[0] != '\0')
                snprintf(cuerpoCpp, MAX_LINEA, "    return (%s + %s) / 2;", nombreParam1, nombreParam2);
            else if (strcmp(nombreFuncion, "multiplicar") == 0 && nombreParam1[0] != '\0' && nombreParam2[0] != '\0')
                snprintf(cuerpoCpp, MAX_LINEA, "    return %s * %s;", nombreParam1, nombreParam2);
            else if (strcmp(nombreFuncion, "dividir") == 0 && nombreParam1[0] != '\0' && nombreParam2[0] != '\0')
                snprintf(cuerpoCpp, MAX_LINEA, "    return %s / %s;", nombreParam1, nombreParam2);
        }

        // Fallback
        if (cuerpoCpp[0] == '\0') {
            if (strcmp(tipoRetorno, "int") == 0)
                snprintf(cuerpoCpp, MAX_LINEA, "    return 0;");
            else if (strcmp(tipoRetorno, "float") == 0)
                snprintf(cuerpoCpp, MAX_LINEA, "    return 0.0;");
            else if (strcmp(tipoRetorno, "bool") == 0)
                snprintf(cuerpoCpp, MAX_LINEA, "    return false;");
            else if (strcmp(tipoRetorno, "char") == 0)
                snprintf(cuerpoCpp, MAX_LINEA, "    return ' ';");
            else
                snprintf(cuerpoCpp, MAX_LINEA, "    // cuerpo de la funcion");
        }

        // Generar función
        if (parametrosCpp[0] == '\0') {
            snprintf(lineaSalida, MAX_LINEA,
                "%s %s() {\n%s\n}", tipoRetorno, nombreFuncion, cuerpoCpp);
        }
        else {
            snprintf(lineaSalida, MAX_LINEA,
                "%s %s(%s) {\n%s\n}", tipoRetorno, nombreFuncion, parametrosCpp, cuerpoCpp);
        }

        char firmaFuncion[MAX_LINEA] = { 0 };
        if (parametrosCpp[0] == '\0') {
            snprintf(firmaFuncion, MAX_LINEA, "%s %s()", tipoRetorno, nombreFuncion);
        }
        else {
            snprintf(firmaFuncion, MAX_LINEA, "%s %s(%s)", tipoRetorno, nombreFuncion, parametrosCpp);
        }

        if (generador != nullptr) {
            if (!generador->contiene(firmaFuncion)) {
                generador->agregarFueraMain(lineaSalida);
            }

            char llamadaCpp[MAX_LINEA] = { 0 };
            generador->generarLlamadaFuncion(nombreFuncion, parametrosRaw, llamadaCpp);
            generador->agregar(llamadaCpp, true);
        }
        return;
    }

    //  Declaración: "crear variable float temperatura" / "crear variable tipo nombre"
    if (strstr(lineaSemantica, "DECLARAR_VAR")) {
        esperandoElse = false;
        const char* tipo = nullptr;
        if (strstr(lineaSemantica, "int")) tipo = "int";
        else if (strstr(lineaSemantica, "float")) tipo = "float";
        else if (strstr(lineaSemantica, "char")) tipo = "char";
        else if (strstr(lineaSemantica, "bool")) tipo = "bool";

        if (tipo == nullptr) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: tipo de variable no reconocido");
            return;
        }

        // Buscar el nombre después de "llamada"
        char nombre[MAX_NOMBRE] = { 0 };
        const char* p = strstr(lineaEntrada, "llamada ");
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

    if ((strstr(lineaEntrada, "=") || strstr(lineaEntrada, "asignar")) && strstr(lineaEntrada, " a ")) {
        esperandoElse = false;
        char expresion[MAX_VALOR] = { 0 };
        char nombre[MAX_NOMBRE] = { 0 };

        const char* p = strstr(lineaSemantica, "asignar ");
        if (p) {
            p += strlen("asignar ");
        }
        else {
            p = strstr(lineaSemantica, "= ");
            if (p) {
                p += strlen("= ");
            }
        }

        if (p) {  // protección extra
            const char* hasta = strstr(p, " a ");
            if (hasta) {
                size_t len = hasta - p;
                strncpy_s(expresion, MAX_VALOR, p, len);
                expresion[len] = '\0';
            }
        }

        p = strstr(lineaEntrada, " a ");
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

    if (strstr(lineaEntrada, "sumar") && strstr(lineaEntrada, " y ")) {
        char a[MAX_VALOR] = { 0 };
        char b[MAX_VALOR] = { 0 };
        const char* p = strstr(lineaEntrada, "sumar ");
        if (p) {
            p += strlen("sumar ");
            sscanf_s(p, "%49s y %49s", a, (unsigned)_countof(a), b, (unsigned)_countof(b));
            snprintf(lineaSalida, MAX_LINEA, "int resultado = %s + %s;", a, b);
            return;
        }
    }

    if (strstr(lineaEntrada, "restar") && strstr(lineaEntrada, " y ")) {
        char a[MAX_VALOR] = { 0 };
        char b[MAX_VALOR] = { 0 };
        const char* p = strstr(lineaEntrada, "restar ");
        if (p) {
            p += strlen("restar ");
            sscanf_s(p, "%49s y %49s", a, (unsigned)_countof(a), b, (unsigned)_countof(b));
            snprintf(lineaSalida, MAX_LINEA, "int resultado = %s - %s;", a, b);
            return;
        }
    }

    if (strstr(lineaEntrada, "multiplicar") && strstr(lineaEntrada, " y ")) {
        char a[MAX_VALOR] = { 0 };
        char b[MAX_VALOR] = { 0 };
        const char* p = strstr(lineaEntrada, "multiplicar ");
        if (p) {
            p += strlen("multiplicar ");
            sscanf_s(p, "%49s y %49s", a, (unsigned)_countof(a), b, (unsigned)_countof(b));
            snprintf(lineaSalida, MAX_LINEA, "int resultado = %s * %s;", a, b);
            return;
        }
    }

    if (strstr(lineaEntrada, "dividir") && strstr(lineaEntrada, " entre ")) {
        char a[MAX_VALOR] = { 0 };
        char b[MAX_VALOR] = { 0 };
        const char* p = strstr(lineaEntrada, "dividir ");
        if (p) {
            p += strlen("dividir ");
            sscanf_s(p, "%49s entre %49s", a, (unsigned)_countof(a), b, (unsigned)_countof(b));
            snprintf(lineaSalida, MAX_LINEA, "int resultado = %s / %s;", a, b);
            return;
        }
    }

    if (strstr(lineaSemantica, "void") && strstr(lineaSemantica, "llamada")) {
        char nombre[MAX_NOMBRE] = { 0 };
        const char* p = strstr(lineaEntrada, "llamada ");
        if (p) {
            p += strlen("llamada ");
            sscanf_s(p, "%49s", nombre, (unsigned)_countof(nombre));
            snprintf(lineaSalida, MAX_LINEA,
                "void %s() {\n    // cuerpo de la función\n}", nombre);
            return;
        }
    }

    if (strstr(lineaSemantica, "nombreFuncion();") && strstr(lineaEntrada, "funcion ")) {
        char nombre[MAX_NOMBRE] = { 0 };
        const char* p = strstr(lineaEntrada, "funcion ");
        if (p) {
            p += strlen("funcion ");
            sscanf_s(p, "%49s", nombre, (unsigned)_countof(nombre));
            snprintf(lineaSalida, MAX_LINEA, "%s();", nombre);
            return;
        }
    }

    if (strstr(lineaEntrada, "repetir") && strstr(lineaEntrada, "veces")) {
        esperandoElse = false;
        int veces = 0;
        char accion[MAX_NOMBRE] = { 0 };

        sscanf_s(lineaEntrada, "repetir %d veces mostrar %49s",
            &veces, accion, (unsigned)_countof(accion));

        snprintf(lineaSalida, MAX_LINEA,
            "for (int i = 0; i < %d; i++) {\n    cout << %s << endl;\n}", veces, accion);
        return;
    }

    if (strstr(lineaEntrada, "mientras") && strstr(lineaEntrada, "mostrar")) {
        esperandoElse = false;
        char variable[MAX_NOMBRE] = { 0 };
        char operadorNatural[MAX_LINEA] = { 0 };
        char valor[MAX_VALOR] = { 0 };
        char accion[MAX_NOMBRE] = { 0 };

        sscanf_s(lineaSemantica, "while %49s %49s %49s cout << %49s",
            variable, (unsigned)_countof(variable),
            operadorNatural, (unsigned)_countof(operadorNatural),
            valor, (unsigned)_countof(valor),
            accion, (unsigned)_countof(accion));

        const char* operadorCpp = buscarTraduccion(operadorNatural);
        if (!operadorCpp) operadorCpp = operadorNatural;

        snprintf(lineaSalida, MAX_LINEA,
            "while (%s %s %s) {\n    cout << %s << endl;\n}", variable, operadorCpp, valor, accion);
        return;
    }

    if (strstr(lineaEntrada, "si") && strstr(lineaEntrada, "sino") && strstr(lineaEntrada, "mostrar")) {
        esperandoElse = false;

        const char* inicioSi = strstr(lineaEntrada, "si");
        const char* inicioSino = strstr(lineaEntrada, "sino");

        char bloqueSi[MAX_LINEA] = { 0 };
        char bloqueSino[MAX_LINEA] = { 0 };

        size_t lenSi = inicioSino - inicioSi;
        strncpy_s(bloqueSi, inicioSi, lenSi);
        bloqueSi[lenSi] = '\0';

        strncpy_s(bloqueSino, inicioSino, MAX_LINEA - 1);
        bloqueSino[MAX_LINEA - 1] = '\0';

        // Procesar bloqueSi
        char variable[MAX_NOMBRE] = { 0 };
        char operadorNatural[MAX_VALOR] = { 0 };
        char valor[MAX_VALOR] = { 0 };
        char accionIf[MAX_NOMBRE] = { 0 };

        const char* mostrarIf = strstr(bloqueSi, "mostrar");
        if (!mostrarIf) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: no se encontró 'mostrar' en bloque si");
            return;
        }

        mostrarIf += strlen("mostrar");
        while (*mostrarIf == ' ') ++mostrarIf;
        sscanf_s(mostrarIf, "%49s", accionIf, (unsigned)_countof(accionIf));

        const char* inicioCond = strstr(bloqueSi, "si");
        if (inicioCond) {
            inicioCond += strlen("si");
            while (*inicioCond == ' ') ++inicioCond;
        }

        char condicion[MAX_LINEA] = { 0 };
        size_t lenCond = mostrarIf - inicioCond;
        strncpy_s(condicion, inicioCond, lenCond);
        condicion[lenCond] = '\0';

        insertarEspaciosOperadores(condicion);

        sscanf_s(condicion, "%49s %49s %49s",
            variable, (unsigned)_countof(variable),
            operadorNatural, (unsigned)_countof(operadorNatural),
            valor, (unsigned)_countof(valor));

        const char* operadorCpp = buscarTraduccion(operadorNatural);
        if (!operadorCpp) operadorCpp = operadorNatural;

        // Procesar bloqueSino
        char accionElse[MAX_NOMBRE] = { 0 };
        const char* mostrarElse = strstr(bloqueSino, "mostrar");
        if (!mostrarElse) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: no se encontró 'mostrar' en bloque sino");
            return;
        }

        mostrarElse += strlen("mostrar");
        while (*mostrarElse == ' ') ++mostrarElse;
        sscanf_s(mostrarElse, "%49s", accionElse, (unsigned)_countof(accionElse));

        // Generar ambos bloques
        snprintf(lineaSalida, MAX_LINEA,
            "if (%s %s %s) {\n    cout << %s << endl;\n} else {\n    cout << %s << endl;\n}",
            variable, operadorCpp, valor, accionIf, accionElse);
        return;
    }

    if ((strstr(lineaEntrada, "sino mostrar") || strstr(lineaEntrada, "si no mostrar")) &&
        !(strstr(lineaEntrada, "sino si") || strstr(lineaEntrada, "si no si"))) {
        esperandoElse = false;
        char accion[MAX_NOMBRE] = { 0 };

        const char* mostrar = strstr(lineaEntrada, "mostrar");
        if (!mostrar) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: no se encontró 'mostrar'");
            return;
        }

        mostrar += strlen("mostrar");
        while (*mostrar == ' ') ++mostrar;

        sscanf_s(mostrar, "%49s", accion, (unsigned)_countof(accion));

        if (accion[0] == '\0') {
            snprintf(lineaSalida, MAX_LINEA, "// Error: acción incompleta");
            return;
        }

        if (esperandoElse) {
            snprintf(lineaSalida, MAX_LINEA,
                "else {\n    cout << %s << endl;\n}", accion);
            esperandoElse = false;
        }
        else {
            snprintf(lineaSalida, MAX_LINEA,
                "// Error: 'sino' sin 'si' previo");
        }
        return;
    }

    if (strstr(lineaEntrada, "si") && strstr(lineaEntrada, "mostrar")) {
        char variable[MAX_NOMBRE] = { 0 };
        char operador[MAX_VALOR] = { 0 };
        char valor[MAX_VALOR] = { 0 };
        char accion[MAX_NOMBRE] = { 0 };

        // Buscar inicio de condición
        const char* inicio = strstr(lineaEntrada, "si");
        if (!inicio) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: no se encontró 'si'");
            return;
        }
        inicio += strlen("si");
        while (*inicio == ' ') ++inicio;

        const char* mostrar = strstr(inicio, " mostrar ");
        if (!mostrar) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: no se encontró 'mostrar'");
            return;
        }

        // Extraer condición
        char condicion[MAX_LINEA] = { 0 };
        size_t len = mostrar - inicio;
        strncpy_s(condicion, inicio, len);
        condicion[len] = '\0';

        parser.traducirLinea(condicion);              
        insertarEspaciosOperadores(condicion); 

        // Extraer acción
        sscanf_s(mostrar + strlen(" mostrar "), "%49s", accion, (unsigned)_countof(accion));

        // Separar tokens
        sscanf_s(condicion, "%49s %49s %49s",
            variable, (unsigned)_countof(variable),
            operador, (unsigned)_countof(operador),
            valor, (unsigned)_countof(valor));
        if ((strcmp(operador, "<") == 0 || strcmp(operador, ">") == 0 || strcmp(operador, "!") == 0 || strcmp(operador, "=") == 0) &&
            valor[0] == '=') {

            // Combinar operador doble
            operador[1] = '=';
            operador[2] = '\0';

            // Buscar el valor real después del '='
            const char* pos = strstr(condicion, "=");
            if (pos) {
                pos += 1;
                while (*pos == ' ') ++pos;
                sscanf_s(pos, "%49s", valor, (unsigned)_countof(valor));
            }
        }

        if (variable[0] == '\0' || operador[0] == '\0' || valor[0] == '\0' || accion[0] == '\0') {
            snprintf(lineaSalida, MAX_LINEA, "// Error: condición incompleta");
            return;
        }

        snprintf(lineaSalida, MAX_LINEA,
            "if (%s %s %s) {\n    cout << %s << endl;\n}",
            variable, operador, valor, accion);
        esperandoElse = true;
        return;
    }

    if (strstr(lineaEntrada, "repetir hasta que") && strstr(lineaEntrada, "mostrar")) {
        esperandoElse = false;
        insertarEspaciosOperadores(lineaSemantica);  // normaliza operadores

        char variable[MAX_NOMBRE] = { 0 };
        char operador[MAX_VALOR] = { 0 };
        char valor[MAX_VALOR] = { 0 };
        char accion[MAX_NOMBRE] = { 0 };

        // Buscar inicio de condición
        const char* inicio = strstr(lineaEntrada, "repetir hasta que");
     
        if (!inicio) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: no se encontró 'repetir hasta que'");
            return;
        }
        inicio += strlen("repetir hasta que");
        while (*inicio == ' ') ++inicio;
        // Buscar 'mostrar' como delimitador final
        const char* mostrar = strstr(inicio, " mostrar ");
        if (!mostrar) {
            snprintf(lineaSalida, MAX_LINEA, "// Error: no se encontró 'mostrar'");
            return;
        }

        // Extraer condición
        char condicion[MAX_LINEA] = { 0 };
        size_t len = mostrar - inicio;
        strncpy_s(condicion, inicio, len);
        condicion[len] = '\0';

        // Extraer acción
        sscanf_s(mostrar + strlen(" mostrar "), "%49s", accion, (unsigned)_countof(accion));

        // Separar condición en tokens
        sscanf_s(condicion, "%49s %49s %49s",
            variable, (unsigned)_countof(variable),
            operador, (unsigned)_countof(operador),
            valor, (unsigned)_countof(valor));

        // Validación
        if (variable[0] == '\0' || operador[0] == '\0' || valor[0] == '\0' || accion[0] == '\0') {
            snprintf(lineaSalida, MAX_LINEA, "// Error: extracción incompleta");
            return;
        }

        snprintf(lineaSalida, MAX_LINEA,
            "do {\n    cout << %s << endl;\n} while (!(%s %s %s));",
            accion, variable, operador, valor);
        return;
    }

    if (strstr(lineaEntrada, "mostrar ") &&
        !strstr(lineaEntrada, "repetir") &&
        !strstr(lineaEntrada, "mientras") &&
        !strstr(lineaEntrada, "si")) {
        esperandoElse = false;
        //printf("// DEBUG: lineaEntrada = '%s'\n", lineaEntrada);
        const char* p = strstr(lineaEntrada, "mostrar ");
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

    // Si no reconoce la instrucción
    snprintf(lineaSalida, MAX_LINEA, "// Instruccion no reconocida: %s", lineaEntrada);
}