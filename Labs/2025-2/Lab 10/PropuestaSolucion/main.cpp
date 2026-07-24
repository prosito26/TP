#include "Bibliotecas/FuncionesAuxiliares.h"
/*
 * NOMBRE:ALVARO HUARI
    CODIGO:20231476
    DESCRIPCION:Mi programa usa el paradigma de las listas simplemente ligadas
    para insertar ordenadamente las categorias por su codigo, y calcular el canal
    con la maxima reporduccion y su duracion,así miusmo la lista de dropp off, y su promedio;por ultimo
    se calcula el tiempo de duracion Total.
*/

int main() {

    struct Nodo *listaCategorias;
    cargarCategorias("ArchivosDeDatos/Categorias.csv",listaCategorias);
    emitirReporte("ArchivosDeReportes/ReporteDePruebaDeCategorias.txt",listaCategorias);
    completarLista("ArchivosDeDatos/StreamsReproducidos.csv",listaCategorias);
    calcularPromedio(listaCategorias);
    emitirReporte("ArchivosDeReportes/ReporteDeCategoriasCompleto.txt",listaCategorias);
    eliminarNodos(listaCategorias);
    emitirReporte("ArchivosDeReportes/ReporteDeCategoriasEliminados.txt",listaCategorias);
    // struct Nodo *p=listaCategorias;
    // while (p) {
    //     cout<<p->categoria.codigo<<" "<<p->categoria.nombre<<" "<<p->categoria.descripcion<<endl;
    //     p=p->siguiente;
    // }


    return 0;
}