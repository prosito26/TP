//
// Created by aml on 29/09/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define NO_ENCONTRADO -1
#define TAM_CANALES 120
#define TAM_ETIQUETA 120


void CargarCanales(const char*NombreArch,int *fechaCreacion,int *numCodCanal,
        char *letraCanal,double *ratingCanal,int &cantCnales);
int TransformarFecha(int dd,int mm,int aa);
double CalcularDuracionHoras(int mm,int ss);
void CargarEtiquetas(const char*NombreArch,int *arrCodEtiqueta,
    double *duracionHorasEtiqueta,int &cantEtiquetas);
void EmitirReporteSimple(const char*NombreArch,int *fechaCreacion,int *numCodCanal,char *letraCanal,double *ratingCanal,int cantCnales,
        int *arrCodEtiqueta,double *duracionHorasEtiqueta,int cantEtiquetas);
void ImprimirLinea(char car,int tam,ofstream &archReporte) ;
void ProcesarReproducciones(const char *NombreArch, int *fechaCreacion, int *numCodCanal, char *letraCanal,
                            double *ratingCanal, int cantCnales,
                            int *arrNumTotalReproCanal, double *arrTiempoTotalReproduccCanal, double *arrPorcentajeRating,
                            double *arrIngresosXReprodEtiquetas,
                            int *arrCodEtiqueta, double *duracionHorasEtiqueta, int cantEtiquetas,
                            int *arrCantidadTotalReproduccEtiqueta, double *arrTiempoTotalReproEtiqueta,
                            double tarifaXDurEtiqueta);
int BuscarCanal(char *letraCanal,int *numCodCanal,
    char letraCanal1,int numCodigoCanal,int cantCnales);
int BuscarEtiqueta(int *arrCodEtiqueta,int codigoEtiqueta,int cantEtiquetas) ;
double ClasificarPorcentaje(double ratingCanal);
void EmitirReporte(const char *NombreArch, int *fechaCreacion, int *numCodCanal, char *letraCanal,
                            double *ratingCanal, int cantCnales,
                            int *arrNumTotalReproCanal, double *arrTiempoTotalReproduccCanal, double *arrPorcentajeRating,
                            double *arrIngresosXReprodEtiquetas,
                            int *arrCodEtiqueta, double *duracionHorasEtiqueta, int cantEtiquetas,
                            int *arrCantidadTotalReproduccEtiqueta, double *arrTiempoTotalReproEtiqueta,
                            double tarifaXDurEtiqueta);
void imprimirCanales( int *numCodCanal, char *letraCanal,double *ratingCanal,int *arrNumTotalReproCanal,double *arrTiempoTotalReproduccCanal,
        double *arrPorcentajeRating,double *arrIngresosXReprodEtiquetas,int cantCnales,ofstream &archReporte,int *fechaCreacion);
void pasarFormatoHora(double tiempoHoras,int &hh,int &min,int &seg);
void imprimirEtiquetas(int *arrCodEtiqueta,double *duracionHoras,
    int *arrCantidadTotalReproduccEtiqueta,double *arrTiempoTotalReproEtiqueta,ofstream &archReporte,
    int cantEtiquetas);
void ImprimirHora(int hh,int min,int seg,ofstream &archReporte);

#endif //FUNCIONESAUXILIARES_H
