#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    int arrCodStream[MAX_STREAMS],arrIdiomaStream[MAX_STREAMS],arrNumCat[MAX_STREAMS],cantStreams=0;
    double arrDuracionHoras[MAX_STREAMS];
    char arrLetraCat[MAX_STREAMS];
    CargarInfoStreams("ArchivosDeDatos/Streams.txt",arrCodStream,arrIdiomaStream,arrDuracionHoras,arrNumCat,
        arrLetraCat,cantStreams);
    VerificarDatos("ArchivosDeReportes/DatosParcialesStreams.txt",arrCodStream,arrIdiomaStream,arrDuracionHoras,arrNumCat,
        arrLetraCat,cantStreams);
    int arrReproReciente[MAX_STREAMS]{},arrReproMasAntigua[MAX_STREAMS]{},arrNumReproducciones[MAX_STREAMS]{};
    double arrPromRting[MAX_STREAMS]{},arrPromTasaDroppOff[MAX_STREAMS]{};
    CargarDemasArreglosAuxiliares("ArchivosDeDatos/Canales.txt",arrCodStream,cantStreams,
        arrReproReciente,arrReproMasAntigua,arrNumReproducciones,arrPromRting,arrPromTasaDroppOff);
    // cout.precision(2);
    // cout<<fixed;
    // for (int i = 0; i < cantStreams; i++) {
    //     cout<<arrCodStream[i]<<" - "<<arrDuracionHoras[i]<<" - "
    //         <<arrIdiomaStream[i]<<" - "<<arrLetraCat[i]
    //         <<arrNumCat[i]<<endl;
    // }
    // cout.precision(2);
    // cout<<fixed;
    // for (int i = 0; i < cantStreams; i++) {
    //         cout<<arrCodStream[i]<<" - "<<arrReproReciente[i]<<" "<<arrReproMasAntigua[i]<<" "<<arrNumReproducciones[i]
    //         <<" "<<arrPromRting[i]<<" "<<arrPromTasaDroppOff[i]<<endl;
    // }
    EmitirReporteStreams("ArchivosDeReportes/Reproducciones_Streams.txt",arrCodStream,arrIdiomaStream,arrDuracionHoras,arrNumCat,
    arrLetraCat,cantStreams,arrReproReciente,arrReproMasAntigua,arrNumReproducciones,arrPromRting,arrPromTasaDroppOff,false);
    OrdenarDatos(arrCodStream,arrIdiomaStream,arrDuracionHoras,arrNumCat,
    arrLetraCat,cantStreams,arrReproReciente,arrReproMasAntigua,arrNumReproducciones,arrPromRting,arrPromTasaDroppOff);
    EmitirReporteStreams("ArchivosDeReportes/DETALLECOMPLETODEREPRODUCCIONDESTREAMSORDENADOPORCATEGORIAYTASADROPP-OOF.txt",arrCodStream,arrIdiomaStream,arrDuracionHoras,arrNumCat,
    arrLetraCat,cantStreams,arrReproReciente,arrReproMasAntigua,arrNumReproducciones,arrPromRting,arrPromTasaDroppOff,true);




    return 0;
}
