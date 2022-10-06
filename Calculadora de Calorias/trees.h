#define MAX_PALAVRA 50
#define LISTA 50

typedef char TipoInfo;
struct TNodoA
{
    TipoInfo *info;
    int cals;
    int FB;
    struct TNodoA *esq;
    struct TNodoA *dir;
};
typedef struct TNodoA pNodoA;

///////////// COMUM //////////
int Altura(pNodoA *a);
void Desenha(pNodoA *a, int nivel);
int calculaNodos(pNodoA *a);
int Calcula_FB(pNodoA *a);
pNodoA *consulta(pNodoA *a, TipoInfo *chave);

/////////  ABPs ///////////////////
pNodoA *InsereABP(pNodoA *a, TipoInfo *ch, TipoInfo *calStr, int *ok);
void preFixadoE(pNodoA *a);
void preFixadoD(pNodoA *a);
void posFixadoE(pNodoA *a);
void posFixadoD(pNodoA *a);
void CentralE(pNodoA *a);
void CentralD(pNodoA *a);

///////// AVLs ///////////////
pNodoA *InsereAVL(pNodoA *a, TipoInfo *x, TipoInfo *calStr, int *ok);
int is_avl(pNodoA *a);
pNodoA *rotacao_direita(pNodoA *pt);
pNodoA *rotacao_esquerda(pNodoA *pt);
pNodoA *rotacao_dupla_direita(pNodoA *pt);
pNodoA *rotacao_dupla_esquerda(pNodoA *pt);
pNodoA *Caso1(pNodoA *a, int *ok);
pNodoA *Caso2(pNodoA *a, int *ok);

////////////////// FUNCOES DE ARQUIVO ///////////////////
void trimTrailing(char *str);
pNodoA *leArquivoParaArvore(char *file_name, pNodoA *root, int type);
int consultaArquivoABP(char *file_entrada, pNodoA *abp, int estatisticas[6], char alimentos[LISTA][MAX_PALAVRA], int valores_alimentos[LISTA][3], int isAvl);
void escreveNoArquivo(char *file_saida, char alimentos[LISTA][MAX_PALAVRA], int valores_alimentos[LISTA][3], int estatisticas_abp[6], int estatisticas_avl[6]);
