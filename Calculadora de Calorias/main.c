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

pNodoABP *le_sinonimosABP(char *file_name, pNodoABP *root)
{
    printf("entrou");
    FILE *entrada;
    char separador[] = {";\n\t"};
    char linha[1000], aux_palavra[30], palavra2[30], palavra3[30];
    entrada = fopen(file_name, "r"); // abre o arquivo para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
    if (entrada == NULL)             // se n�o conseguiu abrir o arquivo
    {
        printf("Erro ao abrir o arquivo %s", file_name);
        return;
    }
    else // arquivo de entrada OK
    {
        // percorre todo o arquivo lendo linha por linha
        while (fgets(linha, 1000, entrada))
        {
            strcpy(aux_palavra, strlwr(strtok(linha, separador))); // copia o token (o nome ate a #)
            trimTrailing(aux_palavra);
            strcpy(palavra2, aux_palavra);

            printf("\n%s", palavra2);
            root = InsereABP(root, palavra2);
        }
    }
    printf("Arquivo lido com sucesso!");
    fclose(entrada); // fecha os arquivos
    return root;
}

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
        pNodoABP *abp = NULL;
        pNodoAVL *avl = NULL;
        int i, ok;
        printf("oie");
        abp = le_sinonimosABP(argv[1], abp);
        Desenha(abp, 1);
        printf("\n\n%d\n\n", alturaABP(abp));
        SetConsoleOutputCP(CPAGE_DEFAULT);
        return 0;
    }
}
