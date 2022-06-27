#include <stdio.h>
#include "./Patricia.h"


typedef struct arq* apointerArq;

typedef struct arq{
    char arquivo[20];
    apointerArq next;
    int tam;
}arq;


void insertArq(FILE* file, apointerArq* arq, apointerP* root, int idDoc);
int contTermos(char termos[]);
int contDj(char term[], apointerP* root);
int contTermos(char termos[]);
void buscaTermos(char termos[], apointerP* root, int idDoc, double *i);
void buscaArq(apointerP* root, int n, apointerArq* arq);
void criaArq(apointerArq* arq, char* name);