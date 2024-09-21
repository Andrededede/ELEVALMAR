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
        (*(*e + i - 1))->passageiros = NULL;
        (*(*e + i - 1))->energia = 0;
        (*(*e + i - 1))->rota = NULL;
    }
}

Rota *buscar_rota(Rota *lista, unsigned long int tempo)
{
    Rota *aux = lista;
    while(aux && aux->tempo != tempo){
        aux = aux->prox;
    }
    return aux;
}

void inserir_rota_f(Rota **lista, unsigned long int tempo, Andar *andar)
{   
    if(buscar_rota(*lista, tempo)) return;
    Rota *aux = malloc(sizeof(Rota));
    aux->tempo = tempo;
    aux->andar = andar;
    aux->prox = NULL;
    if(*lista == NULL){
        *lista = aux;
        return;
    }
    Rota *aux2 = *lista;
    while(aux2->prox){
        aux2 = aux2->prox;
    }
    aux2->prox = aux;
}


void apertar_elevador(Elevador *e, int andar)
{
    for(int i = 0; i < e->botoes->tam; i++){
        if(e->botoes->apertados[i] == andar) return;
    }
    e->botoes->tam++;
    e->botoes->apertados = realloc(e->botoes->apertados, sizeof(int)*e->botoes->tam);
    e->botoes->apertados[e->botoes->tam-1] = andar;
}

void iniciar_elevador(Elevador *e, Andar *predio, char *string)
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
    inserir_rota_f(&(e->rota), 0, e->andar);
    
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

void definir_direcao(Elevador *e, unsigned long int tempo)
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
    inserir_rota_f(&(e->rota), tempo, e->andar);
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
    e->energia++;
}

void descer(Elevador *e)
{
    if(e->andar->baixo == NULL){
            e->direcao = 1;
            return;
    }
    e->andar = e->andar->baixo;
    e->energia++;
}

void mover(Elevador *e)
{
    if (!e->requisicao->requisitado && !e->botoes->apertados) {
        e->direcao = e->direcao * -1;
        return;
    }
    if (e->direcao == 1) {
        subir(e);
    }
    if (e->direcao == -1) {
        descer(e);
    }
}

void controlar_porta(Elevador *e, unsigned long int tempo)
{
    // desapertar o botão interno
    for (int i = 0; i < e->botoes->tam; i++)
    {
        if(e->andar->valor == e->botoes->apertados[i]) {
            inserir_rota_f(&(e->rota), tempo, e->andar);
            //tranferir pessoa para chegados do andar
            Pessoa *aux = e->passageiros;
            while(aux){
                Pessoa *aux2 = aux->prox;
                if(aux->destino == e->andar->valor){
                    tranferir_pessoa(&(e->passageiros), &(e->andar->chegados), aux);
                }   
                aux = aux2;
            }
            //desapertar botao do elevador
            for (int j = i; j < e->botoes->tam - 1; j++)
            {
                e->botoes->apertados[j] = e->botoes->apertados[j+1];
            }
            (e->botoes->tam)--;
            e->botoes->apertados = realloc(e->botoes->apertados, sizeof(int)*e->botoes->tam);
        }
    }

    // desapertar o botao externo e resetar requisição e apertar botao de quem entra
    if(!e->requisicao->requisitado) return;
    if(e->andar == e->requisicao->requisitado) {
        inserir_rota_f(&(e->rota), tempo, e->andar);
        if(e->requisicao->direcaoRequisitada == 1) {
            e->andar->botao_subir = 0;
            while(e->andar->fila_s) {
                apertar_elevador(e, e->andar->fila_s->destino);
                tranferir_pessoa(&(e->andar->fila_s), &(e->passageiros), (e->andar->fila_s));
            }
        }
        if(e->requisicao->direcaoRequisitada == -1) {
            e->andar->botao_descer = 0;
            while(e->andar->fila_d) {
                apertar_elevador(e, e->andar->fila_d->destino);
                tranferir_pessoa(&(e->andar->fila_d), &(e->passageiros), (e->andar->fila_d));
            }
        }
        e->requisicao->requisitado = NULL;
        e->requisicao->direcaoRequisitada = 0;
    }
    // trasnsferir todas as pessoas da fila correspondete para o elevador
    
}

void listar_elevadores(Elevador **elevadores, int m)
{
    for (int i = 0; i < m; i++)
    {
        printf("---------------------------------------------------\n");
        printf("%s: %d, %d\n", elevadores[i]->nome, elevadores[i]->andar->valor, elevadores[i]->direcao);
        printf("Botoes apertados: ");
        for(int j = 0; j < elevadores[i]->botoes->tam; j++){
            printf("%d ", elevadores[i]->botoes->apertados[j]);
        }
        printf("\n");
        if(elevadores[i]->requisicao->requisitado){
            printf("Requisicao: %d\n", elevadores[i]->requisicao->requisitado->valor);
        }
    }
    
}

int encerrar(Pessoa *fila, Elevador **elevadores, int m)
{   
    if (fila) return 0;
    for (int i = 0; i < m; i++)
    {
        if(elevadores[i]->botoes->apertados) return 0;
        if(elevadores[i]->requisicao->requisitado) return 0;
    }
    return 1;
}

void mostrar_rotas(Elevador **elevadores, int m)
{
    for (int i = 0; i < m; i++)
    {
        printf("%s: ", elevadores[i]->nome);
        Rota *r = elevadores[i]->rota;
        while(r) {
            printf("%d(%ld) ", r->andar->valor, r->tempo);
            if(r->prox) printf("-> ");
            else printf("\nTempo Final: %ld", r->tempo);
            r = r->prox;
        }
        printf("\nAndares Percorridos: %d\n\n", elevadores[i]->energia);
    }
}

void limpar_rota(Elevador *e)
{
    Rota *aux = e->rota;
    Rota *aux2 = aux;
    while(aux){
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
}

void limpar_elevadores(Elevador ***e, int m)
{
    for (int i = 0; i < m; i++)
    {
        limpar_rota((*(*e + i)));
        free((*(*e + i))->botoes);
        free((*(*e + i))->botoes->apertados);
        free((*(*e + i))->requisicao);
        free(*(*e + i));
        limpar_pessoas(&((*(*e + i))->passageiros));
    }
    free(*e);
}