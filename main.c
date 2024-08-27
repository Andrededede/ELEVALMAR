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
    
    //Limpar Memoria
    limpar_elevadores(&elevadores, m);
    limpar_predio(&predio);

    return 0;
}