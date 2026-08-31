//
// Created by ALVARO on 13/08/2026.
//

#ifndef LAB01_2025_2_ENTRADAYSALIDADEDATOS_FUNCIONESAUXILIARES_H
#define LAB01_2025_2_ENTRADAYSALIDADEDATOS_FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
using namespace std;

//PROTOTIPOS

void procesarDatos();
void imprimirEncabezado(int fechaInicial,int fechaLimite);
void imprimirFecha(int fechaInicial);
void imprimirLinea(char car,int tam) ;
void leerDatosEimprimirlos(int fechaInicial,int fechaLimite) ;
void imprimirSubEncabezados();
void leerNombreEimprimirlo(char delim);
void leerDemasDatosEimprimirlos(int fecha,char letraCodCanal,int numCodCanal,
    int numSeguidores,double &duracTotalReprod,
    int &cantTotalStreams,double &ingresosTotales);
void imprimirDatos(int fechaPubli,int hhD,int minD,int segD,int numReprod);
void imprimirHora(int hhD,int minD,int segD);
double transformaHora(int hhD,int minD,int segD);
void calcularUltimaPublicacion(int i,int fechaPubli,
    int &fechaUltPubl);
void imprimirResumenCanal(double duracHoras,
    int fechaUltPubl,int acumReprod,double &ingreXPubli);
void convertirAFormatoHora(double duracHoras,
    int &hhDur,int &minDur,int &segDur) ;
double calcularIngresosPorPublicidad(int acumReprod);
void imprimirResumenFinal(double ingresosTotales,
    double duracTotalReprod,int cantTotalStreams);





#endif //LAB01_2025_2_ENTRADAYSALIDADEDATOS_FUNCIONESAUXILIARES_H