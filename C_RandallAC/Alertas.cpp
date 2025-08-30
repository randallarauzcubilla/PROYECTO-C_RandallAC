#include "pch.h"
#include "Alertas.h"

void Alertas::MostrarInfo(String^ mensaje) {
    MessageBox::Show(mensaje, "Información", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

void Alertas::MostrarAdvertencia(String^ mensaje) {
    MessageBox::Show(mensaje, "Advertencia", MessageBoxButtons::OK, MessageBoxIcon::Warning);
}

void Alertas::MostrarError(String^ mensaje) {
    MessageBox::Show(mensaje, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
}

bool Alertas::Confirmar(String^ mensaje) {
    DialogResult resultado = MessageBox::Show(mensaje, "Confirmar", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
    return resultado == DialogResult::Yes;
}