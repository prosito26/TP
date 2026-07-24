//
// Created by aml on 10/11/2025.
//

#ifndef CATEGORIA_H
#define CATEGORIA_H

#include "Reproduccion.h"

struct Categoria {
    char codigo[10];
    char nombre[50];
    struct Reproduccion reproducciones[15];
    int numReproducciones;
    double promedioRating;
    int duracionTotal;
};

#endif //CATEGORIA_H
