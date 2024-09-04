#ifndef PESSOA_H
#define PESSOA_H

#include "Predio.h"

typedef struct Pessoa {
    int id;
    int andar;
    int destino;
    Pessoa *prox;
} Pessoa;

void inserir_pessoa(Pessoa *p, int id, int andar, int destino);
void remover_pessoa(Pessoa **p);
void limpar_pessoas(Pessoa **p);

#endif