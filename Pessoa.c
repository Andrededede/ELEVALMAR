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

void tranferir_pessoa(Pessoa **origem, Pessoa **destino, Pessoa *p)
{   
    Pessoa *aux = no_anterior(*origem, p);
    if(*origem == p){
        *origem = p->prox;
    } else{
        if(!aux) return;
        aux->prox = p->prox;
    }
    inserir_no_pessoa_f(destino, p);
}

Pessoa *buscar_pessoa(Pessoa *lista, char id[5])
{
    Pessoa *aux = lista;
    while(aux && strcmp(aux->id,id)){
        aux = aux->prox;
    }
    return aux;
}

Pessoa *no_anterior(Pessoa *lista, Pessoa *no){
    Pessoa *aux = no;
    Pessoa *aux2 = lista;
    if(aux == aux2){
        return NULL;
    }
    while(aux2 && aux2->prox && aux2->prox != aux){
        aux2 = aux2->prox;
    }
    if(!aux2->prox){
        return NULL;
    }
    return aux2;
}

void inserir_no_pessoa_f(Pessoa **lista, Pessoa *p){
    p->prox = NULL;
    if(!(*lista)) {
        *lista = p;
        return;
    }
    Pessoa *aux = *lista;
    while(aux->prox) {
        aux = aux->prox;
    }
    aux->prox = p;
}

void remover_pessoa_C(Pessoa **fila)
{
    Pessoa *aux = *fila;
    if (!aux) return;
    *fila = aux->prox;
    free(aux);
}

void remover_pessoa(Pessoa **lista, char id[5])
{   
    Pessoa *aux = buscar_pessoa(*lista, id);
    Pessoa *aux2 = no_anterior(*lista, aux);
    if(!aux) return;
    aux2->prox = aux->prox;
    free(aux);
}

void limpar_pessoas(Pessoa **fila, int n)
{
    for(int i = 0; i < n; i++){

    }
    while (*fila) {
        remover_pessoa_C(fila);
    }
}
