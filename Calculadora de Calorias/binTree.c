#include <stdio.h>
#include <stdlib.h>
#include "binTree.h"

pNodoABP *InsereABP(pNodoABP *a, tipoinfo *ch)
{
    int res;
    if (a == NULL)
    {
        a = (pNodoABP*)malloc(sizeof(pNodoABP));
        a->info = malloc(strlen(ch) + 1);
        strcpy (a->info, ch);
        a->cals = 0;
        a->esq = NULL;
        a->dir = NULL;
    }
    else
    {
        res = strcmp(ch, a->info);
        printf("\n%d", res);
        if (res < 0)
            a->esq = InsereABP(a->esq, ch);
        else if (res > 0)
            a->dir = InsereABP(a->dir, ch);
        else
            return;
    }
    return a;

}

int alturaABP(pNodoABP *a)
{
    if (a == NULL)
        return 0;
    int dir = alturaABP(a->dir);
    int esq = alturaABP(a->esq);
    return 1 + (esq > dir ? esq : dir);
}

int calculaNodosABP(pNodoABP *a)
{
    if (a == NULL)
        return 0;
    return 1 + calculaNodosABP(a->dir) + calculaNodosABP(a->esq);
}

int fbNodoABP(pNodoABP *a)
{
    return (alturaABP(a->esq) - alturaABP(a->dir));
}

void fbABP(pNodoABP *a, int *fb)
{
    int nodo;
    if (a != NULL)
    {
        nodo = fbNodoABP(a);
        if (nodo > *fb)
            *fb = nodo;
        // printf("%d\n", fb);
        // fb = fb > nodo ? fb : nodo;
        fbABP(a->esq, fb);
        fbABP(a->dir, fb);
    }
}

void preFixadoE(pNodoABP *a)
{
    if (a != NULL)
    {
        printf("%s - ", a->info);
        preFixadoE(a->esq);
        preFixadoE(a->dir);
    }
}

void preFixadoD(pNodoABP *a)
{
    if (a != NULL)
    {
        printf("%s - ", a->info);
        preFixadoD(a->dir);
        preFixadoD(a->esq);
    }
}

void posFixadoE(pNodoABP *a)
{
    if (a != NULL)
    {
        posFixadoE(a->esq);
        posFixadoE(a->dir);
        printf("%s - ", a->info);
    }
}

void posFixadoD(pNodoABP *a)
{
    if (a != NULL)
    {
        posFixadoD(a->dir);
        posFixadoD(a->esq);
        printf("%s - ", a->info);
    }
}

void CentralE(pNodoABP *a)
{
    if (a != NULL)
    {
        CentralE(a->esq);
        printf("%s - ", a->info);
        CentralE(a->dir);
    }
}

void CentralD(pNodoABP *a)
{
    if (a != NULL)
    {
        CentralD(a->dir);
        printf("%s - ", a->info);
        CentralD(a->esq);
    }
}

pNodoABP *consultaABP(pNodoABP *a, tipoinfo *chave)
{
    int res;
    while (a != NULL)
    {
        res = strcmp(chave, a->info);
        if (res == 0)
            return a; // achou entao retorna o ponteiro para o nodo
        else if (res < 0)
            a = a->esq;
        else if (res > 0)
            a = a->dir;
        else
            return NULL;
    }
    return NULL; // se nao achou
}

pNodoABP *consultaABP2(pNodoABP *a, tipoinfo *chave)
{
    int res;
    if (a != NULL)
    {
        res = strcmp(chave, a->info);
        if (res == 0)
            return a;
        else if (res < 0)
            return consultaABP2(a->esq, chave);
        else if (res > 0)
            return consultaABP2(a->dir, chave);

        else
            return NULL;
    }
    else
        return NULL;
}
