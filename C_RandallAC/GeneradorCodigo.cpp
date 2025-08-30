#include "pch.h"
#include "GeneradorCodigo.h"

// Verifica si una línea ya existe en el código generado
bool GeneradorCodigo::Contiene(String^ texto) {
    for each (String ^ linea in lineas) {
        if (linea->Contains(texto)) return true;
    }
    return false;
}

// Constructor: inicializa el código base con encabezados y función main si no existen
GeneradorCodigo::GeneradorCodigo() {
    lineas = gcnew List<String^>();

    if (!Contiene("#include <iostream>"))
        lineas->Add("#include <iostream>");

    if (!Contiene("using namespace std;"))
        lineas->Add("using namespace std;");

    if (!Contiene("int main() {"))
        lineas->Add("int main() {");
}

// Agrega una instrucción traducida al cuerpo del main
void GeneradorCodigo::Agregar(String^ instruccionCpp) {
    lineas->Add("    " + instruccionCpp);
}

// Finaliza el código agregando return y cierre de función si no existen
List<String^>^ GeneradorCodigo::Finalizar() {
    if (!Contiene("return 0;"))
        lineas->Add("    return 0;");

    if (!Contiene("}"))
        lineas->Add("}");

    return lineas;
}