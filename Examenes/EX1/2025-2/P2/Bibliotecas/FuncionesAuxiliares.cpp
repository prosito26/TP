//
// Created by aml on 13/10/2025.
//

#include "FuncionesAuxiliares.h"

void CargarStreams(const char*NombreArch,int *arrCodStream,int *arrCodIdioma,int *arrNumCat,
    double *arrDuracionHoras,char *arrCharCat,int &cantStreams) {
    ifstream arch(NombreArch,ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int codStream,hh,min,ss,idioma,numCat;
    double duracion;
    char car,charCat;
    while (true) {
        arch >> codStream;
        if (arch.eof()) break;
        arch >> hh>>car>>min>>car>>ss>>idioma>>charCat>>numCat;
        duracion=CalcularDuracionHoras(hh,min,ss);
        arrCodStream[cantStreams]=codStream;
        arrDuracionHoras[cantStreams]=duracion;
        arrCharCat[cantStreams]=charCat;
        arrNumCat[cantStreams]=numCat;
        arrCodIdioma[cantStreams]=idioma;
        cantStreams++;
    }
}
double CalcularDuracionHoras(int hh,int min,int ss) {
    return hh + (double)min/60 + (double)ss/3600;
}
void VerificarDatos(const char *NombreArch,int *arrCodStream,int *arrCodIdioma,int *arrNumCat,
    double *arrDuracionHoras,char *arrCharCat,int cantStreams) {
    ofstream archReporte(NombreArch,ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    archReporte<<setprecision(4)<<fixed;
    archReporte<<setw(40)<<" "<<"DATOS DE STREAMS"<<endl;
    ImprimirLinea('=',100,archReporte);
    archReporte<<"Codigo Stream"<<setw(8)<<" "
                <<"Codigo Idioma"<<setw(10)<<" "
                <<"Duracion Horas"<<setw(8)<<" "
                <<"Categoria"<<endl;
    ImprimirLinea('=',100,archReporte);
    for (int i=0;i<cantStreams;i++) {
        archReporte<<arrCodStream[i]<<setw(19)<<" "<<
                    arrCodIdioma[i]<<setw(18)<<" "<<setw(8)<<arrDuracionHoras[i]<<setw(14)<<" "
                    <<arrCharCat[i]<<arrNumCat[i]<<endl;
    }
}
void ImprimirLinea(char car,int tam,ofstream &archReporte) {
    for (int i=0;i<tam;i++) {
        archReporte<<car;
    }
    archReporte<<endl;
}
void cargarArreglosAuxiliares(const char *NombreArch,int *arrCodStream,int *arrCodIdioma,int *arrNumCat,double *arrDuracionHoras,char *arrCharCat,
        int *arrRepAntigua,int *arrRepRec,int *arrNumRepr,double *arrPromRatCal,double *arrPromTasa,double *arrTiempoTotalRepr,int cantStreams) {
    ifstream arch(NombreArch,ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int num,numCanal,codigoStream,ddR,mmR,aaR,hI,minI,ssI,posStream,fecha;
    double rating,tasa;
    char car,letraCanal;
    while (true) {
        arch>>num>>car>>num>>car>>num;
        if (arch.eof()) break;
        arch>>letraCanal>>numCanal;
        arch>>ws;
        while (arch.get()!=' ');
        while (true) {
            arch>>codigoStream>>ddR>>car>>mmR>>car>>aaR>>hI>>car>>minI>>car>>ssI>>rating>>tasa;
            fecha=aaR*10000+mmR*100+ddR;
            posStream=BuscarIndice(codigoStream,arrCodStream,cantStreams);
            if (posStream!=NO_ENCONTRADO) {
                arrNumRepr[posStream]++;
                arrPromRatCal[posStream]+=rating;
                arrPromTasa[posStream]+=tasa;
                //arrPromRatCal[posStream]=arrPromRatCal[posStream]/arrNumRepr[posStream];
                //arrPromTasa[posStream]=arrPromTasa[posStream]/arrNumRepr[posStream];
                arrTiempoTotalRepr[posStream]=arrDuracionHoras[posStream]*arrNumRepr[posStream];
                CalcularRepAntYRec(fecha,arrNumRepr[posStream],arrRepAntigua[posStream],arrRepRec[posStream]);
            }
            if (arch.get()=='\n') break;
        }
    }
}
int BuscarIndice(int codigoStream,int *arrCodStream,int cantStreams) {
    for (int i=0;i<cantStreams;i++) {
        if (arrCodStream[i]==codigoStream) return  i;
    }
    return NO_ENCONTRADO;
}
void CalcularRepAntYRec(int fecha,int arrNumRepr,int &arrRepAntigua,int &arrRepRec) {
    if (arrNumRepr==1) {
        arrRepAntigua=arrRepRec=fecha;
    }
    else if (arrNumRepr>1) {
        if (fecha<arrRepAntigua) {
            arrRepAntigua=fecha;
        }
        if (fecha>arrRepRec) {
            arrRepRec=fecha;
        }
    }
}
void EmitirReporte(const char *NombreArch,int *arrCodStream,int *arrCodIdioma,int *arrNumCat,double *arrDuracionHoras,char *arrCharCat,
        int *arrRepAntigua,int *arrRepRec,int *arrNumRepr,double *arrPromRatCal,double *arrPromTasa,double *arrTiempoTotalRepr,int cantStreams,
        bool CambioTitulo,bool primeraVez) {
    ofstream archReporte(NombreArch,ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    imprimirTituloSubtitulos(archReporte,CambioTitulo);
    archReporte<<setprecision(2)<<fixed;
    int ddRAnt,mmRAnt,aaRAnt,ddRec,mmRec,aaRec,hDur,minDur,segDur,hTotal,minTotal,segTotal;
    int streamMayor,streamMenor;
    double mayorDur=0,menorDur=99999999;
    for (int i=0;i<cantStreams;i++) {
        calcularMayorMenorStreamDur(streamMayor,streamMenor,mayorDur,menorDur,arrCodStream[i],arrDuracionHoras[i]);
        calcularDdMmAa(aaRAnt,mmRAnt,ddRAnt,arrRepAntigua[i]);
        calcularDdMmAa(aaRec,mmRec,ddRec,arrRepRec[i]);
        calcularHhMinSeg(hDur,minDur,segDur,arrDuracionHoras[i]);
        calcularHhMinSeg(hTotal,minTotal,segTotal,arrTiempoTotalRepr[i]);
        archReporte<<setw(2)<<" "<<arrCodStream[i]<<setw(10)<<" "<<arrCodIdioma[i]<<setw(10)<<" "
                    <<arrCharCat[i]<<arrNumCat[i]<<setw(10)<<" ";
        ImprimirFecha(archReporte,aaRAnt,mmRAnt,ddRAnt);
        ImprimirFecha(archReporte,aaRec,mmRec,ddRec);
        if (arrNumRepr[i]!=0) {
            if (primeraVez) {
                arrPromRatCal[i]=arrPromRatCal[i]/arrNumRepr[i];
                arrPromTasa[i]=arrPromTasa[i]/arrNumRepr[i];
            }
            archReporte<<setw(15)<<arrPromRatCal[i]<<setw(8)<<" "<<setw(15)<<arrPromTasa[i]*100<<"%"<<setw(10)<<" ";
        }
        else archReporte<<setw(15)<<"-"<<setw(8)<<" "<<setw(15)<<"-"<<setw(11)<<" ";
        ImprimirHora(archReporte,segDur,minDur,hDur);
        archReporte<<setw(10)<<" "<<setw(3)<<arrNumRepr[i]<<setw(8)<<" ";
        ImprimirHora(archReporte,segTotal,minTotal,hTotal);
        archReporte<<endl;
    }
    if (primeraVez) imprimirResumen(archReporte,streamMayor,mayorDur,streamMenor,menorDur);
}

void calcularMayorMenorStreamDur(int &streamMayor,int &streamMenor,
    double &mayorDur,double &menorDur,int codStream,double duracion) {
    if (duracion>mayorDur) {
        mayorDur=duracion;
        streamMayor=codStream;
    }
    if (duracion<menorDur) {
        menorDur=duracion;
        streamMenor=codStream;
    }
}

void imprimirTituloSubtitulos(ofstream &archReporte,bool CambioTitulo) {
    ImprimirLinea('=',170,archReporte);
    archReporte<<setw(57)<<" "<<"PLATAFORMA DE STREAMING TP"<<endl;
    if (CambioTitulo)
        archReporte<<setw(40)<<" "<<"DETALLE COMPLETO DE REPRODUCCION DE STREAMS ORDENADO POR IDIOMA Y TASA DROP-OFF"<<endl;
    else
        archReporte<<setw(50)<<" "<<"DETALLE COMPLETO DE REPRODUCCION DE STREAMS"<<endl;
    ImprimirLinea('=',170,archReporte);
    archReporte<<"  STREAM"<<setw(8)<<" "<<"IDIOMA"<<setw(8)<<" "<<"CATEGORIA"<<setw(7)<<" "<<"REP.ANTIGUA"
    <<setw(5)<<" "<<"REP.RECIENTE"<<setw(10)<<" "<<"PROM.RAT.CAL"<<setw(8)<<" "<<"PROM.TASA.DROP-OFF"
    <<setw(5)<<" "<<"DURAC."<<setw(15)<<" "<<"#REPR."<<setw(5)<<" "<<"TOT.REPR."<<endl;
    ImprimirLinea('-',170,archReporte);
}


void calcularDdMmAa(int &aa,int &mm,int &dd,int fecha) {
    aa=fecha/10000,mm=(fecha%10000)/100,dd=fecha%100;
}

void calcularHhMinSeg(int &hh,int &min,int &seg,double duracionHoras) {
    hh=(int)duracionHoras;
    min=(int)((duracionHoras-hh)*60);
    seg=(int)((((duracionHoras-hh)*60)-min)*60);
}

void ImprimirFecha(ofstream & archReporte,int aa,int mm,int dd) {
    if (dd==0)
        archReporte<<setw(2)<<"--"<<"/"<<setw(2)<<"--"<<"/"<<setw(4)<<"----"<<setw(5)<<" ";
    else
        archReporte<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ')<<setw(5)<<" ";
}
void ImprimirHora(ofstream &archReporte,int seg,int min,int h) {
    archReporte<<setfill('0')<<setw(2)<<h<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ')<<setw(5)<<" ";
}

void imprimirResumen(ofstream &archReporte,int streamMayor,double mayorDur,
    int streamMenor,double menorDur) {
    int hhDurMay,minDurMay,segDurMay;
    int hhDurMen,minDurMen,segDurMen;
    ImprimirLinea('-',170,archReporte);
    calcularHhMinSeg(hhDurMay,minDurMay,segDurMay,mayorDur);
    calcularHhMinSeg(hhDurMen,minDurMen,segDurMen,menorDur);
    archReporte<<"STREAM CON MAYOR DURACION: "<<setw(8)<<streamMayor<<" - ";
    ImprimirHora(archReporte,segDurMay,minDurMay,hhDurMay);
    archReporte<<" hrs."<<endl;
    archReporte<<"STREAM CON MENOR DURACION: "<<setw(8)<<streamMenor<<" - ";
    ImprimirHora(archReporte,segDurMen,minDurMen,hhDurMen);
    archReporte<<" hrs.";
}

void OrdenarArreglos(int *arrCodStream,int *arrCodIdioma,int *arrNumCat,double *arrDuracionHoras,char *arrCharCat,
        int *arrRepAntigua,int *arrRepRec,int *arrNumRepr,double *arrPromRatCal,double *arrPromTasa,double *arrTiempoTotalRepr,int cantStreams) {
    for (int i=0;i<cantStreams-1;i++)
        for (int j=i+1;j<cantStreams;j++)
            if (arrCodIdioma[i]>arrCodIdioma[j] or
                arrCodIdioma[i]==arrCodIdioma[j] and arrPromTasa[i]<arrPromTasa[j]) {
                IntercambiarInt(arrCodIdioma[i],arrCodIdioma[j]);
                IntercambiarInt(arrCodStream[i],arrCodStream[j]);
                IntercambiarInt(arrNumCat[i],arrNumCat[j]);
                IntercambiarInt(arrNumRepr[i],arrNumRepr[j]);
                IntercambiarInt(arrRepRec[i],arrRepRec[j]);
                IntercambiarInt(arrRepAntigua[i],arrRepAntigua[j]);
                IntercambiarDbl(arrDuracionHoras[i],arrDuracionHoras[j]);
                IntercambiarDbl(arrPromRatCal[i],arrPromRatCal[j]);
                IntercambiarDbl(arrPromTasa[i],arrPromTasa[j]);
                IntercambiarDbl(arrTiempoTotalRepr[i],arrTiempoTotalRepr[j]);
                IntercambiarChar(arrCharCat[i],arrCharCat[j]);
            }
}
void IntercambiarInt(int &datoI,int &datoJ) {
    int aux;
    aux=datoI;
    datoI=datoJ;
    datoJ=aux;
}
void IntercambiarDbl(double &datoI,double &datoJ) {
    double aux;
    aux=datoI;
    datoI=datoJ;
    datoJ=aux;
}
void IntercambiarChar(char &datoI,char &datoJ) {
    char aux;
    aux=datoI;
    datoI=datoJ;
    datoJ=aux;
}