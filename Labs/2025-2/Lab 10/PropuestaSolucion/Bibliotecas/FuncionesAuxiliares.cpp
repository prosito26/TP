//
// Created by aml on 24/11/2025.
//

#include "FuncionesAuxiliares.h"

void cargarCategorias(const char *nombArch,struct Nodo *&listaCategorias) {
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    struct Categoria categoriaNueva{};
    listaCategorias=nullptr;
    while (true) {
        categoriaNueva.codigo=leeCadenaExactaDelim(arch,',');
        if (arch.eof()) break;
        categoriaNueva.nombre=leeCadenaExactaDelim(arch,',');
        categoriaNueva.descripcion=leeCadenaExactaDelim(arch,'\n');
        insertarOrdenado(listaCategorias,categoriaNueva);
    }
}
char *leeCadenaExactaDelim(ifstream &arch,char delim) {
    char cadena[100],*ptr;
    arch.getline(cadena,100,delim);
    if (arch.eof()) return nullptr;
    ptr=new char[strlen(cadena)+1];
    strcpy(ptr,cadena);
    return ptr;
}
void insertarOrdenado(struct Nodo *&listaCategorias,struct Categoria categoriaNueva) {
    struct Nodo *nuevo,*ant=nullptr,*recorre=listaCategorias;
    nuevo =new struct Nodo;
    nuevo->categoria=categoriaNueva;
    while (recorre) {
        if (strcmp(recorre->categoria.codigo,categoriaNueva.codigo)>0) break;
        ant=recorre;
        recorre=recorre->siguiente;
    }
    nuevo->siguiente=recorre;
    if (ant==nullptr) listaCategorias=nuevo;
    else ant->siguiente=nuevo;
}
void emitirReporte(const char *nombArch,struct Nodo *listaCategorias) {
    ofstream arch(nombArch,ios::out);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    struct Nodo *p=listaCategorias;
    arch<<setprecision(2)<<fixed;
    arch<<setw(40)<<" "<<"REPORTE POR CATEGORIAS"<<endl;
    while (p) {
        imprimirLinea('=',120,arch);
        arch<<"Codigo: "<<setw(6)<<" "<<left<<setw(50)<<p->categoria.codigo<<endl;
        arch<<"Nombre: "<<setw(6)<<" "<<left<<setw(50)<<p->categoria.nombre<<endl;
        arch<<"Descripcion:  "<<p->categoria.descripcion<<endl<<right;
        if (listaCategorias->categoria.cantidadDeReproducciones!=0) {
            imprimirLinea('-',120,arch);
            imprimirDemasDatos(p->categoria,arch);
        }
        p=p->siguiente;
    }
}
void imprimirLinea(char car,int tam,ofstream &arch) {
    for (int i=0;i<tam;i++) {
        arch<<car;
    }
    arch<<endl;
}
void completarLista(const char *nombArch,struct Nodo *listaCategorias) {
    ifstream arch(nombArch,ios::in);
    if (not arch.is_open()) {
        cout<<"Error al abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    struct Nodo *encuentra=listaCategorias;
    char *codCategoria,*nombreCanal,car;
    double tasaDropp;
    int hh,min,seg,duracionSeg;
    while (true) {
        codCategoria=leeCadenaExactaDelim(arch,',');
        if (arch.eof()) break;
        nombreCanal=leeCadenaExactaDelim(arch,',');
        arch>>tasaDropp>>car>>hh>>car>>min>>car>>seg;
        arch.get();
        duracionSeg=hh*3600+min*60+seg;
        encuentra=BuscarCodigo(codCategoria,listaCategorias);
        if (encuentra!=nullptr) {
            modificarStreams(encuentra->categoria,tasaDropp,duracionSeg,nombreCanal);
        }
    }
}
struct Nodo *BuscarCodigo(char *codCategoria,struct Nodo *listaCategorias) {
    struct Nodo *p=listaCategorias;
    while (p) {
        if (strcmp(p->categoria.codigo,codCategoria)==0) return p;
        p=p->siguiente;
    }
    return nullptr;
}
void modificarStreams(struct Categoria &categoria,double tasaDropp,int duracionSeg,
    char *nombreCanal) {
    int n=categoria.cantidadDeReproducciones;
    categoria.arrDropOff[n]=tasaDropp;
    categoria.duracionTotal+=duracionSeg;
    if (categoria.duracionMaxima==0) {
        categoria.duracionMaxima=duracionSeg;
        asignarCadena(categoria.canalConDuracionMaxima,nombreCanal);
    }
    else {
        if (duracionSeg>categoria.duracionMaxima) {
            categoria.duracionMaxima=duracionSeg;
            asignarCadena(categoria.canalConDuracionMaxima,nombreCanal);
        }
    }
    categoria.cantidadDeReproducciones++;
}
void asignarCadena(char *&cadenaDest,char *cadenaOrigen) {
    cadenaDest=new char[strlen(cadenaOrigen)+1];
    strcpy(cadenaDest,cadenaOrigen);
}
void calcularPromedio(struct Nodo *listaCategorias) {
    struct Nodo *p=listaCategorias;
    while (p) {
        calcularPromedioCategoria(p->categoria);
        p=p->siguiente;
    }
}
void calcularPromedioCategoria(struct Categoria &categoria) {
    double suma=0.0;
    for (int i=0;i<categoria.cantidadDeReproducciones;i++)
        suma += categoria.arrDropOff[i];
    if (categoria.cantidadDeReproducciones!=0)
        categoria.promedioDroppOff=(double)suma/categoria.cantidadDeReproducciones;
}
void imprimirDemasDatos(struct Categoria categoria,ofstream &arch) {
    arch<<"INFORMACION DE LAS REPRODUCCIONES:"<<endl;
    arch<<"DURACION MAXIMA:"<<endl;
    arch<<"NOMBRE DEL CANAL: "<<categoria.canalConDuracionMaxima<<endl;
    arch<<"DURACION:"<<setw(9)<<" ";
    imprimirHora(categoria.duracionMaxima,arch);
    imprimirLinea('-',120,arch);
    arch<<"LISTA DE DROPP-OFF: ";
    for (int i=0;i<categoria.cantidadDeReproducciones;i++) {
        arch<<left<<setw(10)<<categoria.arrDropOff[i]<<right;
    }
    arch<<endl;
    arch<<"PROMEDIO DE DROPP-OFF: "<<setw(19)<<categoria.promedioDroppOff<<endl;
    arch<<"TIEMPO DE DURACION TOTAL: "<<setw(8)<<" ";
    imprimirHora(categoria.duracionTotal,arch);
}
void imprimirHora(int duracion,ofstream &arch) {
    int hh,min,seg;
    double duracionHoras=(double)duracion/3600.0;
    hh=(int )duracionHoras;
    min=(int)((duracionHoras-hh)*60);
    seg=(int)((((duracionHoras-hh)*60)-min)*60);
    arch<<setfill('0')<<setw(2)<<hh<<":"<<setw(2)<<min<<":"<<setw(2)<<seg<<setfill(' ')<<endl;
}
void eliminarNodos(struct Nodo *&listaCategorias) {
    struct Nodo *p=listaCategorias,*sale,*ant=nullptr;
    while (p) {
        if (p->categoria.promedioDroppOff>3.5) {
            ant=p;
            p=p->siguiente;
        }
        else {
            sale=p;
            if (ant==nullptr) {
                listaCategorias=p->siguiente;
                p=listaCategorias;
            }
            else {
                ant->siguiente=p->siguiente;
                p=p->siguiente;
            }
            delete sale;
        }
    }
}