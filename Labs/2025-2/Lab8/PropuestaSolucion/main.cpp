#include "Bibliotecas/FuncionesAuxiliares.h"
/*
 * NOMBRE:ALVARO HUARI
 * CODIGO:20231476
   DESCRIPCION:Mi programa usa el metodo de estructuras y areglo de estructuras estáticas para poder
   generar un reporte por categoria donde se muestra los canales donde se reproduccioneron, los nombres de dichos canales,
   el rating al canal asociado, la duracion. Asi como un resumen final del promedio del rating y duracion total por categoria .
 */

int main() {

    struct Categoria arrCategorias[MAX_CATEGORIAS]{};
    int cantCategorias=0;

    cargarCategorias("ArchivosDeDatos/Categorias.csv",arrCategorias,cantCategorias);
    emitirReporte("ArchivosDeReportes/ReporteDePruebaDeCategorias.txt",arrCategorias,cantCategorias,false,false);
    cargarDemasDatosCategorias("ArchivosDeDatos/Reproducciones.csv",arrCategorias,cantCategorias);
    emitirReporte("ArchivosDeReportes/ReporteDePruebaConReproducciones.txt",arrCategorias,cantCategorias,true,false);
    calcularPromedioYDuracionTotal(arrCategorias,cantCategorias);
    emitirReporte("ArchivosDeReportes/ReportePorCategorias.txt",arrCategorias,cantCategorias,true,true);

    return 0;
}