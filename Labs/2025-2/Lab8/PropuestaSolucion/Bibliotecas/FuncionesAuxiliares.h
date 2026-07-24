//
// Created by aml on 10/11/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
using namespace std;

#include "Categoria.h"

#define NO_ENCONTRADO -1
#define MAX_CATEGORIAS 120

void cargarCategorias(const char*nombArch,struct Categoria *arrCategorias,int &cantCategorias);
void emitirReporte(const char*nombArch,struct Categoria *arrCategorias,int cantCategorias,bool mostrarDemasDatos,bool mostraResumen);
void imprimirLinea(char car,int tam,ofstream &archReporte);
void cargarDemasDatosCategorias(const char*nombArch,struct Categoria *arrCategorias,int cantCategorias);
int BuscarCategoria(const char *codigoCategoria,struct Categoria *arrCategorias,int cantCategorias);
void imprimirCanales(struct Reproduccion *reproducciones,int numReproducciones,ofstream &archReporte);
void imprimirDuracion(ofstream &archReporte,int duracion);
void calcularPromedioYDuracionTotal(struct Categoria *arrCategorias,int cantCategorias);
double promedio(struct Reproduccion *reproducciones,int numReproducciones);
int acumulacionDuracion(struct Reproduccion *reproducciones,int numReproducciones);
void imprimirResumen(int duracionTotal,double promedioRating,ofstream &archReporte);

#endif //FUNCIONESAUXILIARES_H
