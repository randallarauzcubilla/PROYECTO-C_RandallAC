#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_PALABRA 80
#define MAX_TRADUCCION 100

// Nodo de palabra natural (lista interna)
struct NodoPalabra {
    char palabraNatural[MAX_PALABRA];
    NodoPalabra* siguiente;
};

// Entrada del diccionario (lista principal)
struct EntradaDiccionario {
    char traduccionCpp[MAX_TRADUCCION];
    NodoPalabra* listaPalabras;
    EntradaDiccionario* siguiente;
};

// Diccionario principal
extern EntradaDiccionario* diccionario;

// Funciones públicas
void agregarEntrada(const char* traduccionCpp, const char* palabras[], int cantidad);
const char* buscarTraduccion(const char* palabra);
void inicializarDiccionario();
void liberarDiccionario();