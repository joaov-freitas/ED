#include <stdio.h>
#include <stdlib.h>
#define TAM 10 // tamanho da Heap

void limpaHeap(int *heap){ //inicia a heap com 0 em todos as posições
    for(int i=0;i<TAM;i++){
        heap[i] = 0;
    }
}

void ajustaSubindo(int* heap, int pos){ //ajusta a posição dos elementos após inserção
    if(pos > 0){
        int pai = (int)(pos-1)/2;
        if(pai >= 0){
            if(heap[pos] < heap[pai]){
                int aux = heap[pos];
                heap[pos] = heap[pai];
                heap[pai] = aux;
                ajustaSubindo(heap,pai);
            }
        }
    } 
}

void ajustaDescendo(int* heap,int pos){ //ajusta a posição dos elementos após remoção
    int posMenorfilho = pos*2+1;
    if(heap[pos*2+2] < heap[pos*2+1]){
        posMenorfilho = pos*2+2;
    }
    if(posMenorfilho < TAM && heap[posMenorfilho] != 0){
        if(heap[pos] > heap[posMenorfilho]){
            int *aux = heap[pos];
            heap[pos] = heap[posMenorfilho];
            heap[posMenorfilho] = aux;
            ajustaDescendo(heap,posMenorfilho);
        }
    } 
}

void Inserir(int *heap, int x){
    int cont = 0;
    while(heap[cont] != 0){//percorre o vetor até a próxima posicao livre
        cont++;
    }
    if(cont < TAM){//insere se tiver espaco no vetor
        heap[cont] = x;
        ajustaSubindo(heap,cont);
    }
    else{
        printf("Heap cheia. Remova algum valor antes.\n\n");//mensagem de aviso caso não tenha espaco livre
    }
    
}

int Remover(int *heap){
    int aux = heap[0];
    int i,cont = 0;
    for(i=0;i<TAM;i++){
        if(heap[i] != 0){//percorre o vetor até a proxima posicao livre
            cont++;
        }
    }
    if(cont > 0){//se houver algum elemento na heap o primeiro e o ultimo elementos serão trocados e depois retirado, fazendo os ajustes necessários
        heap[0] = heap[cont-1];
        heap[cont-1] = 0;
        ajustaDescendo(heap,0);//ajustes necessários
    }
    return aux;
}

void imprimir(int* heap){
    for(int i=0;i<TAM;i++){
        if(heap[i] != 0){
            printf("%d ",heap[i]);
        }
    }
}

int main() {
    int x,op = 0;// x é o valor a ser inserido ou removido, indicado pelo usuário.
    //op guarda o numero relacionado a operacao que o usúario deseja realizar
    int *heap = NULL;
    heap = (int*)malloc(TAM*sizeof(int));
    limpaHeap(heap);

    while(op != 3){
        printf("\n1- Inserir\n");
        printf("2- Remover\n");
        printf("3- Sair\n\n");

        printf("Digite a opção desejada: ");
        scanf("%d",&op);

        switch(op){
            case 1://inserir
                printf("\nDigite o valor a ser inserido: ");
                scanf("%d",&x);
                printf("\n");
                Inserir(heap,x);
                printf("Heap: ");
                imprimir(heap);
                printf("\n");
                break;
            case 2://remover
                x = Remover(heap);
                if(x != 0){
                    printf("\nValor Removido: %d\n\n",x);
                    printf("Heap: ");
                    imprimir(heap);
                    printf("\n");
                }
                else{
                    printf("\nHeap vazia\n");
                }
                break;
            case 3://sair do programa
                break;
            default:
                printf("\nOpção inválida\n");
                break;
        }
    } 
return 0;
}
