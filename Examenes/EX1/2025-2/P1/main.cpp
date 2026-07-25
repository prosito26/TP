#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    ifstream archCanales("ArchivosDeDatos/Canales.txt", ios::in);
    if (not archCanales.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }
    ifstream archCategorias("ArchivosDeDatos/Categorias.txt", ios::in);
    if (not archCategorias.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }
    ifstream archIdiomas("ArchivosDeDatos/Idiomas.txt", ios::in);
    if (not archIdiomas.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }
    ifstream archStreams("ArchivosDeDatos/Streams.txt", ios::in);
    if (not archStreams.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }
    ofstream archReporte("ArchivosDeReporte/Reporte.txt", ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }

    EmitirReporte(archCanales,archStreams,archCategorias,archIdiomas,archReporte);

    return 0;
}
