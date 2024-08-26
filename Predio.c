#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Predio.h>

Andar* buscar(Andar **predio, int valor) {
    Andar *aux = *predio;
    while (aux && aux->valor != valor) {
        aux = aux->cima;
    }
    return aux;
}

void inserir_i(Andar **predio, int valor) {
    Andar *aux = malloc(sizeof(struct Andar));
    aux->valor = valor;
    aux->cima = NULL;
    aux->baixo = *predio;
    if (*predio) (*predio)->baixo = aux;
    *predio = aux; 
}

void inserir_f(Andar **predio, int valor) {
    Andar *aux = malloc(sizeof(Andar));
    aux->valor = valor;
    aux->cima = NULL;
    aux->baixo = NULL;

    Andar *aux2  = *predio;
    while(aux2 && aux2->cima) {
        aux2 = aux2->cima;
    }

    if(aux2) 
    {
        aux2->cima = aux;
        aux->baixo = aux2;
    }
    else *predio = aux;
}

void remover(Andar **predio, int valor) {
    Andar *aux = *predio;
    while(aux && aux->valor != valor) {
        aux = aux->cima;
    }
    if(!aux) return; 
    if(aux == *predio) *predio = aux->cima;
    if(aux->cima) aux->cima->baixo = aux->baixo;
    if(aux->baixo) aux->baixo->cima = aux->cima;
    free(aux);
}

void listar(Andar *predio) {
    Andar *aux = predio;
    while(aux) {
        printf("%d\n", aux->valor);
        aux = aux->cima;
    }
}

void limpar(Andar **predio) {
    Andar *aux = *predio;
    while(aux->cima) {
        free(aux->valor);
        aux = aux->cima;
        free(aux->baixo);
    }
    free(aux);
    *predio = NULL;
}