#include "Bibliotecas/FuncionesAuxiliares.h"
/*
 * NOMBRE: ALVARO HUARI
 * CODIGO:20231476
 * DESCRICPION: MI PROGRAMA SE ENCARGA DE GENERAR ARCHIVOS DE REPORTE POR CADA CATEGORIA Y SU RESPECTICA RATING TASA  IMPRIMIR LOS CANALES DONDE
 * ESTE SE REPRODUCCE LAS FECHAS Y EL PROMEDIO DE RATINNG Y TASA.
 */

int main() {

    int arrFechaReproduccStream[MAX_STREAMS],cantStreams=0,cantCategorias=0;
    char *arrNombreCanal[MAX_STREAMS],*arrCategoriaAsociada[MAX_STREAMS];
    double arrDuracionHorasStream[MAX_STREAMS],arrRatingCalidad[MAX_STREAMS],arrTasaDroppOf[MAX_STREAMS];
    char enlace[70];
    char *arrCodigoCategoria[MAX_CATEGORIAS],*arrNombreCategoria[MAX_CATEGORIAS];

    //generaArchivoEnlace(arrCodigoCategoria,"ArchivosDeReportes/",enlace);

    cargarCategorias("ArchivosDeDatos/Categorias.txt",arrCodigoCategoria,arrNombreCategoria,cantCategorias);

    VerificarDatos("ArchivosDeReportes/ReporteDePruebaDeCategorias.txt",arrCodigoCategoria,arrNombreCategoria,cantCategorias);
    // for (int i=0;i<cantCategorias;i++) {
    //     cout<<setw(20)<<arrCodigoCategoria[i]<<" "<<setw(80)<<arrNombreCategoria[i]<<endl;
    // }
    cargarStreams("ArchivosDeDatos/Reproducciones.txt",arrFechaReproduccStream,arrNombreCanal,arrCategoriaAsociada,arrDuracionHorasStream,
        arrRatingCalidad,arrTasaDroppOf,cantStreams);

    VerificarStreams("ArchivosDeReportes/ReporteDePruebaDeStreamsReproducidos.txt",arrFechaReproduccStream,arrNombreCanal,arrCategoriaAsociada,arrDuracionHorasStream,
        arrRatingCalidad,arrTasaDroppOf,cantStreams);

    EmitirReporte(arrFechaReproduccStream,arrNombreCanal,arrCategoriaAsociada,arrDuracionHorasStream,
    arrRatingCalidad,arrTasaDroppOf,cantStreams,arrCodigoCategoria,arrNombreCategoria,cantCategorias);




    return 0;
}