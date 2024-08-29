#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Predio.c"
#include "Elevador.c"


int main() {
    // Ler String
    char string[255] = "sadfsaadasd";
    int n = 20; //andares
    int m = 5; //elevadores

    // Buildar predio e elevadores
    Andar *predio;
    iniciar_predio(&predio, n);
    Elevador **elevadores;
    iniciar_elevadores(&elevadores, predio, m);

    int tempo = 0;

    while(1){
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
        break;
        // wait 1seg sleep()
    }

    printf("\nOs elevadores levaram %d segundos para entregar todas as pessoas a seus destinos.\n", tempo);
    
    //Limpar Memoria
    limpar_elevadores(&elevadores, m);
    limpar_predio(&predio);

    return 0;
}