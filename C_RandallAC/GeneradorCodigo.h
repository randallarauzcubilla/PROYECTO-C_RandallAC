#define MAX_LINEA 256
struct NodoCodigo {
    char linea[MAX_LINEA];
    NodoCodigo* siguiente;
};

class GeneradorCodigo {
private:
    NodoCodigo* cabeza;
    NodoCodigo* cola;

    bool contiene(const char* texto);

public:
    GeneradorCodigo();
    ~GeneradorCodigo();

    void agregar(const char* instruccionCpp, bool indentar);
    void finalizar();
    void imprimirCodigo();  // útil para debug
    void generarArchivo(const char* nombreArchivo);
    void limpiar();
    void agregarFueraMain(const char* instruccionCpp);
};
