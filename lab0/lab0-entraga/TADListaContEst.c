//#include "q2.h"
#include "TADListaContEst.h"



// Implementações de funções
void inicializar(ListaContEst *l) {
    l->tamanho = 0;
}

int tamanho(const ListaContEst *l) {
    return l->tamanho;
}

Produto acessar(const ListaContEst *l, int pos) {
    Produto pAux;
    if (pos >= l->tamanho || pos < 0) // posição inválida
        pAux.cod = -1;
    else
        pAux = l->dados[pos];

    return pAux;
}

int inserir(ListaContEst *l, Produto novo, int pos) {
    int i;

    if (l->tamanho == CAPACIDADE) return 0; // lista cheia
    if (pos > l->tamanho || pos < 0) return 0; // posição inválida

    for (i = l->tamanho; i > pos; i--) // abre espaço, empurrando para a direita
        l->dados[i] = l->dados[i - 1];

    l->dados[pos] = novo;
    l->tamanho++;
    return 1;
}

int remover(ListaContEst *l, int pos) {
    int i;

    if (pos >= l->tamanho || pos < 0) return 0; // posição inválida

    for (i = pos; i < l->tamanho - 1; i++) // puxa elementos seguintes para a esquerda
        l->dados[i] = l->dados[i + 1];

    l->tamanho--;
    return 1;
}

int buscar(const ListaContEst *l, int cod) {
    int i;

    for (i = 0; i < l->tamanho; i++) {
        if (l->dados[i].cod == cod) {
            return i; // posição onde o produto foi encontrado
        }
    }

    return -1; // não encontrado
}

void destruir(ListaContEst *l) {
    l->tamanho = 0;
}

Produto criarProduto(int cod, const char* nome, float preco) {
    Produto produto;
    produto.cod = cod;
    produto.preco = preco;
    strcpy(produto.nome, nome);

    return produto;
}

// Preenche a lista com produtos pré-definidos
void preencherLista(ListaContEst *l) {
    inserir(l, criarProduto(15, "lapis", 3.50), 0);
    inserir(l, criarProduto(7, "cacetinho", 1.02), 1);
    inserir(l, criarProduto(22, "refrigerante", 8.60), 2);
    inserir(l, criarProduto(9, "mochila", 89.99), 3);
    inserir(l, criarProduto(18, "camiseta", 30.10), 4);
    inserir(l, criarProduto(96, "celular", 1238.97), 5);
    inserir(l, criarProduto(53, "garrafa", 25.40), 6);
    inserir(l, criarProduto(44, "presunto", 9.45), 7);
    inserir(l, criarProduto(36, "tesoura", 15.99), 8);
    inserir(l, criarProduto(21, "caderno", 11.20), 9);
    inserir(l, criarProduto(80, "travesseiro", 67.80), 10);
}


/*1) void filtrarProdutosPorPreco:
Esta função recebe duas listas de produtos, l1 e l2 e um float preco. l2 deve ser vazia.
A função deve preencher l2 com cópias apenas dos produtos de l1 cujo preço é menor ou
igual a preco. l1 deve permanecer inalterada.*/

// Funções a implementar
void filtrarProdutosPorPreco(const ListaContEst* l1, ListaContEst *l2, float preco) {
    
    for(int i = 0; i <l1->tamanho; i++){ 
        if (l1->dados[i].preco <= preco){
            inserir(l2, l1->dados[i], l2->tamanho);
        }
    }


}

/*2) void imprimirEEsvaziarLista:
Esta função recebe uma lista de produtos l e deve imprimir os produtos de l em ordem
decrescente de preço. Além disso, cada produto impresso deve ser removido da lista, de tal forma
que ela termine a função vazia. Devem ser impressos o código, nome e preço de cada produto.
Além disso, você deve estimar a complexidade das funções implementadas, anotandoa como comentário junto aos protótipos no arquivo .h.*/

void imprimirEEsvaziarLista(ListaContEst *l) {
    while (l->tamanho > 0) {
        int maxIdx = 0;
        for (int i = 1; i < l->tamanho; i++) {
            if (l->dados[i].preco > l->dados[maxIdx].preco)
                maxIdx = i;
        }
        printf("Cod: %d, Nome: %s, Preco: %.2f\n", l->dados[maxIdx].cod, l->dados[maxIdx].nome, l->dados[maxIdx].preco);
        remover(l, maxIdx);
    }
}


// Função main
int main() {
    // Inicializa as listas
    ListaContEst l1Var, l2Var;
    ListaContEst *l1 = &l1Var, *l2 = &l2Var;
    inicializar(l1);
    inicializar(l2);
    preencherLista(l1);

    printf("Tamanho de l1: %d\n", l1->tamanho);
    printf("Tamanho de l2: %d\n\n", l2->tamanho);

    // Preenche l2 com os produtos filtrados de l1
    filtrarProdutosPorPreco(l1, l2, 30.00);
    printf("Tamanho de l2: %d\n\n", l2->tamanho);

    printf("Produtos de ate R$30.00:\n");
    imprimirEEsvaziarLista(l2);

    printf("Tamanho de l1: %d\n", l1->tamanho);
    printf("Tamanho de l2: %d\n\n", l2->tamanho);

    return 0;
}