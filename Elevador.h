#ifndef ELEVADOR_H
#define ELEVADOR_H

#include "Predio.h"

typedef struct rota{
    unsigned long int tempo;
    Andar andar;
    struct rota *prox;
} Rota;

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
    Pessoa *passageiros;
    int energia;
    Rota *rota;
} Elevador;


void construir_elevadores(Elevador ***e, Andar *predio, int m);
void apertar_elevador(Elevador *e, int andar);
void iniciar_elevador(Elevador *e, Andar *predio, char *string);
void atribuir(Elevador *e);
void definir_direcao(Elevador *e);
void subir(Elevador *e);
void descer(Elevador *e);
//void chamar(Elevador *e);
void mover(Elevador *e);
void controlar_porta(Elevador *e);
void listar_elevadores(Elevador **elevadores, int m);
int encerrar(Pessoa *fila, Elevador **elevadores, int m);
void limpar_elevadores(Elevador ***e, int m);

#endif