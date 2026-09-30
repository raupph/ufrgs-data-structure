#include <stdio.h>
#include <stdlib.h>
#include "listaDuplaEnc.h"

void inicializar(ListaDuplaEnc *l) {
    l->ini = NULL;
    l->fim = NULL;
}

void imprimir(ListaDuplaEnc *l) {
    NodoD *aux = l->ini;

    while (aux != NULL) {
        printf("%d - %s - %.2f\n", aux->dado.cod, aux->dado.nome, aux->dado.preco);
        aux = aux->prox;
    }
}

void imprimirInverso(ListaDuplaEnc *l) {
    NodoD *aux = l->fim;

    while (aux != NULL) {
        printf("%d - %s - %.2f\n", aux->dado.cod, aux->dado.nome, aux->dado.preco);
        aux = aux->ant;
    }
}

Produto acessar(ListaDuplaEnc *l, int cod) {
    NodoD *aux = l->ini;
    Produto prod = {-1, "", 0.0f};

    while (aux != NULL) {
        if (aux->dado.cod == cod)
            return aux->dado;
        aux = aux->prox;
    }

    return prod;
}

int inserirInicio(ListaDuplaEnc *l, Produto prod) {
    NodoD *novo = (NodoD*) malloc(sizeof(NodoD));
    if (novo == NULL)
        return 0;

    novo->dado = prod;
    novo->ant = NULL;
    novo->prox = l->ini;

    if (l->ini != NULL)
        l->ini->ant = novo; // o antigo início passa a ter um antecessor
    else
        l->fim = novo;      // lista estava vazia: novo nodo também é o fim

    l->ini = novo;
    return 1;
}

int inserirFim(ListaDuplaEnc *l, Produto prod) {
    NodoD *novo = (NodoD*) malloc(sizeof(NodoD));
    if (novo == NULL)
        return 0;

    novo->dado = prod;
    novo->prox = NULL;
    novo->ant = l->fim;

    if (l->fim != NULL)
        l->fim->prox = novo; // o antigo fim passa a apontar para o novo nodo
    else
        l->ini = novo;       // lista estava vazia: novo nodo também é o início

    l->fim = novo;
    return 1;
}

int removerPorCod(ListaDuplaEnc *l, int cod) {
    NodoD *aux = l->ini;

    while (aux != NULL && aux->dado.cod != cod)
        aux = aux->prox;

    if (aux == NULL) // não encontrado
        return 0;

    if (aux->ant != NULL) // existe antecessor: religa por ele
        aux->ant->prox = aux->prox;
    else                  // removendo o próprio início
        l->ini = aux->prox;

    if (aux->prox != NULL) // existe sucessor: religa por ele
        aux->prox->ant = aux->ant;
    else                   // removendo o próprio fim
        l->fim = aux->ant;

    free(aux);
    return 1;
}

void destruir(ListaDuplaEnc *l) {
    NodoD *ant;
    NodoD *aux = l->ini;

    while (aux != NULL) {
        ant = aux;
        aux = aux->prox;
        free(ant);
    }

    l->ini = NULL;
    l->fim = NULL;
}

int tamanho(ListaDuplaEnc *l) {
    NodoD *aux = l->ini;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

// Funções a implementar

/** Você deverá adicionar duas novas funções ao TAD:
1) void imprimirPelasPontas(ListaDuplaEnc *l):
Esta função recebe o um ponteiro para uma lista, l. Ela deve imprimir o conteúdo de l “de
fora para dentro”, alternando entre esquerda e direita. Considere que a lista terá tamanho par.
Por exemplo, a sequência 012345 seria impressa como 051423.
Desafio bônus: caso queira, implemente a função tal que garanta a correta impressão mesmo
quando a lista tem tamanho ímpar.
*/

void imprimirPelasPontas(ListaDuplaEnc *l) {

    NodoD *auxIni = l->ini;
    NodoD *auxFim = l->fim;

    if (l->ini == NULL) {
        printf("Lista vazia\n\n");
        return;
    }

    while (auxIni != auxFim && auxFim->prox != auxIni) {
        printf("\n");

        printf("%d - %s - %.2f\n", auxIni->dado.cod, auxIni->dado.nome, auxIni->dado.preco);
        printf("%d - %s - %.2f\n", auxFim->dado.cod, auxFim->dado.nome, auxFim->dado.preco);
        auxIni = auxIni->prox;
        auxFim = auxFim->ant;
    }

}

/** 2) void inverter(ListaEnc *l):
Esta função recebe uma lista de produtos l. Ela deve inverter a ordem de encadeamento dos
nodos da lista, tal que o prox de um nodo passe a ser o seu ant e vice-versa. Ao final, também
deve trocar os atributos ini e fim de l. **/

void inverter(ListaDuplaEnc *l) {

    if (l->ini == NULL){
        printf("Lista Vazia\n");
        return;
    }

    NodoD *aux = l->ini;
    NodoD *temp;

    while (aux != NULL) {
        temp = aux->prox;
        aux->prox = aux->ant;
        aux->ant = temp;
        aux = temp;
    }

    temp = l->ini;
    l->ini = l->fim;
    l->fim = temp;
}