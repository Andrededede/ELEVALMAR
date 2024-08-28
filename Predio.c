#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Predio.h"

void iniciar_predio(Andar **predio, int andares)
{
    *predio = NULL;
    for (int i = 0; i < andares; i++)
    {
        inserir_f(predio, i);
    }
}

Andar *buscar_andar(Andar **predio, int valor)
{
    Andar *aux = *predio;
    while (aux && aux->valor != valor) {
        aux = aux->cima;
    }
    return aux;
}

void inserir_f(Andar **predio, int valor) 
{
    Andar *aux = malloc(sizeof(Andar));
    aux->valor = valor;
    aux->cima = NULL;
    aux->baixo = NULL;
    aux->botao_subir = 0;
    aux->botao_subir = 0;

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

void remover_andar(Andar **predio, int valor) 
{
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

void listar_andares(Andar *predio) {
    Andar *aux = predio;
    while(aux) {
        printf("%d\n", aux->valor);
        aux = aux->cima;
    }
}

void limpar_predio(Andar **predio) {
    if(!(*predio)){
        return;
    }
    Andar *aux = *predio;
    while(aux->cima) {
        free(aux->valor);
        aux = aux->cima;
        free(aux->baixo);
    }
    free(aux);
    *predio = NULL;
}

void chamar(Andar *predio, int valor, int direcao) {
    //direcao é 1 ou -1
    Andar *aux = buscar_andar(&predio, valor);
    if(!aux){
        return;
    }
    
}