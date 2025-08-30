#include "pch.h"
#include "GeneradorCodigo.h"

GeneradorCodigo::GeneradorCodigo() {
    lineas = gcnew List<String^>();
    lineas->Add("#include <iostream>");
    lineas->Add("using namespace std;");
    lineas->Add("int main() {");
}

void GeneradorCodigo::Agregar(String^ instruccionCpp) {
    lineas->Add("    " + instruccionCpp);
}

List<String^>^ GeneradorCodigo::Finalizar() {
    lineas->Add("    return 0;");
    lineas->Add("}");
    return lineas;
}