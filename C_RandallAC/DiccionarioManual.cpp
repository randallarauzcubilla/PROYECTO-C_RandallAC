#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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
                //std::cout << "Traducción encontrada: " << actual->traduccionCpp << std::endl;
                return actual->traduccionCpp;
            }
            nodo = nodo->siguiente;
        }
        actual = actual->siguiente;
    }
    std::cerr << "Palabra no encontrada en diccionario: " << palabra << std::endl;
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
    liberarDiccionario();
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

    const char* tipoChar[] = { "caracter", "texto", "cadena de texto" };
    agregarEntrada("char", tipoChar, 3);

    const char* tipoBool[] = { "booleana", "boolean", "bool" };
    agregarEntrada("bool", tipoBool, 3);

    const char* valorTrue[] = { "verdadero" };
    agregarEntrada("true", valorTrue, 1);

    const char* valorFalse[] = { "falso" };
    agregarEntrada("false", valorFalse, 1);

    const char* tipoListaInt[] = { "lista de números", "lista de enteros", "arreglo de números", "arreglo de enteros" };
    agregarEntrada("int[]", tipoListaInt, 4);

    const char* tipoListaChar[] = { "lista de letras", "lista de caracteres", "arreglo de letras", "arreglo de caracteres" };
    agregarEntrada("char[]", tipoListaChar, 4);

    const char* tipoListaBool[] = { "lista booleana", "arreglo booleano" };
    agregarEntrada("bool[]", tipoListaBool, 2);

    const char* tipoListaFloat[] = { "lista decimal", "arreglo decimal", "lista de decimales" };
    agregarEntrada("float[]", tipoListaFloat, 3);

    const char* declarar[] = { "declarar", "definir variable", "crear una variable" };
    agregarEntrada("DECLARAR_VAR", declarar, 3);

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

    const char* simboloMayor[] = { ">" };
    agregarEntrada(">", simboloMayor, 1);

    const char* simboloMenor[] = { "<" };
    agregarEntrada("<", simboloMenor, 1);

    const char* simboloIgual[] = { "==" };
    agregarEntrada("==", simboloIgual, 1);

    const char* simboloMayorIgual[] = { ">=" };
    agregarEntrada(">=", simboloMayorIgual, 1);

    const char* simboloMenorIgual[] = { "<=" };
    agregarEntrada("<=", simboloMenorIgual, 1);

    const char* simboloDistinto[] = { "!=" };
    agregarEntrada("!=", simboloDistinto, 1);

    // Bucles
    const char* bucleMientras[] = { "mientras", "mientras que" };
    agregarEntrada("while", bucleMientras, 2);

    const char* bucleRepetir[] = { "repetir", "repetir hasta que" };
    agregarEntrada("do { } while(...)", bucleRepetir, 2);

    const char* buclePara[] = { "para", "repetir n veces" };
    agregarEntrada("for", buclePara, 2);

    const char* menorQue[] = { "menor", "menor que" };
    agregarEntrada("<", menorQue, 2);

    const char* mayorQue[] = { "mayor", "mayor que" };
    agregarEntrada(">", mayorQue, 2);

    const char* igualQue[] = { "igual", "igual que" };
    agregarEntrada("==", igualQue, 2);

    const char* distintoDe[] = { "distinto", "distinto de" };
    agregarEntrada("!=", distintoDe, 2);

    const char* verboCondicion[] = { "sea", "es", "fue", "este" };
    agregarEntrada("", verboCondicion, 4);  // reemplazo vacío

    const char* tipoFuncionInt[] = { "función entera", "función de tipo entero" };
    agregarEntrada("int", tipoFuncionInt, 2);

    const char* tipoFuncionFloat[] = { "función decimal", "función de tipo decimal" };
    agregarEntrada("float", tipoFuncionFloat, 2);

    const char* tipoFuncionBool[] = { "función booleana", "función de tipo booleana" };
    agregarEntrada("bool", tipoFuncionBool, 2);

    const char* tipoFuncionChar[] = { "función de tipo caracter", "función de tipo char", "función que retorna caracter" };
    agregarEntrada("char", tipoFuncionChar, 3);

    const char* tipoFuncionVoid[] = { "función vacía", "función sin retorno" };
    agregarEntrada("void", tipoFuncionVoid, 2);

    const char* crearFuncion[] = { "crear una función", "definir una función", "crear función" };
    agregarEntrada("FUNCION_INICIO", crearFuncion, 3);

    const char* recibe[] = { "reciba", "con", "que tome", "que acepte" };
    agregarEntrada("FUNCION_PARAM", recibe, 4);

    const char* retorna[] = { "retorne", "devuelva", "regrese" };
    agregarEntrada("return", retorna, 3);

    const char* imprime[] = { "imprima", "muestre", "escriba" };
    agregarEntrada("cout <<", imprime, 3);

    const char* finalizar[] = { "terminar programa", "finalizar", "cerrar programa", "fin" };
    agregarEntrada("return 0; }", finalizar, 4);

    // Inicio
    const char* iniciar[] = { "comenzar programa", "inicio" };
    agregarEntrada("int main() {", iniciar, 2);
}