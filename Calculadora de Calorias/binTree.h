
typedef int tipoinfo;

struct TNodoABP{
        tipoinfo info;
        struct TNodoABP *esq;
        struct TNodoABP *dir;
};

typedef struct TNodoABP pNodoABP;

pNodoABP* InsereABP(pNodoABP *a, tipoinfo ch);
void preFixadoE(pNodoABP *a);
void preFixadoD(pNodoABP *a);
void posFixadoE(pNodoABP *a);
void posFixadoD(pNodoABP *a);
void CentralE(pNodoABP *a);
void CentralD(pNodoABP *a);
pNodoABP* consultaABP(pNodoABP *a, tipoinfo chave);
pNodoABP* consultaABP2(pNodoABP *a, tipoinfo chave);
void imprimiABP(pNodoABP *a, int key);
int alturaABP(pNodoABP *a);
int calculaNodosABP(pNodoABP *a);
int fbNodoABP(pNodoABP *a);
void fbABP(pNodoABP *a, int *fb);
