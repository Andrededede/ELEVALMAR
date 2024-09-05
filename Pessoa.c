#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pessoa.h"

char * avancar_string(char *s, char *p, int tam) {
    char *aux = s;
    int cont = 0;
    while (aux != p) {
        aux = aux + 1;
        cont++;
    }
    while (*aux != '\0') {
        aux = aux + 1;
        cont++;
    }
    while (*aux == '\0' && cont!=tam-1) {
        aux = aux + 1;
        cont++;
    }
    if(cont == tam - 1) return NULL;
    return aux;
}

void inserir_pessoa(Pessoa **fila, int tempo, char id[5], int direcao, Andar *andar, int destino)
{
    Pessoa *aux = malloc(sizeof(Pessoa));
    aux->tempo = tempo;
    strcpy(aux->id, id);
    aux->direcao = direcao;
    aux->andar = andar;
    aux->destino = destino;
    aux->prox = NULL;

    if(!(*fila)) *fila = aux;
    else {
        Pessoa *aux2 = *fila;
        while(aux2->prox) {
            aux2 = aux2->prox;
        }
        aux2->prox = aux;
    }
}

void iniciar_pessoas(Pessoa **fila, char **ps, char *string, int string_tam, Andar *predio)
{
    while(*ps) {
        int tam = strlen(*ps);
        for (int i = 0; i < tam; i++)
        {
            if((*ps)[i] == '_') (*ps)[i] = '\0';
        }
        int tempo = atoi(&(*ps)[1]);
        *ps = avancar_string(string, *ps, string_tam);
        char id[5];
        strcpy(id, *ps);
        *ps = avancar_string(string, *ps, string_tam);
        int direcao;
        if((*ps)[0] == 'S') direcao = 1;
        if((*ps)[0] == 'D') direcao = -1;
        *ps = avancar_string(string, *ps, string_tam);
        Andar *andar = buscar_andar(predio, atoi(*ps));
        *ps = avancar_string(string, *ps, string_tam);
        int destino = atoi(*ps);
        *ps = avancar_string(string, *ps, string_tam);
        
        printf("tempo:%d\nid:%s\ndirecao:%d\nandar:%d\ndestino:%d\n\n", tempo, id, direcao, andar->valor, destino);

        inserir_pessoa(fila, tempo, id, direcao, andar, destino);
    }
}

void tranferir_pessoa(Pessoa **origem, Pessoa **destino)
{
    Pessoa *aux = *origem;
    if (!aux) return;
    *origem = aux->prox;
    aux->prox = NULL;
    if(!(*destino)) *destino = aux;
    else {
        Pessoa *aux2 = *destino;
        while(aux2->prox) {
            aux2 = aux2->prox;
        }
        aux2->prox = aux;
    }
    if((*destino)){
        printf("\n\n%d  %s  %d  %d\n\n", (*destino)->andar->valor, (*destino)->id, (*destino)->direcao, (*destino)->tempo);
    }
}

Pessoa *buscar_pessoa(Pessoa *lista, char id[5])
{
    Pessoa *aux = lista;
    while(aux && strcmp(aux->id,id)){
        aux = aux->prox;
    }
    return aux;
}

void remover_pessoa(Pessoa **fila)
{
    Pessoa *aux = *fila;
    if (!aux) return;
    *fila = aux->prox;
    free(aux);
}

void removerL_pessoa(Pessoa **lista, char id[5])
{
    Pessoa *aux = buscar_pessoa(*lista, id);
    Pessoa *aux2 = *lista;
    if(!aux2) return;
    while(aux->prox && ){
        aux2 = aux2->prox;
    }
    return aux;
}

void limpar_pessoas(Pessoa **fila)
{
    while (*fila) {
        remover_pessoa(fila);
    }
}
