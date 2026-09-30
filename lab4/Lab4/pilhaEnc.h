#ifndef PILHAENC_H
#define PILHAENC_H

typedef struct {
    int cod;
    char nome[50];
    float preco;
} Produto;

typedef struct str_Nodo Nodo;

struct str_Nodo {
    Nodo *prox;
    Produto dado;
};

typedef struct {
    Nodo *topo;
} PilhaEnc;

void inicializaPilha(PilhaEnc *p);
int  estaVaziaPilha(PilhaEnc *p);
int  empilha(PilhaEnc *p, Produto valor);
int  desempilha(PilhaEnc *p, Produto *valorRemovido);
int  topo(PilhaEnc *p, Produto *valor);
int  tamanhoPilha(PilhaEnc *p);

#endif
