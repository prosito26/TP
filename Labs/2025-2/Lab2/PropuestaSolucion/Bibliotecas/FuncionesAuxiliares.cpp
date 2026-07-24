//
// Created by aml on 15/09/2025.
//

#include "FuncionesAuxiliares.h"

void ProcesarDatos(ifstream &archLeer,ofstream &archReporte,
    int ddI,int mmI,int aaI,int ddF,int mmF,int aaF,double pagoXRepr,double pagoXTiempo) {
    int fechaInicio=TransformarFecha(ddI,mmI,aaI);
    int fechaLimite=TransformarFecha(ddF,mmF,aaF);
    int dd,mm,aa,fechaAEvaluar,i=1, cantTotalStreams=0;
    double duracionTotalStreams=0,ingresosTotalesXPubli=0,ingresosTotalesXDuracion=0;
    char car;
    ImprimirEncabezado(archReporte,ddI,mmI,aaI,ddF,mmF,aaF,pagoXRepr,pagoXTiempo);
    while (true) {
        archLeer>>dd>>car>>mm>>car>>aa;
        if (archLeer.eof()) break;
        fechaAEvaluar=TransformarFecha(dd,mm,aa);
        if (fechaAEvaluar>=fechaInicio and fechaAEvaluar<=fechaLimite) {
            LeerDatosEImprimirlos(dd,mm,aa,pagoXRepr,pagoXTiempo,archReporte,archLeer,i,
            cantTotalStreams, duracionTotalStreams,
            ingresosTotalesXPubli, ingresosTotalesXDuracion);
            i++;
        }
        else
            while (archLeer.get()!='\n');
    }
    imprimirResumenFinal(archReporte,cantTotalStreams,duracionTotalStreams,
        ingresosTotalesXPubli,ingresosTotalesXDuracion);
}
void ImprimirEncabezado(ofstream &archReporte,int ddI,int mmI,int aaI,int ddF,int mmF,int aaF,
    double pagoXRepr,double pagoXTiempo) {
    archReporte<<setprecision(2)<<fixed;
    archReporte<<setw(50)<<" "<<"PLATAFORMA TP_Twitch"<<endl;
    archReporte<<setw(42)<<" "<<"REGISTRO DE LOS CANALES AFILIADOS"<<endl;
    archReporte<<setw(30)<<" "<<"FECHAS DE CREACION ENTRE EL ";
    ImprimirFecha(ddI,mmI,aaI,archReporte);
    archReporte<<" Y EL ";
    ImprimirFecha(ddF,mmF,aaF,archReporte);
    archReporte<<endl;
    archReporte<<setw(20)<<" "<<"TARIFA POR NUMERO DE REPRODUCCIONES: "<<setw(4)<<pagoXRepr;
    archReporte<<" POR CADA 1,000 REPRODUCCIONES Y FRACCION"<<endl;
    archReporte<<setw(30)<<" "<<"TARIFA POR DURACION DEL STREAM: "<<setw(4)<<pagoXTiempo;
    archReporte<<" POR CADA MINUTO Y FRACCION"<<endl;

}
int  TransformarFecha(int dd,int mm,int aa) {
    return aa*10000+mm*100+dd;
}
void ImprimirFecha(int dd,int mm,int aa,ofstream &archReporte) {
    archReporte<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}
void LeerDatosEImprimirlos(int dd,int mm,int aa,double pagoXRepr,double pagoXTiempo,
    ofstream &archReporte,ifstream &archLeer,int i,
    int &cantTotalStreams,double &duracionTotalStreams,
        double &ingresosTotalesXPubli,double &ingresosTotalesXDuracion) {
    ImprimirSubEncabezados(archReporte,i);
    char letraCod;
    int numCod;
    long long numSeguiNuevosXMes,numVisitasXMes,maxEspect;
    archLeer>>letraCod>>numCod;
    archReporte<<setw(6)<<" ";
    LeerNombreEImprimirlo(archReporte,archLeer,' ',20);
    archReporte<<" "<<letraCod<<numCod<<setw(16)<<" ";
    ImprimirFecha(dd,mm,aa,archReporte);
    archReporte<<setw(16)<<" ";
    archLeer>>numSeguiNuevosXMes>>numVisitasXMes>>maxEspect;
    archReporte<<numSeguiNuevosXMes<<setw(21)<<" "<<numVisitasXMes<<setw(17)<<" "<<maxEspect<<endl;
    LeerDemasDatosEImprimirlos(archLeer,archReporte,dd,mm,aa,letraCod,numCod,
    numSeguiNuevosXMes,numVisitasXMes,maxEspect,pagoXRepr,pagoXTiempo,cantTotalStreams,duracionTotalStreams,
    ingresosTotalesXPubli,ingresosTotalesXDuracion);
}
void ImprimirSubEncabezados(ofstream &archReporte,int i) {
    ImprimirLinea('=',150,archReporte);
    archReporte<<"CANAL No."<<i<<endl;
    archReporte<<setw(6)<<" "<<"NOMBRE"<<setw(15)<<" "
                            <<"CODIGO"<<setw(15)<<" "
                            <<"CREADO EL"<<setw(8)<<" "
                            <<"SEGUIDORES NUEVOS POR MES"<<setw(5)<<" "
                            <<"VISITAS NUEVAS POR MES"<<setw(5)<<" "
                            <<"MAXIMO DE ESPECTADORES"<<endl;


}
void ImprimirLinea(char car,int tam,ofstream &archReporte) {
    for (int i=0;i<tam;i++) {
        archReporte<<car;
    }
    archReporte<<endl;
}
void LeerNombreEImprimirlo(ofstream &archReporte,ifstream &arch,char delim,int tam) {
    arch>>ws;
    int cantCar=0;
    char car;
    while (true) {
        car=arch.get();
        if (car==delim) break;
        if (car>='a' and car<='z') car -= 'a'-'A';
        archReporte<<car;
        cantCar++;
    }
    archReporte<<setw(tam-cantCar)<<" ";
}
void LeerDemasDatosEImprimirlos(ifstream &archLeer,ofstream &archReporte,
    int dd,int mm,int aa,char letraCod,int numCod,
    long long numSeguiNuevosXMes,long long numVisitasXMes,long long maxEspect,double pagoXRepr,double pagoXTiempo,
    int &cantTotalStreams,double &duracionTotalStreams,
        double &ingresosTotalesXPubli,double &ingresosTotalesXDuracion) {
    int ddPubli,mmPubli,aaPubli,hhDur,minDur,segDur,cantRepr,acumRepro=0;
    char car;
    double duracionHoras,acumHoras=0,ingresosXDuracion,acumIngresoXDuraci=0,ingresosXPublicidad;
    ImprimirSubEncabezadosCanal(archReporte);
    double engaIndex=((numSeguiNuevosXMes + (numVisitasXMes/1000.0))/maxEspect);
    while (true) {
        cantTotalStreams++;
        archLeer>>ddPubli>>car>>mmPubli>>car>>aaPubli>>hhDur>>car>>minDur>>car>>segDur>>cantRepr;
        archReporte<<setw(11)<<" ";
        ImprimirFecha(ddPubli,mmPubli,aaPubli,archReporte);
        archReporte<<setw(20)<<" ";
        ImprimirHora(hhDur,minDur,segDur,archReporte);
        archReporte<<setw(14)<<" ";
        CalcularDuracionHorasEImprimirlo(hhDur,minDur,segDur,archReporte,pagoXRepr,pagoXTiempo,
            cantRepr,duracionHoras,ingresosXDuracion);
        acumHoras+=duracionHoras;
        acumIngresoXDuraci+=ingresosXDuracion;
        acumRepro+=cantRepr;
        archReporte<<setw(7)<<cantRepr<<endl;
        if (archLeer.get()=='\n') break;
    }
    ingresosXPublicidad= ((acumRepro*pagoXRepr)/1000.0);
    ImprimirLinea('=',150,archReporte);
    ImprimirEstadisticasCanal(archReporte,acumHoras,acumIngresoXDuraci,acumRepro,ingresosXPublicidad,engaIndex);
    ingresosTotalesXDuracion+=acumIngresoXDuraci;
    ingresosTotalesXPubli+=ingresosXPublicidad;
    duracionTotalStreams+=acumHoras;
}
void ImprimirSubEncabezadosCanal(ofstream &archReporte) {
    ImprimirLinea('-',150,archReporte);
    archReporte<<setw(5)<<" "<<"ULTIMAS REPRODUCCIONES"<<endl;
    archReporte<<setw(11)<<" "<<"FECHA DE PUBLICACION"<<setw(6)<<" ";
    archReporte<<"TIEMPO DE DURACION"<<setw(6)<<" "<<"INGRESOS POR DURACION";
    archReporte<<setw(6)<<" "<<"NUMEROS DE REPRODUCCIONES"<<endl;
}
void ImprimirHora(int hh,int min,int seg,ofstream &archReporte) {
    archReporte<<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ');
}
void CalcularDuracionHorasEImprimirlo(int hhDur,int minDur,int segDur,
    ofstream &archReporte,double pagoXRepr,double pagoXTiempo,int cantRepr,
    double &duracionHoras,double &ingresosXDuracion) {
    duracionHoras=CalcularDuracionHoras(hhDur,minDur,segDur);
    archReporte<<setprecision(2)<<fixed;
    ingresosXDuracion = duracionHoras*60*pagoXTiempo;//lo paso a minutos
    archReporte<<setw(8)<<ingresosXDuracion<<setw(22)<<" ";
}
double CalcularDuracionHoras(int hh,int min,int seg) {
    return hh + (double)min/60 + (double)seg/3600;
}
void ImprimirEstadisticasCanal(ofstream &archReporte,double acumHoras,double acumIngresoXDuraci,
    int acumRepro,double ingresosXPublicidad,double engaIndex) {
    archReporte<<setprecision(2)<<fixed;
    int h,min,seg;

    TransformarFormatoHora(acumHoras,h,min,seg);
    archReporte<<setw(6)<<" "<<"RESUMEN DEL CANAL:"<<endl;
    archReporte<<setw(6)<<" "<<"DURACION TOTAL DE LAS REPRODUCCIONES: ";
    ImprimirHora(h,min,seg,archReporte);
    archReporte<<endl;
    archReporte<<setw(6)<<" "<<"INGRESOS POR DURACION: "<<setw(15)<<" "<<"$"<<setw(7)<<acumIngresoXDuraci<<endl;
    archReporte<<setw(6)<<" "<<"TOTAL DE REPRODUCCIONES: "<<setw(16)<<" "<<left<<setw(8)<<acumRepro<<right<<endl;
    archReporte<<setw(6)<<" "<<"INGRESOS POR PUBLICIDAD: "<<setw(15)<<"$"<<setw(6)<<ingresosXPublicidad<<endl;
    archReporte<<setw(6)<<" "<<"ENGAGEMENT INDEX: "<<setw(21)<<" "<<setw(7)<<engaIndex<<endl;

}
void TransformarFormatoHora(double acumHoras,int &h,int &min,int &seg) {
    h = (int ) acumHoras;
    min = (int ) ((acumHoras-h)*60);
    seg = (int ) ((((acumHoras-h)*60)-min)*60);
}
void imprimirResumenFinal(ofstream &archReporte,int cantTotalStreams,double duracionTotalStreams,
        double ingresosTotalesXPubli,double ingresosTotalesXDuracion) {
    int h,min,seg;
    TransformarFormatoHora(duracionTotalStreams,h,min,seg);
    ImprimirLinea('=',150,archReporte);
    archReporte<<"RESUMEN FINAL:"<<endl;
    archReporte<<"CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES: "<<setw(11)<<cantTotalStreams<<endl;
    archReporte<<"DURACION TOTAL DE LOS STREAMS PUBLICADOS: "<<setw(12)<<" ";
    archReporte<<setfill('0')<<setw(4)<<h<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ');
    archReporte<<endl;
    archReporte<<"INGRESOS TOTALES POR DURACION: "<<setw(22)<<" "<<"$"<<setw(10)<<ingresosTotalesXDuracion<<endl;
    archReporte<<"INGRESOS TOTALES POR PUBLICIDAD: "<<setw(20)<<" "<<"$"<<setw(10)<<ingresosTotalesXPubli<<endl;
}


