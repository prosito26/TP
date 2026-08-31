#include <iostream>
#include <iomanip>
using namespace std;
//LLAMAN A LAS CABECERAS DE FUNCIONES
#include "Bibliotecas/FuncionesAuxiliares.h"

/*
 *coidgo:20231476
nombre:alvaro
descripcion:mi programa se encarga de hacer .......
 *
 */


//20/01/2022          D9513          DreadzTV    675908    // STREAMS 24/08/2025   01:30:01   10003
int main() {

    // int fechaInicial=20220909;
    // int fechaLimite=20230101;
    cout<<fixed;
    cout<<setprecision(2);
    procesarDatos();

    return 0;
}


//NOTEPAD++

//DEMOSTRACION INICIAL C++:
// int num1,num2;
//
// cout<<"Ingrese le valor del numero 1:"<<endl;
// cin>>num1;
// cout<<"Ingrese le valor del numero 2:"<<endl;
// cin>>num2;

// double numero=3.141657888;
// cout<<fixed;
// cout<<setprecision(2)<<setw(10)<<numero<<endl;
// cout<<setprecision(5)<<numero<<endl;

// int a=39963, b=20, c=150;
//
// cout<<setw(10)<<a<<" "<<left<<setw(10)<<b<<c<<right<<setw(10)<<a;

// int dd=3,mm=8,aa=2026;
// int dd1=10,mm1=10,aa1=2026;
//
// cout<<setfill('0')<<setw(2)<<dd<<"/"<<setw(2)<<mm<<"/"<<setw(4)<<aa<<setfill(' ')endl;
// cout<<dd1<<"/"<<mm1<<"/"<<aa1<<endl;

//Formato Fehca:aa*10000+mm*100+dd