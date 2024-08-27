#ifndef ELEVADOR_H
#define ELEVADOR_H

#include "Predio.h"

typedef struct Elevador{
    Andar *andar;
    char nome[3];
    int direcao;
} Elevador;

void iniciar_elevadores(Elevador ***e, Andar *predio, int m);
void subir(Elevador *e);
void descer(Elevador *e);
void chamar(Elevador *e);
void limpar_elevadores(Elevador ***e, int m);

#endif