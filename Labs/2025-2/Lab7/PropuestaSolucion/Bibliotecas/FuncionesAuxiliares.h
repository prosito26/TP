//
// Created by aml on 3/11/2025.
//

#ifndef FUNCIONESAUXILIARES_H
#define FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

#define NO_ENCONTRADO -1
#define MAX_STREAMS 430
#define MAX_CATEGORIAS 120

void cargarCategorias(const char*nombreArch,char **arrCodigoCategoria,char **arrNombreCategoria,int &cantCategorias);

char *leeCadenaExacta(ifstream &arch);
void VerificarDatos(const char*nombreArch,char **arrCodigoCategoria,char **arrNombreCategoria,int cantCategorias);;
void ImprimirLinea(char car,ofstream &archReporte,int tam);
void cargarStreams(const char*nombreArch,int *arrFechaReproduccStream,char **arrNombreCanal,char **arrCategoriaAsociada,double *arrDuracionHorasStream,
        double *arrRatingCalidad,double *arrTasaDroppOf,int &cantStreams);
void VerificarStreams(const char*nombreArch,int *arrFechaReproduccStream,char **arrNombreCanal,char **arrCategoriaAsociada,double *arrDuracionHorasStream,
        double *arrRatingCalidad,double *arrTasaDroppOf,int cantStreams);
void EmitirReporte(int *arrFechaReproduccStream,char **arrNombreCanal,char **arrCategoriaAsociada,double *arrDuracionHorasStream,
                   double *arrRatingCalidad,double *arrTasaDroppOf,int cantStreams,char **arrCodigoCategoria,char **arrNombreCategoria,int cantCategorias);
void generaArchivoEnlace(const char *arrCodigoCategoria,char *nombArch,char *enlace);
void ImprimirSubtitulos(ofstream &archReporte,const char *arrNombreCategoria,const char *arrCodigoCategoria,const char *enlace);
void modificarCadena(char *arrNombreCategoria);
void ImprimirFecha(ofstream &archReporte,int arrFechaReproduccStream);
void ImprimirHora(ofstream &archReporte,double arrDuracionHorasStream);
void ImprimirResumen(ofstream &archReporte,double acumHoras,double promediotasa,double promedioRting,int cantVeces);


#endif //FUNCIONESAUXILIARES_H
