#include <stdio.h>
#include "filaEnc.h"
#include <stdlib.h>

/** 1) void imprimePilhaInverso(PilhaEnc *p):
Esta função recebe o um ponteiro para uma pilha, p. Ela deve imprimir o conteúdo de p na
ordem do fundo ao topo. Ou seja, o elemento do topo será o último a ser impresso. Ao retornar
da função, o conteúdo de p deve ser o mesmo de quando a função foi chamada.
Atenção: para sua implementação, a única estrutura auxiliar que pode ser usada é outra
pilha. Você não pode usar filas, listas, vetores, ou qualquer outra estrutura.*/
/*

void imprimePilhaInverso(PilhaEnc *p) {
    PilhaEnc pilhaAux;
    Nodo *aux;       // <- acesso direto ao Nodo, proibido
    Produto prod;

    aux = p->topo;   // <- acesso direto ao campo topo, proibido
    inicializaPilha(&pilhaAux);

    if(estaVaziaPilha(p)){
        printf("Pilha vazia\n");
    }

    printf("\n Iniciando Inversa\n");

    while(aux != NULL){
        printf("%d -- %s -- %.4f\n", aux->dado.cod, aux->dado.nome, aux->dado.preco);
        empilha(&pilhaAux, aux->dado);
        aux = aux->prox;   // <- percorre lista pelo Nodo, proibido
    }

    printf("\n");

    while(!estaVaziaPilha(&pilhaAux)){
        desempilha(&pilhaAux, &prod);
        printf("%d -- %s -- %.4f\n", prod.cod, prod.nome, prod.preco);
    }
}

*/


void imprimePilhaInverso(PilhaEnc *p) {

    PilhaEnc pilhaAux;
    Produto prod;

    inicializaPilha(&pilhaAux);

    if (estaVaziaPilha(p)) {

        printf("Pilha vazia\n");

        return;
    }
    //esvasiando para empilhar o contrario da original
    while (!estaVaziaPilha(p)) {
        desempilha(p, &prod);
        empilha(&pilhaAux, prod);
    }
    
    //esvaziando aux para empilhar aux ao contrario na original
    while (!estaVaziaPilha(&pilhaAux)) {

        desempilha(&pilhaAux, &prod);
        printf("%d -- %s -- %.2f\n", prod.cod, prod.nome, prod.preco);
        empilha(p, prod);
    }

    printf("\n");
}


/** 2) void transfereOrdenado(FilaEnc *f, PilhaEnc *p):
Esta função recebe ponteiros para uma fila f preenchida com produtos e uma pilha p vazia.
A função deve encerrar com p contendo os produtos de f, ordenados pelo cod tal que o topo de
p possui o menor valor (a pilha é crescente em direção ao fundo). A função termina com f vazia.
Atenção: você não pode usar nenhuma estrutura auxiliar além de f e p.
1
A saída esperada da função main é:
12 -- a -- 0.00
3 -- b -- 0.00
7 -- c -- 0.00
19 -- d -- 0.00
5 -- e -- 0.00
-----------------
20 -- f -- 0.00
15 -- g -- 0.00
10 -- h -- 0.00
4 -- i -- 0.00
1 -- j -- 0.00 */

void transfereOrdenado(FilaEnc *f, PilhaEnc *p) {

    Produto atual, temp;
    int n, sobra;
    int j = 0;

    if (estaVaziaFila(f)){
        return; 
    }

    n = tamanhoFila(f); 
    //deixar o maior sempre no topo
    for (int i = 0; i < n; i++) {

        sobra = n - i; 
        desenfileira(f, &atual); 

        for (j = 1; j < sobra; j++) {

            desenfileira(f, &temp); 

            //eixar o maior sempre no topo
            if (temp.cod > atual.cod) {

                enfileira(f, atual);
                atual = temp; 

            } else {

                enfileira(f, temp);
            }
        }

        empilha(p, atual); //coloc o maior na pilha
    }
}

void enchePilha(PilhaEnc *p) {
    Produto p1 = {12, "a", 0.0};
    Produto p2 = {3, "b", 0.0};
    Produto p3 = {7, "c", 0.0};
    Produto p4 = {19, "d", 0.0};
    Produto p5 = {5, "e", 0.0};

    empilha(p, p1);
    empilha(p, p2);
    empilha(p, p3);
    empilha(p, p4);
    empilha(p, p5);
}

void encheFila(FilaEnc *f) {
    Produto p1 = {15, "g", 0.0};
    Produto p2 = {4, "i", 0.0};
    Produto p3 = {20, "f", 0.0};
    Produto p4 = {1, "j", 0.0};
    Produto p5 = {10, "h", 0.0};    

    enfileira(f, p1);
    enfileira(f, p2);
    enfileira(f, p3);
    enfileira(f, p4);
    enfileira(f, p5);
}

int main() {
    PilhaEnc p, dest;
    FilaEnc f;

    inicializaPilha(&p);
    inicializaPilha(&dest);
    inicializaFila(&f);

    // Testes com estruturas vazias
    imprimePilhaInverso(&p);
    transfereOrdenado(&f, &p);

    // Preenche as estruturas
    enchePilha(&p);
    encheFila(&f);

    // Testa as funções
    imprimePilhaInverso(&p);

    printf("-----------------\n");

    transfereOrdenado(&f, &dest);
    imprimePilhaInverso(&dest);

}