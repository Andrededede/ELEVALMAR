#ifndef PESSOA_H
#define PESSOA_H

#include "Predio.h"

typedef struct Pessoa {
    unsigned long int tempo;
    char id[5];
    int direcao;
    struct Andar *andar;
    int destino;
    struct Pessoa *prox;
} Pessoa;

char *avancar_string(char *s, char *p, int tam);
void inserir_pessoa(Pessoa **fila, int tempo, char id[5], int direcao, struct Andar *andar, int destino);
void inserir_no_pessoa_f(Pessoa **lista, Pessoa *p);
void iniciar_pessoas(Pessoa **fila, char **ps, char *string, int string_tam, struct Andar *predio);
void tranferir_pessoa(Pessoa **origem, Pessoa **destino, Pessoa *p);
Pessoa *buscar_pessoa(Pessoa *lista, char id[5]);
Pessoa *no_anterior(Pessoa *lista, Pessoa *no);
void remover_pessoa_C(Pessoa **fila);
void remover_pessoa(Pessoa **lista, char id[5]);
void limpar_pessoas(Pessoa **fila);

#endif