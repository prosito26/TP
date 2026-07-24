//
// Created by ALVARO on 7/12/2025.
//

#ifndef LAB5_VIRTUAL_TP_2025_2_FUNCIONESAUXILIARES_H
#define LAB5_VIRTUAL_TP_2025_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define MAX_CANALES 120
#define MAX_ETIQUETAS 120
#define MAX_ETIQUETAS_CANALES 600
#define NO_ENCONTRADO -1

void cargarCanales(const char*nombArch,int *arrFechaCreacCanal,int *arrIntCodCanal,
        char *arrCharCodCanal,double *arrRatingCanal,int &cantCanales);
void cargarEtiquetas(const char*nombArch,int *arrCodEtiqueta,double *arrDuracionEtiquetaHoras,
        int &cantEtiquetas);
void cargarEtiqeutasEnCanales(const char*nombArch,int *codigoIntCanalEnEtiqueta,char *codigoCharCanalEnEtiqueta,
        int *codigoEtiquetaEnCanal,int &cantEtiquetaEnCanal);
void ordenarArreglos(int *arrCodEtiqueta,double *arrDuracionEtiquetaHoras,int cantEtiquetas);
void intercambiarInt(int &datoI,int &datoK);
void intercambiarDbl(double &datoI,double &datoK);
void cargarInfoEtiquetas(const char*nombArch, int *arrFechaReproducc,int *arrNumReproducc,
                        int *codigoIntCanalEnEtiqueta, char *codigoCharCanalEnEtiqueta,
                        int *codigoEtiquetaEnCanal, int cantEtiquetaEnCanal);
int BuscarEtiquetaYCanal(char *codigoCharCanalEnEtiqueta,int *codigoIntCanalEnEtiqueta,
            int cantEtiquetaEnCanal,char letra,int num,int etiqueta,int *codigoEtiquetaEnCanal);
void emitirReporte(const char*nombArch,int *arrFechaCreacCanal, int *arrIntCodCanal,
                  char *arrCharCodCanal,double *arrRatingCanal, int cantCanales, int *arrCodEtiqueta, double *arrDuracionEtiquetaHoras,
                  int cantEtiquetas, int *codigoIntCanalEnEtiqueta,char *codigoCharCanalEnEtiqueta,
                  int *codigoEtiquetaEnCanal, int cantEtiquetaEnCanal, int *arrFechaReproducc, int *arrNumReproducc,double tarifa );
void transformarHora(double duracionHoras,ofstream &archRep,int &hh,int &min,int &seg);
void imprimirCanales(ofstream &archRep,double duracionHorasEtiqueta,int arrCodEtiqueta,int *codigoIntCanalEnEtiqueta,char *codigoCharCanalEnEtiqueta,
    int *arrNumReproducc,int *codigoEtiquetaEnCanal,int cantEtiquetaEnCanal,int *arrIntCodCanal,char *arrCharCodCanal,
    double *arrRatingCanal,int cantCanales,double tarifa);
void imprimirLinea(ofstream &archRep,char car,int tam);
void imprimirSubtitulosCanales(ofstream &archRep);
double BuscarRatingCanal(char CharCanal,int IntCanal,int *arrIntCodCanal,char *arrCharCodCanal,
                double *arrRatingCanal,int cantCanales);
void imprimirResumenEtiqueta(ofstream &archRep,int totalRepro,double tiempoTotal,
    double promRating,double tarifa);
double ClasificarRating(double promRating);

#endif //LAB5_VIRTUAL_TP_2025_2_FUNCIONESAUXILIARES_H