#pragma once

#define MAX_LINEA 256
#include "DiccionarioManual.h"

class ParserNatural {
public:
    ParserNatural();

    // Traduce línea natural a C++
    void parseLinea(const char* lineaEntrada, char* lineaSalida);

private:
    bool contienePalabra(const char* linea, const char* palabra);
    void reemplazarPalabra(char* linea, const char* buscar, const char* reemplazar);
};