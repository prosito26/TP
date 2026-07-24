//
// Created by aml on 24/11/2025.
//

#ifndef NODO_H
#define NODO_H
#include "Categoria.h"
struct Nodo {
    struct Categoria categoria;
    struct Nodo *siguiente;
};

#endif //NODO_H
