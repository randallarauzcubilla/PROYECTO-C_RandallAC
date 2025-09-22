#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINEA_GENERADOR 256
struct NodoCodigo {
    char linea[MAX_LINEA_GENERADOR];
    NodoCodigo* siguiente;
};

class GeneradorCodigo {
private:
    NodoCodigo* cabeza;
    NodoCodigo* cola;
    NodoCodigo* cabezaFueraMain;
    NodoCodigo* colaFueraMain;

public:
    GeneradorCodigo();
    ~GeneradorCodigo();
    bool contiene(const char* texto);
    void agregar(const char* instruccionCpp, bool indentar);
    void finalizar();
    void imprimirCodigo();  // útil para debug
    void generarArchivo(const char* nombreArchivo);
    void limpiar();
    void agregarFueraMain(const char* instruccionCpp);
    void  generarLlamadaFuncion(const char* nombre, const char* parametrosRaw, char* llamadaCpp);
};
