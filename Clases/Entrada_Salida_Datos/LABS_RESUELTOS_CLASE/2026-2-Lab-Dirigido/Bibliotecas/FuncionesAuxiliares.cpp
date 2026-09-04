//
// Created by ALVARO on 3/09/2026.
//

#include "FuncionesAuxiliares.h"


//73035996 Gabriela_Gomez_Silva Sanitas_Peru UIY614 08/12/24 28/11/26 12245.83 58 2 1423.60 1587.46
void procesarDatos(int fechaLimite) {
    int dni,fechaFinal,dd,mm,aa,num,edad,cantVeces;
    char car;
    double montoInicial,montoExtra;
    while (true) {
        cin>>dni;
        if (cin.eof()) break;
        leerNombre(' ',true);
        leerNombre(' ',false);
        leerNombre(' ',false);
        cin>>num>>car>>num>>car>>num>>dd>>car>>mm>>car>>aa>>montoInicial>>edad>>cantVeces;
        fechaFinal=aa*10000+mm*100+dd;
        for (int i=0;i<cantVeces;i++) {//entrada controlada
            cin>>montoExtra;
            montoInicial+=montoExtra;
        }
        imprimirDatos(edad,fechaFinal,fechaLimite,montoInicial);
        //2da forma de lectura
        // while (cantVeces>0) {
        //     cin>>montoExtra;
        //     cantVeces--;
        // }
    }
}

void leerNombre(char delim,bool imprime) {
    cin>>ws;
    int cantCar=0;
    char car;
    while (true) {
        car=cin.get();
        if (car==delim) break;
        if (car=='_') car=' ';
        if (imprime) cout<<car;//si es verdadero va a imprimir
        //no entra porque es false, y un false nunca va a entrar en un if
        cantCar++;
    }
    if (imprime) cout<<setw(35-cantCar)<<" ";
}

void imprimirDatos(int edad,int fechaFinal,int fechaLimite,double montoInicial) {
    cout<<edad<<setw(15)<<" ";
    imprimirEstado(fechaFinal,fechaLimite);
    cout<<setw(20)<<montoInicial;
    cout<<endl;
}

void imprimirEstado(int fechaFinal,int fechaLimite) {
    int diasDiferencia;
    //20260103 - 20260102
    if (fechaFinal>fechaLimite) {
        diasDiferencia=fechaFinal-fechaLimite;
        cout<<"Poliza vencida"<<setw(15)<<" "<<diasDiferencia<<" dias vencido"<<setw(15)<<" ";
    }
    else {
        diasDiferencia=fechaLimite-fechaFinal;
        cout<<"Poliza vigente"<<setw(15)<<" "<<diasDiferencia<<" dias para vencer"<<setw(15)<<" ";
    }
}