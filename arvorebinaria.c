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

No* Buscar(No *raiz,int x){
    if(raiz != NULL){
        if(raiz->info > x){
            return Buscar(raiz->esq,x);
        }
        else if(raiz->info < x){
            return Buscar(raiz->dir,x);
        }
    }
    return raiz;
}

void Imprimir(No *raiz){//Imprime a árvore Em Ordem
    if(raiz != NULL){
        Imprimir(raiz->esq);
        printf("%d ",raiz->info);
        Imprimir(raiz->dir);
    }
}

void menu(No* raiz;){
    int op=0,x;
    No *raiz = NULL;
    while(op != 9){
        printf("1-Inserir na árvore\n");
        printf("2-Buscar na árvore\n");
        printf("3- Remover da ávore\n");
        printf("4- Imprimir árvore\n");
        printf("9- Encerrar programa\n");
        printf("Escolha uma opção: ");
        scanf("%d",&op);

        switch(op){
            case 1:
                printf("\nDigite o elemento a ser inserido: ");
                scanf("%d",&x);
                Inserir(&raiz,x);
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                printf("\n");
                Imprimir(raiz);
                printf("\n\n");
                break;
            case 9:
                break;
        }
    }
}

int main(){
    No* raiz = NULL;
    menu(raiz);
return 0;
}
