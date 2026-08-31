//
// Created by ALVARO on 13/08/2026.
//

#include "FuncionesAuxiliares.h"

#include <iostream>
#include <iomanip>
using namespace std;

//IMPLEMENTACION
//Lab01_2025_2_EntradaYSalidaDeDatos.exe < ArchivosDeDatos\twitchdataTP.txt > ArchivosDeReportes\Reporte.txt
void procesarDatos() {
    int fechaInicial=20220909;
    int fechaLimite=20230101;

    imprimirEncabezado(fechaInicial,fechaLimite);
    leerDatosEimprimirlos(fechaInicial,fechaLimite);

}

void imprimirEncabezado(int fechaInicial,int fechaLimite) {
    cout<<setw(35)<<" "<<"PLATAFORMA TP_Twitch"<<endl;
    cout<<setw(30)<<" "<<"REGISTRO DE LOS CANALES AFILIADOS"<<endl;
    cout<<setw(25)<<" "<<"FECHA DE CREACION ENTRE EL ";
    imprimirFecha(fechaInicial);
    cout<<" Y EL ";
    imprimirFecha(fechaLimite);
    cout<<endl;
}

//FUNCION IMPORTANTE
void imprimirFecha(int fechaInicial) {
    int aa=fechaInicial/10000;
    int mm=(fechaInicial%10000)/100;
    int dd=fechaInicial%100;
    cout<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}
//FUNCION IMPORTANTE
void imprimirLinea(char car,int tam) {
    for(int i=0;i<tam;i++) {
        cout<<car;
    }
    cout<<endl;
}

//20/01/2022          D9513          DreadzTV    675908
void leerDatosEimprimirlos(int fechaInicial,int fechaLimite) {
    int ddC,mmC,aaC,numCodCanal,i=1,numSeguidores;
    char letraCodCanal,car;
    double duracTotalReprod=0,ingresosTotales;
    int cantTotalStreams=0;
    while (true) {
        cin>>ddC>>car>>mmC>>car>>aaC;
        if (cin.eof()) break;
        int fecha=aaC*10000+mmC*100+ddC;
        if (fecha>=fechaInicial and fecha<=fechaLimite) {
            //va a continuar el programa
            imprimirLinea('=',150);
            cout<<"CANAL No."<<i<<endl;
            imprimirSubEncabezados();
            cin>>letraCodCanal>>numCodCanal;
            cout<<setw(6)<<" ";
            leerNombreEimprimirlo(' ');
            cout<<letraCodCanal<<numCodCanal<<setw(6)<<" ";
            imprimirFecha(fecha);
            cout<<setw(6)<<" ";
            cin>>numSeguidores;
            cout<<setw(15)<<numSeguidores<<endl;
            leerDemasDatosEimprimirlos(fecha,letraCodCanal,numCodCanal,numSeguidores,
                duracTotalReprod,cantTotalStreams,ingresosTotales);
            //while (cin.get()!='\n');//para ir probando la impresion por partes
            i++;
        }
        else //si en caso no se enecunetra la fecha en el rango, ignorará lo que sigue
            while (cin.get()!='\n');//IMPORTANTE LECTURA

    }
    //RESUMEN FINAL
    imprimirResumenFinal(ingresosTotales,duracTotalReprod,cantTotalStreams);
}

void imprimirSubEncabezados() {

}

void leerNombreEimprimirlo(char delim) {
    //siempre al inicio
    cin>>ws;//ignora todos los espacios en blanco
    char car;
    int cantCar=0;
    while (true) {
        car=cin.get();//saca un caracter
        if (car==delim) break;
        if (car>='a' and car<='z') car -= 'a'-'A';//mayusculas
        //if (car>='A' and car<='Z') car += 'a'-'A';//minusculas
        cout<<car;
        cantCar++;
    }
    //alinear con el nombre en el reporte
    cout<<setw(20-cantCar)<<" ";
}

//16/07/2025   00:25:55   1396
void leerDemasDatosEimprimirlos(int fecha,char letraCodCanal,int numCodCanal,
    int numSeguidores,double &duracTotalReprod,
    int &cantTotalStreams,double &ingresosTotales) {
    int ddPubli,mmPubli,aaPubli,hhD,minD,segD,numReprod,i=1;
    int fechaUltPubl,acumReprod=0;
    char car;
    double duracHoras=0,ingreXPubli;
    while (true) {
        cin>>ddPubli>>car>>mmPubli>>car>>aaPubli;
        cin>>hhD>>car>>minD>>car>>segD>>numReprod;
        int fechaPubli=aaPubli*10000+mmPubli*100+ddPubli;
        calcularUltimaPublicacion(i,fechaPubli,fechaUltPubl);
        duracHoras+=transformaHora(hhD,minD,segD);
        acumReprod+=numReprod;
        imprimirDatos(fechaPubli,hhD,minD,segD,numReprod);
        i++;
        if (cin.get()=='\n') break;//va al inicio o final, probar
    }
    //RESUMEN POR CADA CANAL
    imprimirResumenCanal(duracHoras,fechaUltPubl,acumReprod,ingreXPubli);
    cantTotalStreams+=i;
    duracTotalReprod+=duracHoras;
    ingresosTotales+=ingreXPubli;
}

void imprimirDatos(int fechaPubli,int hhD,int minD,int segD,int numReprod) {
    cout<<setw(11)<<" ";
    imprimirFecha(fechaPubli);
    cout<<setw(25)<<" ";
    imprimirHora(hhD,minD,segD);
    cout<<setw(15)<<" ";
    cout<<setw(11)<<numReprod<<endl;
}

void imprimirHora(int hhD,int minD,int segD) {
    cout<<setfill('0')<<setw(2)<<hhD<<":"<<setw(2)<<minD<<":"<<setw(2)<<segD<<setfill(' ');
}

double transformaHora(int hhD,int minD,int segD) {
    return hhD + (double)minD/60 + segD/3600.0;
}

void calcularUltimaPublicacion(int i,int fechaPubli,
    int &fechaUltPubl) {
    if (i==1) {
        fechaUltPubl=fechaPubli;
    }
    else {
        if (fechaPubli>fechaUltPubl) {
            fechaUltPubl=fechaPubli;
        }
    }
}
void imprimirResumenCanal(double duracHoras,
    int fechaUltPubl,int acumReprod,double &ingreXPubli) {
    int hhDur,minDur,segDur;
    imprimirLinea('-',150);
    convertirAFormatoHora(duracHoras,hhDur,minDur,segDur);
    cout<<setw(5)<<" "<<"RESUMEN DEL CANAL: "<<endl;
    cout<<setw(5)<<" "<<"DURACION TOTAL DE LAS REPRODUCCIONES: ";
    imprimirHora(hhDur,minDur,segDur);
    cout<<endl;
    cout<<setw(5)<<" "<<"ULTIMA PUBLICACION: ";
    cout<<setw(18)<<" ";
    imprimirFecha(fechaUltPubl);
    cout<<endl;
    cout<<setw(5)<<" "<<"TOTAL REPRODCCIONES: ";
    cout<<setw(13)<<" ";
    cout<<setw(10)<<left<<acumReprod<<right<<endl;
    ingreXPubli=calcularIngresosPorPublicidad(acumReprod);
    cout<<setw(5)<<" "<<"INGRESOS POR PUBLICIDAD: ";
    cout<<setw(13)<<" "<<"$ "<<ingreXPubli<<endl;
}

//FUNCION IMPORTANTE(horas a formato hora)
void convertirAFormatoHora(double duracHoras,
    int &hhDur,int &minDur,int &segDur) {
    //3.1245
    hhDur=(int)duracHoras;
    minDur=(int)((duracHoras-hhDur)*60);
    segDur=(int)((((duracHoras-hhDur)*60)-minDur)*60);
}

double calcularIngresosPorPublicidad(int acumReprod) {
    return 3.25*(acumReprod/1000.0);
}

void imprimirResumenFinal(double ingresosTotales,
    double duracTotalReprod,int cantTotalStreams) {
    int hh,min,seg;
    imprimirLinea('=',150);
    cout<<"RESUMEN FINAL: "<<endl;
    cout<<"CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES: "<<setw(10)<<" "<<cantTotalStreams<<endl;
    convertirAFormatoHora(duracTotalReprod,hh,min,seg);
    cout<<"DURACIÓN TOTAL DE LOS STREAMS PUBLICADOS: "<<setw(15)<<" ";
    imprimirHora(hh,min,seg);
    cout<<endl;
    cout<<"INGRESOS TOTALES POR PUBLICIDAD: ";
    cout<<setw(21)<<" "<<"$ "<<setw(10)<<ingresosTotales<<endl;
}
