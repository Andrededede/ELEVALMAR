#ifndef PESSOA_H
#define PESSOA_H

#include "Predio.h"

typedef struct Pessoa {
    int id;
    int andar;
    int destino;
    Pessoa *prox;
} Pessoa;


#endif