
typedef char tipoinfo;

struct TNodoABP{
        tipoinfo *info;
        int cals;
        struct TNodoABP *esq;
        struct TNodoABP *dir;
};

typedef struct TNodoABP pNodoABP;

pNodoABP *InsereABP(pNodoABP *a, tipoinfo *ch, tipoinfo *calStr);
void preFixadoE(pNodoABP *a);
void preFixadoD(pNodoABP *a);
void posFixadoE(pNodoABP *a);
void posFixadoD(pNodoABP *a);
void CentralE(pNodoABP *a);
void CentralD(pNodoABP *a);
pNodoABP* consultaABP(pNodoABP *a, tipoinfo *chave);
pNodoABP* consultaABP2(pNodoABP *a, tipoinfo *chave);
int alturaABP(pNodoABP *a);
int calculaNodosABP(pNodoABP *a);
int fbNodoABP(pNodoABP *a);
void fbABP(pNodoABP *a, int *fb);
