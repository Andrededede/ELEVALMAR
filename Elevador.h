#ifndef ELEVADOR_H
#define ELEVADOR_H

#include "Predio.h"

typedef struct Elevador{
    Andar *andar;
    char nome[3];
    int direcao;
    int *botoes_elevador; //botões apertados
    Andar *requisicao;
    //char *rota;
} Elevador;

void iniciar_elevadores(Elevador ***e, Andar *predio, int m);
void atribuir(Elevador *e);
int parado(Elevador *e);
void definir_direcao(Elevador *e);
void subir(Elevador *e);
void descer(Elevador *e);
void chamar(Elevador *e);
void mover(Elevador *e);
void limpar_elevadores(Elevador ***e, int m);

#endif