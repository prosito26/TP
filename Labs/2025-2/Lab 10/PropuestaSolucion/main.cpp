#include "Bibliotecas/FuncionesAuxiliares.h"


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
