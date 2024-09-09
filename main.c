#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Predio.c"
#include "Elevador.c"
#include "Pessoa.c"

int main() {
    // Ler String
    char string[] = "AM_25 E1_01_S_05,10,15,20,25 E2_25_D_20,15,10,5 E3_13_S_18,23 E4_17_D_22,12,07 E5_09_S_11,16,21 T1_P01_S_03_10 T3_P02_D_12_08 T5_P03_S_15_20 T7_P04_D_22_16 T9_P05_S_18_25 T11_P06_D_13_07 T13_P07_S_05_12 T15_P08_D_20_10 T17_P09_S_08_15 T19_P10_D_18_07 T21_P11_S_11_21 T23_P12_D_25_13 T25_P13_S_06_20 T27_P14_D_22_10 T29_P15_S_14_23 T31_P16_D_18_09 T33_P17_S_07_19 T35_P18_D_20_12 T37_P19_S_13_25 T39_P20_D_15_05 T41_P21_S_09_16 T43_P22_D_23_14 T45_P23_S_18_25 T47_P24_D_12_08 T49_P25_S_11_20 T51_P26_D_17_09 T53_P27_S_14_21 T55_P28_D_22_15 T57_P29_S_07_19 T59_P30_D_23_13 T61_P31_S_05_16 T63_P32_D_18_07 T65_P33_S_20_25 T67_P34_D_25_17 T69_P35_S_08_14 T71_P36_D_22_10 T73_P37_S_11_21 T75_P38_D_20_15 T77_P39_S_13_25 T79_P40_D_18_12 T81_P41_S_06_17 T83_P42_D_23_14 T85_P43_S_12_20 T87_P44_D_22_08 T89_P45_S_07_16 T91_P46_D_20_10 T93_P47_S_11_25 T95_P48_D_23_14 T97_P49_S_09_19 T99_P50_D_18_07";
    char *ps = string;
    int n = atoi(&ps[3]); // numero de andares
    int m = 0;
    for (unsigned int i = 0; i < sizeof(string); i++)
    {
        if(string[i] == ' ') string[i] = '\0'; // quebra da string
        if(string[i] == 'E') m++; // numero de elevadores
    }
    ps = avancar_string(string, ps, sizeof(string));
    printf("%d\n\n", sizeof(*ps));


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

    // Iniciar pessoas
    Pessoa *f = NULL;
    iniciar_pessoas(&f, &ps, &string[0], sizeof(string), predio); // faz uma fila com as pessoas e seus tempos

    unsigned long int tempo = 0;
    while(1){
        printf("tempo %ld\n", tempo);
        listar_andares(predio);
        printf("\n");
        listar_elevadores(elevadores, m);
        chamar_elevador(&f, tempo); // atualizar chamadas no predio
        for (int i = 0; i < m; i++)
        {
            controlar_porta(elevadores[i]); // simular portas abrindo e botões sendo desapertados
            atribuir(elevadores[i]); // atribuir ao elevadores[i] uma chamada externa na direção atual
            definir_direcao(elevadores[i]); // definir se o elevador vai subir(1) ou descer(-1)
            mover(elevadores[i]); // mover elevador
        }
        if(encerrar(f, elevadores, m, predio)) break;
        tempo++;
        // sleep(1); // wait 1seg
    }

    printf("\nOs elevadores levaram %d segundos para entregar todas as pessoas a seus destinos.\n", tempo);
    
    //Limpar Memoria
    limpar_elevadores(&elevadores, m);
    limpar_predio(&predio);

    return 0;
}