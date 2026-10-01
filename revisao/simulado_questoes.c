/* 
 * =====================================================================================
 *  SIMULADO — ESTRUTURAS DE DADOS (PROF. DENNIS BALREIRA)
 *  Parte 2 — Questões de Código (Grupos A, B e C)
 * 
 *  Instruções:
 *  1. Cada função a ser implementada está sinalizada com:
 *     // TODO: Escreva sua implementação aqui
 *  2. O main() já está completamente montado com casos de teste.
 *  3. Para cada questão, o terminal imprimirá:
 *     ==================== QUESTÃO XX ====================
 *     [ESPERADO]: ...
 *     [OBTIDO]  : ...
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* =====================================================================================
 * 1. DEFINIÇÃO DOS TIPOS E TADs (CONFORME DADO NO SIMULADO)
 * =====================================================================================
 */

typedef struct {
    int cod;
    char nome[50];
    float preco;
} Produto;

/* Lista simplesmente encadeada */
typedef struct str_Nodo Nodo;
struct str_Nodo {
    Nodo *prox;
    Produto dado;
};
typedef struct {
    Nodo *ini;
} ListaEnc;

/* TAD Pilha (implementada com lista encadeada) */
typedef struct str_NodoPilha NodoPilha;
struct str_NodoPilha {
    NodoPilha *prox;
    Produto dado;
};
typedef struct {
    NodoPilha *topo;
} PilhaEnc;

/* TAD Fila (implementada com lista encadeada) */
typedef struct str_NodoFila NodoFila;
struct str_NodoFila {
    NodoFila *prox;
    Produto dado;
};
typedef struct {
    NodoFila *ini;
    NodoFila *fim;
} FilaEnc;

/* Árvore Binária de Pesquisa */
typedef struct str_NodoArv NodoArv;
struct str_NodoArv {
    Produto dado;
    NodoArv *esq;
    NodoArv *dir;
};

/* =====================================================================================
 * 2. FUNÇÕES DOS TADs E AUXILIARES DE INFRAESTRUTURA
 * =====================================================================================
 */

/* Auxiliar: criar struct Produto */
Produto criaProd(int cod, const char *nome, float preco) {
    Produto p;
    p.cod = cod;
    strncpy(p.nome, nome, 49);
    p.nome[49] = '\0';
    p.preco = preco;
    return p;
}

/* Auxiliares de ListaEnc */
void inicializaLista(ListaEnc *l) {
    l->ini = NULL;
}

void inserirFimLista(ListaEnc *l, Produto d) {
    Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
    novo->dado = d;
    novo->prox = NULL;
    if (l->ini == NULL) {
        l->ini = novo;
    } else {
        Nodo *aux = l->ini;
        while (aux->prox != NULL) aux = aux->prox;
        aux->prox = novo;
    }
}

void imprimirLista(const ListaEnc *l) {
    Nodo *aux = l->ini;
    printf("[");
    while (aux != NULL) {
        printf("(cod:%d, r$%.2f)", aux->dado.cod, aux->dado.preco);
        if (aux->prox != NULL) printf(" -> ");
        aux = aux->prox;
    }
    printf("]\n");
}

void liberarLista(ListaEnc *l) {
    Nodo *aux = l->ini;
    while (aux != NULL) {
        Nodo *temp = aux->prox;
        free(aux);
        aux = temp;
    }
    l->ini = NULL;
}

/* TAD Pilha */
void inicializaPilha(PilhaEnc *p) {
    p->topo = NULL;
}

int estaVaziaPilha(PilhaEnc *p) {
    return p->topo == NULL;
}

void push(PilhaEnc *p, Produto d) {
    NodoPilha *novo = (NodoPilha*) malloc(sizeof(NodoPilha));
    novo->dado = d;
    novo->prox = p->topo;
    p->topo = novo;
}

Produto pop(PilhaEnc *p) {
    if (estaVaziaPilha(p)) {
        Produto vazio = {0, "VAZIO", 0.0f};
        return vazio;
    }
    NodoPilha *rem = p->topo;
    Produto d = rem->dado;
    p->topo = rem->prox;
    free(rem);
    return d;
}

void imprimirPilha(PilhaEnc *p) {
    PilhaEnc temp;
    inicializaPilha(&temp);
    printf("TOPO -> [");
    while (!estaVaziaPilha(p)) {
        Produto prod = pop(p);
        printf("(cod:%d, r$%.2f) ", prod.cod, prod.preco);
        push(&temp, prod);
    }
    printf("]\n");
    while (!estaVaziaPilha(&temp)) {
        push(p, pop(&temp));
    }
}

void liberarPilha(PilhaEnc *p) {
    while (!estaVaziaPilha(p)) {
        pop(p);
    }
}

/* TAD Fila */
void inicializaFila(FilaEnc *f) {
    f->ini = NULL;
    f->fim = NULL;
}

int estaVaziaFila(FilaEnc *f) {
    return f->ini == NULL;
}

void enqueue(FilaEnc *f, Produto d) {
    NodoFila *novo = (NodoFila*) malloc(sizeof(NodoFila));
    novo->dado = d;
    novo->prox = NULL;
    if (f->fim != NULL) {
        f->fim->prox = novo;
    } else {
        f->ini = novo;
    }
    f->fim = novo;
}

Produto dequeue(FilaEnc *f) {
    if (estaVaziaFila(f)) {
        Produto vazio = {0, "VAZIO", 0.0f};
        return vazio;
    }
    NodoFila *rem = f->ini;
    Produto d = rem->dado;
    f->ini = rem->prox;
    if (f->ini == NULL) {
        f->fim = NULL;
    }
    free(rem);
    return d;
}

void imprimirFila(FilaEnc *f) {
    FilaEnc temp;
    inicializaFila(&temp);
    printf("FRENTE -> [");
    while (!estaVaziaFila(f)) {
        Produto prod = dequeue(f);
        printf("(cod:%d, r$%.2f) ", prod.cod, prod.preco);
        enqueue(&temp, prod);
    }
    printf("] <- FIM\n");
    while (!estaVaziaFila(&temp)) {
        enqueue(f, dequeue(&temp));
    }
}

void liberarFila(FilaEnc *f) {
    while (!estaVaziaFila(f)) {
        dequeue(f);
    }
}

/* Auxiliares para Árvore Binária de Pesquisa (ABP) */
NodoArv* abpInserir(NodoArv *raiz, Produto p) {
    if (raiz == NULL) {
        NodoArv *novo = (NodoArv*) malloc(sizeof(NodoArv));
        novo->dado = p;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (p.cod < raiz->dado.cod) {
        raiz->esq = abpInserir(raiz->esq, p);
    } else if (p.cod > raiz->dado.cod) {
        raiz->dir = abpInserir(raiz->dir, p);
    }
    return raiz;
}

void abpEmOrdem(const NodoArv *raiz) {
    if (raiz != NULL) {
        abpEmOrdem(raiz->esq);
        printf("(cod:%d, r$%.2f) ", raiz->dado.cod, raiz->dado.preco);
        abpEmOrdem(raiz->dir);
    }
}

void abpDestruir(NodoArv *raiz) {
    if (raiz != NULL) {
        abpDestruir(raiz->esq);
        abpDestruir(raiz->dir);
        free(raiz);
    }
}

/* =====================================================================================
 * 3. ESPAÇO RESERVADO PARA A SUA IMPLEMENTAÇÃO DAS QUESTÕES
 * =====================================================================================
 */

/* -------------------------------------------------------------------------------------
 * GRUPO A — Lista Simplesmente Encadeada
 * ------------------------------------------------------------------------------------- */

/* A1. Implemente maiorPreco, que percorre a lista e retorna o produto de maior preco. Assuma lista não vazia. */
Produto maiorPreco(const ListaEnc *lista) {

    Nodo* aux = lista->ini;
    float maior = -1;
    Produto maiorProduto = aux->dado; 

    while(aux != NULL){
        if(aux->dado.preco > maiorProduto.preco){
            maiorProduto = aux->dado;
        }

        aux = aux->prox;
    }
    return maiorProduto;
}


/* A2. Implemente somarPrecosImpares, que percorre a lista e retorna a soma dos preco dos produtos cujo cod seja ímpar. Retorne 0.0 para lista vazia. */
float somarPrecosImpares(const ListaEnc *lista) {
    Nodo *aux = lista->ini;
    float soma = 0;

    while(aux != NULL){

        if((aux->dado.cod % 2) != 0){
            soma += aux->dado.preco;
        }
        aux = aux->prox;
    }

    return soma;
}


/* A3. Implemente removerMenoresQuePreco, que remove da lista todos os produtos com preco estritamente menor que p. Libere cada nodo com free. Trate múltiplos consecutivos no início. */
void removerMenoresQuePreco(ListaEnc *lista, float p) {
    
    while (lista->ini != NULL && lista->ini->dado.preco < p){
        Nodo *removido = lista->ini;
        lista->ini = lista->ini->prox;
        free(removido);
    }
    
    Nodo *aux = lista->ini;
    Nodo *ant = NULL;

    
    while(aux != NULL){

        if(aux->dado.preco < p){
            Nodo *removido = aux;
            ant->prox = aux->prox;
            aux = aux->prox;
            free(removido);
        }else{
            ant = aux;
            aux = aux->prox;
        }
    }
    
}


/* A4. Implemente concatenarListas, que concatena b ao final de a sem criar novos nodos (apenas redirecione ponteiros). Trate os casos em que a ou b estejam vazias. */
void concatenarListas(ListaEnc *a, const ListaEnc *b) {
    if(a->ini == NULL){
        a->ini = b->ini;
        return;
    }

    Nodo *aux = a->ini;
    
    while(aux->prox != NULL){
        aux = aux->prox;
    }

    if(b != NULL){
        aux->prox = b->ini;
    }
    else{
        printf("b vazio \n");
    }
}


/* A5. Implemente inverterLista, que inverte a ordem dos nodos in-place, sem criar novos nodos. Use três ponteiros auxiliares para redirecionar os campos prox. */
void inverterLista(ListaEnc *lista) {
    // TODO: Escreva sua implementação aqui
}

/* A6. Implemente moverPrimeiroParaFim, que move o primeiro nodo da lista para o final sem criar ou destruir nodos. Não faça nada se a lista for vazia ou unitária. */
void moverPrimeiroParaFim(ListaEnc *lista) {
    if((lista->ini == NULL) || (lista->ini->prox == NULL)){
        return;
    }

    Nodo *aux = lista->ini;
    Nodo *novoInicio = lista->ini->prox;

    while(aux->prox != NULL){
        aux = aux->prox;
    }

    aux->prox = lista->ini;
    lista->ini = novoInicio;
    aux->prox->prox = NULL;
    
}

/* A7. Implemente inserirAntesDeCod, que insere um novo produto imediatamente antes do primeiro nodo cujo cod seja igual ao parâmetro. Se o código não existir, insira o novo produto no final da lista. */
void inserirAntesDeCod(ListaEnc *lista, Produto p, int cod) {
    // TODO: Escreva sua implementação aqui
}

/* A8. Implemente segundoMaiorPreco, que percorre a lista e retorna o segundo maior preço distinto. Assuma preços não-negativos; retorne -1.0 se não houver segundo preço distinto. */
float segundoMaiorPreco(const ListaEnc *lista) {
    // if(lista == NULL){
    //     return -2;
    // }

    // Nodo *aux = lista->ini;
    // float maior = lista->ini->dado.preco;
    // float segundoMaior = lista->ini->dado.preco;

    // while(aux != NULL){
    //     if(aux->dado.preco > maior){
    //         segundoMaior = maior;
    //         maior = aux->dado.preco;
    //     }else if(aux ->preco <)

    //     aux = aux->prox;
    // }

    // if(segundoMaior == maior){
    //     return -1;
    // }

    // return segundoMaior;
}

/* -------------------------------------------------------------------------------------
 * GRUPO B — Pilha e Fila (usando apenas o TAD)
 * ------------------------------------------------------------------------------------- */

/* B1. Implemente maiorPrecoFila, que retorna o produto de maior preco da fila sem alterar a ordem dos elementos. Use apenas operações do TAD. */
Produto maiorPrecoFila(FilaEnc *fila) {

    if(estaVaziaFila(fila)){
        Produto vazio = {0, "", 0.0f};
        return vazio;
    }

    FilaEnc aux;
    inicializaFila(&aux);

    Produto maior = fila->fim->dado;

    while(!estaVaziaFila(fila)){
        Produto produtoAtual = dequeue(fila);
        if(produtoAtual.preco > maior.preco){
            maior = produtoAtual;
        }
        enqueue(&aux, produtoAtual);
    }

    while(!estaVaziaFila(&aux)){
        enqueue(fila, dequeue(&aux));
    }
    return maior;
}

/* B2. Implemente maiorPrecoPilha, que retorna o produto de maior preco da pilha sem alterar a ordem dos elementos. Use apenas operações do TAD. */
Produto maiorPrecoPilha(PilhaEnc *pilha) {

    if(estaVaziaPilha(pilha)){
        Produto vazio = {0, "", 0.0};
        return vazio;
    }

    PilhaEnc aux;

    Produto maior = pop(pilha);
    push(pilha, maior);

    inicializaPilha(&aux);

    while(!estaVaziaPilha(pilha)){
        Produto produtoAtual = pop(pilha);
        if(produtoAtual.preco > maior.preco){
            maior = produtoAtual;
        }
        push(&aux, produtoAtual);
    }

    while(!estaVaziaPilha(&aux)){
         push(pilha ,pop(&aux));
     }

    return maior;
}

/* B3. Implemente removerDaFilaPorCod, que remove da fila o primeiro produto cujo cod seja igual ao parâmetro, preservando a ordem dos demais. Use apenas operações do TAD. */
void removerDaFilaPorCod(FilaEnc *fila, int cod) {
    FilaEnc auxFila;
    inicializaFila(&auxFila);
    bool jaRemoveu = false;

    while(!estaVaziaFila(fila)){        
        Produto produtoAtual = dequeue(fila);

        if((false == jaRemoveu)){
            if((produtoAtual.cod != cod)){
                enqueue(&auxFila, produtoAtual);
            }
            else{
                jaRemoveu = true;
                continue;
            }
        }else{
            enqueue(&auxFila, produtoAtual);
        }
        
    }
    
    while(!estaVaziaFila(&auxFila)){
        enqueue(fila, dequeue(&auxFila)); 
    }
}

/* B4. Implemente removerDaPilhaPorCod, que remove da pilha o primeiro produto (do topo para a base) cujo cod seja igual ao parâmetro, preservando a ordem dos demais. Use apenas operações do TAD. */
void removerDaPilhaPorCod(PilhaEnc *pilha, int cod) {

    PilhaEnc auxPilha;
    inicializaPilha(&auxPilha);
    bool jaRemoveu = false;

    while (!estaVaziaPilha(pilha)){
        Produto produtoAtual = pop(pilha);
        //se ja removeu, so continua empilhando
        if(true == jaRemoveu){
            push(&auxPilha, produtoAtual);
        }
        //se nao removeu ainda e nao eh o codigo de pular, empilha
        else{
            if(produtoAtual.cod != cod){
                push(&auxPilha, produtoAtual);
            }
            else{ //eh o codigo de pulhar, nao empilha e seta o removido.
                jaRemoveu = true;
                continue;
            }
        }

    }

    while(!estaVaziaPilha(&auxPilha)){
        push(pilha, pop(&auxPilha));
    }
    
}

/* B5. Implemente separarParImpar, que separa os elementos de fila em duas novas filas: pares (cod par) e impares (cod ímpar), preservando a ordem original em cada fila. A fila original é consumida. */
void separarParImpar(FilaEnc *fila, FilaEnc *pares, FilaEnc *impares) {

    while(!estaVaziaFila(fila)){
        Produto produtoAtual = dequeue(fila);

        if(0 == (produtoAtual.cod % 2)){
            enqueue(pares, produtoAtual);
        }//impares
        else{
            enqueue(impares, produtoAtual);
        }
    }

}

/* B6. Implemente somarPrecosImparesPreservando, que retorna a soma dos preco dos produtos com cod ímpar, preservando o conteúdo e a ordem da fila. Use apenas operações do TAD. */
float somarPrecosImparesPreservando(FilaEnc *fila) {

    FilaEnc auxFila;
    inicializaFila(&auxFila);
    float soma = 0;

    while(!estaVaziaFila(fila)){
        Produto produtoAtual = dequeue(fila);
        enqueue(&auxFila, produtoAtual);

        if(0 != (produtoAtual.cod % 2)){
            soma += produtoAtual.preco;
        }
    }
    
    while(!estaVaziaFila(&auxFila)){
        enqueue(fila, dequeue(&auxFila));
    }

    return soma;
}

/* B7. Implemente temConsecutivosIguais, que retorna 1 se existem dois produtos consecutivos com o mesmo cod na fila, e 0 caso contrário. A fila deve ser preservada. Use apenas operações do TAD. */
int temConsecutivosIguais(FilaEnc *fila) {
    FilaEnc auxFila;
    inicializaFila(&auxFila);
    Produto produtoAnterior = {0, "", 0.0f};
    bool primeiro = true;

    int consecutivos = 0;

    while(!estaVaziaFila(fila)){
        Produto produtoAtual = dequeue(fila);
        enqueue(&auxFila, produtoAtual);

        if((produtoAnterior.cod == produtoAtual.cod) && false == primeiro){
            consecutivos = 1;
        }
        primeiro = false;
        produtoAnterior = produtoAtual;
    }

    while(!estaVaziaFila(&auxFila)){
        enqueue(fila,  dequeue(&auxFila));
    }
    

    return consecutivos;
}

/* B8. Implemente mesmasElementos, que retorna 1 se a pilha e a fila possuem a mesma quantidade de elementos e os mesmos cod na mesma ordem (topo da pilha corresponde à frente da fila), e 0 caso contrário. Ambas devem ser preservadas. Use apenas operações do TAD. */
int mesmasElementos(PilhaEnc *pilha, FilaEnc *fila) {

    FilaEnc auxFila;
    PilhaEnc auxPilha;
    int iguais = 1; 

    inicializaFila(&auxFila);
    inicializaPilha(&auxPilha);

    while(!estaVaziaFila(fila) || !estaVaziaPilha(pilha)){
        Produto atualFila = dequeue(fila);
        Produto atualPilha = pop(pilha);

        if(!estaVaziaFila(fila)){
            enqueue(&auxFila, atualFila);
        }
        else{
            iguais = 0;
        }

        if(!estaVaziaPilha(pilha)){
            push(&auxPilha, atualPilha);
        }
        else{
            iguais = 0;
        }
        if(atualFila.cod != atualPilha.cod){
           iguais = 0;
        }


    }

    while (!estaVaziaFila(&auxFila)){ 
        enqueue(fila, dequeue(&auxFila)); 
    } 
    while (!estaVaziaPilha(&auxPilha)) {
         push(pilha, pop(&auxPilha));
    }

    return 1 && iguais;
}

/* -------------------------------------------------------------------------------------
 * GRUPO C — Árvore Binária de Pesquisa (recursiva)
 * ------------------------------------------------------------------------------------- */

/* C1. Implemente recursivamente abpTodosPares, que retorna 1 se todos os produtos possuem cod par, e 0 se algum é ímpar. Retorne 1 para árvore vazia. */
int abpTodosPares(const NodoArv *raiz) {
    int par = 1;
    if(raiz == NULL)
        return 1;

    if(0 != (raiz->dado.cod % 2))
        par = 0;

    return par && abpTodosPares(raiz->dir) && abpTodosPares(raiz->esq);
}

/* C2. Implemente recursivamente abpContarComUmFilho, que retorna a quantidade de nodos com exatamente um filho (esquerdo ou direito, mas não ambos). */
int abpContarComUmFilho(const NodoArv *raiz) {
    int cont = 0;
    if(raiz == NULL){
        return 0;
    }
    if((raiz->dir == NULL) != (raiz->esq == NULL)){
        cont = 1;
    }

    return cont + abpContarComUmFilho(raiz->dir) + abpContarComUmFilho(raiz->esq);
}

/* C3. Implemente recursivamente abpContarMenoresQue, que retorna a quantidade de produtos cujo cod é estritamente menor que x. Dica: use a propriedade da ABP para podar subárvores. */
int abpContarMenoresQue(const NodoArv *raiz, int x) {
    int cont = 0;
    if(raiz == NULL){
        return 0;
    }

    if(raiz->dado.cod < x){
        cont = 1;
        return cont + abpContarMenoresQue(raiz->dir, x) + abpContarMenoresQue(raiz->esq, x); 
    }
    else{
        return abpContarMenoresQue(raiz->esq, x);
    }

}

/* C4. Implemente recursivamente abpMaiorCod, que retorna o maior cod aproveitando a propriedade da ABP (sem percorrer toda a árvore). Assuma árvore não vazia. */
int abpMaiorCod(const NodoArv *raiz) {
    if(raiz->dir == NULL) return raiz->dado.cod;

    return abpMaiorCod(raiz->dir);
}

/* C5. Implemente recursivamente abpImprimirIntervalo, que imprime em ordem crescente todos os produtos com cod ∈ [minCod, maxCod]. Dica: use a propriedade da ABP para evitar subárvores fora do intervalo. */
void abpImprimirIntervalo(const NodoArv *raiz, int minCod, int maxCod) {
    // TODO: Escreva sua implementação aqui
}

/* C6. Implemente recursivamente abpContarMaioresQue, que retorna a quantidade de produtos cujo cod é estritamente maior que x. Dica: use a propriedade da ABP para podar subárvores. */
int abpContarMaioresQue(const NodoArv *raiz, int x) {
    // TODO: Escreva sua implementação aqui
    return 0;
}

/* C7. Implemente recursivamente abpExisteNoIntervalo, que retorna 1 se existir pelo menos um produto com cod ∈ [minCod, maxCod], e 0 caso contrário. Dica: use a propriedade da ABP para retornar antecipadamente. */
int abpExisteNoIntervalo(const NodoArv *raiz, int minCod, int maxCod) {
    // TODO: Escreva sua implementação aqui
    return 0;
}

/* C8. Implemente recursivamente abpSomaCods, que retorna a soma de todos os cod armazenados na árvore. Retorne 0 para árvore vazia. */
int abpSomaCods(const NodoArv *raiz) {
    // TODO: Escreva sua implementação aqui
    return 0;
}

/* =====================================================================================
 * 4. MAIN COM BATERIA DE TESTES
 * =====================================================================================
 */

int main() {
    printf("=====================================================================\n");
    printf("        BATERIA DE TESTES — SIMULADO ESTRUTURA DE DADOS (PARTE 2)     \n");
    printf("=====================================================================\n\n");

    /* ---------------------------------------------------------------------------------
     * GRUPO A
     * --------------------------------------------------------------------------------- */

    /* Questão A1 */
    printf("==================== QUESTÃO A1 ====================\n");
    {
        ListaEnc l; inicializaLista(&l);
        inserirFimLista(&l, criaProd(10, "A", 15.0f));
        inserirFimLista(&l, criaProd(25, "B", 89.9f));
        inserirFimLista(&l, criaProd(30, "C", 45.5f));
        
        printf("[ESPERADO]: cod:25, nome:B, preco:89.90\n");
        Produto res = maiorPreco(&l);
        printf("[OBTIDO]  : cod:%d, nome:%s, preco:%.2f\n", res.cod, res.nome, res.preco);
        liberarLista(&l);
    }
    printf("\n");

    /* Questão A2 */
    printf("==================== QUESTÃO A2 ====================\n");
    {
        ListaEnc l; inicializaLista(&l);
        inserirFimLista(&l, criaProd(1, "Prod1", 10.0f)); // Ímpar
        inserirFimLista(&l, criaProd(2, "Prod2", 20.0f)); // Par
        inserirFimLista(&l, criaProd(3, "Prod3", 30.5f)); // Ímpar
        
        printf("[ESPERADO]: Soma dos impares (10.0 + 30.5) = 40.50\n");
        float soma = somarPrecosImpares(&l);
        printf("[OBTIDO]  : Soma = %.2f\n", soma);
        liberarLista(&l);
    }
    printf("\n");

    /* Questão A3 */
    printf("==================== QUESTÃO A3 ====================\n");
    {
        ListaEnc l; inicializaLista(&l);
        inserirFimLista(&l, criaProd(1, "Barato1", 5.0f));
        inserirFimLista(&l, criaProd(2, "Barato2", 8.0f));
        inserirFimLista(&l, criaProd(3, "Caro", 50.0f));
        
        printf("[ESPERADO]: [(cod:3, r$50.00)]\n");
        removerMenoresQuePreco(&l, 10.0f);
        printf("[OBTIDO]  : "); imprimirLista(&l);
        liberarLista(&l);
    }
    printf("\n");

    /* Questão A4 */
    printf("==================== QUESTÃO A4 ====================\n");
    {
        printf("--- Teste 1: Ambas com elementos ---\n");
        ListaEnc a1, b1; inicializaLista(&a1); inicializaLista(&b1);
        inserirFimLista(&a1, criaProd(1, "A1", 10.0f));
        inserirFimLista(&b1, criaProd(2, "B1", 20.0f));
        printf("[ESPERADO]: [(cod:1, r$10.00) -> (cod:2, r$20.00)]\n");
        concatenarListas(&a1, &b1);
        printf("[OBTIDO]  : "); imprimirLista(&a1);
        liberarLista(&a1);

        printf("--- Teste 2: Lista 'a' VAZIA e 'b' com elementos ---\n");
        ListaEnc a2, b2; inicializaLista(&a2); inicializaLista(&b2);
        inserirFimLista(&b2, criaProd(5, "B_Unico", 50.0f));
        printf("[ESPERADO]: [(cod:5, r$50.00)]\n");
        concatenarListas(&a2, &b2);
        printf("[OBTIDO]  : "); imprimirLista(&a2);
        liberarLista(&a2);

        printf("--- Teste 3: Lista 'a' com elementos e 'b' VAZIA ---\n");
        ListaEnc a3, b3; inicializaLista(&a3); inicializaLista(&b3);
        inserirFimLista(&a3, criaProd(10, "A_Unico", 100.0f));
        printf("[ESPERADO]: [(cod:10, r$100.00)]\n");
        concatenarListas(&a3, &b3);
        printf("[OBTIDO]  : "); imprimirLista(&a3);
        liberarLista(&a3);
    }
    printf("\n");

    /* Questão A5 */
    printf("==================== QUESTÃO A5 ====================\n");
    {
        ListaEnc l; inicializaLista(&l);
        inserirFimLista(&l, criaProd(1, "P1", 10.0f));
        inserirFimLista(&l, criaProd(2, "P2", 20.0f));
        inserirFimLista(&l, criaProd(3, "P3", 30.0f));
        
        printf("[ESPERADO]: [(cod:3, r$30.00) -> (cod:2, r$20.00) -> (cod:1, r$10.00)]\n");
        inverterLista(&l);
        printf("[OBTIDO]  : "); imprimirLista(&l);
        liberarLista(&l);
    }
    printf("\n");

    /* Questão A6 */
    printf("==================== QUESTÃO A6 ====================\n");
    {
        ListaEnc l; inicializaLista(&l);
        inserirFimLista(&l, criaProd(1, "Primeiro", 10.0f));
        inserirFimLista(&l, criaProd(2, "Segundo", 20.0f));
        inserirFimLista(&l, criaProd(3, "Terceiro", 30.0f));
        
        printf("[ESPERADO]: [(cod:2, r$20.00) -> (cod:3, r$30.00) -> (cod:1, r$10.00)]\n");
        moverPrimeiroParaFim(&l);
        printf("[OBTIDO]  : "); imprimirLista(&l);
        liberarLista(&l);
    }
    printf("\n");

    /* Questão A7 */
    printf("==================== QUESTÃO A7 ====================\n");
    {
        ListaEnc l; inicializaLista(&l);
        inserirFimLista(&l, criaProd(10, "P10", 10.0f));
        inserirFimLista(&l, criaProd(20, "P20", 20.0f));
        
        printf("[ESPERADO]: [(cod:10, r$10.00) -> (cod:15, r$15.00) -> (cod:20, r$20.00)]\n");
        inserirAntesDeCod(&l, criaProd(15, "P15", 15.0f), 20);
        printf("[OBTIDO]  : "); imprimirLista(&l);
        liberarLista(&l);
    }
    printf("\n");

    /* Questão A8 */
    printf("==================== QUESTÃO A8 ====================\n");
    {
        ListaEnc l; inicializaLista(&l);
        inserirFimLista(&l, criaProd(1, "P1", 100.0f));
        inserirFimLista(&l, criaProd(2, "P2", 100.0f));
        inserirFimLista(&l, criaProd(3, "P3", 80.0f));
        inserirFimLista(&l, criaProd(4, "P4", 50.0f));
        
        printf("[ESPERADO]: Segundo maior preco distinto = 80.00\n");
        float seg = segundoMaiorPreco(&l);
        printf("[OBTIDO]  : Segundo maior = %.2f\n", seg);
        liberarLista(&l);
    }
    printf("\n");

    /* ---------------------------------------------------------------------------------
     * GRUPO B
     * --------------------------------------------------------------------------------- */

    /* Questão B1 */
    printf("==================== QUESTÃO B1 ====================\n");
    {
        FilaEnc f; inicializaFila(&f);
        enqueue(&f, criaProd(1, "F1", 10.0f));
        enqueue(&f, criaProd(2, "F2", 95.0f));
        enqueue(&f, criaProd(3, "F3", 40.0f));
        
        printf("[ESPERADO]: Maior preco = 95.00 (Fila preservada)\n");
        Produto m = maiorPrecoFila(&f);
        printf("[OBTIDO]  : Maior preco = %.2f | ", m.preco);
        imprimirFila(&f);
        liberarFila(&f);
    }
    printf("\n");

    /* Questão B2 */
    printf("==================== QUESTÃO B2 ====================\n");
    {
        PilhaEnc p; inicializaPilha(&p);
        push(&p, criaProd(1, "P1", 30.0f));
        push(&p, criaProd(2, "P2", 150.0f));
        push(&p, criaProd(3, "P3", 20.0f));
        
        printf("[ESPERADO]: Maior preco = 150.00 (Pilha preservada)\n");
        Produto m = maiorPrecoPilha(&p);
        printf("[OBTIDO]  : Maior preco = %.2f | ", m.preco);
        imprimirPilha(&p);
        liberarPilha(&p);
    }
    printf("\n");

    /* Questão B3 */
    printf("==================== QUESTÃO B3 ====================\n");
    {
        FilaEnc f; inicializaFila(&f);
        enqueue(&f, criaProd(10, "F10", 10.0f));
        enqueue(&f, criaProd(20, "F20", 20.0f));
        enqueue(&f, criaProd(30, "F30", 30.0f));
        
        printf("[ESPERADO]: Removendo cod 20 -> FRENTE -> [ (cod:10) (cod:30) ]\n");
        removerDaFilaPorCod(&f, 20);
        printf("[OBTIDO]  : "); imprimirFila(&f);
        liberarFila(&f);
    }
    printf("\n");

    /* Questão B4 */
    printf("==================== QUESTÃO B4 ====================\n");
    {
        PilhaEnc p; inicializaPilha(&p);
        push(&p, criaProd(10, "P10", 10.0f));
        push(&p, criaProd(20, "P20", 20.0f));
        push(&p, criaProd(30, "P30", 30.0f));
        
        printf("[ESPERADO]: Removendo cod 20 -> TOPO -> [ (cod:30) (cod:10) ]\n");
        removerDaPilhaPorCod(&p, 20);
        printf("[OBTIDO]  : "); imprimirPilha(&p);
        liberarPilha(&p);
    }
    printf("\n");

    /* Questão B5 */
    printf("==================== QUESTÃO B5 ====================\n");
    {
        FilaEnc f, pares, impares;
        inicializaFila(&f); inicializaFila(&pares); inicializaFila(&impares);
        enqueue(&f, criaProd(1, "I1", 10.0f));
        enqueue(&f, criaProd(2, "P1", 20.0f));
        enqueue(&f, criaProd(3, "I2", 30.0f));
        enqueue(&f, criaProd(4, "P2", 40.0f));
        
        printf("[ESPERADO]: Pares = (cod:2, cod:4) | Impares = (cod:1, cod:3)\n");
        separarParImpar(&f, &pares, &impares);
        printf("[OBTIDO]  : Pares   : "); imprimirFila(&pares);
        printf("            Impares : "); imprimirFila(&impares);
        liberarFila(&f); liberarFila(&pares); liberarFila(&impares);
    }
    printf("\n");

    /* Questão B6 */
    printf("==================== QUESTÃO B6 ====================\n");
    {
        FilaEnc f; inicializaFila(&f);
        enqueue(&f, criaProd(1, "F1", 10.0f)); // Ímpar
        enqueue(&f, criaProd(2, "F2", 20.0f)); // Par
        enqueue(&f, criaProd(5, "F5", 15.0f)); // Ímpar
        
        printf("[ESPERADO]: Soma impares = 25.00 (Fila preservada)\n");
        float s = somarPrecosImparesPreservando(&f);
        printf("[OBTIDO]  : Soma = %.2f | ", s); imprimirFila(&f);
        liberarFila(&f);
    }
    printf("\n");

    /* Questão B7 */
    printf("==================== QUESTÃO B7 ====================\n");
    {
        FilaEnc f; inicializaFila(&f);
        enqueue(&f, criaProd(10, "A", 1.0f));
        enqueue(&f, criaProd(20, "B", 1.0f));
        enqueue(&f, criaProd(20, "C", 1.0f)); // Consecutivo igual!
        
        printf("[ESPERADO]: Consecutivos iguais = 1\n");
        int res = temConsecutivosIguais(&f);
        printf("[OBTIDO]  : Resultado = %d\n", res);
        liberarFila(&f);
    }
    printf("\n");

    /* Questão B8 */
    printf("==================== QUESTÃO B8 ====================\n");
    {
        PilhaEnc p; inicializaPilha(&p);
        FilaEnc f; inicializaFila(&f);
        
        /* Topo da pilha = 30, Frente da fila = 30 */
        push(&p, criaProd(10, "A", 1.0f));
        push(&p, criaProd(20, "B", 1.0f));
        push(&p, criaProd(30, "C", 1.0f)); // Topo
        
        enqueue(&f, criaProd(30, "C", 1.0f)); // Frente
        enqueue(&f, criaProd(20, "B", 1.0f));
        enqueue(&f, criaProd(10, "A", 1.0f));
        
        printf("[ESPERADO]: Mesmos elementos = 1\n");
        int res = mesmasElementos(&p, &f);
        printf("[OBTIDO]  : Resultado = %d\n", res);
        liberarPilha(&p); liberarFila(&f);
    }
    printf("\n");

    /* ---------------------------------------------------------------------------------
     * GRUPO C
     * --------------------------------------------------------------------------------- */

    /* Questão C1 */
    printf("==================== QUESTÃO C1 ====================\n");
    {
        NodoArv *raiz = NULL;
        raiz = abpInserir(raiz, criaProd(50, "P50", 1.0f));
        raiz = abpInserir(raiz, criaProd(20, "P20", 1.0f));
        raiz = abpInserir(raiz, criaProd(70, "P70", 1.0f));
        
        printf("[ESPERADO]: Todos pares = 1\n");
        int res = abpTodosPares(raiz);
        printf("[OBTIDO]  : Resultado = %d\n", res);
        abpDestruir(raiz);
    }
    printf("\n");

    /* Questão C2 */
    printf("==================== QUESTÃO C2 ====================\n");
    {
        NodoArv *raiz = NULL;
        raiz = abpInserir(raiz, criaProd(50, "P50", 1.0f));
        raiz = abpInserir(raiz, criaProd(30, "P30", 1.0f));
        raiz = abpInserir(raiz, criaProd(20, "P20", 1.0f)); // 30 tem apenas 1 filho (20)
        
        printf("[ESPERADO]: Nodos com 1 filho = 1\n");
        int res = abpContarComUmFilho(raiz);
        printf("[OBTIDO]  : Resultado = %d\n", res);
        abpDestruir(raiz);
    }
    printf("\n");

    /* Questão C3 */
    printf("==================== QUESTÃO C3 ====================\n");
    {
        NodoArv *raiz = NULL;
        raiz = abpInserir(raiz, criaProd(50, "P50", 1.0f));
        raiz = abpInserir(raiz, criaProd(30, "P30", 1.0f));
        raiz = abpInserir(raiz, criaProd(70, "P70", 1.0f));
        raiz = abpInserir(raiz, criaProd(20, "P20", 1.0f));
        
        printf("[ESPERADO]: Menores que 40 = 2 (20 e 30)\n");
        int res = abpContarMenoresQue(raiz, 40);
        printf("[OBTIDO]  : Resultado = %d\n", res);
        abpDestruir(raiz);
    }
    printf("\n");

    /* Questão C4 */
    printf("==================== QUESTÃO C4 ====================\n");
    {
        NodoArv *raiz = NULL;
        raiz = abpInserir(raiz, criaProd(50, "P50", 1.0f));
        raiz = abpInserir(raiz, criaProd(30, "P30", 1.0f));
        raiz = abpInserir(raiz, criaProd(85, "P85", 1.0f));
        
        printf("[ESPERADO]: Maior cod = 85\n");
        int res = abpMaiorCod(raiz);
        printf("[OBTIDO]  : Maior cod = %d\n", res);
        abpDestruir(raiz);
    }
    printf("\n");

    /* Questão C5 */
    printf("==================== QUESTÃO C5 ====================\n");
    {
        NodoArv *raiz = NULL;
        raiz = abpInserir(raiz, criaProd(50, "P50", 1.0f));
        raiz = abpInserir(raiz, criaProd(20, "P20", 1.0f));
        raiz = abpInserir(raiz, criaProd(35, "P35", 1.0f));
        raiz = abpInserir(raiz, criaProd(70, "P70", 1.0f));
        
        printf("[ESPERADO]: Intervalo [30, 60] -> (cod:35) (cod:50)\n");
        printf("[OBTIDO]  : ");
        abpImprimirIntervalo(raiz, 30, 60);
        printf("\n");
        abpDestruir(raiz);
    }
    printf("\n");

    /* Questão C6 */
    printf("==================== QUESTÃO C6 ====================\n");
    {
        NodoArv *raiz = NULL;
        raiz = abpInserir(raiz, criaProd(50, "P50", 1.0f));
        raiz = abpInserir(raiz, criaProd(30, "P30", 1.0f));
        raiz = abpInserir(raiz, criaProd(70, "P70", 1.0f));
        raiz = abpInserir(raiz, criaProd(80, "P80", 1.0f));
        
        printf("[ESPERADO]: Maiores que 40 = 3 (50, 70, 80)\n");
        int res = abpContarMaioresQue(raiz, 40);
        printf("[OBTIDO]  : Resultado = %d\n", res);
        abpDestruir(raiz);
    }
    printf("\n");

    /* Questão C7 */
    printf("==================== QUESTÃO C7 ====================\n");
    {
        NodoArv *raiz = NULL;
        raiz = abpInserir(raiz, criaProd(50, "P50", 1.0f));
        raiz = abpInserir(raiz, criaProd(20, "P20", 1.0f));
        raiz = abpInserir(raiz, criaProd(70, "P70", 1.0f));
        
        printf("[ESPERADO]: Existe no intervalo [15, 25] = 1 (cod:20)\n");
        int res = abpExisteNoIntervalo(raiz, 15, 25);
        printf("[OBTIDO]  : Resultado = %d\n", res);
        abpDestruir(raiz);
    }
    printf("\n");

    /* Questão C8 */
    printf("==================== QUESTÃO C8 ====================\n");
    {
        NodoArv *raiz = NULL;
        raiz = abpInserir(raiz, criaProd(10, "P10", 1.0f));
        raiz = abpInserir(raiz, criaProd(20, "P20", 1.0f));
        raiz = abpInserir(raiz, criaProd(30, "P30", 1.0f));
        
        printf("[ESPERADO]: Soma dos cods (10 + 20 + 30) = 60\n");
        int res = abpSomaCods(raiz);
        printf("[OBTIDO]  : Soma = %d\n", res);
        abpDestruir(raiz);
    }
    printf("\n");

    printf("=====================================================================\n");
    printf("                    FIM DA BATERIA DE TESTES                         \n");
    printf("=====================================================================\n");

    return 0;
}