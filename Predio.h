#ifndef PREDIO_H
#define PREDIO_H

typedef struct Andar {
    int valor;
    struct Andar *cima;
    struct Andar *baixo;
    int chamando; // 0: sem chamadas; 1: chamando pra cima; ; -1: chamando pra baixo; 2: chamando os dois
} Andar;

void iniciar_predio(Andar **predio, int andares);
Andar* buscar_andar(Andar **predio, int valor);
void inserir_f(Andar **predio, int valor);
void remover_andar(Andar **predio, int valor);
void listar_andares(Andar *predio);
void limpar_predio(Andar **predio);

#endif