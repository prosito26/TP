//
// Created by aml on 27/10/2025.
//

#include "FuncionesAuxiliares.h"

void CargarInfoStreams(const char *NombreArch, int *arrCodStream, int *arrIdiomaStream, double *arrDuracionHoras,
                       int *arrNumCat,
                       char *arrLetraCat, int &cantStreams) {
    ifstream arch(NombreArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int cod, hh, min, seg, idioma, categoria;
    char car, letra;
    double tiempoHoras;
    while (true) {
        arch >> cod;
        if (arch.eof()) break;
        arch >> hh >> car >> min >> car >> seg >> idioma >> letra >> categoria;
        tiempoHoras = hh + (double) min / 60 + (double) seg / 3600;
        insertarOrdenadoDurHoras(arrCodStream, arrDuracionHoras, arrIdiomaStream, arrLetraCat, arrNumCat,
                                 cod, tiempoHoras, idioma, letra, categoria, cantStreams);
    }
}

void insertarOrdenadoDurHoras(int *arrCodStream, double *arrDuracionHoras, int *arrIdiomaStream, char *arrLetraCat,
                              int *arrNumCat,
                              int cod, double tiempoHoras, int idioma, char letra, int categoria, int &cantStreams) {
    int i = cantStreams - 1;
    while (i >= 0 and arrCodStream[i] > cod) {
        arrCodStream[i + 1] = arrCodStream[i];
        arrDuracionHoras[i + 1] = arrDuracionHoras[i];
        arrIdiomaStream[i + 1] = arrIdiomaStream[i];
        arrLetraCat[i + 1] = arrLetraCat[i];
        arrNumCat[i + 1] = arrNumCat[i];
        i--;
    }
    arrCodStream[i + 1] = cod;
    arrDuracionHoras[i + 1] = tiempoHoras;
    arrIdiomaStream[i + 1] = idioma;
    arrLetraCat[i + 1] = letra;
    arrNumCat[i + 1] = categoria;
    cantStreams++;
}

void VerificarDatos(const char *NombreArch, int *arrCodStream, int *arrIdiomaStream, double *arrDuracionHoras,
                    int *arrNumCat,
                    char *arrLetraCat, int cantStreams) {
    ofstream archReporte(NombreArch, ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    archReporte<<setprecision(2)<<fixed;
    archReporte << setw(17) << " " << "DATOS PARCIALES STREAMS" << endl;
    archReporte << "Codigo" << setw(10) << " " << "Duracion Horas" << setw(10) << " " << "Idioma" << setw(10) << " " <<
            "Categoria" << endl;
    for (int i = 0; i < cantStreams; i++) {
        archReporte << arrCodStream[i] <<setw(5)<< " " <<setw(13)<< arrDuracionHoras[i] <<setw(17)<< " "
                << arrIdiomaStream[i] <<setw(13)<< " "  << arrLetraCat[i]<< arrNumCat[i] << endl;
    }
}
void CargarDemasArreglosAuxiliares(const char *NombreArch,int *arrCodStream,int cantStreams,
        int *arrReproReciente,int *arrReproMasAntigua,int *arrNumReproducciones,double *arrPromRting,double *arrPromTasaDroppOff) {
    ifstream arch(NombreArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int num,codigoStream,dd,mm,aa,hh,min,seg,idStream,fechaRepro;
    double tasa,rating;
    char car;
    while (true) {
        arch>>num>>car>>num>>car>>num;
        if (arch.eof()) break;
        arch>>car>>num>>ws;
        while (arch.get()!=' ');
        while (true) {
            arch>>codigoStream>>dd>>car>>mm>>car>>aa>>hh>>car>>min>>car>>seg>>rating>>tasa;
            fechaRepro=aa*10000+mm*100+dd;
            idStream=BuscarStream(codigoStream,arrCodStream,cantStreams);
            if (idStream!=NO_ENCONTRADO) {
                actualizarAreglos(arrReproReciente[idStream],arrReproMasAntigua[idStream],
                    arrNumReproducciones[idStream],arrPromRting[idStream],arrPromTasaDroppOff[idStream],
                    fechaRepro,rating,tasa);
            }
            if (arch.get()=='\n')break;
        }
    }
}
void actualizarAreglos(int  &arrReproReciente,int  &arrReproMasAntigua,
                    int &arrNumReproducciones,double &arrPromRting,double &arrPromTasaDroppOff,
                    int fechaRepro,double rating,double tasa) {
    arrNumReproducciones++;
    if (arrNumReproducciones==1) {
        arrReproMasAntigua=arrReproReciente=fechaRepro;
        arrPromRting=rating;
        arrPromTasaDroppOff=tasa;
    }
    else if (arrNumReproducciones>1){
        if (fechaRepro>arrReproReciente) arrReproReciente=fechaRepro;
        if (fechaRepro<arrReproMasAntigua) arrReproMasAntigua=fechaRepro;
        double sumaRting=arrPromRting+rating;
        double sumaTasa=arrPromTasaDroppOff+tasa;
        arrPromRting=sumaRting/arrNumReproducciones;
        arrPromTasaDroppOff=sumaTasa/arrNumReproducciones;
    }
}
int BuscarStream(int codigo,int *arr,int cantStreams) {
    int limiteInf=0,limiteSup=cantStreams-1,puntoMedio;
    while (true) {
        if (limiteInf>limiteSup) return NO_ENCONTRADO;
        puntoMedio=(limiteInf+limiteSup)/2;
        if (codigo==arr[puntoMedio]) return puntoMedio;
        if (codigo>arr[puntoMedio]) limiteInf=puntoMedio+1;
        else limiteSup=puntoMedio-1;
    }
}
void EmitirReporteStreams(const char *NombreArch,int *arrCodStream,int *arrIdiomaStream,double *arrDuracionHoras,int *arrNumCat,
    char *arrLetraCat,int cantStreams,int *arrReproReciente,int *arrReproMasAntigua,int *arrNumReproducciones,double *arrPromRting,
    double *arrPromTasaDroppOff,bool ordenado) {
    ofstream archReporte(NombreArch, ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int hDur,minDur,segDur,ddReprRec,mmReprRec,aaReprRec,aaReprMasAnt,mmReprMasAnt,ddReprMasAnt,
    hDurTotal,minDurTotal,segDurTotal,streamMayorDuracion,streamMenorDuracion;
    double mayorDuracion,menorDuracion;
    archReporte<<setprecision(2)<<fixed;
    archReporte << setw(50) << " " << "PLATAFORMA DE STREAMING" << endl;
    if (ordenado==false) {
        archReporte << setw(40) << " " << "DETALLE COMPLETO DE REPRODUCCION STREAMS" << endl;
    }
    else archReporte << setw(20) << " " << "DETALLE COMPLETO DE REPRODUCCION DE STREAMS ORDENADO POR CATEGORIA Y TASA DROPP-OOF" << endl;
    archReporte << "STREAM" << setw(9) << " " << "Idioma" << setw(5) << " " <<
            "Categoria" <<setw(3)<<" "<<"DURACION"<<setw(8)<<" "<<"REP.ANTIGUA"<<setw(8)<<" "<<"REP.RECIENTE"
    <<setw(8)<<" "<<"PROM.RAT.CANAL"<<setw(8)<<" "<<"PROM.TASA DROPP OFF"<<setw(4)<<" "<<"#REPR."<<setw(4)<<" "<<"TOTAL REPR."<< endl;
    for (int i = 0; i < cantStreams; i++) {
        double duracionTotal=arrDuracionHoras[i]*arrNumReproducciones[i];
        hDur=(int )arrDuracionHoras[i],minDur=(int) ((arrDuracionHoras[i]-hDur)*60),segDur=(int) ((((arrDuracionHoras[i]-hDur)*60)-minDur)*60);
        hDurTotal=(int )duracionTotal,minDurTotal=(int) ((duracionTotal-hDurTotal)*60),segDurTotal=(int) ((((duracionTotal-hDurTotal)*60)-minDurTotal)*60);
        aaReprRec=arrReproReciente[i]/10000,mmReprRec=(arrReproReciente[i]%10000)/100,ddReprRec=arrReproReciente[i]%100;
        aaReprMasAnt=arrReproMasAntigua[i]/10000,mmReprMasAnt=(arrReproMasAntigua[i]%10000)/100,ddReprMasAnt=arrReproMasAntigua[i]%100;
        archReporte << arrCodStream[i] <<setw(10)<< " "<< arrIdiomaStream[i]
        <<setw(8)<< " "  << arrLetraCat[i]<< arrNumCat[i] <<setw(5)<<" ";
        ImprimirHora(archReporte,hDur,minDur,segDur);
        ImprimirFecha(archReporte,ddReprMasAnt,mmReprMasAnt,aaReprMasAnt);
        ImprimirFecha(archReporte,ddReprRec,mmReprRec,aaReprRec);
        archReporte<<setw(5)<<arrPromRting[i]<<setw(20)<<" "<<setw(6)<<arrPromTasaDroppOff[i]*100<<"%"<<setw(10)<<" "
        <<setw(3)<<arrNumReproducciones[i]<<setw(8)<<" ";
        ImprimirHora(archReporte,hDurTotal,minDurTotal,segDurTotal);
        archReporte<<endl;
        calcularMayorYMenorStreamDura(i,arrCodStream[i],arrDuracionHoras[i],streamMayorDuracion,streamMenorDuracion,mayorDuracion,menorDuracion);
    }
    if (ordenado==false) {
        ImprimirResumen(mayorDuracion,menorDuracion,streamMayorDuracion,streamMenorDuracion,archReporte);
    }
}
void ImprimirHora(ofstream &archReporte,int h,int min,int seg) {
    archReporte<<setfill('0')<<setw(2)<<h<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ')<<setw(10)<<" ";
}
void ImprimirFecha(ofstream &archReporte,int dd,int mm,int aa) {
    archReporte<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ')<<setw(10)<<" ";
}
void OrdenarDatos(int *arrCodStream,int *arrIdiomaStream,double *arrDuracionHoras,int *arrNumCat,
    char *arrLetraCat,int cantStreams,int *arrReproReciente,int *arrReproMasAntigua,int *arrNumReproducciones,
    double *arrPromRting,double *arrPromTasaDroppOff) {
    for (int i = 0; i < cantStreams-1; i++)
        for (int k = i+1; k < cantStreams; k++) {
            if (arrLetraCat[i]>arrLetraCat[k] or
                arrLetraCat[i]==arrLetraCat[k] and arrNumCat[i]>arrNumCat[k] or
                arrNumCat[i]==arrNumCat[k] and arrPromTasaDroppOff[i]<arrPromTasaDroppOff[k] ) {
                intercambiarInt(arrCodStream[i],arrCodStream[k]);
                intercambiarInt(arrIdiomaStream[i],arrIdiomaStream[k]);
                intercambiarInt(arrNumCat[i],arrNumCat[k]);
                intercambiarInt(arrReproReciente[i],arrReproReciente[k]);
                intercambiarInt(arrReproMasAntigua[i],arrReproMasAntigua[k]);
                intercambiarInt(arrNumReproducciones[i],arrNumReproducciones[k]);
                intercambiarDbl(arrDuracionHoras[i],arrDuracionHoras[k]);
                intercambiarDbl(arrPromRting[i],arrPromRting[k]);
                intercambiarDbl(arrPromTasaDroppOff[i],arrPromTasaDroppOff[k]);
                intercambiarChar(arrLetraCat[i],arrLetraCat[k]);
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
void intercambiarChar(char &datoI,char &datoK) {
    char aux;
    aux=datoI;
    datoI=datoK;
    datoK=aux;
}
void calcularMayorYMenorStreamDura(int i,int arrCodStream,double arrDuracionHoras,
    int &streamMayorDuracion,int &streamMenorDuracion,double &mayorDuracion,double &menorDuracion) {
    if (i==1) {
        streamMayorDuracion=streamMenorDuracion=arrCodStream;
        mayorDuracion=menorDuracion=arrDuracionHoras;
    }
    else if (i>1) {
        if (arrDuracionHoras>mayorDuracion) {
            streamMayorDuracion=arrCodStream;
            mayorDuracion=arrDuracionHoras;
        }
        if (arrDuracionHoras<menorDuracion) {
            streamMenorDuracion=arrCodStream;
            menorDuracion=arrDuracionHoras;
        }
    }
}
void ImprimirResumen(double mayorDuracion,double menorDuracion,int streamMayorDuracion,int streamMenorDuracion,ofstream &archReporte) {
    int hMayDur,segMayDur,minMayDur;
    hMayDur=(int )mayorDuracion;
    minMayDur=(int) ((mayorDuracion-hMayDur)*60);
    segMayDur=(int) ((((mayorDuracion-hMayDur)*60)-minMayDur)*60);
    int hMenDur,segMenDur,minMenDur;
    hMenDur=(int )menorDuracion;
    minMenDur=(int) ((menorDuracion-hMenDur)*60);
    segMenDur=(int) ((((menorDuracion-hMenDur)*60)-minMenDur)*60);
    archReporte<<"RESUMEN:"<<endl;
    archReporte<<"STREAM CON MAYOR DURACION:"<<setw(5)<<" "<<streamMayorDuracion<<" - ";
    ImprimirHora(archReporte,hMayDur,minMayDur,segMayDur);
    archReporte<<endl;
    archReporte<<"STREAM CON MENOR DURACION:"<<setw(5)<<" "<<streamMenorDuracion<<" - ";
    ImprimirHora(archReporte,hMenDur,minMenDur,segMenDur);
    archReporte<<endl;
}