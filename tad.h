#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//representação da ficha de um paciente
typedef struct Ficha
{
    char nome[201];
    int idade;
    int preferencial;
    //"1" para sim e "0" para não
    int id;
} Ficha;

//representação de um nó da fila
typedef struct No
{
    Ficha ficha;
    struct No *proximo;
}No;

//representação de uma fila
typedef struct Fila
{
    No *frente;
    No *tras;
} Fila;

//inicializa as filas
void inicializa(Fila *comum, Fila *pref);

//verifica se a fila esta vazia
int estaVazia(Fila *fila);

//enfileirar novo paciente
void enfileirar(Fila *fila, Ficha *ficha);

//desenfilera o proximo paciente e retorna ele
No* chamarProximo(Fila *fila);

/*
chamada alternada entre comum e preferencial
chama 2 comuns e 1 preferencial
(retorna o paciente chamado)
*/
No* chamadaRegular(Fila *comum, Fila *pref, int *cont);


//imprimir os valores na lista
void imprimir(Fila *fila);

//faz a busca sequencial pra saber se os proximos 10 tem algum preferencial
void buscaSeq(Fila *fila, int tamanho);

//cria a id para realizar a busca binaria do nome do paciente
unsigned long hashMultiplicacao(char *nome);

//faz o tamanho da fila
int filaTamanho(Fila *fila);

//realiza a busca binaria
void buscaBin(Fila *fila, char *nome);

// Função para converter a fila em um array
void filaParaArray(Fila *fila, Ficha *array);

// Função de comparação para o QuickSort baseado na idade das fichas
int compararFichas(const void *a, const void *b);

// Função para trocar fichas
void trocarFichas(Ficha *a, Ficha *b);

// Função para particionar o array
int particionarArray(Ficha *array, int baixo, int alto);

// Função para ordenar um array de fichas usando o QuickSort
void quicksortArray(Ficha *array, int baixo, int alto);

// Função para imprimir o array de fichas ordenado
void imprimirArray(Ficha *array, int tamanho);

// Função para ordenar o array de fichas usando o Bubble Sort
void bubblesortArray(Ficha *array, int tamanho);

// Função para realizar o merge de duas metades ordenadas do array
void merge(Ficha *array, int esquerda, int meio, int direita);

// Função para realizar o Merge Sort recursivamente
void mergeSort(Ficha *array, int esquerda, int direita);