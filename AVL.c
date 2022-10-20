#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct avl{
    int info;
    struct avl *esq, *dir;
    short altura;
}avl;

avl* NovoNo(avl *raiz,int x){
    if(raiz == NULL){
        avl *no = NULL;
        no = (avl*)malloc(sizeof(avl));
        no->info = x;
        no->esq = NULL;
        no->dir = NULL;
        no->altura = 0;
        return no;
    }
    else{
        return NULL;
    }
}


int maior(int a, int b){
    return (a > b)? a: b;
}

int alturaNo(avl* raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        return raiz->altura;
    }
}

int fatorBalanceamento(avl* raiz){
    if(raiz != NULL){
        return (alturaNo(raiz->esq) - alturaNo(raiz->dir));
    }
    else{
        return 0;
    }
}

avl* rotacaoEsq(avl* raiz){
    avl *y,*f;

    y = raiz->dir;
    f = y->esq;

    y->esq = raiz;
    raiz->dir = f;

    raiz->altura = maior(alturaNo(raiz->esq),alturaNo(raiz->dir)) + 1;
    y->altura = maior(alturaNo(y->esq),alturaNo(y->dir)) + 1;

    return y;
}

avl* rotacaoDir(avl *raiz){
    avl *y,*f;
    y = raiz->esq;
    f = y->dir;

    y->dir = raiz;
    raiz->esq = f;

    raiz->altura = maior(alturaNo(raiz->esq),alturaNo(raiz->dir)) + 1;
    y->altura = maior(alturaNo(y->esq),alturaNo(y->dir)) + 1;

    return y;
}

avl* rotacaoDuplaEsq(avl *raiz){
    raiz->esq = rotacaoEsq(raiz->esq);
    return(rotacaoDir(raiz));
}

avl* rotacaoDuplaDir(avl *raiz){
    raiz->dir = rotacaoDir(raiz->dir);
    return(rotacaoEsq(raiz));
}

avl* balancear(avl *raiz){
    short fb = fatorBalanceamento(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->dir) <= 0){
        raiz = rotacaoEsq(raiz);
    }
    else if(fb > 1 && fatorBalanceamento(raiz->esq) >= 0){
        raiz = rotacaoDir(raiz);
    }
    else if(fb > 1 && fatorBalanceamento(raiz->esq) < 0){
        raiz = rotacaoDuplaEsq(raiz);
    }
    else if(fb < -1 && fatorBalanceamento(raiz->dir) > 0){
        raiz = rotacaoDuplaDir(raiz);
    }
    return raiz;
}

avl* inserir(avl* raiz, int x){
    if(raiz == NULL){
        return  NovoNo(raiz,x);
    }
    else{
        if(x <= raiz->info){
            raiz->esq = inserir(raiz->esq,x);
        }
        else{
            raiz->dir = inserir(raiz->dir,x);
        }
    }
    raiz->altura = maior(alturaNo(raiz->esq),alturaNo(raiz->dir)) + 1;
    raiz = balancear(raiz);
    return raiz;
}

avl* remover(avl *raiz, int x){
    if(raiz != NULL){
        if(raiz->info == x){
            if(raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                return NULL;
            }
            else{
                if(raiz->esq != NULL && raiz->dir != NULL){
                    avl* aux = raiz->esq;
                    while (aux->dir != NULL){
                        aux = aux->dir;
                    }
                    raiz->info = aux->info;
                    aux->info = x;
                    raiz->esq = remover(raiz->esq,x);
                    return raiz;
                }
                else{
                    avl *aux;
                    if(raiz->esq != NULL){
                        aux = raiz->esq;
                    }
                    else{
                        aux = raiz->dir;
                    }
                    free(raiz);
                    return aux;
                }
            }
        }
        else{
            if(x < raiz->info){
                raiz->esq = remover(raiz->esq, x);
            }
            else{
                raiz->dir = remover(raiz->dir, x);
            }
            raiz->altura = maior(alturaNo(raiz->esq),alturaNo(raiz->dir)) + 1;
            raiz = balancear(raiz);
            return raiz;
        }
    }
    else{
        return NULL;
    }
}
int existe(avl *raiz, int x){
    if(raiz==NULL){
        return 0;//n achou
    }else{
        if(raiz->info == x){
            return 1;//achou
        }
        else if(x < raiz->info){
            return existe(raiz->esq,x);
        }else{
            return existe(raiz->dir,x);
        }

    }

}

avl* destroi(avl *raiz){

    if(raiz->esq != NULL){//se tem caminho pela esquerda
        raiz->esq = destroi(raiz->esq);
    }
    if(raiz->dir != NULL){//se tem caminho pela direita
        raiz->dir = destroi(raiz->dir);
    }
    if(raiz->esq == NULL && raiz->dir == NULL){//se é uma folha destroi e retorna
        free(raiz);
        return NULL;
    }
}
void preImpressao(avl* raiz){
    if(raiz!=NULL){
        printf("%d ",raiz->info);
        preImpressao(raiz->esq);
        preImpressao(raiz->dir);
    }
}
int main(){
    int alt=0;
    int op =0;
    int x;
    avl *raiz = NULL;
    
    while(op !=9)
    {
        printf("\n1-inserir\n2-remover\n3-imprimir\n9-sair\n");
        scanf("%d",&op);
        switch (op)
        {
            case 1:
                printf("\nValor: ");
                scanf("%d",&x);
                printf("\n");
                raiz = inserir(raiz,x);
                break;
            case 2:
                printf("\nValor: ");
                scanf("%d",&x);
                printf("\n");
                if(existe(raiz,x)!= 0){
                    raiz = remover(raiz,x);
                    printf("removido\n");
                }else{
                    printf("valor nao existe na arvore");
                }

                break;
            case 3:
                printf("\n");
                preImpressao(raiz);
                break;
            case 9:
            if(raiz !=NULL){
                raiz = destroi(raiz);
            }
                break;
            default:
                printf("entrada inválida");
                break;
        }
    }
return 0;
}
