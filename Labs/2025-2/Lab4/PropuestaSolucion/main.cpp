#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char**argv) {

    ifstream archCanales("ArchivosDeDatos/Canales.txt",ios::in);
    if (not archCanales.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }
    ifstream archEtiquetas("ArchivosDeDatos/Etiquetas.txt",ios::in);
    if (not archEtiquetas.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }
    ifstream archReproDeEti("ArchivosDeDatos/ReproduccionesDeEtiquetas.txt",ios::in);
    if (not archReproDeEti.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }
    ofstream archReporte("ArchivosDeReporte/Reporte.txt",ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }
    double tarifaDurEtiq;
    cout<<"Ingrese la tarifa por duracion de la etiqueta:"<<endl;
    cin>>tarifaDurEtiq;

    EmitirReporte(archCanales,archEtiquetas,archReproDeEti,archReporte,tarifaDurEtiq);

    return 0;
}
