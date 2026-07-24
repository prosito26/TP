//
// Created by aml on 3/11/2025.
//

#include "FuncionesAuxiliares.h"

void cargarCategorias(const char*nombreArch,char **arrCodigoCategoria,char **arrNombreCategoria,int &cantCategorias) {
    ifstream arch(nombreArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir archivo"<<nombreArch<<endl;
        exit(1);
    }
    char *nombre,*categoria;
    while (true) {
        categoria=leeCadenaExacta(arch);
        if (arch.eof()) break;
        nombre=leeCadenaExacta(arch);
        arrCodigoCategoria[cantCategorias]=categoria;
        arrNombreCategoria[cantCategorias]=nombre;
        cantCategorias++;
    }
}
char *leeCadenaExacta(ifstream &arch) {
    char nombre[100],*ptrNombre;
    arch>>nombre;
    if (arch.eof()) return nullptr;
    ptrNombre=new char[strlen(nombre)+1];
    strcpy(ptrNombre,nombre);
    return ptrNombre;
}
void VerificarDatos(const char*nombreArch,char **arrCodigoCategoria,char **arrNombreCategoria,int cantCategorias) {
    ofstream archReporte(nombreArch,ios::out);
    if (not archReporte.is_open()) {
        cout<<"Error al abrir archivo"<<nombreArch<<endl;
        exit(1);
    }
    archReporte<<setw(30)<<" "<<" "<<"DATOS DE LAS CATEGORIAS"<<endl;
    ImprimirLinea('=',archReporte,100);
    archReporte<<setw(5)<<" "<<"CODIGO"<<setw(22)<<" "<<"NOMBRE"<<endl;
    ImprimirLinea('-',archReporte,100);
    for (int i=0;i<cantCategorias;i++) {
        archReporte<<setw(5)<<" "<<arrCodigoCategoria[i]<<setw(20)<<" "<<left<<setw(80)<<arrNombreCategoria[i]<<right<<endl;
    }
}
void ImprimirLinea(char car,ofstream &archReporte,int tam) {
    for (int i=0;i<tam;i++) {
        archReporte<<car;
    }
    archReporte<<endl;
}
void cargarStreams(const char*nombreArch,int *arrFechaReproduccStream,char **arrNombreCanal,char **arrCategoriaAsociada,double *arrDuracionHorasStream,
        double *arrRatingCalidad,double *arrTasaDroppOf,int &cantStreams) {
    ifstream arch(nombreArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir archivo"<<nombreArch<<endl;
        exit(1);
    }
    int dd,mm,aa,fechaRepr,h,min,seg;
    double rating,tasa,duracionHoras;
    char car,*nombreCanal,*categoria;
    while (true) {
        arch>>dd>>car>>mm>>car>>aa;
        if (arch.eof()) break;
        fechaRepr=aa*10000+mm*100+dd;
        nombreCanal=leeCadenaExacta(arch);
        categoria=leeCadenaExacta(arch);
        arch>>rating>>tasa>>h>>car>>min>>car>>seg;
        duracionHoras=h + (double)min/60+(double)seg/3600;
        arrFechaReproduccStream[cantStreams]=fechaRepr;
        arrDuracionHorasStream[cantStreams]=duracionHoras;
        arrNombreCanal[cantStreams]=nombreCanal;
        arrCategoriaAsociada[cantStreams]=categoria;
        arrRatingCalidad[cantStreams]=rating;
        arrTasaDroppOf[cantStreams]=tasa;
        cantStreams++;
    }
}
void VerificarStreams(const char*nombreArch,int *arrFechaReproduccStream,char **arrNombreCanal,char **arrCategoriaAsociada,double *arrDuracionHorasStream,
        double *arrRatingCalidad,double *arrTasaDroppOf,int cantStreams) {
    ofstream archReporte(nombreArch,ios::out);
    if (not archReporte.is_open()) {
        cout<<"Error al abrir archivo"<<nombreArch<<endl;
        exit(1);
    }
    archReporte<<setprecision(2)<<fixed;
    archReporte<<setw(50)<<" "<<" "<<"DATOS DE LOS STREAMS"<<endl;
    ImprimirLinea('=',archReporte,150);
    archReporte<<"FECHA TRANSF."<<setw(5)<<" "<<"NOMBRE CANAL"<<setw(23)<<" "<<"CAT.ASOCIADA"<<setw(13  )<<" "
    <<"RATING"<<setw(10)<<" "<<"TASA DROPP-OFF"<<setw(10)<<" "<<"DURACION HORAS"<<endl;
    ImprimirLinea('-',archReporte,150);
    for (int i=0;i<cantStreams;i++) {
        archReporte<<arrFechaReproduccStream[i]
        <<setw(10)<<" "<<left<<setw(25)<<arrNombreCanal[i]<<setw(10)<<" "<<setw(10)<<arrCategoriaAsociada[i]<<right
        <<setw(20)<<arrRatingCalidad[i]<<setw(20)<<arrTasaDroppOf[i]<<setw(24)<<arrDuracionHorasStream[i]<<endl;
    }
}
void EmitirReporte(int *arrFechaReproduccStream,char **arrNombreCanal,char **arrCategoriaAsociada,double *arrDuracionHorasStream,
        double *arrRatingCalidad,double *arrTasaDroppOf,int cantStreams,char **arrCodigoCategoria,char **arrNombreCategoria,int cantCategorias) {
    char enlace[200],nombArch[200];
    double promedioRting,promediotasa,acumHoras;
    int cantVeces;
    for (int i=0;i<cantCategorias;i++) {
        cantVeces=0,promedioRting=0,promediotasa=0,acumHoras=0;
        modificarCadena(arrNombreCategoria[i]);
        generaArchivoEnlace(arrNombreCategoria[i],nombArch,enlace);
        //va dentro para que genere cada archivo de acuerdo a cada categoria.
        ofstream archReporte(nombArch,ios::out);
        if (not archReporte.is_open()) {
            cout<<"Error al abrir archivo "<<nombArch<<endl;
            exit(1);
        }
        archReporte<<setprecision(2)<<fixed;
        ImprimirSubtitulos(archReporte,arrNombreCategoria[i],arrCodigoCategoria[i],enlace);
        for (int k=0;k<cantStreams;k++) {
            if (strcmp(arrCodigoCategoria[i],arrCategoriaAsociada[k]) == 0) {
                ImprimirFecha(archReporte,arrFechaReproduccStream[k]);
                archReporte<<left<<setw(30)<<arrNombreCanal[k]<<setw(5)<<" "<<setw(5)<<arrRatingCalidad[k]<<right<<setw(10)<<" ";
                archReporte<<setw(5)<<arrTasaDroppOf[k]<<setw(10)<<" ";
                ImprimirHora(archReporte,arrDuracionHorasStream[k]);
                promedioRting += arrRatingCalidad[k];
                promediotasa += arrTasaDroppOf[k];
                acumHoras+=arrDuracionHorasStream[k];
                cantVeces++;
                archReporte<<endl;
            }
        }
        ImprimirResumen(archReporte,acumHoras,promediotasa,promedioRting,cantVeces);
    }
}
void generaArchivoEnlace(const char *arrNombreCategoria,char *nombArch,char *enlace) {
    char cadena[200]="ArchivosDeReportes/";
    char aux[200]="https://Laboratorio06_2025_2/";
    char aux1[200];
    char txt[10]=".txt";
    strcat(cadena,arrNombreCategoria);
    strcpy(aux1,cadena);
    strcat(cadena,txt);
    strcpy(nombArch,cadena);
    strcat(aux,aux1);
    strcpy(enlace,aux);
    // cout<<nombArch<<endl;
    // cout<<enlace<<endl;
}
void ImprimirSubtitulos(ofstream &archReporte,const char *arrNombreCategoria,const char *arrCodigoCategoria,const char *enlace) {
    archReporte<<"Codigo: "<<arrCodigoCategoria<<endl;
    archReporte<<"Nombre: "<<arrNombreCategoria<<endl;
    archReporte<<"Enlace: "<<enlace<<endl;
    archReporte<<"REPRODUCCIONES"<<endl;
    ImprimirLinea('=',archReporte,100);
    archReporte<<"FECHA"<<setw(15)<<" "<<"CANAL"<<setw(29)<<" "<<"RATING"<<setw(8)<<" "<<"DROPP-OFF"<<setw(8)<<" "<<"DURACION"<<endl;
}
void modificarCadena(char *arrNombreCategoria) {
    bool pasaMayus=true;
    for (int i=0;arrNombreCategoria[i];i++) {
        if (i==0 or pasaMayus and arrNombreCategoria[i]>='a' and arrNombreCategoria[i]<='z') {
            arrNombreCategoria[i]-='a'-'A';
            pasaMayus=false;
        }
        if (arrNombreCategoria[i]=='_') pasaMayus=true;
    }
}
void ImprimirFecha(ofstream &archReporte,int arrFechaReproduccStream) {
    int aa=arrFechaReproduccStream/10000,mm=(arrFechaReproduccStream%10000)/100,dd=arrFechaReproduccStream%100;
    archReporte<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ')<<setw(10)<<" ";
}
void ImprimirHora(ofstream &archReporte,double DuracionHoras) {
    int hh=(int )DuracionHoras;
    int min=(int) ((DuracionHoras-hh)*60);
    int ss=(int)((((DuracionHoras-hh)*60)-min)*60);
    archReporte<<right<<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<ss<<setfill(' ')<<setw(10)<<" ";
}
void ImprimirResumen(ofstream &archReporte,double acumHoras,double promediotasa,double promedioRting,int cantVeces) {
    promedioRting=(double)promedioRting/cantVeces;
    promediotasa=(double)promediotasa/cantVeces;
    ImprimirLinea('=',archReporte,100);
    archReporte<<"PROMEDIO DE RATING:"<<setw(10)<<promedioRting<<endl;
    archReporte<<"PROMEDIO DE DROP-OFF:"<<setw(8)<<promediotasa<<endl;
    archReporte<<"DURACION TOTAL:"<<setw(6)<<" ";
    ImprimirHora(archReporte,acumHoras);
}