#pragma once
using namespace System;

ref class ParserNatural {
public:
    static String^ ParseLinea(String^ linea) {
        linea = linea->Trim()->ToLower();
        array<String^>^ palabras = linea->Split(' ');

        if (palabras->Length >= 3 && palabras[0] == "sumar") {
            return "cout << (" + palabras[1] + " + " + palabras[2] + ") << endl;";
        }
        else if (palabras->Length >= 2 && palabras[0] == "mostrar") {
            String^ mensaje = linea->Substring(8);
            return "cout << \"" + mensaje + "\" << endl;";
        }
        else {
            return "// Instrucción no reconocida: " + linea;
        }
    }
};