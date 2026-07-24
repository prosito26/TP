#include "Bibliotecas/FuncionesAuxiliares.h"
/*
 * NOMBRE: ALVARO HUARI
 * CODIGO: 20231476
    DESCRIPCION:Mi programa usa el paradigma de las esturcturas para guardar una categoria con su codigo,nombre y descipcion; así mismo
    cada categoria se reproduce en un canal con su respectivo rating y duracion,además, se agrega la lista de comentarios.
 */
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
