#include "Bibliotecas/FuncionesAuxiliares.h"


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
