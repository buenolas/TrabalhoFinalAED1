#include <stdio.h>
#include <stdlib.h>
#include "tad.h"
int main()
{
    int cont, n, tamanhoComum, tamanhoPref;
    //filas comum e preferencial
    Fila comum, pref;
    Ficha aux, fichasComum[0], fichasPref[0];
    No *retorno;
    //setup da variavel de controle da chamada regular
    cont=1;

    inicializa(&comum, &pref);
    
    while (1)
    {
        printf("-------------------------------------------------\n");
        printf("Menu:\n1 - Cadastrar paciente na fila\n2 - Chamar proximo\n3 - Mostrar fila\n4 - Buscar paciente\n5 - Para ordenar a fila\n0 - sair\n");
        printf("-------------------------------------------------\n");
        scanf("%d", &n);
        // if(n > 6 || n < 0){
        //     while(n>6 || n<0){
        //         printf("Entrada invalida! Digite novamente:\n");
        //         scanf("%d", &n);
        //     }
        // }
        getchar();
        if (n==1)
        {
            printf("O atendimento e preferencial?\n1 - sim\n2 - nao\n");
            scanf("%d%*c", &n);
        //     if(n > 2 || n < 1){
        //         while(n>2 || n<1){
        //             printf("Entrada invalida! Digite novamente:\n");
        //             scanf("%d", &n);
        //     }
        // }
            //getchar();
            
            if (n==1)
            {
                aux.preferencial=1;
            }
            else
            {
                aux.preferencial=0;
            }
            n=1;
            printf("Digite o nome do paciente:(max. 200 caracteres)\n");
            scanf("%[^\n]", aux.nome);
            
            printf("Digite a idade do paciente:\n");
            scanf("%d", &aux.idade);
            
            aux.id = hashMultiplicacao(aux.nome);
            if (aux.preferencial==1)
            {
                enfileirar(&pref, &aux);
            }
            else
            {
                enfileirar(&comum, &aux);
                buscaSeq(&comum, tamanhoComum);
            }
        }
        else if (n==2)
        {
            printf("De qual fila voce deseja chamar o proximo?\n1 - Preferencial\n2 - Comum\n");
            scanf("%d", &n);
        //     if(n > 2 || n < 1){
        //         while(n>2 || n<1){
        //             printf("Entrada invalida! Digite novamente:\n");
        //             scanf("%d", &n);
        //     }
        // }
            getchar();
            if(n==1)
            {
                retorno=chamarProximo(&pref);
                if (retorno!=NULL)
                {
                    printf("Proximo\nNome: %s\nIdade: %d\n", retorno->ficha.nome, retorno->ficha.idade);
                }                
            }
            else
            {
                retorno=chamarProximo(&comum);
                if (retorno!=NULL)
                {
                    printf("Proximo\nNome: %s\nIdade: %d\n", retorno->ficha.nome, retorno->ficha.idade);
                }
            }
            n=2;
            free(retorno);
        }
        else if (n==3)
        {
            printf("Qual fila deseja vizualizar?\n1 - Comum\n2 - Preferencial\n3 - Ambas\n");
            scanf("%d", &n);
        //     if(n > 3 || n < 1){
        //         while(n>3 || n<1){
        //             printf("Entrada invalida! Digite novamente:\n");
        //             scanf("%d", &n);
        //     }
        // }
            if (n==1)
            {
                imprimir(&comum);
            }
            if (n==2)
            {
                imprimir(&pref);
            }
            if (n==3)
            {
                printf("------------------------------------------\n");
                printf("Fila comum:\n");
                imprimir(&comum);
                printf("------------------------------------------\n");
                printf("Fila preferencial:\n");
                imprimir(&pref);
            }
        }
        else if(n==4){ // busca o paciente

            char nome[201];
            printf("Digite o nome do paciente que deseja buscar:\n");
            scanf("%[^\n]", nome);
            
            int verif; //armazena valor pra distinguir qual fila
            printf("Digite 1 se o paciente for preferencial e 0 caso contrario\n");
            scanf("%d", &verif);

            // if(verif>1 || verif<0){
            //     while(verif>1 || verif<0){
            //         printf("Entrada invalida! Digite novamente:\n");
            //         scanf("%d", &verif);
            //     }
            // }

            if(verif==1){
                buscaBin(&pref, nome);
            }
            else{
                buscaBin(&comum, nome);
            }

        }
        else if (n==5)
        {
            int x=0;
            printf("Qual fila deseja ordenar?\n1 - Comum\n2 - Preferencial\n3 - Ambas\n");
            scanf("%d", &x);
        //     if(n > 3 || n < 1){
        //         while(n>3 || n<1){
        //             printf("Entrada invalida! Digite novamente:\n");
        //             scanf("%d", &x);
        //     }
        // }
            if (x==1)
            {
              tamanhoComum = filaTamanho(&comum);
              filaParaArray(&comum, fichasComum);
              bubblesortArray(fichasComum, tamanhoComum);
              imprimirArray(fichasComum, tamanhoComum);
              
            }
            if (x==2)
            {
              tamanhoPref = filaTamanho(&pref);
              filaParaArray(&pref, fichasPref);
              bubblesortArray(fichasPref, tamanhoPref);
              imprimirArray(fichasPref, tamanhoPref);  
            }
            if (x==3)
            {
                tamanhoComum = filaTamanho(&comum);
                filaParaArray(&comum, fichasComum);
                mergeSort(fichasComum, 0, tamanhoComum-1);
                printf("------------------------------------------\n");
                printf("Fila comum:\n");
                imprimirArray(fichasComum, tamanhoComum);
                tamanhoPref = filaTamanho(&pref);
                filaParaArray(&pref, fichasPref);
                mergeSort(fichasPref, 0, tamanhoPref-1);
                printf("------------------------------------------\n");
                printf("Fila preferencial:\n");
                imprimirArray(fichasPref, tamanhoPref); 
            }
        }
        else if (n==0)
        {
            break;
        }
    }
    
    return 0;
}