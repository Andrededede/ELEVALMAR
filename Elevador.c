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
    }
}

void subir(Elevador *e)
{
    if(e->andar->cima == NULL){
            e->direcao = 0;
            return;
    }
    e->direcao = 1;
    e->andar = e->andar->cima;
}

void descer(Elevador *e)
{
    if(e->andar->baixo == NULL){
            e->direcao = 0;
            return;
    }
    e->direcao = -1;
    e->andar = e->andar->baixo;
}

void chamar(Elevador *e)
{

}
