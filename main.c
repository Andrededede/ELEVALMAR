#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Predio.c"
#include "Elevador.c"

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

int main() {
    // Ler String
    char string[] = "AM_20 E1_04_S_6,9,8 E2_11_D_5,8,9,3,2,T E3_20_D_5,8,T,9 T5_P01_S_4_6 T8_P01_D_6_4 T9_P02_S_5_10 T10_P03_S_3_9 T10_P04_D_6_T T10_P05_S_8_15 T15_P06_D_9_2 T15_P07_S_2_13 T18_P08_D_8_T T21_P01_D_16_3 T21_P10_S_T_13 T21_P11_S_T_12 T23_P12_S_T_15 T28_P13_S_2_13";
    char *ps = string;
    int n = atoi(&ps[3]); // numero de andares
    int m = 0;
    for (unsigned int i = 0; i < sizeof(string); i++)
    {
        if(string[i] == ' ') string[i] = '\0'; // quebra da string
        if(string[i] == 'E') m++; // numero de elevadores
    }
    ps = avancar_string(string, ps, sizeof(string));

    // Iniciar predio e elevadores
    Andar *predio;
    construir_predio(&predio, n);
    Elevador **elevadores;
    construir_elevadores(&elevadores, predio, m);
    for (int i = 0; i < m; i++)
    {     
        iniciar_elevador(elevadores[i], predio, ps);
        ps = avancar_string(string, ps, sizeof(string));
    }

    int tempo = 0;
    while(tempo < 2){
        // atualizar chamadas no predio
        // atualizar chamadas internas de cada elevador
        printf("%d", tempo);
        for (int i = 0; i < m; i++)
        {
            controlar_porta(elevadores[i]); // simular portas abrindo e botões sendo desapertados
            atribuir(elevadores[i]); // atribuir ao elevadores[i] uma chamada externa na direção atual
            definir_direcao(elevadores[i]); // definir se o elevador vai subir(1) ou descer(-1)
            mover(elevadores[i]); // mover elevador
        }
        tempo++;
        sleep(1);
        // wait 1seg sleep()
    }

    printf("\nOs elevadores levaram %d segundos para entregar todas as pessoas a seus destinos.\n", tempo);
    
    //Limpar Memoria
    limpar_elevadores(&elevadores, m);
    limpar_predio(&predio);

    return 0;
}