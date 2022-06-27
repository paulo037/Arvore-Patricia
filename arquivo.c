#include "./arquivo.h"
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

void criaArq(apointerArq* arq, char* name){
    if ((*arq)== NULL){
        (*arq) = (apointerArq) malloc(sizeof(arq));
        strcpy((*arq)->arquivo, name);
        (*arq)->next = NULL;
        (*arq)->tam = 0;
    }else{
        criaArq(&(*arq)->next , name);
    }
}

void insertArq(FILE* file, apointerArq* arq, apointerP* root, int idDoc){
    char c;
    char palavra[30];
    int cont = 0, flag = 0;
    apointerP* no;
    apointerDoc* aux; 
    no = NULL;
    file = fopen((*arq)->arquivo, "r");
    
    if (file == NULL){
        printf("arquivo não encontrado");
        return;
    }

    do{
        c = fgetc(file);
        if (c == ' ' || c == '.' || c == ',' || c == '\n' || c == '?'){
            if (flag == 0){
                palavra[cont] = '\0';
                if ((*root) != NULL){
                    no = busca(root, palavra);
                    if (!strcmp(palavra, (*no)->NoI.key)){
                       aux = &(*no)->NoI.doc;

                        do{

                            if ((*aux) == NULL){
                                criaDoc(aux, idDoc);
                                cont = 0;
                                flag = 1;
                                break;
                            }

                            if (idDoc == (*aux)->idDoc) {
                                (*aux)->qtd ++;
                                cont = 0;
                                flag = 1;
                                break;
                            }                          

                            aux = &(*aux)->next;

                        }while(1);
                        
                    }else{
                        insertRoot(root, palavra, idDoc);
                        (*arq)->tam++;
                        cont = 0;
                        flag = 1;   
                    }
                }else{
                    insertRoot(root, palavra, idDoc); 
                    (*arq)->tam++;
                    cont = 0;
                    flag = 1;  
                }
            }
        } 
        else{
            palavra[cont] = tolower(c);
            cont++;
            flag = 0;
        }

    }while(c != EOF);
    fclose(file);
}

void buscaArq(apointerP* root, int n, apointerArq* arq){
    char termos[200];
    apointerArq aux = (*arq);
    float releTxt[n];
    apointerP no;
    gets(termos);

    double w = 0;
    int q = contTermos(termos);

    for (int i = 0; i < n; i++){
        buscaTermos(termos, root, i, &w);
        printf("%f", w);
    }

}
void buscaTermos(char termos[], apointerP* root, int idDoc, double *i){
    char* term;
    apointerP* no;
    apointerDoc aux ;
    int Dj;
    double l;

    term = strtok(termos, ", \n\0");
    no = busca(root, term);
    aux = (*no)->NoI.doc;
    Dj = contDj(term, root);
    l = log(2);

    while(aux != NULL){
        if (aux->idDoc == idDoc){
            (*i) = (aux->qtd * l / Dj) + (*i);
        }else{
            aux = aux->next;
        }
    }

    while(term != NULL){
        term = strtok(NULL, ", \n\0");
         no = busca(root, term);
        aux = (*no)->NoI.doc;
        Dj = contDj(term, root);
        l = log(2);

        while(aux != NULL){
            if (aux->idDoc == idDoc){
                (*i) = (aux->qtd * l / Dj) + (*i);
            }else{
                aux = aux->next;
            }

        }
    }
   

}

int contTermos(char termos[]){
    int cont;
    char* term;

    term = strtok(termos, ", \n\0");
    cont = 1;
    while(term != NULL){
        term = strtok(NULL, ", \n\0");
        cont++;
    }
    return cont;
}

int contDj(char term[], apointerP* root){
    apointerP *no;
    apointerDoc aux ;
    int Dj;

    no = busca(root, term);
    aux =(*no)->NoI.doc;

    while(aux != NULL){
        Dj++;
        aux = aux->next;
    }
    return Dj;
}
