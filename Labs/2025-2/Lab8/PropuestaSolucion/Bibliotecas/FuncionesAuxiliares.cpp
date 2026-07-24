//
// Created by aml on 10/11/2025.
//

#include "FuncionesAuxiliares.h"

void cargarCategorias(const char*nombArch,struct Categoria *arrCategorias,int &cantCategorias) {
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    while (true) {
        arch.getline(arrCategorias[cantCategorias].codigo,10,',');
        if (arch.eof()) break;
        arch.getline(arrCategorias[cantCategorias].nombre,50,'\n');
        cantCategorias++;
    }
}
void emitirReporte(const char*nombArch,struct Categoria *arrCategorias,int cantCategorias,bool mostrarDemasDatos,bool mostraResumen) {
    ofstream archReporte(nombArch,ios::out);
    if (not archReporte.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    archReporte<<setprecision(2)<<fixed;
    if (mostrarDemasDatos) {
        archReporte<<setw(10)<<" "<<"REPORTE POR CATEGORIAS"<<endl;
    }
    else {
        archReporte<<setw(10)<<" "<<"DATOS PARCIALES DE LAS CATEGORIAS"<<endl;
        imprimirLinea('=',60,archReporte);
        archReporte<<"CODIGO"<<setw(22)<<" "<<"NOMBRE"<<endl;
        imprimirLinea('-',60,archReporte);
    }
    for (int i = 0; i < cantCategorias; i++) {
        if (mostrarDemasDatos) {
            imprimirLinea('=',60,archReporte);
            archReporte<<"Codigo:"<<arrCategorias[i].codigo<<endl<<"Nombre:"<<arrCategorias[i].nombre<<endl;
            imprimirLinea('-',60,archReporte);
            archReporte<<"REPRODUCCIONES:"<<endl;
            archReporte<<"CANAL"<<setw(21)<<" "<<"RATING"<<setw(5)<<" "<<"DURACION"<<endl;
            imprimirCanales(arrCategorias[i].reproducciones,arrCategorias[i].numReproducciones,archReporte);
            if (mostraResumen) {
                imprimirResumen(arrCategorias[i].duracionTotal,arrCategorias[i].promedioRating,archReporte);
            }
        }
        else {
            archReporte<<arrCategorias[i].codigo<<setw(20)<<" "<<arrCategorias[i].nombre<<endl;
        }
    }
}
void imprimirLinea(char car,int tam,ofstream &archReporte) {
    for (int i = 0; i < tam; i++) {
        archReporte<<car;
    }
    archReporte<<endl;
}
void cargarDemasDatosCategorias(const char*nombArch,struct Categoria *arrCategorias,int cantCategorias) {
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    char nombreCanal[20],codigoCategoria[9],car;
    int duracionSeg,hhDur,minDur,segDur,posCategoria;
    double rating;
    while (true) {
        arch.getline(nombreCanal,20,',');
        if (arch.eof()) break;
        arch.getline(codigoCategoria,9,',');
        arch>>rating>>car>>hhDur>>car>>minDur>>car>>segDur;
        duracionSeg= hhDur*3600+ minDur*60+segDur;
        arch.get();
        posCategoria=BuscarCategoria(codigoCategoria,arrCategorias,cantCategorias);
        if (posCategoria!=NO_ENCONTRADO) {
            int i=arrCategorias[posCategoria].numReproducciones;
            strcpy(arrCategorias[posCategoria].reproducciones[i].canal,nombreCanal);
            arrCategorias[posCategoria].reproducciones[i].rating=rating;
            arrCategorias[posCategoria].reproducciones[i].duracion=duracionSeg;
            arrCategorias[posCategoria].numReproducciones++;
        }
    }
}
int BuscarCategoria(const char *codigoCategoria,struct Categoria *arrCategorias,int cantCategorias) {
    for (int i = 0; i < cantCategorias; i++) {
        if (strcmp(codigoCategoria,arrCategorias[i].codigo)==0) return i;
    }
    return NO_ENCONTRADO;
}
void imprimirCanales(struct Reproduccion *reproducciones,int numReproducciones,ofstream &archReporte) {
    for (int i = 0; i < numReproducciones; i++) {
        archReporte<<left<<setw(20)<<reproducciones[i].canal<<right<<setw(5)<<" ";
        archReporte<<setw(5)<<reproducciones[i].rating<<setw(7)<<" ";
        imprimirDuracion(archReporte,reproducciones[i].duracion);
        archReporte<<endl;
    }
}
void imprimirDuracion(ofstream &archReporte,int duracion) {
    int h,min,seg;
    h=duracion/3600;
    min=((duracion%3600)/60);
    seg=duracion%60;
    archReporte<<setfill('0')<<setw(2)<<h<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ');
}
void calcularPromedioYDuracionTotal(struct Categoria *arrCategorias,int cantCategorias) {
    for (int i = 0; i < cantCategorias; i++) {
        arrCategorias[i].promedioRating=promedio(arrCategorias[i].reproducciones,arrCategorias[i].numReproducciones);
        arrCategorias[i].duracionTotal=acumulacionDuracion(arrCategorias[i].reproducciones,arrCategorias[i].numReproducciones);
    }
}
double promedio(struct Reproduccion *reproducciones,int numReproducciones) {
    double suma=0;
    if (numReproducciones!=0) {
        for (int i = 0; i < numReproducciones; i++) {
            suma+=reproducciones[i].rating;
        }
        return (double)suma/numReproducciones;
    }
    else return 0.0;
}
int acumulacionDuracion(struct Reproduccion *reproducciones,int numReproducciones) {
    int suma=0;
    if (numReproducciones!=0) {
        for (int i = 0; i < numReproducciones; i++) {
            suma+=reproducciones[i].duracion;
        }
        return suma;
    }
    else return 0.0;
}
void imprimirResumen(int duracionTotal,double promedioRating,ofstream &archReporte) {
    imprimirLinea('-',60,archReporte);
    archReporte<<left<<setw(20)<<"RATING PROMEDIO:"<<right<<setw(5)<<promedioRating<<endl;
    archReporte<<left<<setw(20)<<"DURACION TOTAL: "<<right<<" ";
    imprimirDuracion(archReporte,duracionTotal);
    archReporte<<endl;
}