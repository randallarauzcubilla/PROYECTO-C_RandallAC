#include "pch.h"
#include "DiccionarioManual.h"
#include <cstring>

EntradaDiccionario* diccionario = nullptr;

void agregarEntrada(const char* traduccionCpp, const char* palabras[], int cantidad) {
    EntradaDiccionario* nueva = new EntradaDiccionario;
    strncpy(nueva->traduccionCpp, traduccionCpp, MAX_TRADUCCION);
    nueva->traduccionCpp[MAX_TRADUCCION - 1] = '\0';
    nueva->listaPalabras = nullptr;
    nueva->siguiente = nullptr;

    NodoPalabra* anterior = nullptr;
    for (int i = 0; i < cantidad; ++i) {
        NodoPalabra* nodo = new NodoPalabra;
        strncpy(nodo->palabraNatural, palabras[i], MAX_PALABRA);
        nodo->palabraNatural[MAX_PALABRA - 1] = '\0';
        nodo->siguiente = nullptr;

        if (anterior == nullptr) {
            nueva->listaPalabras = nodo;
        }
        else {
            anterior->siguiente = nodo;
        }
        anterior = nodo;
    }

    if (diccionario == nullptr) {
        diccionario = nueva;
    }
    else {
        EntradaDiccionario* actual = diccionario;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nueva;
    }
}

const char* buscarTraduccion(const char* palabra) {
    EntradaDiccionario* actual = diccionario;
    while (actual != nullptr) {
        NodoPalabra* nodo = actual->listaPalabras;
        while (nodo != nullptr) {
            if (strcmp(nodo->palabraNatural, palabra) == 0) {
                return actual->traduccionCpp;
            }
            nodo = nodo->siguiente;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

void liberarDiccionario() {
    EntradaDiccionario* actual = diccionario;
    while (actual != nullptr) {
        NodoPalabra* nodo = actual->listaPalabras;
        while (nodo != nullptr) {
            NodoPalabra* temp = nodo;
            nodo = nodo->siguiente;
            delete temp;
        }
        EntradaDiccionario* tempEntrada = actual;
        actual = actual->siguiente;
        delete tempEntrada;
    }
    diccionario = nullptr;
}

void inicializarDiccionario() {
    // Operaciones
    const char* opSuma[] = { "sumar", "añadir", "agregar" };
    agregarEntrada("+", opSuma, 3);

    const char* opResta[] = { "restar", "quitar" };
    agregarEntrada("-", opResta, 2);

    const char* opMult[] = { "multiplicar", "por" };
    agregarEntrada("*", opMult, 2);

    const char* opDiv[] = { "dividir", "entre" };
    agregarEntrada("/", opDiv, 2);

    // Tipos de datos
    const char* tipoInt[] = { "entero", "entera", "numero" };
    agregarEntrada("int", tipoInt, 3);

    const char* tipoFloat[] = { "decimal", "numero decimal" };
    agregarEntrada("float", tipoFloat, 2);

    const char* tipoChar[] = { "caracter", "letra", "texto", "cadena de texto" };
    agregarEntrada("char", tipoChar, 4);

    const char* tipoBool[] = { "booleano", "boolean", "bool", "verdadero", "falso" };
    agregarEntrada("bool", tipoBool, 5);

    // Declaración
    const char* declarar[] = { "crear", "declarar", "definir variable", "crear una variable" };
    agregarEntrada("crear", declarar, 4);

    // Asignación
    const char* asignar[] = { "asignar", "establecer", "igualar" };
    agregarEntrada("=", asignar, 3);

    // Entrada/Salida
    const char* mostrar[] = { "mostrar", "imprimir", "escribir", "mostrar mensaje" };
    agregarEntrada("cout <<", mostrar, 4);

    const char* leer[] = { "leer", "capturar", "ingresar valor", "leer valor" };
    agregarEntrada("cin >>", leer, 4);

    // Comentarios
    const char* comentario[] = { "agrega un comentario que diga", "comentario" };
    agregarEntrada("//", comentario, 2);

    // Condicionales
    const char* condSi[] = { "si", "en caso que" };
    agregarEntrada("if", condSi, 2);

    const char* condSino[] = { "sino", "si no" };
    agregarEntrada("else", condSino, 2);

    const char* mayor[] = { "mayor que", "es mayor que" };
    agregarEntrada(">", mayor, 2);

    const char* menor[] = { "menor que", "es menor que" };
    agregarEntrada("<", menor, 2);

    const char* igual[] = { "igual a", "es igual a" };
    agregarEntrada("==", igual, 2);

    const char* diferente[] = { "diferente de", "es diferente de" };
    agregarEntrada("!=", diferente, 2);

    const char* mayorIgual[] = { "mayor o igual que" };
    agregarEntrada(">=", mayorIgual, 1);

    const char* menorIgual[] = { "menor o igual que" };
    agregarEntrada("<=", menorIgual, 1);

    const char* logicoY[] = { "y", "además" };
    agregarEntrada("&&", logicoY, 2);

    const char* logicoO[] = { "o", "o bien" };
    agregarEntrada("||", logicoO, 2);

    // Bucles
    const char* bucleMientras[] = { "mientras", "mientras que" };
    agregarEntrada("while", bucleMientras, 2);

    const char* bucleRepetir[] = { "repetir", "repetir hasta" };
    agregarEntrada("do { } while(...)", bucleRepetir, 2);

    const char* buclePara[] = { "para", "repetir n veces" };
    agregarEntrada("for", buclePara, 2);

    // Funciones
    const char* funcionDefinir[] = { "definir funcion", "crear funcion" };
    agregarEntrada("void nombreFuncion() {", funcionDefinir, 2);

    const char* funcionLlamar[] = { "llamar funcion", "ejecutar funcion" };
    agregarEntrada("nombreFuncion();", funcionLlamar, 2);

    // Finalización
    const char* finalizar[] = { "terminar programa", "finalizar", "cerrar programa", "fin" };
    agregarEntrada("return 0; }", finalizar, 4);

    // Inicio
    const char* iniciar[] = { "comenzar programa", "inicio" };
    agregarEntrada("int main() {", iniciar, 2);
}