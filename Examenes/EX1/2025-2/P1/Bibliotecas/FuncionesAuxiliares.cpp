//
// Created by aml on 13/10/2025.
//

#include "FuncionesAuxiliares.h"

void EmitirReporte(ifstream &archCanales,ifstream &archStreams,ifstream &archCategorias,
    ifstream &archIdiomas,ofstream &archReporte) {
    int codStream,idioma,h,m,s,numCat,numCanalMay,numCanalMen,
    numVecesReprod,numStreams=0;
    char letraCat,car,letraCanalMay,letraCanalMen;
    double duracionHoras,tiempoTotalRepro,duracTotalRepro=0,
    tasaMenor,tasaMayor;
    archReporte<<setprecision(2)<<fixed;
    ImprimirEncabezado(archReporte);
    while (true) {
        archStreams>>codStream;
        if (archStreams.eof()) break;
        numVecesReprod=0,tiempoTotalRepro=0,tasaMenor=999999,tasaMayor=0;
        ImprimirLinea('=',150,archReporte);
        archStreams>>h>>car>>m>>car>>s>>idioma>>letraCat>>numCat;
        archReporte<<"STREAM: "<<codStream<<setw(5)<<" "<<"CATEGORIA: "<<letraCat<<numCat<<" - ";
        BuscarEImprimirCategoria(archCategorias,archReporte,letraCat,numCat);
        archReporte<<"IDIOMA: "<<idioma<<" - ";
        BuscarEImprimirIdioma(archIdiomas,archReporte,idioma);
        archReporte<<"DURACION: ";
        CalcularDurHorEImprimirHora(archReporte,h,m,s,duracionHoras);
        archReporte<<endl;
        BuscarEImprimirDemasDatos(codStream,duracionHoras,archCanales,archReporte,
            numVecesReprod,tiempoTotalRepro,
            letraCanalMay,letraCanalMen,numCanalMay,numCanalMen,tasaMenor,tasaMayor);
        imprimirResumenStream(archReporte,numVecesReprod,tiempoTotalRepro,
            letraCanalMay,letraCanalMen,numCanalMay,numCanalMen,tasaMenor,tasaMayor);
        duracTotalRepro+=tiempoTotalRepro,numStreams++;
    }
    imprimirResumenTotal(archReporte,numStreams,duracTotalRepro);
}

void imprimirResumenStream(ofstream &archReporte,
    int numVecesReprod,double tiempoTotalRepro,
    char letraCanalMay,char letraCanalMen,int numCanalMay,int numCanalMen,double tasaMenor,double tasaMayor) {
    int hh,mm,seg;
    calcularHoraMinSeg(tiempoTotalRepro,hh,mm,seg);
    archReporte<<"RESUMEN DEL STREAM: "<<endl;
    archReporte<<"#VECES REPRODUCIDAS: "<<setw(5)<<numVecesReprod<<endl;
    archReporte<<"TIEMPO TOTAL REPRODUCCION: ";
    ImprimirHora(hh,mm,seg,archReporte);
    archReporte<<endl;
    archReporte<<"TASA DROPP-OFF MENOR: "<<setw(5)<<tasaMenor<<" CANAL:"<<letraCanalMen<<numCanalMen<<endl;
    archReporte<<"TASA DROPP-OFF MAYOR: "<<setw(5)<<tasaMayor<<" CANAL:"<<letraCanalMay<<numCanalMay<<endl;
}

void imprimirResumenTotal(ofstream &archReporte,int numStreams,double duracTotalRepro) {
    archReporte<<"RESUMEN TOTAL: "<<endl;
    int hh,min,seg;
    ImprimirLinea('-',150,archReporte);
    archReporte<<"# STREAMS: "<<numStreams<<endl;
    calcularHoraMinSeg(duracTotalRepro,hh,min,seg);
    archReporte<<"DURACION TOTAL REPRODUCCION: ";
    ImprimirHora(hh,min,seg,archReporte);
}

void ImprimirEncabezado(ofstream &archReporte) {
    ImprimirLinea('=',150,archReporte);
    archReporte<<setw(50)<<" "<<"PLATAFORMA DE STREAMING TP"<<endl;
    archReporte<<setw(53)<<" "<<"REPRODUCCION DE STREAMS"<<endl;
}
void ImprimirLinea(char car,int tam,ofstream &archReporte) {
    for (int i=0;i<tam;i++) {
        archReporte<<car;
    }
    archReporte<<endl;
}
void BuscarEImprimirCategoria(ifstream &archCategorias,ofstream &archReporte,char letraCat,int numCat) {
    archCategorias.clear();
    archCategorias.seekg(0,ios::beg);
    int num;
    char letra;
    while (true) {
        archCategorias>>letra>>num;
        if (archCategorias.eof()) break;
        if (letra==letraCat and num==numCat) {
            leerNombreEImprimirlo(archCategorias,archReporte,'\n',true,40,false);
            break;
        }
        else while (archCategorias.get()!='\n') ;
    }
}

void BuscarEImprimirIdioma(ifstream &archIdiomas,ofstream &archReporte,int idioma) {
    archIdiomas.clear();
    archIdiomas.seekg(0,ios::beg);
    int codIdioma;
    while (true) {
        archIdiomas>>codIdioma;
        if (archIdiomas.eof()) break;
        if (codIdioma==idioma) {
            leerNombreEImprimirlo(archIdiomas,archReporte,'\n',true,30,true);
            break;
        }
        else while (archIdiomas.get()!='\n') ;
    }
}
void leerNombreEImprimirlo(ifstream &arch,ofstream &archReporte,char delim,bool cambioMayus,int tam,bool idioma) {
    arch>>ws;
    int cantCar=0;
    char car;
    while (true) {
        car=arch.get();
        if (car==delim) break;
        if (car>='a' and car<='z' and cambioMayus==true and idioma==false) car-='a'-'A';
        if (idioma and cantCar==0 and car>='a' and car<='z') {
            car-='a'-'A';
            cantCar++;
        }
        if (car=='_') car=' ';
        archReporte<<car;
        cantCar++;
    }
    archReporte<<setw(tam-cantCar)<<" ";
}
void CalcularDurHorEImprimirHora(ofstream &archReporte,int h,int m,int s,double &duracionHoras) {
    duracionHoras=h+(double)m/60+(double)s/3600;
    ImprimirHora(h,m,s,archReporte);
    archReporte<<endl;
    ImprimirLinea('=',150,archReporte);
}
void ImprimirHora(int h,int m,int s,ofstream &archReporte) {
    archReporte<<setfill('0')<<setw(2)<<h<<":"<<setw(2)<<m<<":"<<setw(2)<<s<<setfill(' ')<<setw(5)<<" ";
}
void BuscarEImprimirDemasDatos(int codStream,double duracionHoras,ifstream &archCanales,
    ofstream &archReporte,int &numVecesReprod,double &tiempoTotalRepro,
    char &letraCanalMay,char &letraCanalMen,int &numCanalMay,int &numCanalMen,double &tasaMenor,double &tasaMayor) {
    archCanales.clear();
    archCanales.seekg(0,ios::beg);
    int ddC,mmC,aaC,numCanal,cantCanles=1;
    char car,letraCanal;
    while (true) {
        archCanales>>ddC>>car>>mmC>>car>>aaC;
        if (archCanales.eof()) break;
        archCanales>>letraCanal>>numCanal;
        archCanales>>ws;
        while (archCanales.get()!=' ') ;
        leerDemasDatosEImprimirlos(archCanales,archReporte,letraCanal,numCanal,codStream,duracionHoras,
            numVecesReprod,tiempoTotalRepro,cantCanles,
            letraCanalMay,letraCanalMen,numCanalMay,numCanalMen,tasaMenor,tasaMayor);
    }
}
void leerDemasDatosEImprimirlos(ifstream &archCanales,ofstream &archReporte,char letraCanal,int numCanal,int codStream,double duracionHoras,
    int &numVecesReprod,double &tiempoTotalRepro,int &cantCanles,
    char &letraCanalMay,char &letraCanalMen,int &numCanalMay,int &numCanalMen,double &tasaMenor,double &tasaMayor) {
    int codigoStream,ddRepr,mmRepr,aaRepr,
    hhI,minI,segI,hhF,minF,segF,cantReprod=1;
    double ratingCal,tasaAbandono,sumaRating=0,sumaTasa=0;
    char car;
    //flag para saber si al menos encontramos un canal
    //para poder imprimir el resumen de ese canal
    bool Encontro=false,impCabCanal=true;
    while (true) {
        archCanales>>codigoStream>>ddRepr>>car>>mmRepr>>car>>aaRepr>>hhI>>car>>minI>>car>>segI
                    >>ratingCal>>tasaAbandono;
        //si en caso lo encuentra,haremos lo que sigue
        if (codigoStream==codStream ) {
            Encontro=true;
            if (impCabCanal) {
                archReporte<<setfill('0')<<setw(2)<<cantCanles<<")"<<setfill(' ')<<"CANAL: "<<letraCanal<<numCanal<<endl;
                archReporte<<setw(3)<<" "<<"REPRODUCCIONES"<<endl;
                imprimirSubtiCanales(archReporte);
                cantCanles++;//se va aumentando solo una vez
                impCabCanal=false;
            }
            encontrarMenorYMayorTasa(letraCanal,numCanal,tasaAbandono,
                letraCanalMay,letraCanalMen,numCanalMay,numCanalMen,tasaMenor,tasaMayor);
            archReporte<<setw(3)<<" "<<setfill('0')<<setw(2)<<cantReprod<<")"<<setfill(' ')<<setw(5)<<" ";
            double duracionInciial=hhI+(double)minI/60+(double)segI/3600;
            double duracionFinal=duracionInciial+duracionHoras;
            sumaRating+=ratingCal,sumaTasa+=tasaAbandono;
            calcularHoraMinSeg(duracionFinal,hhF,minF,segF);
            ImprimirFecha(ddRepr,mmRepr,aaRepr,archReporte);
            ImprimirHora(hhI,minI,segI,archReporte);
            ImprimirHora(hhF,minF,segF,archReporte);
            archReporte<<setw(5)<<ratingCal<<setw(14)<<" "<<tasaAbandono*100<<"%"<<endl;
            cantReprod++;
        }
        if (archCanales.get()=='\n') break;
    }
    if (Encontro)
        imprimirResumenCanal(archReporte,duracionHoras,
            cantReprod,numVecesReprod,tiempoTotalRepro,
            sumaRating,sumaTasa);
}

void imprimirSubtiCanales(ofstream &archReporte) {
    archReporte<<setw(3)<<" "<<"No."<<setw(7)<<" "<<"FECHA"<<setw(9)<<" "<<"INICIO"<<setw(8)<<" "<<"FIN"
    <<setw(5)<<" "<<"RATING CALIDAD"<<setw(5)<<" "<<"TASA DROP-OFF"<<endl;
}

void encontrarMenorYMayorTasa(char letraCanal,int numCanal,double tasaAbandono,
                char &letraCanalMay,char &letraCanalMen,int &numCanalMay,int &numCanalMen,double &tasaMenor,double &tasaMayor) {
    if (tasaAbandono>tasaMayor) {
        letraCanalMay=letraCanal;
        numCanalMay=numCanal;
        tasaMayor=tasaAbandono;
    }
    if (tasaAbandono<tasaMenor) {
        letraCanalMen=letraCanal;
        numCanalMen=numCanal;
        tasaMenor=tasaAbandono;
    }
}

void imprimirResumenCanal(ofstream &archReporte,double duracionHoras,int cantReprod,
    int &numVecesReprod,double &tiempoTotalRepro,double sumaRating,double sumaTasa) {
    cantReprod--;//porque iniciamos en uno
    double tiempoTotalReproXCanal=duracionHoras*cantReprod;
    //para el resumen del stream
    numVecesReprod+=cantReprod;
    tiempoTotalRepro+=tiempoTotalReproXCanal;
    //
    int hhC,minC,segC;
    calcularHoraMinSeg(tiempoTotalReproXCanal,hhC,minC,segC);
    archReporte<<setw(3)<<" "<<"RESUMEN CANAL:"<<endl;
    archReporte<<setw(3)<<" "<<"TOTAL TIEMPO DE REPRODUCCIONES: ";
    ImprimirHora(hhC,minC,segC,archReporte);
    archReporte<<endl;
    archReporte<<setw(3)<<" "<<"PROMEDIO DE RATING CALIDAD: "<<setw(5)<<sumaRating/cantReprod<<endl;
    archReporte<<setw(3)<<" "<<"PROMEDIO DE LA TASA DROPP-OFF: "<<setw(5)<<(sumaTasa/cantReprod)*100<<"%"<<endl;
    ImprimirLinea('-',150,archReporte);
}

void calcularHoraMinSeg(double duracion,int &hh,int &min,int &seg) {
    hh=(int)duracion;
    min=(int)((duracion-hh)*60);
    seg=(int )((((duracion-hh)*60)-min)*60);
}
void ImprimirFecha(int dd,int mm,int aa,ofstream &archReporte) {
    archReporte<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ')<<setw(5)<<" ";
}