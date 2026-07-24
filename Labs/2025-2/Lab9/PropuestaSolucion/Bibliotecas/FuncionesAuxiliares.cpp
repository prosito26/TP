//
// Created by aml on 17/11/2025.
//

#include "FuncionesAuxiliares.h"

void cargarCategorias(const char *nombArch, struct Categoria *arrCategorias, int &cantidadCategorias) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo " << nombArch << endl;
        exit(1);
    }
    while (true) {
        arrCategorias[cantidadCategorias].codigo = leeCadenaExactaDelim(arch, ',');
        if (arch.eof()) break;
        arrCategorias[cantidadCategorias].nombre = leeCadenaExactaDelim(arch, ',');
        arrCategorias[cantidadCategorias].descripcion = leeCadenaExactaDelim(arch, '\n');
        arrCategorias[cantidadCategorias].reproducciones = new struct Reproduccion[MAX_REPRODUCCIONES]{};
        cantidadCategorias++;
    }
}

char *leeCadenaExactaDelim(ifstream &arch, char delim) {
    char cadena[100], *ptr;
    arch.getline(cadena, 100, delim);
    if (arch.eof()) return nullptr;
    ptr = new char[strlen(cadena) + 1];
    strcpy(ptr, cadena);
    return ptr;
}

void emitirDatos(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias, bool verificar,
                 bool emitirReproducc, bool comentarios) {
    ofstream archReporte(nombArch, ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo " << nombArch << endl;
        exit(1);
    }
    archReporte << setprecision(2) << fixed;
    archReporte << setw(50) << " " << "REPORTE POR CATEGORIAS" << endl;
    for (int i = 0; i < cantidadCategorias; i++) {
        if (verificar) {
            imprimirLinea(archReporte, '=', 120);
            archReporte << "Codigo: " << setw(5) << " " << left << setw(50) << arrCategorias[i].codigo << right << endl;
            archReporte << "Nombre: " << setw(5) << " " << left << setw(50) << arrCategorias[i].nombre << right << endl;
            archReporte << "Descripcion: " << left << setw(15) << arrCategorias[i].descripcion << right << endl;
            if (emitirReproducc) {
                imprimirReproducciones(arrCategorias[i].reproducciones, arrCategorias[i].numReproducciones, archReporte,
                                       comentarios);
            }
        }
    }
}

void imprimirLinea(ofstream &archReporte, char car, int tam) {
    for (int i = 0; i < tam; i++) {
        archReporte << car;
    }
    archReporte << endl;
}

void cargarDemasDatosCategorias(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo " << nombArch << endl;
        exit(1);
    }
    char nombreCanal[30], categoriaAsociadas[10], car;
    double rating;
    int duracionSeg, hh, min, seg, posCategoria;
    while (true) {
        arch.getline(nombreCanal, 30, ',');
        if (arch.eof()) break;
        arch.getline(categoriaAsociadas, 10, ',');
        arch >> rating >> car >> hh >> car >> min >> car >> seg;
        duracionSeg = hh * 3600 + min * 60 + seg;
        arch.get();
        posCategoria = BuscarCategoria(categoriaAsociadas, arrCategorias, cantidadCategorias);
        if (posCategoria != NO_ENCONTRADO) {
            int i = arrCategorias[posCategoria].numReproducciones;
            asignarCadena(arrCategorias[posCategoria].reproducciones[i].canal, nombreCanal);
            arrCategorias[posCategoria].reproducciones[i].duracion = duracionSeg;
            arrCategorias[posCategoria].reproducciones[i].rating = rating;
            arrCategorias[posCategoria].numReproducciones++;
        }
    }
}

int BuscarCategoria(const char *categoriaAsociadas, struct Categoria *arrCategorias, int cantidadCategorias) {
    for (int i = 0; i < cantidadCategorias; i++) {
        if (strcmp(arrCategorias[i].codigo, categoriaAsociadas) == 0) return i;
    }
    return NO_ENCONTRADO;
}

void asignarCadena(char *&cadenaDestino, char *cadenaFuente) {
    cadenaDestino = new char[strlen(cadenaFuente) + 1];
    strcpy(cadenaDestino, cadenaFuente);
}

void imprimirReproducciones(struct Reproduccion *reproducciones, int numReproducciones,
                            ofstream &archReporte, bool comentarios) {
    imprimirLinea(archReporte, '-', 120);
    archReporte << "REPRODUCCIONES: " << endl;
    for (int i = 0; i < numReproducciones; i++) {
        archReporte << "CANAL:" << left << setw(50) << reproducciones[i].canal << "RATING:" << right << setw(5) <<
                reproducciones[i].rating
                << setw(10) << " " << "DURACION:";
        imprimirDuracion(reproducciones[i].duracion, archReporte);
        archReporte << endl;
        if (comentarios) {
            archReporte << setw(10) << " " << "COMENTARIOS:" << endl;
            imprimirComentarios(reproducciones[i].comentarios, reproducciones[i].numComentarios, archReporte);
        }
    }
}

void imprimirDuracion(int duracion, ofstream &archReporte) {
    int hh, min, seg;
    hh = duracion / 3600;
    min = ((duracion % 3600) / 60);
    seg = duracion % 60;
    archReporte << setfill('0') << setw(2) << hh << ":" << setw(2) << min << ":" << setw(2) << seg << setfill(' ') <<
            setw(10) << " ";
}

void imprimirComentarios(char **comentarios, int numComentarios, ofstream &archReporte) {
    for (int i = 0; i < numComentarios; i++) {
        archReporte << setw(10) << " " << "- ";
        archReporte << comentarios[i] << endl;
    }
}

void ordenarCategorias(struct Categoria *arrCategorias, int cantidadCategorias) {
    for (int i = 0; i < cantidadCategorias - 1; i++) {
        for (int k = i + 1; k < cantidadCategorias; k++) {
            if (strcmp(arrCategorias[i].nombre, arrCategorias[k].nombre) > 0) {
                intercambiarStruct(arrCategorias[i], arrCategorias[k]);
            }
        }
    }
}

void intercambiarStruct(struct Categoria &arrCategoriasI, struct Categoria &arrCategoriasK) {
    struct Categoria aux;
    aux = arrCategoriasI;
    arrCategoriasI = arrCategoriasK;
    arrCategoriasK = aux;
}

void cargarComentarios(const char *nombArch, struct Categoria *arrCategorias, int cantidadCategorias) {
    ifstream arch(nombArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo " << nombArch << endl;
        exit(1);
    }
    char canal[50], *ptrComentario;
    while (true) {
        arch.getline(canal, 50, ',');
        if (arch.eof()) break;
        ptrComentario = leeCadenaExactaDelim(arch, '\n');
        asignarComentario(canal, arrCategorias, cantidadCategorias, ptrComentario);
    }
}

void asignarComentario(const char *canal, struct Categoria *arrCategorias, int cantidadCategorias,
                       char *ptrComentario) {
    for (int i = 0; i < cantidadCategorias; i++) {
        for (int k = 0; k < arrCategorias[i].numReproducciones; k++) {
            if (strcmp(canal, arrCategorias[i].reproducciones[k].canal) == 0) {
                int n = arrCategorias[i].reproducciones[k].numComentarios;
                asignarCadena(arrCategorias[i].reproducciones[k].comentarios[n], ptrComentario);
                arrCategorias[i].reproducciones[k].numComentarios++;
            }
        }
    }
}
