#pragma once

using namespace System;
using namespace System::Collections::Generic;

ref class GeneradorCodigo {
private:
    List<String^>^ lineas;

public:
    GeneradorCodigo();
    void Agregar(String^ instruccionCpp);
    List<String^>^ Finalizar();
};