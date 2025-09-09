#pragma once

#define MAX_ENTRADAS 80
#define MAX_PALABRA 80
#define MAX_TRADUCCION 100

struct EntradaDiccionario {
    char palabraNatural[MAX_PALABRA];
    char traduccionCpp[MAX_TRADUCCION];
};

extern EntradaDiccionario diccionario[MAX_ENTRADAS];