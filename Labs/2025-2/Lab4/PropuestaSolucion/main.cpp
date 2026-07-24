#include "Bibliotecas/FuncionesAuxiliares.h"

int main(int argc, char**argv) {
    int fechaCreacion[TAM_CANALES],numCodCanal[TAM_CANALES],cantCnales=0,
        arrCodEtiqueta[TAM_ETIQUETA],cantEtiquetas=0,arrNumTotalReproCanal[TAM_CANALES]{},
        arrCantidadTotalReproduccEtiqueta[TAM_ETIQUETA]{};
    char letraCanal[TAM_CANALES];
    double ratingCanal[TAM_CANALES],duracionHorasEtiqueta[TAM_ETIQUETA],arrTiempoTotalReproduccCanal[TAM_CANALES]{},
        arrIngresosXReprodEtiquetas[TAM_CANALES]{},arrTiempoTotalReproEtiqueta[TAM_ETIQUETA]{},arrPorcentajeRating[TAM_CANALES],
        tarifaXDurEtiqueta;

    CargarCanales("ArchivosDeDatos/Canales.txt",fechaCreacion,numCodCanal,
        letraCanal,ratingCanal,cantCnales);
    CargarEtiquetas("ArchivosDeDatos/Etiquetas.txt",arrCodEtiqueta,duracionHorasEtiqueta,cantEtiquetas);
    EmitirReporteSimple("ArchivosDeReporte/ReporteSimple.txt",fechaCreacion,numCodCanal,letraCanal,ratingCanal,cantCnales,
        arrCodEtiqueta,duracionHorasEtiqueta,cantEtiquetas);
    cout<<"Ingrese la tarifa por duración de la etiqueta:"<<endl;
    cin>>tarifaXDurEtiqueta;
    //0.78
    ProcesarReproducciones("ArchivosDeDatos/ReproduccionesDeEtiquetas.txt",fechaCreacion,numCodCanal,
        letraCanal,ratingCanal,cantCnales,arrNumTotalReproCanal,arrTiempoTotalReproduccCanal,arrPorcentajeRating,arrIngresosXReprodEtiquetas,
        arrCodEtiqueta,duracionHorasEtiqueta,cantEtiquetas,arrCantidadTotalReproduccEtiqueta,arrTiempoTotalReproEtiqueta,tarifaXDurEtiqueta);

    EmitirReporte("ArchivosDeReporte/ReporteDeCanales_Y_Etiquetas.txt",fechaCreacion,numCodCanal,
        letraCanal,ratingCanal,cantCnales,arrNumTotalReproCanal,arrTiempoTotalReproduccCanal,arrPorcentajeRating,arrIngresosXReprodEtiquetas,
        arrCodEtiqueta,duracionHorasEtiqueta,cantEtiquetas,arrCantidadTotalReproduccEtiqueta,arrTiempoTotalReproEtiqueta,tarifaXDurEtiqueta);



    return 0;
}
