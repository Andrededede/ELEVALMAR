//#ifndef ELEVALMAR_H
//#define ELEVALMAR_H

typedef struct Andar {
    int valor;
    struct Andar *cima;
    struct Andar *baixo;
    int chamando; // 0: sem chamadas; 1: chamando pra cima; ; -1: chamando pra baixo; 2: chamando os dois
} Andar;

typedef struct Predio {
    Andar *head;
    Andar *tail;
} Predio;

Andar* buscar(Andar **predio, int valor);
void inserir_i(Andar **predio, int valor);
void inserir_f(Andar **predio, int valor);
void remover(Andar **predio, int valor);
void listar(Andar *predio);
void limpar(Andar **predio);

//#endif