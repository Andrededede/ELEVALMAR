#ifndef PESSOA_H
#define PESSOA_H

#include "Predio.h"

typedef struct Pessoa {
    int tempo;
    char id[5];
    int direcao;
    int andar;
    int destino;
    struct Pessoa *prox;
} Pessoa;

char * avancar_string(char *s, char *p, int tam);
void inserir_pessoa(Pessoa **fila, int tempo, char id[5], int direcao, int andar, int destino);
void iniciar_pessoas(Pessoa **fila, char **ps, char *string, int string_tam);
void remover_pessoa(Pessoa **fila);
void limpar_pessoas(Pessoa **fila);

#endif