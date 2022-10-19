#include <stdio.h>
#include <stdlib.h>

typedef struct no { //criação da estrutura No
    int info;
    struct no *esq;
    struct no *dir;
}No;

void CriarNo(No **raiz,int x){//Função auxiliar do Inserir() que insere o elemento quando encontra NULL
    if(*raiz == NULL){
        *raiz = (No*)malloc(sizeof(No));
        (*raiz)->info = x;
        (*raiz)->esq = (*raiz)->dir = NULL;
    }
}

void Inserir(No **raiz,int x){//Percorre a árvore até o local correto pra inserir o valor, respeitando a ordenação
    if(*raiz != NULL){
        if((*raiz)->info >= x){
            Inserir(&(*raiz)->esq,x);
        }
        else{
            Inserir(&(*raiz)->dir,x);
        }
    }
    else{
        CriarNo(&(*raiz),x);
    }
}

void Imprimir(No *raiz){//Imprime a árvore Em Ordem
    if(raiz != NULL){
        Imprimir(raiz->esq);
        printf("%d ",raiz->info);
        Imprimir(raiz->dir);
    }
}

int main(){
No* raiz = NULL;
int x=1;
while(1){//fica no laço de repetição enquanto x != 0 e imprime a árvore após sair do while
    scanf("%d",&x);
    if(x!=0){
        Inserir(&raiz,x);
    }
    else break;
}

Imprimir(raiz);
return 0;
}
