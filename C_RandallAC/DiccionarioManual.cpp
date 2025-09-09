#include "pch.h"
#include "DiccionarioManual.h"
#include <cstring>

EntradaDiccionario diccionario[MAX_ENTRADAS] = {
    {"sumar", "+"},
    {"restar", "-"},
    {"multiplicar", "*"},
    {"dividir", "/"},
    {"calcular", "operacion"}, // Esto es genérico, usar en parser con lógica adicional
    {"total", "nombre"},
    { "entero", "int" },
    { "entera", "int" },

    {"crear", "crear"}, // solo para detección
    {"declarar", "crear"},
    {"variable", "nombre;"}, // se combina con tipo
    {"entero", "int"},
    {"decimal", "float"},
    {"numero decimal", "float"},
    {"texto", "char"}, // En C++ puro sin STL, se usa arreglo de chars
    {"palabra", "char"},
    {"cadena de texto", "char"},
    {"caracter", "char"},
    {"booleano", "bool"},
    {"valor inicial", "variable = valor;"},
    {"asignar valor", "variable = valor;"},

    {"crear lista", "tipo nombre[];"},
    {"crear arreglo", "tipo nombre[];"},
    {"lista", "[]"}, // estructura
    {"elementos", "n"}, // cantidad
    {"recorrer la lista", "for"},  // Debe expandirse en parser
    {"agregar a la lista", "// agregar elemento manualmente"}, // sin STL no hay push_back

    {"si", "if"},
    {"sino", "else"},
    {"mientras", "while"},
    {"repetir hasta", "do { } while(...)"},
    {"para", "for"},

    {"condicion", "expresion booleana"},
    {"igual a", "=="},
    {"diferente de", "!="},
    {"mayor que", ">"},
    {"menor que", "<"},
    {"y", "&&"},
    {"o", "||"},

    {"mostrar", "cout <<"},
    {"imprimir", "cout <<"},
    {"leer", "cin >>"},
    {"ingresar valor", "cin >>"},
    {"mensaje", "\"texto\""},

    {"comenzar programa", "int main() {"},
    {"terminar programa", "return 0; }"},
    {"fin", "return 0; }"},
    {"comentario", "// comentario"},
    {"definir funcion", "tipo nombreFuncion(...)"},
    {"llamar funcion", "nombreFuncion();"},

{ "definir variable", "crear" },
{ "inicializar variable", "crear" },
{ "establecer variable", "crear" },
{ "crear una variable", "crear" },

{ "numero", "int" },
{ "string", "char" },
{ "boolean", "bool" },

{ "es igual a", "==" },
{ "es diferente de", "!=" },
{ "mayor o igual que", ">=" },
{ "menor o igual que", "<=" },

{ "escribir", "cout <<" },
{ "mostrar mensaje", "cout <<" },
{ "leer valor", "cin >>" },
{ "capturar", "cin >>" },

{ "si no", "else" },
{ "mientras que", "while" },
{ "repetir", "do { } while(...)" },

{ "finalizar", "return 0; }" },
{ "cerrar programa", "return 0; }" }
};