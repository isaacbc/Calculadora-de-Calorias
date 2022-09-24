#include <stdio.h>
#include <stdlib.h>
#include "binTree.h"

pNodoABP* InsereABP(pNodoABP *a, tipoinfo ch)
{
     if (a == NULL)
     {
         a =  (pNodoABP*) malloc(sizeof(pNodoABP));
         a->info = ch;
         a->esq = NULL;
         a->dir = NULL;
         return a;
     }
     else
          if (ch < a->info)
              a->esq = InsereABP(a->esq,ch);
          else if (ch > a->info)
              a->dir = InsereABP(a->dir,ch);
     return a;
}

void imprimiABP(pNodoABP *a, int key)
{
    if (a != NULL)
    {
        int i;
        for (i = 0; i < key; i++)
            printf("=");
        printf("%d\n", a->info);
        imprimiABP(a->esq, key + 1);
        imprimiABP(a->dir, key + 1);
    }
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
    return 1 + calculaNodosABP(a->dir) +  calculaNodosABP(a->esq);
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
            *fb= nodo;
        //printf("%d\n", fb);
        //fb = fb > nodo ? fb : nodo;
        fbABP(a->esq, fb);
        fbABP(a->dir, fb);
    }
}

void preFixadoE(pNodoABP *a)
{
     if (a!= NULL)
     {
          printf("%d - ",a->info);
          preFixadoE(a->esq);
          preFixadoE(a->dir);
      }
}

void preFixadoD(pNodoABP *a)
{
     if (a!= NULL)
     {
          printf("%d - ",a->info);
          preFixadoD(a->dir);
          preFixadoD(a->esq);
      }
}

void posFixadoE(pNodoABP *a)
{
     if (a!= NULL)
     {
          posFixadoE(a->esq);
          posFixadoE(a->dir);
          printf("%d - ",a->info);
      }
}

void posFixadoD(pNodoABP *a)
{
     if (a!= NULL)
     {
          posFixadoD(a->dir);
          posFixadoD(a->esq);
          printf("%d - ",a->info);
      }
}

void CentralE(pNodoABP *a)
{
     if (a!= NULL)
     {
          CentralE(a->esq);
          printf("%d - ",a->info);
          CentralE(a->dir);
      }
}

void CentralD(pNodoABP *a)
{
     if (a!= NULL)
     {
          CentralD(a->dir);
          printf("%d - ",a->info);
          CentralD(a->esq);
      }
}


pNodoABP* consultaABP(pNodoABP *a, tipoinfo chave) {

    while (a!=NULL){
          if (a->info == chave )
             return a; //achou entao retorna o ponteiro para o nodo
          else
            if (a->info > chave)
               a = a->esq;
            else
               a = a->dir;
            }
            return NULL; //se nao achou
}

pNodoABP* consultaABP2(pNodoABP *a, tipoinfo chave) {
    if (a!=NULL) {
       if (a->info == chave)
         return a;
       else
           if (a->info > chave)
                return consultaABP2(a->esq,chave);
            if (a->info < chave)
                return consultaABP2(a->dir,chave);

            else return a;
       }
       else return NULL;
}



