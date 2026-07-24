//
// Created by aml on 22/09/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void EmitirReporte(ifstream &archCanales,ifstream &archEtiquetas,ifstream &archReproDeEti,
    ofstream &archReporte,double tarifaDurEtiq);
void ImprimirEncabezado(ofstream &archReporte,double tarifaDurEtiq);
void ImprimirLinea(ofstream &archReporte,char car,int tam) ;
void LeerNombreEImprimirlo(ofstream &archReporte,char delim,int tam,ifstream &archCanales,bool pasaMayus);
void ImprimirFecha(int dd,int mm,int aa,ofstream &archReporte);
void ImprimirSubtitulos(ofstream &archReporte,int ddC,int mmC,int aaC,
    char letraCod,int numCod,ifstream &archCanales,int i);
void ImprimirSubEtiquetasRepro(ofstream &archReporte);
void BuscarEImprimirDemasDatos(char letraCod,int numCod,
    double ratingCal,long long etiqueta,ofstream &archReporte,
    ifstream &archReproDeEti,int &cantEti,ifstream &archEtiquetas,double &acumTiempo);
void BuscarEImprimirDescripcion(ofstream &archReporte,ifstream &archReproDeEti,long long etiquetaCanal,
    int numRepr,ifstream &archEtiquetas,double &tiempoTotal);
void ImprimirDuracion(int min,int seg,ofstream &archReporte);
void imprimirTiempo(double tiempoTotal,ofstream &archReporte);
void ImprimirResumenFinal(ofstream &archReporte,double tarifaDurEtiq,double ratingCal,
    double acumTiempo);
double ClasificarTrifa(double ratingCal);









#endif //FUNCIONESAUXILIARES_H
