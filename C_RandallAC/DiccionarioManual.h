#ifndef DICCIONARIO_MANUAL_H
#define DICCIONARIO_MANUAL_H

const int MAX_ENTRADAS = 50;

struct EntradaDiccionario {
    char palabraNatural[40];
    char traduccionCpp[40];
};

EntradaDiccionario diccionario[MAX_ENTRADAS] = {
    {"sumar", "+"},
    {"restar", "-"},
    {"multiplicar", "*"},
    {"dividir", "/"},
    {"calcular", "operaci�n"},
    {"total", "int total;"},
    {"resultado", "int resultado;"},

    {"crear variable", "tipo nombre;"},
    {"entero", "int"},
    {"n�mero entero", "int"},
    {"decimal", "float"},
    {"n�mero decimal", "float"},
    {"texto", "string"},
    {"palabra", "string"},
    {"cadena de texto", "string"},
    {"car�cter", "char"},
    {"booleano", "bool"},
    {"valor inicial", "variable = valor;"},
    {"asignar valor", "variable = valor;"},

    {"crear lista", "tipo nombre[];"},
    {"crear arreglo", "tipo nombre[];"},
    {"lista de", "tipo nombre[];"},
    {"con elementos", "tipo nombre[n];"},
    {"recorrer la lista", "for"},
    {"agregar a la lista", "push_back"},

    {"si", "if"},
    {"sino", "else"},
    {"mientras", "while"},
    {"repetir hasta", "do { } while(...)"},
    {"para", "for"},

    {"condici�n", "expresi�n booleana"},
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
    {"mensaje", "texto dentro de cout"},

    {"comenzar programa", "int main() {"},
    {"terminar programa", "return 0; }"},
    {"fin", "return 0; }"},
    {"comentario", "// comentario"},
    {"definir funci�n", "tipo nombreFuncion(...)"},
    {"llamar funci�n", "nombreFuncion();"}
};

#endif