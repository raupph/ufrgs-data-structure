#include "abp.h"

NodoArv* abpBuscar(NodoArv *raiz, int cod) {
    if (raiz == NULL)              return NULL;    // não encontrado
    if (cod == raiz->dado.cod)     return raiz;    // encontrado
    if (cod < raiz->dado.cod)
        return abpBuscar(raiz->esq, cod);           // só olha a esquerda
    return abpBuscar(raiz->dir, cod);               // só olha a direita
}

NodoArv* abpInserir(NodoArv *raiz, Produto valor) {
    if (raiz == NULL) {
        NodoArv *novo = (NodoArv*) malloc(sizeof(NodoArv));
        novo->dado = valor;
        novo->esq  = NULL;
        novo->dir  = NULL;
        return novo;                         // pai vai "pendurar" este nó
    }
    if (valor.cod < raiz->dado.cod)
        raiz->esq = abpInserir(raiz->esq, valor);
    else if (valor.cod > raiz->dado.cod)
        raiz->dir = abpInserir(raiz->dir, valor);
    // se igual: código já existe, não insere duplicado
    return raiz;                             // devolve raiz (inalterada) ao pai
}

// encontra o nó de menor valor (mais à esquerda) de uma subárvore
NodoArv* abpMinimo(NodoArv *raiz) {
    while (raiz->esq != NULL)
        raiz = raiz->esq;
    return raiz;
}

NodoArv* abpRemover(NodoArv *raiz, int cod) {
    if (raiz == NULL) return NULL;               // não encontrado

    if (cod < raiz->dado.cod)
        raiz->esq = abpRemover(raiz->esq, cod);   // procura/remove na esquerda
    else if (cod > raiz->dado.cod)
        raiz->dir = abpRemover(raiz->dir, cod);   // procura/remove na direita
    else {
        // achou o nó a remover
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);   // caso 1: folha
            return NULL;
        }
        if (raiz->esq == NULL) {
            NodoArv *filho = raiz->dir;   // caso 2: só filho direito
            free(raiz);
            return filho;
        }
        if (raiz->dir == NULL) {
            NodoArv *filho = raiz->esq;   // caso 2: só filho esquerdo
            free(raiz);
            return filho;
        }
        // caso 3: dois filhos
        NodoArv *sucessor = abpMinimo(raiz->dir);
        raiz->dado = sucessor->dado;                              // copia valor do sucessor
        raiz->dir  = abpRemover(raiz->dir, sucessor->dado.cod);  // remove o sucessor
    }
    return raiz;
}

void abpDestruir(NodoArv *raiz) {
    if (raiz == NULL) return;
    abpDestruir(raiz->esq);
    abpDestruir(raiz->dir);
    free(raiz);
}

void abpEmOrdem(const NodoArv *raiz) {
    if (raiz == NULL) return;
    abpEmOrdem(raiz->esq);
    Produto prod = raiz->dado;
    printf("[%d] -- %s -- %.2f\n", prod.cod, prod.nome, prod.preco);
    abpEmOrdem(raiz->dir);
}

// Funções a implementar
/** 1) void abpContarParesImpares(const NodoArv *raiz, int *pares, int *impares):
Esta função recebe uma árvore, raiz e dois ponteiros para inteiros, pares e impares. Assu-
mindo que o conteúdo dos inteiros apontados seja inicialmente zero, ela deve modificá-los para
contarem, respectivamente, quantos produtos de código par ou ímpar constam na árvore. */

void abpContarParesImpares(const NodoArv *raiz, int *pares, int *impares) {
    // caso receber uma arvoc vaziua
    if (raiz == NULL){
        return;
    } 

    if (raiz->dado.cod % 2 == 0){
       *pares = *pares + 1;
    }
    else{
        *impares = *impares + 1;
    }
    //conta Pra sub da esquerda
    abpContarParesImpares(raiz->esq, pares, impares);
    // conta pra sub da dir
    abpContarParesImpares(raiz->dir, pares, impares);
}
/**
 * 2) void abpPodar(NodoArv *raiz, int altura):
Esta função recebe uma árvore, raiz e um inteiro, altura. Caso a altura de raiz seja maior
que altura, a função deve remover os nodos dos níveis inferiores até que a altura da árvore seja
igual a altura. Assuma altura ≥ 1.
 */
void abpPodar(NodoArv *raiz, int altura) {
    // se receber arvore vazia
    if (raiz == NULL){ 
        return;
    }
    
    // chegopiu no ultimo nivel
    if (altura == 0) {
        // Desttruindo sub arvores esq e dir
        abpDestruir(raiz->esq); 
        raiz->esq = NULL;         

        abpDestruir(raiz->dir);  
        raiz->dir = NULL;        
    } else {
        // se ainda tem no pra baixo, segue podando até chegar na raiz
        //abpPodar(raiz->esq, altura);
        //abpPodar(raiz->dir, altura);
        abpPodar(raiz->esq, altura - 1);
        abpPodar(raiz->dir, altura - 1);
    }
}

// Questão bônus
NodoArv* abpExtrairFolhas(const NodoArv *raiz) {
    return raiz;
}