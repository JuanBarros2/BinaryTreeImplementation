#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct arv{
    int dado;
    struct arv *ant;
    struct arv *prox;
}arv;

struct arv *raiz;

int menu_principal();
void verificar();
void inserir();
void insercao(arv *aux, int n);
void inordem(arv *aux);
void posordem();
void preordem();

int main(){
    setlocale(LC_ALL,"Portuguese");
    while(1){
        switch(menu_principal()){
            case 1:{
                verificar();
                break;
            }
            case 2:{
                inserir();
                break;
            }
            case 3:{
                printf("\n\n\tPos Ordem: ");
                posordem(raiz);
                system("pause>>null");
                break;
            }
            case 4:{
                printf("\n\n\tPos Ordem: ");
                inordem(raiz);
                system("pause>>null");
                break;
            }
            case 5:{
                printf("\n\n\tPre Ordem: ");
                preordem(raiz);
                system("pause>>null");
                break;
            }
            case 6:{
                break;
            case 0:{
                return(0);
                break;
                }
            }
        }
    }
}

int menu_principal(){
    int op;
    system("cls");
    printf("\n\n\t------------M-E-N-U------------\n\n");
    printf("\t1- Verificar se a AB está vazia\n");
    printf("\t2- Inserir elementos\n");
    printf("\t3- Exibição In-Ordem\n");
    printf("\t4- Exibição Pós-Ordem\n");
    printf("\t5- Exibição Pré-Ordem\n");
    printf("\t6- Procurar um elemento específico\n");
    printf("\t0- SAIR\n");
    printf("\n\n\tEntre com a opção :");
    scanf("%d",&op);
    system("cls");
    return (op);
    }

void verificar(){
    if(raiz==NULL)
        printf("\n\n\tA árvore está vazia");
    else printf("\n\n\tA árvore contem folhas");
    system("PAUSE>>null");
    return;
}

void inserir(){
    int num;
    printf("\n\n\tEscreva o número de entrada: ");
    scanf("%d",&num);
    system("cls");
    if(raiz==NULL){
        raiz= (arv*) malloc(sizeof(arv));
        raiz->ant=NULL;
        raiz->prox=NULL;
        raiz->dado=num;
        return;
    }
    insercao(raiz,num);
    printf("\n\n\tInserida com sucesso");
    system("pause>>null");
    return;
}

void insercao(arv *aux, int n){
    if(aux->dado==n)
        return;
    arv *novo;
    if(aux->dado > n){
        if (aux->ant==NULL){
            novo=(arv*)malloc(sizeof(arv));
            novo->dado=n;
            novo->prox=NULL;
            novo->ant=NULL;
            aux->ant=novo;
        }
        else if (aux->ant!=NULL)
            insercao(aux->ant,n);
        return;
    }
    if(aux->dado < n){
        if (aux->ant==NULL){
            novo=(arv*)malloc(sizeof(arv));
            novo->dado=n;
            novo->prox=NULL;
            novo->ant=NULL;
            aux->prox=novo;
        }
        else if (aux->ant != NULL)
            insercao(aux->prox,n);
        return;
    }
}

// Algoritmo recursivo pre-ordem
void preordem(arv *aux ) {
    if(aux!=NULL){
        printf( "%d  ", aux->dado );
        preordem( aux->ant );
        preordem( aux->prox);
        }
    return;
}

void posordem(arv *aux ) {
    if(aux!=NULL){
        preordem( aux->ant );
        preordem( aux->prox);
        printf( "%d  ", aux->dado );
        }
    return;
}
void inordem(arv *aux ) {
    if(aux!=NULL){
        preordem( aux->ant );
        printf( "%d  ", aux->dado );
        preordem( aux->prox);
        }
    return;
}
