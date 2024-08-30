#ifndef ELEVADOR_H
#define ELEVADOR_H

#include "Predio.h"

typedef struct requisicao{
    Andar *requisitado;
    int direcaoRequisitada; //0 ou 1 ou -1
} Requisicao;

typedef struct Botoes{
    int *apertados;
    int tam;
} Botoes;

typedef struct Elevador{
    Andar *andar;
    char nome[3];
    int direcao;
    Botoes *botoes; //botões apertados
    Requisicao *requisicao;
    //char *rota;
} Elevador;


void iniciar_elevadores(Elevador ***e, Andar *predio, int m);
void atribuir(Elevador *e);
void definir_direcao(Elevador *e);
void subir(Elevador *e);
void descer(Elevador *e);
void chamar(Elevador *e);
void mover(Elevador *e);
void controlar_porta(Elevador *e);
void limpar_elevadores(Elevador ***e, int m);

#endif