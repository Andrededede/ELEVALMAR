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

void inserir_pessoa(Pessoa **fila, int tempo, char id[5], int direcao, int andar, int destino)
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

void iniciar_pessoas(Pessoa **fila, char **ps, char *string, int string_tam)
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
        int andar = atoi(*ps);
        *ps = avancar_string(string, *ps, string_tam);
        int destino = atoi(*ps);
        *ps = avancar_string(string, *ps, string_tam);
        
        printf("tempo:%d\nid:%s\ndirecao:%d\nandar:%d\ndestino:%d\n\n", tempo, id, direcao, andar, destino);

        inserir_pessoa(fila, tempo, id, direcao, andar, destino);
    }
}

void remover_pessoa(Pessoa **fila)
{
    Pessoa *aux = *fila;
    if (!aux) return;
    *fila = aux->prox;
    free(aux);
}

void limpar_pessoas(Pessoa **fila)
{
    while (*fila) {
        remover_pessoa(fila);
    }
}
