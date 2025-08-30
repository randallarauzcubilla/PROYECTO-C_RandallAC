#ifndef DICCIONARIO_MANUAL_H
#define DICCIONARIO_MANUAL_H

const int MAX_ENTRADAS = 50;

struct EntradaDiccionario {
    char palabraNatural[40];
    char traduccionCpp[40];
};

extern EntradaDiccionario diccionario[MAX_ENTRADAS];

#endif