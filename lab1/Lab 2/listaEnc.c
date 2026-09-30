#include <stdio.h>
#include <stdlib.h>
#include "listaEnc.h"

void inicializar(ListaEnc *lista) {
    lista->ini = NULL;
}

int tamanho(const ListaEnc *lista) {
    Nodo *aux = lista->ini;
    int contador = 0;

    while (aux != NULL) {
        contador++;
        aux = aux->prox;
    }

    return contador;
}

void imprimir(const ListaEnc *lista) {
    Nodo *aux;
    aux = lista->ini;

    while (aux != NULL) {
        printf("Codigo: %d\n", aux->dado.cod);
        printf("Nome: %s\n", aux->dado.nome);
        printf("Preco: %.2f\n", aux->dado.preco);
        printf("-------\n");
        aux = aux->prox;
    }
}

Produto buscar(const ListaEnc *lista, int cod) {
    Nodo *aux;
    Produto prod = {0, "", 0.0f};
    aux = lista->ini;

    while (aux != NULL) {
        if (aux->dado.cod == cod)
            return aux->dado;
        aux = aux->prox;
    }

    return prod; // não encontrado: produto "vazio"
}

int inserirInicio(ListaEnc *lista, Produto prod) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0; // falha na alocação

    novo->dado = prod;
    novo->prox = lista->ini; // o novo nodo aponta para o antigo início
    lista->ini = novo;        // o novo nodo passa a ser o início

    return 1;
}

int inserirFim(ListaEnc *lista, Produto prod) {
    Nodo *novo;
    Nodo *aux;

    novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo == NULL)
        return 0;

    novo->dado = prod;
    novo->prox = NULL;

    if (lista->ini == NULL) { // lista vazia: o novo nodo é o único (e o início)
        lista->ini = novo;
    } else {
        aux = lista->ini;
        while (aux->prox != NULL) // percorre até o último nodo
            aux = aux->prox;
        aux->prox = novo;
    }

    return 1;
}

int removerPorCod(ListaEnc *lista, int cod) {
    Nodo *ant;
    Nodo *aux;

    ant = NULL;
    aux = lista->ini;

    while (aux != NULL && aux->dado.cod != cod) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) // não encontrado
        return 0;

    if (ant == NULL) // removendo o primeiro nodo
        lista->ini = aux->prox;
    else             // removendo do meio ou do final
        ant->prox = aux->prox;

    free(aux);
    return 1;
}

void destruir(ListaEnc *lista) {
    Nodo *ant;
    Nodo *aux;
    aux = lista->ini;

    while (aux != NULL) {
        ant = aux;
        aux = aux->prox;
        free(ant);
    }

    lista->ini = NULL;
}

// Funções a implementar

/*1) int removerFim(ListaEnc *l, Produto *prodRemovido):
Esta função recebe o um ponteiro para uma lista, l, e um ponteiro para uma variável do
tipo Produto, prodRemovido. Ela deve remover o último nodo de l e colocar o seu conteúdo em
prodRemovido. Lembre-se de evitar vazamentos de memória; o nodo removido deve ser liberado.
A função deve retornar 1 caso a remoção seja bem sucedida, ou 0 caso a lista seja inicialmente
vazia. */
int removerFim(ListaEnc *l, Produto *prodRemovido) {

    Nodo *aux = l->ini;
    Nodo *ant = NULL;

    if (aux == NULL)
        return 0;

    while (aux->prox != NULL) {
        ant = aux;
        aux = aux->prox;
    }

    *prodRemovido = aux->dado;

    if (ant == NULL)
        l->ini = NULL;
    else
        ant->prox = NULL;

    free(aux);

    return 1;
}


/** 2) trocarComProximo(ListaEnc *l, int pos):
Esta função recebe uma lista de produtos l e um inteiro pos representando o índice de um
elemento da lista. Ela deve trocar o conteúdo do nodo na pos-ésima posição com o do nodo na
posição seguinte na lista.
Caso a troca seja bem-sucedida, a função deve retornar 1. Caso o nodo selecionado seja o
último da lista, ou pos exceda o número de nodos da lista, a função deve retornar 0.
Desafio bônus: caso queira, implemente a função tal que, caso pos indique o último nodo
da lista, o seu conteúdo é trocado com o primeiro ao invés da função retornar 0 **/

int trocarComProximo(ListaEnc *l, int pos) {

    int cont = 0;
    Nodo *aux = l->ini;
    Produto produtoAuxiliar;

    while (aux != NULL) {

        if (cont == pos) {

            if (aux->prox == NULL){
                return 0;
            }    

            produtoAuxiliar = aux->dado;
            aux->dado = aux->prox->dado;
            aux->prox->dado = produtoAuxiliar;

            return 1;
        }
        
        aux = aux->prox;
        cont++;
    }


    return 0;
}
