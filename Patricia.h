typedef enum{
    Interno, Externo
}tipoNo;

typedef enum{
    left, right
}direcao;

typedef struct Patricia* apointerP;

typedef struct doc* apointerDoc;

typedef struct doc{
    int qtd;
    int idDoc;
    apointerDoc next;
}Doc;

typedef struct Patricia {

    tipoNo tipo;
    union {
        struct{
            char key[50];
            apointerDoc doc;
        };
        struct{
          int index;
          char bit;
          apointerP left, right;
        };
    }NoI;
  
}Patricia;


void criaDoc(apointerDoc* doc, int idDoc);
void criaNoInterno(apointerP* root, int* index,char* string);
void criaNoExterno(apointerP* root,char* string,int idDoc);
void insertRoot(apointerP* root, char* string, int idDoc);
void iInsert(apointerP* root, char* string, apointerP* no,int*  flag, direcao dir, int* end,  int idDoc);
void createNo(apointerP* no, char* string, int index, int idDoc, direcao dir);
void insert(apointerP* no, apointerP* root, direcao dir);
void caseOne(apointerP* no, apointerP* root, char* string, int idDoc);
void insertInicio(apointerP* no, apointerP* root,direcao dir);
apointerP* busca(apointerP* root, char* string);
direcao find(apointerP*, char x, int index);
void imprimirPat(apointerP* root);