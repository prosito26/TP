#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {
    struct Categoria *arrCategorias;
    int cantidadCategorias = 0;
    arrCategorias = new struct Categoria[MAX_CATEGORIAS]{};

    cargarCategorias("ArchivosDeDatos/Categorias.csv", arrCategorias, cantidadCategorias);
    emitirDatos("ArchivosDeReportes/ReporteDePruebaDeCategorias.txt", arrCategorias, cantidadCategorias, true, false,
                false);
    cargarDemasDatosCategorias("ArchivosDeDatos/StreamsReproducidos.csv", arrCategorias, cantidadCategorias);
    emitirDatos("ArchivosDeReportes/ReporteDePruebaConReproducciones.txt", arrCategorias, cantidadCategorias, true,
                true, false);
    ordenarCategorias(arrCategorias, cantidadCategorias);
    emitirDatos("ArchivosDeReportes/ReporteDePruebaOrdenado.txt", arrCategorias, cantidadCategorias, true, true, false);
    cargarComentarios("ArchivosDeDatos/ComentariosAlCanal.csv", arrCategorias, cantidadCategorias);
    emitirDatos("ArchivosDeReportes/ReporteDePruebaConComentarios.txt", arrCategorias, cantidadCategorias, true, true,
                true);

    return 0;
}
