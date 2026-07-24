#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char **argv) {

    ifstream archLeer("ArchivosDeDatos/twitchdataTP.txt",ios::in);
    if (not archLeer.is_open()) {
        cout<<"El archivo ArchivosDeDatos/twitchdataTP.txt no se pudo abrir";
        exit(1);
    }
    ofstream archReporte("ArchivosDeReporte/Reporte.txt",ios::out);
    if (not archReporte.is_open()) {
        cout<<"El archivo ArchivosDeReporte/Reporte.txt no se pudo abrir";
        exit(1);
    }
    int ddI,mmI,aaI,ddF,mmF,aaF;
    double pagoXRepr,pagoXTiempo;
    cout<<"Ingrese la fecha inicial:"<<endl;
    cin>>ddI>>mmI>>aaI;
    cout<<endl;
    cout<<"Ingrese la fecha límite:"<<endl;
    cin>>ddF>>mmF>>aaF;
    cout<<endl;
    cout<<"Ingrese el pago por el numero de reproducciones y el pago por tiempo de reproducciones:"<<endl;
    cin>>pagoXRepr>>pagoXTiempo;
    ProcesarDatos(archLeer,archReporte,ddI,mmI,aaI,ddF,mmF,aaF,pagoXRepr,pagoXTiempo);



    return 0;
}
