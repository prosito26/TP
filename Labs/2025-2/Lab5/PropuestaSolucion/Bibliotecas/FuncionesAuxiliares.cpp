//
// Created by ALVARO on 7/12/2025.
//

#include "FuncionesAuxiliares.h"

#include <chrono>

void cargarCanales(const char*nombArch,int *arrFechaCreacCanal,int *arrIntCodCanal,
                   char *arrCharCodCanal,double *arrRatingCanal,int &cantCanales) {
    ifstream arch(nombArch,ios::in);
    if(!arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int dd,mm,aa,fecha,numCanal;
    char car,letraCanal;
    double rating;
    while (true) {
        arch>>dd>>car>>mm>>car>>aa;
        if (arch.eof()) break;
        fecha=aa*10000+mm*100+dd;
        arch>>letraCanal>>numCanal;
        arch>>ws;
        while (arch.get()!=' ');
        arch>>rating;
        arrFechaCreacCanal[cantCanales]=fecha;
        arrIntCodCanal[cantCanales]=numCanal;
        arrCharCodCanal[cantCanales]=letraCanal;
        arrRatingCanal[cantCanales]=rating;
        cantCanales++;
    }
}
void cargarEtiquetas(const char*nombArch,int *arrCodEtiqueta,double *arrDuracionEtiquetaHoras,
        int &cantEtiquetas) {
    ifstream arch(nombArch,ios::in);
    if(!arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int cod,min,seg;
    double duracion;
    char car;
    while (true) {
        arch>>cod;
        if (arch.eof()) break;
        arch>>ws;
        while (arch.get()!=' ');
        arch>>min>>car>>seg;
        duracion=(double)min/60+(double)seg/3600;
        arrCodEtiqueta[cantEtiquetas]=cod;
        arrDuracionEtiquetaHoras[cantEtiquetas]=duracion;
        cantEtiquetas++;
    }
}
void cargarEtiqeutasEnCanales(const char*nombArch,int *codigoIntCanalEnEtiqueta,char *codigoCharCanalEnEtiqueta,
        int *codigoEtiquetaEnCanal,int &cantEtiquetaEnCanal) {
    ifstream arch(nombArch,ios::in);
    if(!arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    char letra;
    int num,etiqueta;
    while(true) {
        arch>>letra>>num;
        if (arch.eof()) break;
        arch>>etiqueta;
        codigoCharCanalEnEtiqueta[cantEtiquetaEnCanal]=letra;
        codigoIntCanalEnEtiqueta[cantEtiquetaEnCanal]=num;
        codigoEtiquetaEnCanal[cantEtiquetaEnCanal]=etiqueta;
        cantEtiquetaEnCanal++;
    }
}
void ordenarArreglos(int *arrCodEtiqueta,double *arrDuracionEtiquetaHoras,int cantEtiquetas) {
    for(int i=0;i<cantEtiquetas-1;i++) {
        for(int k=i+1;k<cantEtiquetas;k++) {
            if (arrDuracionEtiquetaHoras[i]<arrDuracionEtiquetaHoras[k]) {
                intercambiarInt(arrCodEtiqueta[i],arrCodEtiqueta[k]);
                intercambiarDbl(arrDuracionEtiquetaHoras[i],arrDuracionEtiquetaHoras[k]);
            }
        }
    }
}
void intercambiarInt(int &datoI,int &datoK) {
    int aux;
    aux=datoI;
    datoI=datoK;
    datoK=aux;
}
void intercambiarDbl(double &datoI,double &datoK) {
    double aux;
    aux=datoI;
    datoI=datoK;
    datoK=aux;
}
void cargarInfoEtiquetas(const char*nombArch, int *arrFechaReproducc,int *arrNumReproducc,
                        int *codigoIntCanalEnEtiqueta, char *codigoCharCanalEnEtiqueta,
                        int *codigoEtiquetaEnCanal, int cantEtiquetaEnCanal) {
    ifstream arch(nombArch,ios::in);
    if(!arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int dd,mm,aa,fecha,num,etiqueta,numRepro;
    char car,letra;
    while(true) {
        arch>>dd>>car>>mm>>car>>aa;
        if (arch.eof()) break;
        fecha=aa*10000+mm*100+dd;
        arch>>letra>>num>>etiqueta>>numRepro;
        int posEtiquetaEnCanal=BuscarEtiquetaYCanal(codigoCharCanalEnEtiqueta,codigoIntCanalEnEtiqueta,
            cantEtiquetaEnCanal,letra,num,etiqueta,codigoEtiquetaEnCanal);
        if (posEtiquetaEnCanal!=NO_ENCONTRADO) {
            arrFechaReproducc[posEtiquetaEnCanal]=fecha;
            arrNumReproducc[posEtiquetaEnCanal]+=numRepro;
        }
    }
}
int BuscarEtiquetaYCanal(char *codigoCharCanalEnEtiqueta,int *codigoIntCanalEnEtiqueta,
            int cantEtiquetaEnCanal,char letra,int num,int etiqueta,int *codigoEtiquetaEnCanal) {
    for(int i=0;i<cantEtiquetaEnCanal;i++) {
        if (codigoCharCanalEnEtiqueta[i]==letra and codigoIntCanalEnEtiqueta[i]==num and codigoEtiquetaEnCanal[i]==etiqueta) return i;
    }
    return NO_ENCONTRADO;
}
void emitirReporte(const char*nombArch,int *arrFechaCreacCanal, int *arrIntCodCanal,
                  char *arrCharCodCanal,double *arrRatingCanal, int cantCanales, int *arrCodEtiqueta, double *arrDuracionEtiquetaHoras,
                  int cantEtiquetas, int *codigoIntCanalEnEtiqueta,char *codigoCharCanalEnEtiqueta,
                  int *codigoEtiquetaEnCanal, int cantEtiquetaEnCanal, int *arrFechaReproducc, int *arrNumReproducc,double tarifa) {
    ofstream archRep(nombArch,ios::out);
    if(!archRep.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int hh,min,seg;
    archRep<<setprecision(2)<<fixed;
    archRep<<setw(30)<<" "<<"PALTAFORMA TP_Twitch"<<endl;
    archRep<<setw(10)<<" "<<" TARIFA POR DURACION DE LAS ETIQUETAS: "<<tarifa<<" POR CADA MINUTO Y FRACCION"<<endl;
    for(int i=0;i<cantEtiquetas;i++) {
        imprimirLinea(archRep,'=',90);
        archRep<<"ETIQUETA No."<<i+1<<endl;
        archRep<<setw(4)<<" "<<"CODIGO: "<<arrCodEtiqueta[i]<<endl;
        archRep<<setw(4)<<" "<<"DURACION: ";
        transformarHora(arrDuracionEtiquetaHoras[i],archRep,hh,min,seg);
        archRep<<setfill('0')<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ')<<endl;
        imprimirCanales(archRep,arrDuracionEtiquetaHoras[i],arrCodEtiqueta[i],codigoIntCanalEnEtiqueta,codigoCharCanalEnEtiqueta,arrNumReproducc,
            codigoEtiquetaEnCanal,cantEtiquetaEnCanal,arrIntCodCanal,arrCharCodCanal,arrRatingCanal,cantCanales,tarifa);
    }
}
void transformarHora(double duracionHoras,ofstream &archRep,int &hh,int &min,int &seg) {
    hh=(int)duracionHoras;
    min=(int)((duracionHoras-hh)*60);
    seg=(int)((((duracionHoras-hh)*60)-min)*60);
}
void imprimirCanales(ofstream &archRep,double duracionHorasEtiqueta,int arrCodEtiqueta,int *codigoIntCanalEnEtiqueta,char *codigoCharCanalEnEtiqueta,
    int *arrNumReproducc,int *codigoEtiquetaEnCanal,int cantEtiquetaEnCanal,int *arrIntCodCanal,char *arrCharCodCanal,
    double *arrRatingCanal,int cantCanales,double tarifa) {
    int hh,min,seg,totalRepro=0,i,k;
    double tiempoTotal=0,sumaRating=0,promRating;
    imprimirLinea(archRep,'-',90);
    imprimirSubtitulosCanales(archRep);
    for( i=0,k=0;i<cantEtiquetaEnCanal;i++) {
        if (arrCodEtiqueta==codigoEtiquetaEnCanal[i]) {
            double duracionHorasTotal=arrNumReproducc[i]*duracionHorasEtiqueta;
            totalRepro+=arrNumReproducc[i],tiempoTotal+=duracionHorasTotal;
            archRep<<" "<<setw(3)<<k+1<<")"<<setw(5)<<" ";
            archRep<<codigoCharCanalEnEtiqueta[i]<<codigoIntCanalEnEtiqueta[i]<<setw(10)<<" ";
            double rating=BuscarRatingCanal(codigoCharCanalEnEtiqueta[i],codigoIntCanalEnEtiqueta[i],arrIntCodCanal,arrCharCodCanal,
                arrRatingCanal,cantCanales);
            sumaRating+=rating;
            archRep<<setw(5)<<rating<<setw(10)<<" "<<setw(5)<<arrNumReproducc[i]<<setw(20)<<" ";
            transformarHora(duracionHorasTotal,archRep,hh,min,seg);
            archRep<<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ')<<endl;
            k++;
        }
    }
    promRating=(double)sumaRating/(k);
    imprimirResumenEtiqueta(archRep,totalRepro,tiempoTotal,promRating,tarifa);
}
void imprimirLinea(ofstream &archRep,char car,int tam) {
    for(int i=0;i<tam;i++) {
        archRep<<car;
    }
    archRep<<endl;
}
void imprimirSubtitulosCanales(ofstream &archRep) {
    archRep<<setw(4)<<" "<<"CANALES DONDE SE REPRODUCE:"<<endl;
    archRep<<setw(24)<<" "<<"RATING DE"<<setw(7)<<" "<<"NUMERO TOTAL"<<setw(10)<<" "<<"TIEMPO TOTAL DE "<<endl;
    archRep<<"No."<<setw(7)<<" "<<"CODIGO"<<setw(9)<<" "<<"CALIDAD"<<setw(5)<<" "<<"DE REPRODUCCIONES"<<setw(9)<<" "<<"REPRODUCCIONES"<<endl;
}
double BuscarRatingCanal(char CharCanal,int IntCanal,int *arrIntCodCanal,char *arrCharCodCanal,
                double *arrRatingCanal,int cantCanales) {
    for(int i=0,k=0;i<cantCanales;i++) {
        if (CharCanal==arrCharCodCanal[i] and arrIntCodCanal[i]==IntCanal) return arrRatingCanal[i];
    }
    return 0.0;
}
void imprimirResumenEtiqueta(ofstream &archRep,int totalRepro,double tiempoTotal,
    double promRating,double tarifa) {
    int hh,min,seg;
    double ingresos;
    archRep<<setw(5)<<" "<<"RESUMEN DE LA ETIQUETA:"<<endl;
    archRep<<setw(8)<<" "<<"TOTAL DE REPRODUCCIONES:"<<setw(20)<<totalRepro<<endl;
    archRep<<setw(8)<<" "<<"TIEMPO TOTAL REPRODUCIDO:"<<setw(11)<<" ";
    transformarHora(tiempoTotal,archRep,hh,min,seg);
    archRep<<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ')<<endl;
    double porcPromRating=ClasificarRating(promRating);
    archRep<<setw(8)<<" "<<"PORCENTAJE PROMEDIO POR RATING:"<<setw(7)<<" ";
    double promFinal=((porcPromRating*100)-100);
    if (promFinal>=0) archRep<<"+";
    archRep<<promFinal<<"%"<<endl;
    ingresos=porcPromRating*tiempoTotal*60*tarifa;
    archRep<<setw(8)<<" "<<"INGRESOS POR REPRODUCCIONES:"<<setw(17)<<ingresos<<endl;
}
double ClasificarRating(double promRating) {
    double prom;
    if (promRating>4 and promRating<5) prom=1+0.3;
    else if (promRating>3 and promRating<4) prom=1+0.2;
    else if (promRating>2 and promRating<3) prom=1;
    else prom=1-0.25;
    return prom;
}
