#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Elevador.h"


void iniciar_elevadores(Elevador ***e, Andar *predio, int m)
{
    *e = malloc(m * sizeof(Elevador *));
    for (int i = 0; i < m; i++)
    {
        *(*e + i) = malloc(sizeof(Elevador));
    }
    
    for (int i = 1; i <= m; i++)
    {
        (*(*e + i - 1))->andar = predio;
        (*(*e + i - 1))->direcao = 0;
        (*(*e + i - 1))->nome[0] = 'E';
        (*(*e + i - 1))->nome[1] = i+'0';
        (*(*e + i - 1))->nome[2] = '\0';
        (*(*e + i - 1))->botoes_elevador = NULL;
        (*(*e + i - 1))->requisicao = NULL;
    }
}

void atribuir(Elevador *e)
{
    Andar *aux = e->andar;
    if(e->direcao == 1){
        while(aux && aux->botao_subir != 1) {
            aux = aux->cima;
        }
        if(aux) {
            //if (e->requisicao && e->requisicao->botao_subir == 1) return;
            if (e->requisicao && e->requisicao->valor < aux->valor) return;
            if (e->requisicao && e->requisicao->valor > aux->valor) e->requisicao->botao_subir = 1;
            e->requisicao = aux;
            e->requisicao->botao_subir = 2;
            return;
        }
        aux = e->andar;
        while(aux && aux->botao_descer != 1) {
            aux = aux->cima;
        }
        if(aux) {
            if(e->requisicao && e->requisicao->botao_subir == 2) return;


            if(e->requisicao) e->requisicao->botao_subir = 1;
            e->requisicao = aux; // inserir requisição
            aux->botao_subir = 2;
            return;
        }
    }
    if(e->direcao == -1){
        while(aux && aux->botao_descer!=1) {
            aux = aux->baixo;
        }
        if(aux) {
            if(e->requisicao) e->requisicao->botao_descer = 1;
            e->requisicao = aux; // inserir requisição
            aux->botao_descer = 2;
        }
    }
}

int parado(Elevador *e) 
{
    if (e->direcao == 0) return 1;
    else return 0;
}

void definir_direcao(Elevador * e)
{
    if(e->requisicao);


    if(e->direcao == -1) {
        if(!e->requisicao && (!(e->botoes_elevador) || *(e->botoes_elevador) > e->andar->valor)) { // se n ha requisições externas ou internas
            e->direcao = e->direcao * -1;
            return;
        }   
    }
}

void subir(Elevador *e)
{
    if(e->andar->cima == NULL){
            e->direcao = -1;
            return;
    }
    e->andar = e->andar->cima;
}

void descer(Elevador *e)
{
    if(e->andar->baixo == NULL){
            e->direcao = 1;
            return;
    }
    e->andar = e->andar->baixo;
}

void chamar(Elevador *e)
{

}

void mover(Elevador *e)
{
    if (e->direcao == 1) {
        subir(e);
    }
    if (e->direcao == -1) {
        descer(e);
    }
}

void limpar_elevadores(Elevador ***e, int m)
{
    for (int i = 0; i < m; i++)
    {
        free((*(*e + i))->botoes_elevador);
        free((*(*e + i))->requisicao);
        free(*(*e + i));
    }
    free(*e);
}