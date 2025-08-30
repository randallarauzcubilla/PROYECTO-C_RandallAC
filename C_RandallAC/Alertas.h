#pragma once
using namespace System;
using namespace System::Windows::Forms;

ref class Alertas {
public:
    static void MostrarInfo(String^ mensaje) {
        MessageBox::Show(mensaje, "Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
    }

    static void MostrarAdvertencia(String^ mensaje) {
        MessageBox::Show(mensaje, "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
    }

    static void MostrarError(String^ mensaje) {
        MessageBox::Show(mensaje, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }

    static bool Confirmar(String^ mensaje) {
        DialogResult resultado = MessageBox::Show(mensaje, "Confirmar", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
        return resultado == DialogResult::Yes;
    }
};