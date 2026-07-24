//
// Created by aml on 22/09/2025.
//

#include "FuncionesAuxiliares.h"

void EmitirReporte(ifstream &archCanales,ifstream &archEtiquetas,ifstream &archReproDeEti,
    ofstream &archReporte,double tarifaDurEtiq) {
    archReporte<<setprecision(2)<<fixed;
    ImprimirEncabezado(archReporte,tarifaDurEtiq);
    int i=1,ddC,mmC,aaC,numCod,cantEti;
    long long etiqueta;
    char letraCod,car;
    double ratingCal,acumTiempo;
    while (true) {
        cantEti=1,acumTiempo=0;
        archCanales>>ddC>>car>>mmC>>car>>aaC;
        if (archCanales.eof())break;
        archCanales>>letraCod>>numCod;
        ImprimirLinea(archReporte,'=',120);
        ImprimirSubtitulos(archReporte,ddC,mmC,aaC,letraCod,numCod,archCanales,i);
        archCanales>>ratingCal;
        archReporte<<setw(5)<<ratingCal<<endl;
        ImprimirSubEtiquetasRepro(archReporte);
        while (true) {
            archCanales>>etiqueta;
            BuscarEImprimirDemasDatos(letraCod,numCod,ratingCal,etiqueta,archReporte,
                archReproDeEti,cantEti,archEtiquetas,
                acumTiempo);
            //cantEti++;
            if (archCanales.get()=='\n') break;
        }
        ImprimirLinea(archReporte,'=',120);
        ImprimirResumenFinal(archReporte,tarifaDurEtiq,ratingCal,acumTiempo);
        i++;
    }
}
void ImprimirEncabezado(ofstream &archReporte,double tarifaDurEtiq) {
    archReporte<<setw(50)<<" "<<"PLATAFORMA TP_Twitch"<<endl;
    archReporte<<setw(35)<<" "<<"TARIFA POR DURACION DE LAS ETIQUETAS:"<<tarifaDurEtiq
    <<" POR CADA MINUTO Y FRACCION"<<endl;
}
void ImprimirLinea(ofstream &archReporte,char car,int tam) {
    for(int i=0;i<tam;i++) {
        archReporte<<car;
    }
    archReporte<<endl;
}
void ImprimirSubtitulos(ofstream &archReporte,int ddC,int mmC,int aaC,
    char letraCod,int numCod,ifstream &archCanales,int i) {
    archReporte<<"CANAL No. "<<i<<endl;
    archReporte<<setw(6)<<" "<<"NOMBRE"<<setw(19)<<" "<<"CODIGO"<<setw(4)<<" "
    <<"CREADO EL"<<setw(3)<<" "<<"RATING DE CALIDAD"<<endl;
    archReporte<<setw(6)<<" ";
    LeerNombreEImprimirlo(archReporte,' ',25,archCanales,true);
    archReporte<<letraCod<<numCod<<setw(5)<<" ";
    ImprimirFecha(ddC,mmC,aaC,archReporte);
    archReporte<<setw(10)<<" ";
}
void LeerNombreEImprimirlo(ofstream &archReporte,char delim,int tam,ifstream &archCanales,bool pasaMayus) {
    archCanales>>ws;
    int cantCar=0;
    char car;
    while (true) {
        car=archCanales.get();
        if (car==delim) break;
        if (car>='a' and car<='z' and pasaMayus) car-='a'-'A';
        archReporte<<car;
        cantCar++;
    }
    archReporte<<setw(tam-cantCar)<<" ";
}
void ImprimirFecha(int dd,int mm,int aa,ofstream &archReporte) {
    archReporte<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}
void ImprimirSubEtiquetasRepro(ofstream &archReporte) {
    archReporte<<"ETIQUETAS REPRODUCIDAS"<<endl;
    archReporte<<setw(2)<<" "<<"No."<<setw(4)<<" "<<"FECHA"
                <<setw(9)<<" "<<"ETIQUETA"
                <<setw(4)<<" "<<"DESCRIPCION"
                <<setw(12)<<" "<<"DURACION"
                <<setw(4)<<" "<<"CANTIDAD DE REPRODUCCIONES"
                <<setw(4)<<" "<<"TIEMPO TOTAL REPRODUCIDO"<<endl;
}
void BuscarEImprimirDemasDatos(char letraCod,int numCod,
    double ratingCal,long long etiqueta,ofstream &archReporte,
    ifstream &archReproDeEti,int &cantEti,ifstream &archEtiquetas,double &acumTiempo) {
    archReproDeEti.clear();
    archReproDeEti.seekg(0,ios::beg);
    int dd,mm,aa,numeroCodCnal,numRepr;
    long long etiquetaCanal;
    char car,letraCanal;
    double tiempoTotal;
    while (true) {
        archReproDeEti>>dd>>car>>mm>>car>>aa;
        if (archReproDeEti.eof()) break;
        archReproDeEti>>letraCanal>>numeroCodCnal;;
        if (letraCanal==letraCod and numeroCodCnal==numCod ) {
            archReproDeEti>>etiquetaCanal;
            if (etiquetaCanal==etiqueta) {
                archReproDeEti>>numRepr;
                archReporte<<setw(2)<<" "<<setfill('0')<<setw(2)<<cantEti<<")"<<setfill(' ');
                archReporte<<setw(2)<<" ";
                ImprimirFecha(dd,mm,aa,archReporte);
                archReporte<<setw(6)<<" "<<etiquetaCanal<<setw(6)<<" ";
                BuscarEImprimirDescripcion(archReporte,archReproDeEti,
                    etiquetaCanal,numRepr,archEtiquetas,tiempoTotal);
                acumTiempo+=tiempoTotal;
                archReporte<<endl;
                cantEti++;
            }
            else
                while (archReproDeEti.get()!='\n') ;
        }
        else
            while (archReproDeEti.get()!='\n') ;
    }
}
void BuscarEImprimirDescripcion(ofstream &archReporte,ifstream &archReproDeEti,long long etiquetaCanal,
    int numRepr,ifstream &archEtiquetas,double &tiempoTotal) {
    archEtiquetas.clear();
    archEtiquetas.seekg(0,ios::beg);
    long long etiquetaEncontrar;
    char car;
    double tiempoMin=0;
    tiempoTotal=0;
    int min,seg;
    while (true) {
        archEtiquetas>>etiquetaEncontrar;
        if (archEtiquetas.eof()) break;
        if (etiquetaEncontrar==etiquetaCanal) {
            LeerNombreEImprimirlo(archReporte,' ',25,archEtiquetas,false);
            archEtiquetas>>min>>car>>seg;
            tiempoMin=min+seg/60.0;
            ImprimirDuracion(min,seg,archReporte);
            archReporte<<right<<setw(15)<<" "<<setw(3)<<numRepr<<setw(23)<<" ";
            tiempoTotal=tiempoMin*numRepr;//tiempo esta en min
            imprimirTiempo(tiempoTotal,archReporte);
            break;//salimos porque ya encontramos
        }
        else
            while (archEtiquetas.get()!='\n') ;
    }
}
void ImprimirDuracion(int min,int seg,ofstream &archReporte) {
    archReporte<<setfill('0')<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ');
}
void imprimirTiempo(double tiempoTotal,ofstream &archReporte) {
    int h,min,seg;
    tiempoTotal=tiempoTotal/60.0;//pasarlo a horas
    h=(int)tiempoTotal;
    min=(int)((tiempoTotal-h)*60);
    seg=(int)((((tiempoTotal-h)*60)-min)*60);
    archReporte<<setfill('0')<<setw(2)<<h<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ');
}
void ImprimirResumenFinal(ofstream &archReporte,double tarifaDurEtiq,double ratingCal,
    double acumTiempo) {
    double Porc=ClasificarTrifa(ratingCal),ingresos=0;
    archReporte<<"TIEMPO TOTAL DE REPRODUCIONES DE ETIQUETAS: "<<setw(8)<<" ";
    imprimirTiempo(acumTiempo,archReporte);
    archReporte<<endl;
    archReporte<<"PORCENTAJE POR RATING  DE CALIDAD: ";
    if (Porc==-2.25)
        archReporte<<setw(18)<<" "<<setw(5)<<Porc<<"%"<<endl;
    else
        archReporte<<setw(18)<<" "<<"+"<<setw(5)<<Porc<<"%"<<endl;
    ingresos = (tarifaDurEtiq*acumTiempo*((100+Porc)/100.0));
    archReporte<<"INGRESOS POR REPRODUCCION DE ETIQUETAS: "<<setw(20)<<ingresos<<endl;
}
double ClasificarTrifa(double ratingCal) {
    double tarifa;
    if (ratingCal>4 and ratingCal<5)       tarifa=0.3*100.0;
    else if (ratingCal>3 and ratingCal<=4) tarifa=0.20*100.0;
    else if (ratingCal>2 and ratingCal<=3) tarifa=0.03*100.0;
    else tarifa=-2.25;
    return tarifa;
}