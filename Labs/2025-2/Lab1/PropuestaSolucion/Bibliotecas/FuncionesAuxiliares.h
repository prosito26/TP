//
// Created by aml on 8/09/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
using namespace std;

void ProcesarDatos();
void ImprimirEncabezado(int ddI,int mmI,int aaI,int ddF,int mmF,int aaF);
void ImprimirFecha(int dd,int mm,int aa);
void ImprimirLinea(char car,int tam);
void ImprimirSubEncabezados() ;
void LeerDatosEImprimirlos(int fechaInicio,int fechaFin);
void LeerNombreEImprimirlo(char delim,char LetraCodigo,int numCodigo) ;
void LeerDemasDatosEImprimirlos(int ddC,int mmC,int aaC,
    char LetraCodigo,int numCodigo,int numSeguidores,int &streamTotales, double &HorasTotales,double &IngresoTotalXPubli) ;
void ImprimirSubEncabezados2();
void ImprimirDatos(int ddPubli,int mmPubli,int aaPubli,
    int hhDura,int minDura,int segDura,int cantReprodu);
void ImprimirHora(int hh,int min,int seg);
void ImprimirEstadisticasCanal(int hhD,int minD,int segD,int ddUlt,int mmUlt,int aaUlt,int AcumReproducciones,double &ingresosXPubli);
double TransformarAHoras(int hh,int min,int seg);
void ConvertirAFormatoHora(double AcumularHorasDuracion,int &hhD,int &minD,int &segD) ;
void CalcularUltimaPublicacion(int i,int ddPubli,int mmPubli,int aaPubli,
    int &ddUlt,int &mmUlt,int &aaUlt);
double CalcularIngresosPorPublicidad(int AcumReproducciones);
void ImprimirEstadisticasFinales(int streamTotales,double HorasTotales,double IngresoTotalXPubli) ;
#endif //FUNCIONESAUXILIARES_H
