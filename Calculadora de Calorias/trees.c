#include <stdio.h>
#include <stdlib.h>
#include "trees.h"

///////////// COMUM //////////////

int rotacoes = 0;
int comp = 0;

int Altura(pNodoA *a)
{
    if (a == NULL)
        return 0;
    int dir = Altura(a->dir);
    int esq = Altura(a->esq);
    return 1 + (esq > dir ? esq : dir);
}

void Desenha(pNodoA *a, int nivel)
{
    int x;

    if (a != NULL)
    {
        for (x = 1; x <= nivel; x++)
            printf("=");
        printf("%s FB= %d\n", a->info, Calcula_FB(a));
        if (a->esq != NULL)
            Desenha(a->esq, (nivel + 1));
        if (a->dir != NULL)
            Desenha(a->dir, (nivel + 1));
    }
    else
    {
        printf("vazio");
    }
}

int calculaNodos(pNodoA *a)
{
    if (a == NULL)
        return 0;
    return 1 + calculaNodos(a->dir) + calculaNodos(a->esq);
}

int Calcula_FB(pNodoA *a)
{
    return (Altura(a->esq) - Altura(a->dir));
}

pNodoA *consulta(pNodoA *a, TipoInfo *chave)
{
    int res;
    while (a != NULL)
    {
        comp++;
        res = strcmp(chave, a->info);
        if (res == 0)
            return a; // achou entao retorna o ponteiro para o nodo
        else
        {
            if (res < 0)
                a = a->esq;
            else
                a = a->dir;
        }
    }
    return NULL; // se nao achou
}

pNodoA *consulta2(pNodoA *a, TipoInfo *chave)
{
    int res;
    if (a != NULL)
    {
        res = strcmp(chave, a->info);
        if (res == 0)
            return a;
        else if (res < 0)
            return consulta2(a->esq, chave);
        else if (res > 0)
            return consulta2(a->dir, chave);

        else
            return NULL;
    }
    else
        return NULL;
}

///////////////////// ABP /////////////////////////

pNodoA *InsereABP(pNodoA *a, TipoInfo *ch, TipoInfo *calStr, int *ok)
{
    int cals = atoi(calStr);
    int res;
    if (a == NULL)
    {
        a = (pNodoA *)malloc(sizeof(pNodoA));
        a->info = malloc(strlen(ch) + 1);
        strcpy(a->info, ch);
        a->cals = cals;
        a->esq = NULL;
        a->dir = NULL;
    }
    else
    {
        res = strcmp(ch, a->info);
        if (res < 0)
            a->esq = InsereABP(a->esq, ch, calStr, ok);
        else if (res > 0)
            a->dir = InsereABP(a->dir, ch, calStr, ok);
        else
            return NULL;
    }
    return a;
}

void preFixadoE(pNodoA *a)
{
    if (a != NULL)
    {
        printf("%s - ", a->info);
        preFixadoE(a->esq);
        preFixadoE(a->dir);
    }
}

void preFixadoD(pNodoA *a)
{
    if (a != NULL)
    {
        printf("%s - ", a->info);
        preFixadoD(a->dir);
        preFixadoD(a->esq);
    }
}

void posFixadoE(pNodoA *a)
{
    if (a != NULL)
    {
        posFixadoE(a->esq);
        posFixadoE(a->dir);
        printf("%s - ", a->info);
    }
}

void posFixadoD(pNodoA *a)
{
    if (a != NULL)
    {
        posFixadoD(a->dir);
        posFixadoD(a->esq);
        printf("%s - ", a->info);
    }
}

void CentralE(pNodoA *a)
{
    if (a != NULL)
    {
        CentralE(a->esq);
        printf("%s - ", a->info);
        CentralE(a->dir);
    }
}

void CentralD(pNodoA *a)
{
    if (a != NULL)
    {
        CentralD(a->dir);
        printf("%s - ", a->info);
        CentralD(a->esq);
    }
}

////////////////////// AVL //////////////////////

int is_avl(pNodoA *a)
{
    int alt_esq, alt_dir;

    if (a != NULL)
    {
        alt_esq = Altura(a->esq);
        alt_dir = Altura(a->dir);
        return ((alt_esq - alt_dir < 2) && (alt_dir - alt_esq < 2) && (is_avl(a->esq)) && (is_avl(a->dir)));
    }
    else
        return 1;
}

pNodoA *rotacao_direita(pNodoA *pt)
{
    pNodoA *ptu;

    rotacoes++;
    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

pNodoA *rotacao_esquerda(pNodoA *pt)
{
    pNodoA *ptu;

    rotacoes++;
    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}

pNodoA *rotacao_dupla_direita(pNodoA *pt)
{
    pNodoA *ptu, *ptv;

    rotacoes++;
    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;
    if (ptv->FB == 1)
        pt->FB = -1;
    else
        pt->FB = 0;
    if (ptv->FB == -1)
        ptu->FB = 1;
    else
        ptu->FB = 0;
    pt = ptv;
    return pt;
}

pNodoA *rotacao_dupla_esquerda(pNodoA *pt)
{
    pNodoA *ptu, *ptv;

    rotacoes++;
    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1)
        pt->FB = 1;
    else
        pt->FB = 0;
    if (ptv->FB == 1)
        ptu->FB = -1;
    else
        ptu->FB = 0;
    pt = ptv;
    return pt;
}

pNodoA *Caso1(pNodoA *a, int *ok)
{
    pNodoA *ptu;

    ptu = a->esq;
    if (ptu->FB == 1)
    {
        // printf("fazendo rotacao direita em %s\n", a->info);
        a = rotacao_direita(a);
    }
    else
    {
        // printf("fazendo rotacao dupla direita em %s\n", a->info);
        a = rotacao_dupla_direita(a);
    }

    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA *Caso2(pNodoA *a, int *ok)
{
    pNodoA *ptu;

    ptu = a->dir;
    if (ptu->FB == -1)
    {
        // Desenha(a, 1);
        // printf("fazendo rotacao esquerda em %s\n", a->info);
        a = rotacao_esquerda(a);
    }
    else
    {
        // Desenha(a, 1);
        // printf("fazendo rotacao dupla esquerda em %s\n", a->info);
        a = rotacao_dupla_esquerda(a);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA *InsereAVL(pNodoA *a, TipoInfo *x, TipoInfo *calStr, int *ok)
{
    int cals = atoi(calStr);
    int res;
    if (a == NULL)
    {
        a = (pNodoA *)malloc(sizeof(pNodoA));
        a->info = malloc(strlen(x) + 1);
        strcpy(a->info, x);
        a->cals = cals;
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else
    {
        res = strcmp(x, a->info);
        if (res < 0)
        {
            a->esq = InsereAVL(a->esq, x, calStr, ok);
            if (*ok)
            {
                switch (a->FB)
                {
                case -1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case 0:
                    a->FB = 1;
                    break;
                case 1:
                    a = Caso1(a, ok);
                    break;
                }
            }
        }
        else if (res > 0)
        {
            a->dir = InsereAVL(a->dir, x, calStr, ok);
            if (*ok)
            {
                switch (a->FB)
                {
                case 1:
                    a->FB = 0;
                    *ok = 0;
                    break;
                case 0:
                    a->FB = -1;
                    break;
                case -1:
                    a = Caso2(a, ok);
                    break;
                }
            }
        }
        else
            return NULL;
    }
    return a;
}

////////////////// FUNCOES DE ARQUIVO ///////////////////

// FUNCAO DE REMOVER ESPAÇO AO FIM DE UMA STRING
void trimTrailing(char *str)
{
    int index, i;
    index = -1;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }
        i++;
    }

    str[index + 1] = '\0';
}

pNodoA *leArquivoParaArvore(char *file_name, pNodoA *root, int type)
{
    int i, ok = 0;
    rotacoes = 0;
    char separador[] = {";\n\t"};
    char linha[1000], aux_palavra[30], palavra1[30], palavra2[30];
    FILE *entrada;

    pNodoA *(*InsereArvore)(pNodoA *, TipoInfo *, TipoInfo *, int *); // cria um tipo função genérico para receber uma das duas
    if (type)
        InsereArvore = InsereAVL;
    else
        InsereArvore = InsereABP;

    entrada = fopen(file_name, "r");

    if (entrada == NULL) // se no conseguiu abrir o arquivo
    {
        printf("Erro ao abrir o arquivo %s", file_name);
        return NULL;
    }
    else // arquivo de entrada OK
    {
        // percorre todo o arquivo lendo linha por linha
        while (fgets(linha, 1000, entrada))
        {
            strcpy(aux_palavra, strlwr(strtok(linha, separador))); // copia o token (o nome ate a ;)
            trimTrailing(aux_palavra);
            strcpy(palavra1, aux_palavra);

            strcpy(aux_palavra, strlwr(strtok(NULL, separador))); // copia o token (o nome ate o fim)
            trimTrailing(aux_palavra);
            strcpy(palavra2, aux_palavra);

            root = InsereArvore(root, palavra1, palavra2, &ok);
        }
    }
    printf("Arquivo lido com sucesso!\n");
    fclose(entrada); // fecha os arquivos
    return root;
}

int consultaArquivoABP(char *file_entrada, pNodoA *abp, int estatisticas[6], char alimentos[LISTA][MAX_PALAVRA], int valores_alimentos[LISTA][3], int isAvl)
{
    int calsLidas, calsTotais, calsDia = 0;
    FILE *entrada;
    char separador[] = {";\n\t"};
    char linha[1000], aux_palavra[30], palavra1[30], palavra2[30];
    pNodoA *busca = NULL;
    int count = 0;

    entrada = fopen(file_entrada, "r");
    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo %s", file_entrada);
        return 1;
    }
    else
    {
        // percorre todo o arquivo lendo linha por linha
        while (fgets(linha, 1000, entrada))
        {
            strcpy(aux_palavra, strlwr(strtok(linha, separador))); // copia o token (o nome ate a #)
            trimTrailing(aux_palavra);
            strcpy(palavra1, aux_palavra);

            strcpy(aux_palavra, strlwr(strtok(NULL, separador))); // copia o token (o nome ate a #)
            trimTrailing(aux_palavra);
            strcpy(palavra2, aux_palavra);

            calsLidas = atoi(palavra2);
            busca = consulta(abp, strlwr(palavra1));

            if (busca && !isAvl) //cria a legenda dos alimentos apenas uma vez na abp
            {
                calsTotais = calsLidas * busca->cals / 100;
                calsDia += calsTotais;
                valores_alimentos[count][0] = calsLidas;
                valores_alimentos[count][1] = busca->cals;
                valores_alimentos[count][2] = calsTotais;
                strcpy(alimentos[count], busca->info);
            }
            count++;
        }
        estatisticas[0] = calsDia;
        estatisticas[1] = calculaNodos(abp);
        estatisticas[2] = Altura(abp);
        estatisticas[3] = rotacoes;
        estatisticas[4] = comp;
        estatisticas[5] = count;

        comp = 0;

        fclose(entrada); // fecha os arquivos
        return 0;
    }
};

void escreveNoArquivo(char *file_saida, char alimentos[LISTA][MAX_PALAVRA], int valores_alimentos[LISTA][3], int estatisticas_abp[6], int estatisticas_avl[6])
{
    FILE *saida;
    saida = fopen(file_saida, "w");
    int nodos_consultados =  estatisticas_abp[5];
    for (int i = 0; i < nodos_consultados; i++)
    {
        fprintf(saida, "\n%dg de %s (%d calorias por 100g) = %d calorias", valores_alimentos[i][0], alimentos[i], valores_alimentos[i][1], valores_alimentos[i][2]);
    }

    fprintf(saida, "\n\nTotal de %d calorias consumidas no dia.\n\n", estatisticas_abp[0]);
    fprintf(saida, "\n============ABP============\n");
    fprintf(saida, "\nNumero de Nodos: %d", estatisticas_abp[1]);
    fprintf(saida, "\naltura: %d", estatisticas_abp[2]);
    fprintf(saida, "\nRotaçoes: %d", estatisticas_abp[3]);
    fprintf(saida, "\ncomparacoes: %d", estatisticas_abp[4]);
    fprintf(saida, "\n==========================\n");

    fprintf(saida, "\n============AVL==============\n");
    fprintf(saida, "\nNumero de Nodos: %d", estatisticas_avl[1]);
    fprintf(saida, "\naltura: %d", estatisticas_avl[2]);
    fprintf(saida, "\nRotaçoes: %d", estatisticas_avl[3]);
    fprintf(saida, "\ncomparacoes: %d", estatisticas_avl[4]);
    fprintf(saida, "\n==========================\n");

    fclose(saida); // fecha os arquivos
};