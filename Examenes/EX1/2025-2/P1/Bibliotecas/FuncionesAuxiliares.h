//
// Created by aml on 13/10/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void EmitirReporte(ifstream &archCanales,ifstream &archStreams,ifstream &archCategorias,
    ifstream &archIdiomas,ofstream &archReporte);
void imprimirResumenStream(ofstream &archReporte,
    int numVecesReprod,double tiempoTotalRepro,
    char letraCanalMay,char letraCanalMen,int numCanalMay,int numCanalMen,double tasaMenor,double tasaMayor);
void imprimirResumenTotal(ofstream &archReporte,int numStreams,double duracTotalRepro);
void ImprimirEncabezado(ofstream &archReporte) ;
void ImprimirLinea(char car,int tam,ofstream &archReporte);
void BuscarEImprimirCategoria(ifstream &archCategorias,ofstream &archReporte,char letraCat,int numCat);
void leerNombreEImprimirlo(ifstream &arch,ofstream &archReporte,char delim,bool cambioMayus,int tam,bool idioma);
void BuscarEImprimirIdioma(ifstream &archIdiomas,ofstream &archReporte,int idioma);
void CalcularDurHorEImprimirHora(ofstream &archReporte,int h,int m,int s,double &duracionHoras);
void ImprimirHora(int h,int m,int s,ofstream &archReporte);
void BuscarEImprimirDemasDatos(int codStream,double duracionHoras,ifstream &archCanales,
    ofstream &archReporte,int &numVecesReprod,double &tiempoTotalRepro,
    char &letraCanalMay,char &letraCanalMen,int &numCanalMay,int &numCanalMen,double &tasaMenor,double &tasaMayor);
void leerDemasDatosEImprimirlos(ifstream &archCanales,ofstream &archReporte,char letraCanal,int numCanal,int codStream,double duracionHoras,
    int &numVecesReprod,double &tiempoTotalRepro,int &cantCanles,
    char &letraCanalMay,char &letraCanalMen,int &numCanalMay,int &numCanalMen,double &tasaMenor,double &tasaMayor) ;
void RecorreCanalesEImprimirlos(ifstream &archCanales,ofstream &archReporte,int codigoStream,char letraCanal,int numCanal) ;
void calcularHoraMinSeg(double duracion,int &hh,int &min,int &seg);
void ImprimirFecha(int dd,int mm,int aa,ofstream &archReporte);
void imprimirSubtiCanales(ofstream &archReporte);
void encontrarMenorYMayorTasa(char letraCanal,int numCanal,double tasaAbandono,
                char &letraCanalMay,char &letraCanalMen,int &numCanalMay,int &numCanalMen,double &tasaMenor,double &tasaMayor);
void imprimirResumenCanal(ofstream &archReporte,double duracionHoras,int cantReprod,int &numVecesReprod,
    double &tiempoTotalRepro,double sumaRating,double sumaTasa);





#endif //FUNCIONESAUXILIARES_H
