#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    int arrFechaCreacCanal[MAX_CANALES], arrIntCodCanal[MAX_CANALES], cantCanales = 0;
    double arrRatingCanal[MAX_CANALES];
    char arrCharCodCanal[MAX_CANALES];

    cargarCanales("ArchivosDeDatos/Canales (4).txt", arrFechaCreacCanal, arrIntCodCanal,
                  arrCharCodCanal, arrRatingCanal, cantCanales);

    int arrCodEtiqueta[MAX_ETIQUETAS], cantEtiquetas = 0;
    double arrDuracionEtiquetaHoras[MAX_ETIQUETAS];

    cargarEtiquetas("ArchivosDeDatos/Etiquetas (1).txt", arrCodEtiqueta, arrDuracionEtiquetaHoras,
                    cantEtiquetas);

    double tarifa;
    cout<<"Ingrese el valor de la tarifa por duracion:"<<endl;
    cin>>tarifa;


    int codigoIntCanalEnEtiqueta[MAX_ETIQUETAS_CANALES], codigoEtiquetaEnCanal[MAX_ETIQUETAS_CANALES],
            cantEtiquetaEnCanal = 0;
    char codigoCharCanalEnEtiqueta[MAX_ETIQUETAS_CANALES];

    cargarEtiqeutasEnCanales("ArchivosDeDatos/EtiquetasEnCanales (1).txt", codigoIntCanalEnEtiqueta,
                             codigoCharCanalEnEtiqueta,
                             codigoEtiquetaEnCanal, cantEtiquetaEnCanal);

    ordenarArreglos(arrCodEtiqueta, arrDuracionEtiquetaHoras, cantEtiquetas);

    int arrFechaReproducc[MAX_ETIQUETAS_CANALES]{}, arrNumReproducc[MAX_ETIQUETAS_CANALES]{};
    cargarInfoEtiquetas("ArchivosDeDatos/ReproduccionesDeEtiquetas (1).txt", arrFechaReproducc, arrNumReproducc,
                        codigoIntCanalEnEtiqueta, codigoCharCanalEnEtiqueta,
                        codigoEtiquetaEnCanal, cantEtiquetaEnCanal);

    emitirReporte("ArchivosDeReportes/ReporteDeCanales_Y_Etiquetas.txt", arrFechaCreacCanal, arrIntCodCanal,
                  arrCharCodCanal, arrRatingCanal, cantCanales, arrCodEtiqueta, arrDuracionEtiquetaHoras,
                  cantEtiquetas, codigoIntCanalEnEtiqueta,codigoCharCanalEnEtiqueta,
                  codigoEtiquetaEnCanal, cantEtiquetaEnCanal, arrFechaReproducc, arrNumReproducc,tarifa);
    // for (int i=0;i<cantEtiquetaEnCanal;i++) {
    //     cout<<codigoCharCanalEnEtiqueta[i]<<codigoIntCanalEnEtiqueta[i]<<" "<<codigoEtiquetaEnCanal[i]<<endl;
    // }

    // cout.precision(2);
    // cout<<fixed;
    // for (int i=0;i<cantEtiquetas;i++) {
    //     cout<<arrCodEtiqueta[i]<<" "<<arrDuracionEtiquetaHoras[i]<<endl;
    // }

    // for(int i=0;i<cantCanales;i++) {
    //     cout<<arrFechaCreacCanal[i]<<" "<<arrCharCodCanal[i]<<arrIntCodCanal[i]<<" "<<arrRatingCanal[i]<<endl;
    // }


    return 0;
}
