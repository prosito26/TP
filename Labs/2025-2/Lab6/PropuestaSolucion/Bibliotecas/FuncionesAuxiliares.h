//
// Created by aml on 27/10/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define NO_ENCONTRADO -1
#define MAX_STREAMS 120

void CargarInfoStreams(const char*NombreArch,int *arrCodStream,int *arrIdiomaStream,double *arrDuracionHoras,int *arrNumCat,
        char *arrLetraCat,int &cantStreams);
void insertarOrdenadoDurHoras(int *arrCodStream,double *arrDuracionHoras,int *arrIdiomaStream,char *arrLetraCat,int *arrNumCat,
            int cod,double tiempoHoras,int idioma,char letra,int categoria,int &cantStreams);
void VerificarDatos(const char *NombreArch, int *arrCodStream, int *arrIdiomaStream, double *arrDuracionHoras,
                    int *arrNumCat,
                    char *arrLetraCat, int cantStreams);
void CargarDemasArreglosAuxiliares(const char *NombreArch,int *arrCodStream,int cantStreams,
        int *arrReproReciente,int *arrReproMasAntigua,int *arrNumReproducciones,double *arrPromRting,double *arrPromTasaDroppOff);
void actualizarAreglos(int  &arrReproReciente,int  &arrReproMasAntigua,
                    int &arrNumReproducciones,double &arrPromRting,double &arrPromTasaDroppOff,
                    int fechaRepro,double rating,double tasa);
int BuscarStream(int codigo,int *arr,int cantStreams);
void EmitirReporteStreams(const char *NombreArch,int *arrCodStream,int *arrIdiomaStream,double *arrDuracionHoras,int *arrNumCat,
    char *arrLetraCat,int cantStreams,int *arrReproReciente,int *arrReproMasAntigua,int *arrNumReproducciones,double *arrPromRting,
    double *arrPromTasaDroppOff,bool ordenado) ;
void ImprimirHora(ofstream &archReporte,int h,int min,int seg);
void ImprimirFecha(ofstream &archReporte,int dd,int mm,int aa);
void OrdenarDatos(int *arrCodStream,int *arrIdiomaStream,double *arrDuracionHoras,int *arrNumCat,
    char *arrLetraCat,int cantStreams,int *arrReproReciente,int *arrReproMasAntigua,int *arrNumReproducciones,
    double *arrPromRting,double *arrPromTasaDroppOff);
void intercambiarInt(int &datoI,int &datoK);
void intercambiarDbl(double &datoI,double &datoK);
void intercambiarChar(char &datoI,char &datoK);
void calcularMayorYMenorStreamDura(int i,int arrCodStream,double arrDuracionHoras,
    int &streamMayorDuracion,int &streamMenorDuracion,double &mayorDuracion,double &menorDuracion);
void ImprimirResumen(double mayorDuracion,double menorDuracion,int streamMayorDuracion,int streamMenorDuracion,ofstream &archReporte);

#endif //FUNCIONESAUXILIARES_H
