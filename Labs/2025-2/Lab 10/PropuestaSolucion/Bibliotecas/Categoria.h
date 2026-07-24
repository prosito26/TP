//
// Created by aml on 24/11/2025.
//

#ifndef CATEGORIA_H
#define CATEGORIA_H

struct Categoria {
    char *codigo;
    char *nombre;
    char *descripcion;
    char *canalConDuracionMaxima;
    int duracionMaxima;
    int duracionTotal;
    double arrDropOff[20];
    int cantidadDeReproducciones;
    double promedioDroppOff;
};
#endif //CATEGORIA_H
