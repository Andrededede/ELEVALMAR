#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Elevador.h"


void construir_elevadores(Elevador ***e, Andar *predio, int m)
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
        (*(*e + i - 1))->botoes = malloc(sizeof(Botoes));
        (*(*e + i - 1))->botoes->tam = 0 ;
        (*(*e + i - 1))->botoes->apertados = NULL ;
        (*(*e + i - 1))->requisicao = malloc(sizeof(Requisicao));
        (*(*e + i - 1))->requisicao->requisitado = NULL;
        (*(*e + i - 1))->requisicao->direcaoRequisitada = 0;
        (*(*e + i - 1))->cont = 0;
    }
}

void apertar_elevador(Elevador *e, int andar){
    e->botoes->tam++;
    e->botoes->apertados = realloc(e->botoes->apertados, sizeof(int)*e->botoes->tam);
    e->botoes->apertados[e->botoes->tam-1] = andar;
}

void iniciar_elevador(Elevador * e, Andar *predio, char *string)
{
    char s[255];
    strcpy(s, string);
    for (unsigned int i = 0; i < sizeof(s); i++)
    {
        if(s[i] == 'T') s[i] = '0';
    }
    e->andar = buscar_andar(predio, atoi(&s[3])); // definir andar inicial
    for (unsigned int i = 0; i < sizeof(s); i++) // definir direção inicial
    {
        if(s[i] == 'S') e->direcao = 1;
        if(s[i] == 'D') e->direcao = -1;
    }
    // definir botoes apertados iniciais
    strcpy(s, &s[8]);
    char *p = strtok(s, ",");
    while(p) {
        apertar_elevador(e, atoi(p));
        p = strtok(NULL, ",");
    }

    // for (int i = 0; i < e->botoes->tam; i++)
    // {
    //     printf("%d", e->botoes->apertados[i]);
    // }
    // printf("\ntam: %d\n\n", e->botoes->tam);
}

void atribuir(Elevador *e)
{
    Andar *aux = e->andar;
    if(e->direcao == 1){
        while(aux && aux->botao_subir != 1) {
            aux = aux->cima;
        }
        if(aux) { // achou uma requisição e vai descidir se pega ou não
            if(e->requisicao->requisitado && e->requisicao->direcaoRequisitada == 1) { // ja tenho uma req na direção
                if(e->requisicao->requisitado->valor < aux->valor) return; // ela é melhor
                if(e->requisicao->requisitado->valor > aux->valor) e->requisicao->requisitado->botao_subir = 1; // ela é pior, desisto dela
            }
            if(e->requisicao->requisitado && e->requisicao->direcaoRequisitada == -1) { // ja tenho uma na direção oposta
                e->requisicao->requisitado->botao_descer = 1; // desisto dela pq quero manter a direção
            }
            // pegar a req nova
            e->requisicao->requisitado = aux;
            e->requisicao->requisitado->botao_subir = 2;
            e->requisicao->direcaoRequisitada = 1;
            return;
        }
        if(e->requisicao->requisitado && e->requisicao->direcaoRequisitada == 1) return; // opa ja tenho req na melhor direção
        aux = e->andar;
        while(aux && aux->botao_descer != 1) {
            aux = aux->cima;
        }
        if(aux) { // achou requisição
            if(e->requisicao->requisitado && e->requisicao->direcaoRequisitada == -1) { // ja tenho uma req na direção
                if(e->requisicao->requisitado->valor > aux->valor) return; // a minha é melhor
                if(e->requisicao->requisitado->valor < aux->valor) e->requisicao->requisitado->botao_descer = 1; // a minha é pior, desisto dela
            }
            // pegar a req nova
            e->requisicao->requisitado = aux;
            e->requisicao->requisitado->botao_descer = 2;
            e->requisicao->direcaoRequisitada = -1;
            return;
        }
    }
    if(e->direcao == -1){
        while(aux && aux->botao_descer != 1) {
            aux = aux->baixo;
        }
        if(aux) { // achou uma requisição e vai descidir se pega ou não
            if(e->requisicao->requisitado && e->requisicao->direcaoRequisitada == -1) { // ja tenho uma req na direção
                if(e->requisicao->requisitado->valor > aux->valor) return; // ela é melhor
                if(e->requisicao->requisitado->valor < aux->valor) e->requisicao->requisitado->botao_descer = 1; // ela é pior, desisto dela
            }
            if(e->requisicao->requisitado && e->requisicao->direcaoRequisitada == 1) { // ja tenho uma na direção oposta
                e->requisicao->requisitado->botao_subir = 1; // desisto dela pq quero manter a direção
            }
            // pegar a req nova
            e->requisicao->requisitado = aux;
            e->requisicao->requisitado->botao_descer = 2;
            e->requisicao->direcaoRequisitada = -1;
            return;
        }
        if(e->requisicao->requisitado && e->requisicao->direcaoRequisitada == -1) return; // opa ja tenho req na melhor direção
        aux = e->andar;
        while(aux && aux->botao_subir != 1) {
            aux = aux->baixo;
        }
        if(aux) { // achou requisição
            if(e->requisicao->requisitado && e->requisicao->direcaoRequisitada == 1) { // ja tenho uma req na direção
                if(e->requisicao->requisitado->valor < aux->valor) return; // a minha é melhor
                if(e->requisicao->requisitado->valor > aux->valor) e->requisicao->requisitado->botao_subir = 1; // a minha é pior, desisto dela
            }
            // pegar a req nova
            e->requisicao->requisitado = aux;
            e->requisicao->requisitado->botao_subir = 2;
            e->requisicao->direcaoRequisitada = 1;
            return;
        }
    }
}

void definir_direcao(Elevador * e)
{
    if(e->requisicao->requisitado) return; // tenho requisição, vou manter a direção
    if(!e->botoes->apertados)  { // se não tem botões apertados, inverto a direção
        e->direcao = e->direcao * -1;
        atribuir(e);
        return;
    }
    for (int i = 0; i < e->botoes->tam; i++) // verifica se tem um botao apertado em um andar seguindo a direção atual
    {
        if(e->direcao == 1) {
            if(e->botoes->apertados[i] > e->andar->valor) return;
        }
        if(e->direcao == -1) {
            if(e->botoes->apertados[i] < e->andar->valor) return;
        }
    }
    e->direcao = e->direcao * -1;
    atribuir(e);
    return;
}

void subir(Elevador *e)
{
    if(e->andar->cima == NULL){
            e->direcao = -1;
            return;
    }
    e->andar = e->andar->cima;
    e->cont++;
}

void descer(Elevador *e)
{
    if(e->andar->baixo == NULL){
            e->direcao = 1;
            return;
    }
    e->andar = e->andar->baixo;
    e->cont++;
}

// void chamar(Elevador *e)
// {
//     return;
// }

void mover(Elevador *e)
{
    if (!e->requisicao->requisitado && !e->botoes->apertados) e->direcao = -1;
    if (e->direcao == 1) {
        subir(e);
    }
    if (e->direcao == -1) {
        descer(e);
    }
}

void controlar_porta(Elevador *e)
{
    // desapertar o botão interno
    for (int i = 0; i < e->botoes->tam; i++)
    {
        if(e->andar->valor == e->botoes->apertados[i]) {
            for (int j = i; j < e->botoes->tam - 1; j++)
            {
                e->botoes->apertados[j] = e->botoes->apertados[j+1];
            }
            (e->botoes->tam)--;
            e->botoes->apertados = realloc(e->botoes->apertados, sizeof(int)*e->botoes->tam);
        }
    }

    // desapertar o botao externo e resetar requisição
    if(!e->requisicao->requisitado) return;
    if(e->andar == e->requisicao->requisitado) {
        if(e->requisicao->direcaoRequisitada == 1) e->andar->botao_subir = 0;
        if(e->requisicao->direcaoRequisitada == -1) e->andar->botao_descer = 0;
        e->requisicao->requisitado = NULL;
        e->requisicao->direcaoRequisitada = 0;
    }
}

void limpar_elevadores(Elevador ***e, int m)
{
    for (int i = 0; i < m; i++)
    {
        free((*(*e + i))->botoes);
        free((*(*e + i))->botoes->apertados);
        free((*(*e + i))->requisicao);
        free(*(*e + i));
    }
    free(*e);
}