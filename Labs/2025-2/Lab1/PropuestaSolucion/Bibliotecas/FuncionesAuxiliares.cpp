//
// Created by aml on 8/09/2025.
//

#include "FuncionesAuxiliares.h"
//Cuando ingrese al CMD pon esto:
//primero va el punto .exe < archivos de datos > archivo de reporte
//.exe < ArchivosDeDatos\twitchdataTP.txt > ArchivosDeReporte\Reporte.txt
void ProcesarDatos() {
    int ddI=9,mmI=9,aaI=2022,ddF=1,mmF=1,aaF=2023;
    int fechaInicio=aaI*10000+mmI*100+ddI;
    int fechaFin=aaF*10000+mmF*100+ddF;
    ImprimirEncabezado(ddI,mmI,aaI,ddF,mmF,aaF);
    LeerDatosEImprimirlos(fechaInicio,fechaFin);
}
void ImprimirEncabezado(int ddI,int mmI,int aaI,int ddF,int mmF,int aaF) {
    cout<<setw(35)<<" "<<"PLATAFORMA DE TP_Twitch"<<endl;
    cout<<setw(30)<<" "<<"REGISTRO DE LOS CANALES AFILIADOS"<<endl;
    cout<<setw(25)<<" "<<"FECHAS DE CREACIOM ENTRE EL ";
    ImprimirFecha(ddI,mmI,aaI);
    cout<<" Y EL ";
    ImprimirFecha(ddF,mmF,aaF);
    cout<<endl;
}
void ImprimirFecha(int dd,int mm,int aa) {
    cout<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ');
}
void ImprimirLinea(char car,int tam) {
    for(int i=0;i<tam;i++) {
        cout<<car;
    }
    cout<<endl;
}
void LeerDatosEImprimirlos(int fechaInicio,int fechaFin) {
    int ddC,mmC,aaC,numCodigo,numSeguidores,streamTotales=0;
    char LetraCodigo,car;
    int i=1;
    double HorasTotales=0,IngresoTotalXPubli=0;
    while (true) {
        cin>>ddC>>car>>mmC>>car>>aaC;
        if (cin.eof()) break;
        int fecha=aaC*10000+mmC*100+ddC;
        if (fecha>=fechaInicio and fecha<=fechaFin) {
            ImprimirLinea('=',100);
            cout<<"CANAL No."<<i<<endl;
            ImprimirSubEncabezados();
            cin>>LetraCodigo>>numCodigo;
            cout<<setw(6)<<" ";
            LeerNombreEImprimirlo(' ',LetraCodigo,numCodigo);
            cout<<setw(6)<<" ";
            ImprimirFecha(ddC,mmC,aaC);
            cout<<setw(6)<<" ";
            cin>>numSeguidores;
            cout<<setw(8)<<" "<<numSeguidores<<endl;
            ImprimirLinea('-',100);
            LeerDemasDatosEImprimirlos(ddC,mmC,aaC,LetraCodigo,numCodigo,numSeguidores,streamTotales,HorasTotales,IngresoTotalXPubli);
            //while (cin.get()!='\n');//esto era para probar mientras iba leyendo
            //este es importante cuando quieres ver si va leyendo bien tus datos.
            i++;
        }
        else while (cin.get()!='\n');//se valida el rango de fechas sino se descarta hasta el salto de linea
    }
    ImprimirEstadisticasFinales(streamTotales,HorasTotales,IngresoTotalXPubli);
}
void ImprimirSubEncabezados() {
    cout<<setw(6)<<" "<<"NOMBRE"<<setw(14)<<" "
        <<"CODIGO"<<setw(5)<<" "
        <<"CREADO EL"<<setw(10)<<" "
        <<"NUMERO DE SEGUIDORES"<<endl;
}
void LeerNombreEImprimirlo(char delim,char LetraCodigo,int numCodigo) {
    cin>>ws;
    char car;
    int cantCar=0;
    while (true) {
        car=cin.get();
        if (car==delim) break;
        if (car>='a' and car<='z') car-='a' - 'A';
        cout<<car;
        cantCar++;
    }
    cout<<setw(20-cantCar)<<" "<<LetraCodigo<<numCodigo;
}
void LeerDemasDatosEImprimirlos(int ddC,int mmC,int aaC,
    char LetraCodigo,int numCodigo,int numSeguidores,int &streamTotales, double &HorasTotales,double &IngresoTotalXPubli) {
    int ddPubli,mmPubli,aaPubli, hhD,minD, segD,ddUlt,mmUlt,aaUlt;
    int hhDura,minDura,segDura,cantReprodu,i=1,AcumReproducciones=0;
    double HorasDurac,AcumularHorasDuracion=0,ingresosXPubli;
    char car;
    ImprimirSubEncabezados2();
    while (true) {
        cin>>ddPubli>>car>>mmPubli>>car>>aaPubli;
        CalcularUltimaPublicacion(i,ddPubli,mmPubli,aaPubli,ddUlt,mmUlt,aaUlt);
        cin>>hhDura>>car>>minDura>>car>>segDura>>cantReprodu;
        AcumReproducciones+=cantReprodu;
        HorasDurac=TransformarAHoras(hhDura,minDura,segDura);
        AcumularHorasDuracion+=HorasDurac;
        ImprimirDatos(ddPubli,mmPubli,aaPubli,hhDura,minDura,segDura,cantReprodu);
        i++;
        if (cin.get()=='\n') break;
    }
    streamTotales+=i;
    HorasTotales+=AcumularHorasDuracion;
    ConvertirAFormatoHora(AcumularHorasDuracion,hhD,minD,segD);
    ImprimirEstadisticasCanal(hhD,minD,segD,ddUlt,mmUlt,aaUlt,AcumReproducciones,ingresosXPubli);
    IngresoTotalXPubli+=ingresosXPubli;
}
void ImprimirSubEncabezados2() {
    cout<<setw(5)<<" "<<"ULTIMAS REPRODUCCIONES"<<endl;
    cout<<setw(11)<<" "<<"FECHA DE PUBLICACION"
        <<setw(10)<<" "<<"TIEMPO DE DURACION"
        <<setw(10)<<" "<<"NUMERO DE REPRODUCCIONES"<<endl;
}
void ImprimirDatos(int ddPubli,int mmPubli,int aaPubli,
    int hhDura,int minDura,int segDura,int cantReprodu) {
    cout<<setw(11)<<" ";
    ImprimirFecha(ddPubli,mmPubli,aaPubli);
    cout<<setw(25)<<" ";
    ImprimirHora(hhDura,minDura,segDura);
    cout<<setw(15)<<" ";
    cout<<setw(11)<<cantReprodu<<endl;
}
void ImprimirHora(int hh,int min,int seg) {
    cout<<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ');
}
void ImprimirEstadisticasCanal(int hhD,int minD,int segD,int ddUlt,int mmUlt,int aaUlt,int AcumReproducciones,double &ingresosXPubli) {

    ImprimirLinea('-',100);
    cout<<setw(5)<<" "<<"RESUMEN DEL CANAL: "<<endl;
    cout<<setw(5)<<" "<<"DURACION TOTAL DE LAS REPRODUCCIONES: ";
    ImprimirHora(hhD,minD,segD);
    cout<<endl;
    cout<<setw(5)<<" "<<"ULTIMA PUBLICACION: ";
    cout<<setw(18)<<" ";
    ImprimirFecha(ddUlt,mmUlt,aaUlt);
    cout<<endl;
    cout<<setw(5)<<" "<<"TOTAL DE REPRODUCCIONES: ";
    cout<<setw(13)<<" ";
    cout<<setw(10)<<left<<AcumReproducciones<<right<<endl;
    ingresosXPubli=CalcularIngresosPorPublicidad(AcumReproducciones);
    cout<<setw(5)<<" "<<"INGRESOS POR PUBLICIDAD: ";
    cout<<setw(13)<<" "<<"$ "<<ingresosXPubli<<endl;
}
double TransformarAHoras(int hh,int min,int seg) {
    return hh + (double)min/60 + (double)seg/3600;
}
void ConvertirAFormatoHora(double AcumularHorasDuracion,int &hhD,int &minD,int &segD) {
    hhD=(int)AcumularHorasDuracion;
    minD=(int)((AcumularHorasDuracion-hhD)*60);
    segD=(int)((((AcumularHorasDuracion-hhD)*60)-minD)*60);
}
void CalcularUltimaPublicacion(int i,int ddPubli,int mmPubli,int aaPubli,
    int &ddUlt,int &mmUlt,int &aaUlt) {
    if (i==1) {
        ddUlt=ddPubli;
        mmUlt=mmPubli;
        aaUlt=aaPubli;
    }
    else {
        if (aaPubli>aaUlt) {
            ddUlt=ddPubli;
            mmUlt=mmPubli;
            aaUlt=aaPubli;
        }
        else if (aaPubli==aaUlt and mmPubli>mmUlt) {
            ddUlt=ddPubli;
            mmUlt=mmPubli;
            aaUlt=aaPubli;
        }
        else if (aaPubli==aaUlt and mmPubli==mmUlt and ddPubli>ddUlt) {
            ddUlt=ddPubli;
            mmUlt=mmPubli;
            aaUlt=aaPubli;
        }
    }
}
double CalcularIngresosPorPublicidad(int AcumReproducciones) {
    return 3.25*(AcumReproducciones/1000.0);
}
void ImprimirEstadisticasFinales(int streamTotales,double HorasTotales,double IngresoTotalXPubli) {
    int hhT,minT,segT;
    ImprimirLinea('=',100);
    cout<<"RESUMEN FINAL: "<<endl;
    cout<<"CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES : "<<setw(10)<<" "<<streamTotales<<endl;
    ConvertirAFormatoHora(HorasTotales,hhT,minT,segT);
    cout<<"DURACIÓN TOTAL DE LOS STREAMS PUBLICADOS : "<<setw(15)<<" ";
    ImprimirHora(hhT,minT,segT);
    cout<<endl;
    cout<<"INGRESOS TOTALES POR PUBLICIDAD: ";
    cout<<setw(21)<<" "<<"$ "<<setw(10)<<IngresoTotalXPubli<<endl;
    cout<<endl;

}