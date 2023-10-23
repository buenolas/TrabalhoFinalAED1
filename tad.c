#include <stdio.h>
#include <stdlib.h>
#include "tad.h"

//inicializa a fila
void inicializa(Fila *comum, Fila *pref) {
    comum->frente = (No*)malloc(sizeof(No));
    if (comum->frente == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    comum->frente->proximo = NULL;
    comum->tras = comum->frente;

    pref->frente = (No*)malloc(sizeof(No));
    if (pref->frente == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    pref->frente->proximo = NULL;
    pref->tras = pref->frente;
}


int estaVazia(Fila *fila)
{
    return (fila->frente==fila->tras);
}

//enfileirar novo paciente
void enfileirar(Fila *fila, Ficha *ficha)
{
   No *aux;
    if (estaVazia(fila))
    {
        fila->frente->proximo=(No*)malloc(sizeof(No));
        fila->tras=fila->frente->proximo;
        strcpy(fila->frente->proximo->ficha.nome, ficha->nome);
        fila->frente->proximo->ficha.idade=ficha->idade;
        fila->frente->proximo->ficha.id = ficha->id;
        fila->frente->proximo->ficha.preferencial=ficha->preferencial;
        fila->frente->proximo->proximo=NULL;
        return;
    }
    aux=fila->frente;
    while (1)
    {
        if (aux->proximo==NULL)
        {
            aux->proximo=(No*)malloc(sizeof(No));
            break;
        }
        else
        {
            aux=aux->proximo;
        }
    }
    fila->tras=aux->proximo;
    strcpy(aux->proximo->ficha.nome, ficha->nome);
    aux->proximo->ficha.idade=ficha->idade;
    aux->proximo->ficha.id = ficha->id;
    aux->proximo->ficha.preferencial=ficha->preferencial;
    aux->proximo->proximo=NULL;
}

//desenfilera o proximo paciente e retorna ele
No* chamarProximo(Fila *fila)
{
    No *aux;
    if (estaVazia(fila))
    {
        printf("Erro: a fila está vazia.\n");
        return NULL;
    }
    if (fila->frente->proximo->proximo==NULL)
    {
        aux=fila->frente->proximo;
        fila->frente=NULL;
        fila->tras=fila->frente;
        return aux;
    }
    else
    {
        aux=fila->frente->proximo;
        fila->frente->proximo=fila->frente->proximo->proximo;
        return aux;
    }
}

/*
chamada alternada entre comum e preferencial
chama 2 comuns e 1 preferencial
(retorna o paciente chamado)
*/
No* chamadaRegular(Fila *comum, Fila *pref, int *cont)
{   No *aux;
    if(*cont%3==0)
    {
        if (estaVazia(pref))
        {
            if (estaVazia(comum))
            {
                printf("As filas estão vazias.\n");
                *cont=1;
                return NULL;
            }
            printf("A fila preferencial está vazia. Chamando proximo!\n");
            *cont++;
            return chamadaRegular(comum, pref, cont);
        }
        if (pref->frente->proximo->proximo == NULL)
        {
            aux=pref->frente->proximo;
            pref->frente=NULL;
            pref->tras=pref->frente;
            return aux;
        }
        else
        {
            aux=pref->frente->proximo;
            pref->frente->proximo=pref->frente->proximo->proximo;
            return aux;
        }
    }
    else
    {
        if (estaVazia(comum))
        {
            if (estaVazia(pref))
            {
                printf("As filas estão vazias.\n");
                *cont=1;
                return NULL;
            }
            printf("A fila comum está vazia. Chamando proximo!\n");
            *cont++;
            return chamadaRegular(comum, pref, cont);
        }
        if (comum->frente->proximo->proximo == NULL)
        {
            aux=comum->frente->proximo;
            comum->frente=NULL;
            comum->tras=comum->frente;
            return aux;
        }
        else
        {
            aux=comum->frente->proximo;
            comum->frente->proximo=comum->frente->proximo->proximo;
            return aux;
        }
    }
}

//imprimir os valores na lista
void imprimir(Fila *fila) {
    No *aux = fila->frente->proximo;
    
    while (aux != NULL) {
        printf("Nome: %s\n", aux->ficha.nome);
        printf("Idade: %d\n", aux->ficha.idade);
        if (aux->ficha.preferencial == 1) {
            printf("Tipo de atendimento: Preferencial\n");
        } else {
            printf("Tipo de atendimento: Comum\n");
        }
        printf("-------------------------\n");
        
        aux = aux->proximo; // Mova para o próximo nó
    }
    
    if (estaVazia(fila)) {
        printf("A fila está vazia.\n");
    }
}

void buscaSeq(Fila *fila, int tamanho){ //realiza a busca sequencial
    No *aux = fila->frente->proximo;

    Ficha *fichasArray = (Ficha *)malloc(sizeof(Ficha) * filaTamanho(fila));
    filaParaArray(fila, fichasArray);

    int i=0;
    if(estaVazia(fila)){ // verifica se a fila ta vazia
        printf("A fila esta vazia\n");
        return;
    }
    while(aux!=NULL || i == 9){ // faz um loop para verificar a idade pra ver se tem algum >=60 anos
        if(aux->ficha.idade >= 60){
            if(tamanho < 9){
                bubblesortArray(fichasArray, tamanho);
            }
            else{
                bubblesortArray(fichasArray, 9);
            }
            return;
        }
        i++;
        aux = aux->proximo; // incrementa para continuar a procura
    }
}

unsigned long hashMultiplicacao(char *nome) { // função para criar um int id que corresponde ao nome do paciente para busca binaria
    unsigned long hash = 5381; // Valor inicial do hash
    int c;

    while ((c = *nome++) != '\0') {
        hash = ((hash << 5) + hash) + c; // Fórmula de hash de multiplicação
    }

    return hash; //retorna um id unico para cada nome para poder realizar a busca
}

// realiza a busca binaria a partir de um id e retorna o paciente
void buscaBin(Fila *fila, char *nome) {
    No *aux = fila->frente->proximo;

    Ficha *fichasArray = (Ficha *)malloc(sizeof(Ficha) * filaTamanho(fila));
    filaParaArray(fila, fichasArray);
    
    quicksortArray(fichasArray, 0, filaTamanho(fila) - 1);

    int id = hashMultiplicacao(nome);
    int esq = 0;
    int dir = filaTamanho(fila) - 1;
    int i;

    if (estaVazia(fila)) {
        printf("A fila está vazia\n");
    }

    do {
        i = (esq + dir) / 2;
        if (id > fichasArray[i].id)
            esq = i + 1;
        else
            dir = i - 1;

    } while (id != fichasArray[i].id && esq <= dir);

    if (id == fichasArray[i].id) {
        printf("-----------------------------------------\n");
        printf("Nome: %s\nIdade: %d\nPreferencial: %d (1 para sim e 0 para nao)\n", fichasArray[i].nome, fichasArray[i].idade, fichasArray[i].preferencial);
    } else {
        printf("Paciente nao encontrado\n");
    }

    free(fichasArray);
}

//tamanho da lista
int filaTamanho(Fila *fila) {
    int tamanho = 0;
    No *aux = fila->frente->proximo;
    while (aux != NULL) {
        tamanho++;
        aux = aux->proximo;
    }
    return tamanho;
}

// Função para converter a fila em um array
void filaParaArray(Fila *fila, Ficha *array) {
    int i = 0;
    No *aux = fila->frente->proximo;
    while (aux != NULL) {
        array[i++] = aux->ficha;
        aux = aux->proximo;
    }
}

// Função de comparação para o QuickSort baseado no id das fichas
int compararFichas(const void *a, const void *b) {
    Ficha *fichaA = (Ficha *)a;
    Ficha *fichaB = (Ficha *)b;

    return fichaB->id - fichaA->id;
}

// Função para trocar fichas
void trocarFichas(Ficha *a, Ficha *b) {
    Ficha temp = *a;
    *a = *b;
    *b = temp;
}

// Função para particionar o array
int particionarArray(Ficha *array, int baixo, int alto) {
    Ficha pivot = array[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (compararFichas(&array[j], &pivot) >= 0) {
            i++;
            compararFichas(&array[i], &array[j]);
        }
    }
    compararFichas(&array[i + 1], &array[alto]);
    return (i + 1);
}

// Função para ordenar um array de fichas usando o QuickSort
void quicksortArray(Ficha *array, int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionarArray(array, baixo, alto);

        quicksortArray(array, baixo, pi - 1);
        quicksortArray(array, pi + 1, alto);
    }
}

// Função para imprimir o array de fichas ordenado
void imprimirArray(Ficha *array, int tamanho) {
    printf("Fila ordenada pela idade:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s\n", array[i].nome);
        printf("Idade: %d\n", array[i].idade);
        printf("ID: %d\n", array[i].id);
        if (array[i].preferencial == 1) {
            printf("Tipo de atendimento: Preferencial\n");
        } else {
            printf("Tipo de atendimento: Comum\n");
        }
        printf("-------------------------\n");
    }
}

// Função para ordenar o array de fichas usando o Bubble Sort
void bubblesortArray(Ficha *array, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (array[j].idade < array[j + 1].idade) {
                trocarFichas(&array[j], &array[j + 1]);
            }
        }
    }
}
// Função para realizar o merge de duas metades ordenadas do array
void merge(Ficha *array, int esquerda, int meio, int direita) {
    int tamanhoEsquerda = meio - esquerda + 1;
    int tamanhoDireita = direita - meio;

    Ficha *tempEsquerda = (Ficha *)malloc(tamanhoEsquerda * sizeof(Ficha));
    Ficha *tempDireita = (Ficha *)malloc(tamanhoDireita * sizeof(Ficha));

    for (int i = 0; i < tamanhoEsquerda; i++) {
        tempEsquerda[i] = array[esquerda + i];
    }
    for (int j = 0; j < tamanhoDireita; j++) {
        tempDireita[j] = array[meio + 1 + j];
    }

    int indiceEsquerda = 0;
    int indiceDireita = 0;
    int indiceMerged = esquerda;

    while (indiceEsquerda < tamanhoEsquerda && indiceDireita < tamanhoDireita) {
        if (tempEsquerda[indiceEsquerda].idade >= tempDireita[indiceDireita].idade) {
            array[indiceMerged] = tempEsquerda[indiceEsquerda];
            indiceEsquerda++;
        } else {
            array[indiceMerged] = tempDireita[indiceDireita];
            indiceDireita++;
        }
        indiceMerged++;
    }

    while (indiceEsquerda < tamanhoEsquerda) {
        array[indiceMerged] = tempEsquerda[indiceEsquerda];
        indiceEsquerda++;
        indiceMerged++;
    }

    while (indiceDireita < tamanhoDireita) {
        array[indiceMerged] = tempDireita[indiceDireita];
        indiceDireita++;
        indiceMerged++;
    }

    free(tempEsquerda);
    free(tempDireita);
}

// Função para realizar o Merge Sort recursivamente
void mergeSort(Ficha *array, int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;

        mergeSort(array, esquerda, meio);
        mergeSort(array, meio + 1, direita);

        merge(array, esquerda, meio, direita);
    }
}