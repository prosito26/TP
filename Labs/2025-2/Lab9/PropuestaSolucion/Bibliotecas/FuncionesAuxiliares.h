//
// Created by aml on 17/11/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

#include "Categoria.h"
#define NO_ENCONTRADO -1
#define MAX_CATEGORIAS 110
#define MAX_REPRODUCCIONES 15

void cargarCategorias(const char*nombArch,struct Categoria *arrCategorias,int &cantidadCategorias) ;
char *leeCadenaExactaDelim(ifstream &arch,char delim);
void emitirDatos(const char*nombArch,struct Categoria *arrCategorias,int cantidadCategorias,bool verificar,
    bool emitirReproducc,bool comentarios);
void imprimirLinea(ofstream &archReporte,char car,int tam);
void cargarDemasDatosCategorias(const char*nombArch,struct Categoria *arrCategorias,int cantidadCategorias);
int BuscarCategoria(const char *categoriaAsociadas,struct Categoria *arrCategorias,int cantidadCategorias);
void asignarCadena(char *&cadenaDestino,char *cadenaFuente) ;
void imprimirReproducciones(struct Reproduccion *reproducciones,int numReproducciones,
    ofstream &archReporte,bool comentarios);
void imprimirDuracion(int duracion,ofstream &archReporte);
void imprimirComentarios(char **comentarios,int numComentarios,ofstream &archReporte);
void ordenarCategorias(struct Categoria *arrCategorias,int cantidadCategorias);
void intercambiarStruct(struct Categoria &arrCategoriasI,struct Categoria &arrCategoriasK);
void cargarComentarios(const char*nombArch,struct Categoria *arrCategorias,int cantidadCategorias);
void asignarComentario(const char *canal,struct Categoria *arrCategorias,int cantidadCategorias,char *ptrComentario);



#endif //FUNCIONESAUXILIARES_H
