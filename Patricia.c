#include "./Patricia.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void insertRoot(apointerP* root, char* string, int idDoc){
    if ((*root) == NULL){
       criaNoExterno(root, string, idDoc);
    }else{
        apointerP no = NULL;
        if ((*root)->tipo == Externo){
            caseOne(&no, root, string, idDoc);
        }else{
            int cont = 0;
            int flag = 0;
            iInsert(root, string, &no, &flag, Externo, &cont, idDoc);
        }
    }
}

void iInsert(apointerP* root, char* string, apointerP* no,int*  flag, direcao dir, int* cont, int idDoc){
    int fim = (*cont);
    (*cont)++;
    if ((*root)->tipo == Interno){
        int i = (*root)->NoI.index;
        if (string[i] < (*root)->NoI.bit){
            iInsert(&(*root)->NoI.left, string, no, flag, dir, cont, idDoc);
            dir = left;
        }else {
            iInsert(&(*root)->NoI.right, string, no, flag, dir, cont, idDoc);
            dir = right;
        }
        if ((*no)->NoI.index >= (*root)->NoI.index && !(*flag)){
            insert(no, root, dir);
            (*flag) = 1;
        }
    }else{ 

        int j = 0;
        int index = 0;
        while((*root)->NoI.key[j] == string[j]){
            if((*root)->NoI.key[j] == '\0' || string[j] == '\0')break;
            index++;
            j++;
        }
        createNo(no, string, index, idDoc, right);
        return;
    }
    if (!fim && !(*flag)){
        if ((*no)->NoI.index < (*root)->NoI.index)
            insertInicio(no, root, dir);
        else  insert(no, root, dir);
    }
}

void createNo(apointerP* no, char* string, int index, int idDoc, direcao dir){
    apointerP externo = NULL;
    criaNoInterno(no, &index, string);
    criaNoExterno(&externo, string, idDoc);
    if (dir == right) (*no)->NoI.right = externo;
    else (*no)->NoI.left = externo;
}

void insertInicio(apointerP* no, apointerP* root,direcao dir){
    int i = (*no)->NoI.index;
    if (dir == right){
        if ((*no)->NoI.bit > (*root)->NoI.right->NoI.key[i]){
            (*no)->NoI.left = (*root);
            (*root)= (*no);
        }else{
            (*no)->NoI.left = (*no)->NoI.right;
            (*no)->NoI.right = (*root);
            (*root) = (*no);
        }
    }else{
         if ((*no)->NoI.bit > (*root)->NoI.left->NoI.key[i]){
            (*no)->NoI.left = (*root);
            (*root)= (*no);
        }else{
            (*no)->NoI.bit = (*root)->NoI.left->NoI.key[i];
            (*no)->NoI.left = (*no)->NoI.right;
            (*no)->NoI.right = (*root);
            (*root) = (*no);
        }
    }
}

void insert(apointerP* no, apointerP* root, direcao dir){
    direcao lado;
    if (dir == right){
        if ((*root)->NoI.right->tipo == Interno){
            lado = find(&(*root)->NoI.right, (*no)->NoI.bit, (*no)->NoI.index);
            if (lado == right){
                (*no)->NoI.left = (*root)->NoI.right;
                (*root)->NoI.right = (*no);
            }else{
                (*no)->NoI.left = (*no)->NoI.right;
                (*no)->NoI.right = (*root)->NoI.right;
                (*root)->NoI.right = (*no);
            }
        }else{
            int i = (*no)->NoI.index;
            if((*root)->NoI.right->NoI.key[i] < (*no)->NoI.bit){
                (*no)->NoI.left = (*root)->NoI.right;
                (*root)->NoI.right = (*no);
            }else{
                (*no)->NoI.left = (*no)->NoI.right;
                (*no)->NoI.right = (*root)->NoI.right;
                (*root)->NoI.right = (*no);
            }
            
        }
    }else{
        if ((*root)->NoI.left->tipo == Interno){
            lado = find(&(*root)->NoI.left, (*no)->NoI.bit, (*no)->NoI.index);
            if (lado == right){
                (*no)->NoI.left = (*root)->NoI.left;
                (*root)->NoI.left = (*no);
            }else{
                int i = (*no)->NoI.index;
                (*no)->NoI.left = (*no)->NoI.right;
                (*no)->NoI.right = (*root)->NoI.left;
                (*no)->NoI.bit = (*root)->NoI.left->NoI.key[i];
                (*root)->NoI.left = (*no);
            }
        }else{
            int i = (*no)->NoI.index;
            if((*root)->NoI.left->NoI.key[i] < (*no)->NoI.bit){
                (*no)->NoI.left = (*root)->NoI.left;
                (*root)->NoI.left = (*no);
            }else{
                (*no)->NoI.left = (*no)->NoI.right;
                (*no)->NoI.right = (*root)->NoI.left;
                (*no)->NoI.bit = (*root)->NoI.left->NoI.key[i];
                (*root)->NoI.left = (*no);
            }
            
        }
    }
}

direcao find(apointerP* root, char x, int index){
    apointerP aux = (*root);

    while(aux->tipo == Interno){
        aux = aux->NoI.right;
    }

    if (aux->NoI.key[index] >= x) return left;
    else return right;
}

void criaNoInterno(apointerP* root, int* index,char* string){
    (*root) = (apointerP) malloc(sizeof(Patricia));
    (*root)->tipo = Interno;
    (*root)->NoI.index = (*index);
    (*root)->NoI.bit = string[(*index)];
    (*root)->NoI.left = NULL;
    (*root)->NoI.right = NULL;
}

void criaNoExterno(apointerP* root,char* string, int idDoc){
    int tam = strlen(string);
    (*root) = (apointerP) malloc(sizeof(Patricia));
    (*root)->tipo = Externo;
    criaDoc(&(*root)->NoI.doc, idDoc);
    strcpy((*root)->NoI.key, string);
}

void caseOne(apointerP* no, apointerP* root, char* string, int idDoc){
    int j = 0;
    int index = 0;
    while((*root)->NoI.key[j] == string[j]){
        if((*root)->NoI.key[j] == '\0' || string[j] == '\0')break;
        index++;
        j++;
    }
    if ((*root)->NoI.key[index-1] ==  string[index-1] && strlen(string) <= j){
        createNo(no, string, index, idDoc, left);
        (*no)->NoI.bit = (*root)->NoI.key[index];
        (*no)->NoI.right = (*root);
        (*root) = (*no);
        return;
    }
    if (string[index] >= (*root)->NoI.key[index]){
        createNo(no, string, index, idDoc, right);
        (*no)->NoI.left = (*root);
        (*root) = (*no);
    }
    else{
        createNo(no, string, index, idDoc, left);
        (*no)->NoI.bit = (*root)->NoI.key[index];
        (*no)->NoI.right = (*root);
        (*root) = (*no);
    }
}

apointerP* busca(apointerP* root, char* string){
    apointerP* resp;
    if((*root)->tipo == Interno){
        int i = (*root)->NoI.index;
        if (string[i] >= (*root)->NoI.bit && i < strlen(string)){
            resp = busca(&(*root)->NoI.right, string);
        }else resp = busca(&(*root)->NoI.left, string);
    }else{
        resp = root;
    } return resp;
}

void criaDoc(apointerDoc* doc, int idDoc){
    (*doc)= (apointerDoc) malloc(sizeof(Doc));
    (*doc)->idDoc = idDoc;
    (*doc)->qtd = 1;
    (*doc)->next = NULL;
}

void imprimirPat(apointerP* root){

    if ((*root)->tipo == Interno){
        imprimirPat(&(*root)->NoI.left);
        imprimirPat(&(*root)->NoI.right);
    }else{
        apointerDoc aux = (*root)->NoI.doc;
        printf("%s",  (*root)->NoI.key);
        while(aux != NULL){
            printf(" <%d,%d>",aux->qtd, aux->idDoc  );
            aux = aux->next;
        }
        printf("\n");
    }
    
}