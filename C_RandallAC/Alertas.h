#pragma once

using namespace System;
using namespace System::Windows::Forms;

ref class Alertas {
public:
    static void MostrarInfo(String^ mensaje);
    static void MostrarAdvertencia(String^ mensaje);
    static void MostrarError(String^ mensaje);
    static bool Confirmar(String^ mensaje);
};