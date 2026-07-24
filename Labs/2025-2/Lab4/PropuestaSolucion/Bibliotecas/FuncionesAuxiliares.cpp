//
// Created by aml on 29/09/2025.
//

#include "FuncionesAuxiliares.h"

void CargarCanales(const char *NombreArch, int *fechaCreacion, int *numCodCanal,
                   char *letraCanal, double *ratingCanal, int &cantCnales) {
    ifstream arch(NombreArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int dd, mm, aa, numCod, fecha;
    char letra, car;
    double rating;
    while (true) {
        arch >> dd >> car >> mm >> car >> aa;
        if (arch.eof()) break;
        fecha = TransformarFecha(dd, mm, aa);
        arch >> letra >> numCod;
        arch >> ws;
        while (arch.get() != ' ');
        arch >> rating;
        while (arch.get() != '\n');
        fechaCreacion[cantCnales] = fecha;
        letraCanal[cantCnales] = letra;
        numCodCanal[cantCnales] = numCod;
        ratingCanal[cantCnales] = rating;
        cantCnales++;
    }
}

int TransformarFecha(int dd, int mm, int aa) {
    return aa * 10000 + mm * 100 + dd;
}

void CargarEtiquetas(const char *NombreArch, int *arrCodEtiqueta,
                     double *duracionHorasEtiqueta, int &cantEtiquetas) {
    ifstream arch(NombreArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int codigo, mm, ss;
    char car;
    double duracionHoras;
    while (true) {
        arch >> codigo;
        if (arch.eof()) break;
        arch >> ws;
        while (arch.get() != ' ');
        arch >> mm >> car >> ss;
        duracionHoras = CalcularDuracionHoras(mm, ss);
        arrCodEtiqueta[cantEtiquetas] = codigo;
        duracionHorasEtiqueta[cantEtiquetas] = duracionHoras;
        cantEtiquetas++;
    }
}

double CalcularDuracionHoras(int mm, int ss) {
    return (double) mm / 60 + (double) ss / 3600;
}

void EmitirReporteSimple(const char *NombreArch, int *fechaCreacion, int *numCodCanal, char *letraCanal,
                         double *ratingCanal, int cantCnales,
                         int *arrCodEtiqueta, double *duracionHorasEtiqueta, int cantEtiquetas) {
    ofstream archReporte(NombreArch, ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    archReporte << setprecision(2) << fixed;
    archReporte << setw(10) << " " << "DATOS DE LOS CANALES" << endl;
    ImprimirLinea('=', 50, archReporte);
    archReporte << "Codigo" << setw(6) << " " << "Fecha" << setw(14) << "Rating" << endl;
    ImprimirLinea('-', 50, archReporte);
    for (int i = 0; i < cantCnales; i++) {
        archReporte << letraCanal[i] << numCodCanal[i] << setw(7) << " " << fechaCreacion[i]
                << setw(5) << " " << setw(4) << ratingCanal[i] << endl;
    }
    ImprimirLinea('=', 50, archReporte);
    archReporte << setw(10) << " " << "DATOS DE LAS ETIQUETAS" << endl;
    ImprimirLinea('=', 50, archReporte);
    archReporte << "Codigo" << setw(6) << " " << "Duracion Horas" << endl;
    ImprimirLinea('-', 50, archReporte);
    for (int i = 0; i < cantEtiquetas; i++) {
        archReporte << setw(6) << arrCodEtiqueta[i] << setw(5) << " " << setw(6) << duracionHorasEtiqueta[i] << endl;
    }
}

void ImprimirLinea(char car, int tam, ofstream &archReporte) {
    for (int i = 0; i < tam; i++) {
        archReporte << car;
    }
    archReporte << endl;
}

void ProcesarReproducciones(const char *NombreArch, int *fechaCreacion, int *numCodCanal, char *letraCanal,
                            double *ratingCanal, int cantCnales,
                            int *arrNumTotalReproCanal, double *arrTiempoTotalReproduccCanal, double *arrPorcentajeRating,
                            double *arrIngresosXReprodEtiquetas,
                            int *arrCodEtiqueta, double *duracionHorasEtiqueta, int cantEtiquetas,
                            int *arrCantidadTotalReproduccEtiqueta, double *arrTiempoTotalReproEtiqueta,
                            double tarifaXDurEtiqueta) {
    ifstream arch(NombreArch, ios::in);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int d,m,a,numCodigoCanal,codigoEtiqueta,numReproducciones,indCanal,indEtiqueta;
    char car,letraCanal1;
    double duracionHoras,ingresos=0;
    while (true) {
        arch>>d>>car>>m>>car>>a;
        if (arch.eof()) break;
        arch>>letraCanal1>>numCodigoCanal>>codigoEtiqueta>>numReproducciones;
        indCanal=BuscarCanal(letraCanal,numCodCanal,letraCanal1,numCodigoCanal,cantCnales);
        indEtiqueta=BuscarEtiqueta(arrCodEtiqueta,codigoEtiqueta,cantEtiquetas);
        if (indCanal!=NO_ENCONTRADO and indEtiqueta!=NO_ENCONTRADO) {
                arrNumTotalReproCanal[indCanal]+=numReproducciones;
                arrCantidadTotalReproduccEtiqueta[indEtiqueta]+=numReproducciones;
                double duracion=duracionHorasEtiqueta[indEtiqueta];
                arrTiempoTotalReproduccCanal[indCanal]+=numReproducciones*duracion;
                arrPorcentajeRating[indCanal]=ClasificarPorcentaje(ratingCanal[indCanal]);
                arrIngresosXReprodEtiquetas[indCanal]=(arrTiempoTotalReproduccCanal[indCanal]*60)*tarifaXDurEtiqueta*arrPorcentajeRating[indCanal];
                arrTiempoTotalReproEtiqueta[indEtiqueta]+=numReproducciones*duracionHorasEtiqueta[indEtiqueta];
        }
    }
}
int BuscarCanal(char *letraCanal,int *numCodCanal,
    char letraCanal1,int numCodigoCanal,int cantCnales) {
    for (int i = 0; i < cantCnales; i++) {
        if (letraCanal[i] == letraCanal1 and numCodCanal[i] == numCodigoCanal) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}
int BuscarEtiqueta(int *arrCodEtiqueta,int codigoEtiqueta,int cantEtiquetas) {
    for (int i = 0; i < cantEtiquetas; i++) {
        if (arrCodEtiqueta[i] == codigoEtiqueta) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}
double ClasificarPorcentaje(double ratingCanal) {
    if (ratingCanal>4 and ratingCanal<5) {
        return 1.3;
    }
    else if (ratingCanal>3 and ratingCanal<4) {
        return 1.2;
    }
    else if (ratingCanal>2 and ratingCanal<3) {
        return 1.0;
    }
    else
        return 0.75;
}
void EmitirReporte(const char *NombreArch, int *fechaCreacion, int *numCodCanal, char *letraCanal,
                            double *ratingCanal, int cantCnales,
                            int *arrNumTotalReproCanal, double *arrTiempoTotalReproduccCanal, double *arrPorcentajeRating,
                            double *arrIngresosXReprodEtiquetas,
                            int *arrCodEtiqueta, double *duracionHorasEtiqueta, int cantEtiquetas,
                            int *arrCantidadTotalReproduccEtiqueta, double *arrTiempoTotalReproEtiqueta,
                            double tarifaXDurEtiqueta) {
    ofstream archReporte(NombreArch, ios::out);
    if (not archReporte.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    int dd,mm,aa,hh,min,seg,hE,minE,segE;
    archReporte<<setprecision(2)<<fixed;
    archReporte<<setw(50)<<" "<<"PLATAFORMA TP_Twitch"<<endl;
    archReporte<<setw(25)<<" "<<"TARIFA POR DURACION DE LAS ETIQUETAS:"<<tarifaXDurEtiqueta
    <<" POR CADA MINUTO Y FRACCION"<<endl;
    ImprimirLinea('=', 150, archReporte);
    archReporte<<"CANALES ADSCRITOS A LA PLATAFORMA"<<endl;
    ImprimirLinea('=', 150, archReporte);
    imprimirCanales(numCodCanal,letraCanal,ratingCanal,arrNumTotalReproCanal,arrTiempoTotalReproduccCanal,
        arrPorcentajeRating,arrIngresosXReprodEtiquetas,cantCnales,archReporte,fechaCreacion);
    ImprimirLinea('=', 150, archReporte);
    archReporte<<"ETIQUETAS DE LA PLATAFORMA"<<endl;
    ImprimirLinea('=', 150, archReporte);
    imprimirEtiquetas(arrCodEtiqueta,duracionHorasEtiqueta,
                      arrCantidadTotalReproduccEtiqueta,arrTiempoTotalReproEtiqueta,archReporte,cantEtiquetas);
}
void imprimirCanales( int *numCodCanal, char *letraCanal,double *ratingCanal,int *arrNumTotalReproCanal,double *arrTiempoTotalReproduccCanal,
        double *arrPorcentajeRating,double *arrIngresosXReprodEtiquetas,int cantCnales,ofstream &archReporte,int *fechaCreacion) {
    int dd,mm,aa,hh,min,seg;
    for (int i = 0; i < cantCnales;i++) {
        archReporte<<setw(3)<<i+1<<")"<<setw(3)<<" "<<left<<letraCanal[i]<<numCodCanal[i]<<right<<setw(7)<<" ";
        aa=fechaCreacion[i]/10000;
        mm=(fechaCreacion[i]/100)%100;
        dd=fechaCreacion[i]%100;
        archReporte<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ')<<setw(10)<<" ";
        archReporte<<setw(6)<<ratingCanal[i]<<setw(15)<<" "<<setw(5)<<arrNumTotalReproCanal[i]<<setw(10)<<" ";
        pasarFormatoHora(arrTiempoTotalReproduccCanal[i],hh,min,seg);
        ImprimirHora(hh,min,seg,archReporte);
        archReporte<<setw(10)<<" "<<setw(8)<<((arrPorcentajeRating[i]*100)-100)<<"%"<<setw(20)<<" "<<setw(10)<<arrIngresosXReprodEtiquetas[i];
        archReporte<<endl;
    }
}
void pasarFormatoHora(double tiempoHoras,int &hh,int &min,int &seg) {
    hh=(int )(tiempoHoras);
    min=(int )((tiempoHoras-hh)*60);
    seg=(int )((((tiempoHoras-hh)*60)-min)*60);
}
void imprimirEtiquetas(int *arrCodEtiqueta,double *duracionHorasEtiqueta,
    int *arrCantidadTotalReproduccEtiqueta,double *arrTiempoTotalReproEtiqueta,ofstream &archReporte,
    int cantEtiquetas) {
    int hh,min,seg,minEti,segEti,hhEti;
    for (int i = 0; i < cantEtiquetas; i++) {
        archReporte<<setw(3)<<i+1<<")"<<setw(3)<<" ";
        pasarFormatoHora(duracionHorasEtiqueta[i],hhEti,minEti,segEti);
        archReporte<<arrCodEtiqueta[i]<<setw(8)<<" ";
        archReporte<<setfill('0')<<setw(2)<<minEti<<":"<<setw(2)<<segEti<<setfill(' ')<<setw(10)<<" ";
        archReporte<<setw(8)<<arrCantidadTotalReproduccEtiqueta[i]<<setw(8)<<" ";
        pasarFormatoHora(arrTiempoTotalReproEtiqueta[i],hh,min,seg);
        ImprimirHora(hh,min,seg,archReporte);
        archReporte<<endl;
    }
}
void ImprimirHora(int hh,int min,int seg,ofstream &archReporte) {
    archReporte<<setfill('0')<<setw(3)<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ');
}

