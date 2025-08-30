#pragma once

using namespace System;
using namespace System::Collections::Generic;

ref class GeneradorCodigo {
private:
    List<String^>^ lineas;

public:
    GeneradorCodigo() {
        lineas = gcnew List<String^>();
        lineas->Add("#include <iostream>");
        lineas->Add("using namespace std;");
        lineas->Add("int main() {");
    }

    void Agregar(String^ instruccionCpp) {
        lineas->Add("    " + instruccionCpp);
    }

    List<String^>^ Finalizar() {
        lineas->Add("    return 0;");
        lineas->Add("}");
        return lineas;
    }
};