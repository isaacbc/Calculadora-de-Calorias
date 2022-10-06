#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "avl.h"
#include "trees.h"

int Altura(pNodoA *a)
{
    if (a == NULL)
        return 0;
    int dir = Altura(a->dir);
    int esq = Altura(a->esq);
    return 1 + (esq > dir ? esq : dir);
}

int Calcula_FB(pNodoA *a)
{
    return (Altura(a->esq) - Altura(a->dir));
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
        printf("fazendo rotacao direita em %d\n", a->info);
        a = rotacao_direita(a);
    }
    else
    {
        printf("fazendo rotacao dupla direita em %d\n", a->info);
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
        Desenha(a, 1);
        printf("fazendo rotacao esquerda em %d\n", a->info);
        a = rotacao_esquerda(a);
    }
    else
    {
        Desenha(a, 1);
        printf("fazendo rotacao dupla esquerda em %d\n", a->info);
        a = rotacao_dupla_esquerda(a);
    }
    a->FB = 0;
    *ok = 0;
    return a;
}

pNodoA *InsereAVL(pNodoA *a, TipoInfo *x, TipoInfo *calStr, int *ok)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
      x, a chave a ser inserida e h a altura da árvore */
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
        else if(res > 0)
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
            return;
    }
    return a;
}
