#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    //803100    1:22:25    4003    C1072
    int arrCodStream[MAX_STREAMS],arrCodIdioma[MAX_STREAMS],arrNumCat[MAX_STREAMS],cantStreams=0;
    double arrDuracionHoras[MAX_STREAMS];
    char arrCharCat[MAX_STREAMS];
    CargarStreams("ArchivosDeDatos/Streams.txt",arrCodStream,arrCodIdioma,arrNumCat,arrDuracionHoras,arrCharCat,cantStreams);
    VerificarDatos("ArchivosDeReporte/ReporteSimple.txt",arrCodStream,arrCodIdioma,arrNumCat,arrDuracionHoras,arrCharCat,cantStreams);


    int arrRepAntigua[MAX_STREAMS]{},arrRepRec[MAX_STREAMS]{},arrNumRepr[MAX_STREAMS]{};
    double arrPromRatCal[MAX_STREAMS]{},arrPromTasa[MAX_STREAMS]{},arrTiempoTotalRepr[MAX_STREAMS]{};

    cargarArreglosAuxiliares("ArchivosDeDatos/Canales.txt",arrCodStream,arrCodIdioma,arrNumCat,arrDuracionHoras,arrCharCat,
        arrRepAntigua,arrRepRec,arrNumRepr,arrPromRatCal,arrPromTasa,arrTiempoTotalRepr,cantStreams);
    cout.precision(2);
    cout<<fixed;
    // for (int i=0;i<cantStreams;i++) {
    //     cout<<arrCodStream[i]<<" "<<arrNumRepr[i]<<" - "<<arrPromRatCal[i]<<" - "<<arrPromTasa[i]<<endl;
    // }

    EmitirReporte("ArchivosDeReporte/Reproducciones-Streams.txt",arrCodStream,arrCodIdioma,arrNumCat,arrDuracionHoras,arrCharCat,
        arrRepAntigua,arrRepRec,arrNumRepr,arrPromRatCal,arrPromTasa,arrTiempoTotalRepr,cantStreams,false,
        true);

    OrdenarArreglos(arrCodStream,arrCodIdioma,arrNumCat,arrDuracionHoras,arrCharCat,
        arrRepAntigua,arrRepRec,arrNumRepr,arrPromRatCal,arrPromTasa,arrTiempoTotalRepr,cantStreams);

    EmitirReporte("ArchivosDeReporte/Reproducciones-Streams-Ordenado.txt",arrCodStream,arrCodIdioma,arrNumCat,arrDuracionHoras,arrCharCat,
        arrRepAntigua,arrRepRec,arrNumRepr,arrPromRatCal,arrPromTasa,arrTiempoTotalRepr,cantStreams,true,false);

    return 0;

}