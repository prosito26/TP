//
// Created by aml on 13/10/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define NO_ENCONTRADO -1
#define MAX_STREAMS 120

void CargarStreams(const char*NombreArch,int *arrCodStream,int *arrCodIdioma,int *arrNumCat,
    double *arrDuracionHoras,char *arrCharCat,int &cantStreams);
double CalcularDuracionHoras(int hh,int min,int ss);
void VerificarDatos(const char *NombreArch,int *arrCodStream,int *arrCodIdioma,int *arrNumCat,
    double *arrDuracionHoras,char *arrCharCat,int cantStreams);
void ImprimirLinea(char car,int tam,ofstream &archReporte) ;
void cargarArreglosAuxiliares(const char *NombreArch,int *arrCodStream,int *arrCodIdioma,int *arrNumCat,double *arrDuracionHoras,char *arrCharCat,
        int *arrRepAntigua,int *arrRepRec,int *arrNumRepr,double *arrPromRatCal,double *arrPromTasa,double *arrTiempoTotalRepr,int cantStreams) ;
int BuscarIndice(int codigoStream,int *arrCodStream,int cantStreams);
void CalcularRepAntYRec(int fecha,int arrNumRepr,int &arrRepAntigua,int &arrRepRec);
void calcularDdMmAa(int &aa,int &mm,int &dd,int fecha);
void calcularHhMinSeg(int &hh,int &min,int &seg,double duracionHoras);
void ImprimirFecha(ofstream & archReporte,int aa,int mm,int dd);
void ImprimirHora(ofstream &archReporte,int seg,int min,int h);
void imprimirResumen(ofstream &archReporte,int streamMayor,double mayorDur,
    int streamMenor,double menorDur);
void EmitirReporte(const char *NombreArch,int *arrCodStream,int *arrCodIdioma,int *arrNumCat,double *arrDuracionHoras,char *arrCharCat,
        int *arrRepAntigua,int *arrRepRec,int *arrNumRepr,double *arrPromRatCal,double *arrPromTasa,double *arrTiempoTotalRepr,int cantStreams,
        bool CambioTitulo,bool primeraVez);
void calcularMayorMenorStreamDur(int &streamMayor,int &streamMenor,
    double &mayorDur,double &menorDur,int codStream,double duracion);
void imprimirTituloSubtitulos(ofstream &archReporte,bool CambioTitulo) ;
void OrdenarArreglos(int *arrCodStream,int *arrCodIdioma,int *arrNumCat,double *arrDuracionHoras,char *arrCharCat,
        int *arrRepAntigua,int *arrRepRec,int *arrNumRepr,double *arrPromRatCal,double *arrPromTasa,double *arrTiempoTotalRepr,int cantStreams);
void IntercambiarInt(int &datoI,int &datoJ) ;
void IntercambiarDbl(double &datoI,double &datoJ) ;
void IntercambiarChar(char &datoI,char &datoJ);


#endif //FUNCIONESAUXILIARES_H
