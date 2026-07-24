//
// Created by aml on 15/09/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void ProcesarDatos(ifstream &archLeer,ofstream &archReporte,
    int ddI,int mmI,int aaI,int ddF,int mmF,int aaF,double pagoXRepr,double pagoXTiempo);
void ImprimirEncabezado(ofstream &archReporte,int ddI,int mmI,int aaI,int ddF,int mmF,int aaF,
    double pagoXRepr,double pagoXTiempo);
int  TransformarFecha(int dd,int mm,int aa) ;
void ImprimirFecha(int dd,int mm,int aa,ofstream &archReporte);
void LeerDatosEImprimirlos(int dd,int mm,int aa,double pagoXRepr,double pagoXTiempo,
    ofstream &archReporte,ifstream &archLeer,int i,
    int &cantTotalStreams,double &duracionTotalStreams,
        double &ingresosTotalesXPubli,double &ingresosTotalesXDuracion);
void ImprimirLinea(char car,int tam,ofstream &archReporte);
void ImprimirSubEncabezados(ofstream &archReporte,int i) ;
void LeerNombreEImprimirlo(ofstream &archReporte,ifstream &arch,char delim,int tam);
void LeerDemasDatosEImprimirlos(ifstream &archLeer,ofstream &archReporte,
    int dd,int mm,int aa,char letraCod,int numCod,
    long long numSeguiNuevosXMes,long long numVisitasXMes,long long maxEspect,double pagoXRepr,double pagoXTiempo,
    int &cantTotalStreams,double &duracionTotalStreams,
        double &ingresosTotalesXPubli,double &ingresosTotalesXDuracion);
void ImprimirSubEncabezadosCanal(ofstream &archReporte);
void ImprimirHora(int hh,int minDur,int seg,ofstream &archReporte);
void CalcularDuracionHorasEImprimirlo(int hhDur,int minDur,int segDur,
    ofstream &archReporte,double pagoXRepr,double pagoXTiempo,int cantRepr,
    double &duracionHoras,double &ingresosXDuracion);
double CalcularDuracionHoras(int hh,int min,int seg);
void ImprimirEstadisticasCanal(ofstream &archReporte,double acumHoras,double acumIngresoXDuraci,
    int acumRepro,double ingresosXPublicidad,double engaIndex);
void TransformarFormatoHora(double acumHoras,int &h,int &min,int &seg);
void imprimirResumenFinal(ofstream &archReporte,int cantTotalStreams,double duracionTotalStreams,
        double ingresosTotalesXPubli,double ingresosTotalesXDuracion);







#endif //FUNCIONESAUXILIARES_H
