#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include "binTree.h"
#include "avl.h"

// FUNCAO DE REMOVER ESPAÇO AO FIM DE UMA STRING
void trimTrailing(char *str)
{
    int index, i;

    /* Set default index */
    index = -1;

    /* Find last index of non-white space character */
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }
        i++;
    }

    /* Mark next character to last non-white space character as NULL */
    str[index + 1] = '\0';
}

// int main(int argc, char *argv[])
int main()
{
    // Define o valor das páginas de código UTF8 e default do Windows
    // UINT CPAGE_UTF8 = 65001;
    // UINT CPAGE_DEFAULT = GetConsoleOutputCP();

    // Define codificação como sendo UTF-8
    // SetConsoleOutputCP(CPAGE_UTF8);

    // Define codificação como sendo UTF-8
    // SetConsoleOutputCP(CPAGE_UTF8);
    // printf("Utilizando caracteres e acentuação da língua portuguesa!\n\n");
    ///////////////////////////////////////

    struct pNodoABP *abp = NULL;
    struct pNodoAVL *avl = NULL;
    int i, ok;

    avl = InsereAVL(avl, 42, &ok);
    avl = InsereAVL(avl, 15, &ok);
    avl = InsereAVL(avl, 88, &ok);
    avl = InsereAVL(avl, 6, &ok);
    avl = InsereAVL(avl, 27, &ok);
    avl = InsereAVL(avl, 4, &ok);

    Desenha(avl, 1);

    if (is_avl(avl))
        puts("Eh AVL");
    else
        puts("Nao eh AVL");

    abp = InsereABP(abp, 8);
    abp = InsereABP(abp, 4);
    abp = InsereABP(abp, 9);
    abp = InsereABP(abp, 2);
    abp = InsereABP(abp, 6);
    abp = InsereABP(abp, 1);

    imprimiABP(abp, 1);
    printf("\n\n%d\n\n", alturaABP(abp));

    /*
        if (argc != 4) // o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
        {
            printf("Numero incorreto de parametros.\n Para chamar o programa digite: exemplo <arq_entrada> <arq_saida>\n");
            return 1;
        }
        else
        {
            // le_sinonimosABP(argv[1], &abp);
            // escreve_parafraseABP(argv[2], argv[3], abp);
            le_sinonimosAVL(argv[1], &avl, ok);
            printf("%d", alturaABP(avl));
            // desenhaArvore(avl);
            // escreve_parafraseABP(argv[2], argv[3], avl);

            SetConsoleOutputCP(CPAGE_DEFAULT);
            return 0;
        } */
}
