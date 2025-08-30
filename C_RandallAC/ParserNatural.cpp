#include "pch.h"
#include "DiccionarioManual.h"
#include "ParserNatural.h"

String^ ParserNatural::ParseLinea(String^ linea) {
    linea = linea->Trim()->ToLower();

    // Reemplazo manual usando el diccionario
    for (int i = 0; i < MAX_ENTRADAS; ++i) {
        String^ clave = gcnew String(diccionario[i].palabraNatural);
        String^ traduccion = gcnew String(diccionario[i].traduccionCpp);

        if (linea->Contains(clave)) {
            linea = linea->Replace(clave, traduccion);
        }
    }

    // Validaci�n m�nima
    if (linea->Contains("cout") || linea->Contains("int") || linea->Contains("for")) {
        return linea;
    }
    else {
        return "// Instrucci�n no reconocida: " + linea;
    }
}