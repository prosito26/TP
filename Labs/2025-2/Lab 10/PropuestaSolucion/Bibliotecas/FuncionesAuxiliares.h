//
// Created by aml on 24/11/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Nodo.h"

void cargarCategorias(const char *nombArch,struct Nodo *&listaCategorias);
char *leeCadenaExactaDelim(ifstream &arch,char delim);
void insertarOrdenado(struct Nodo *&listaCategorias,struct Categoria categoriaNueva);
void emitirReporte(const char *nombArch,struct Nodo *listaCategorias);
void imprimirLinea(char car,int tam,ofstream &arch);
void completarLista(const char *nombArch,struct Nodo *listaCategorias);
struct Nodo *BuscarCodigo(char *codCategoria,struct Nodo *listaCategorias);
void modificarStreams(struct Categoria &categoria,double tasaDropp,int duracionSeg,
    char *nombreCanal);
void asignarCadena(char *&cadenaDest,char *cadenaOrigen);
void calcularPromedio(struct Nodo *listaCategorias);
void calcularPromedioCategoria(struct Categoria &categoria);
void imprimirDemasDatos(struct Categoria categoria,ofstream &arch);
void imprimirHora(int duracionMaxima,ofstream &arch);
void eliminarNodos(struct Nodo *&listaCategorias);






#endif //FUNCIONESAUXILIARES_H
