#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include "trees.h"

int main(int argc, char *argv[])
{
    // Define o valor das páginas de código UTF8 e default do Windows
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();

    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);

    // Define codificação como sendo UTF-8
    SetConsoleOutputCP(CPAGE_UTF8);
    printf("Utilizando caracteres e acentuação da língua portuguesa!\n\n");
    ///////////////////////////////////////
    if (argc != 4) // o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
    {
        printf("Numero incorreto de parametros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else
    {
        pNodoA *abp = NULL;
        pNodoA *avl = NULL;

        char alimentos[LISTA][MAX_PALAVRA];
        int valores_alimentos[LISTA][3];
        int estatisticas_avl[6];
        int estatisticas_abp[6];

        abp = leArquivoParaArvore(argv[1], abp, 0);
        consultaArquivoABP(argv[2], abp, estatisticas_abp, alimentos, valores_alimentos, 0);

        avl = leArquivoParaArvore(argv[1], avl, 1);
        consultaArquivoABP(argv[2], avl, estatisticas_avl, alimentos, valores_alimentos, 1);

        escreveNoArquivo(argv[3], alimentos, valores_alimentos, estatisticas_abp, estatisticas_avl);

        SetConsoleOutputCP(CPAGE_DEFAULT);
        return 0;
    }
}