
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define TAM 10//Tamanho do vetor
///Se alterar o TAM, trocar o vetor vet_temp da função main, caso contrario a função shellsort pode não funcionar

///Declaração de funções
void menu_vetor(int v[]);
int menu();
void ler_vetor(int v[]);
void vetor_aleatorio(int v[]);
void imprime_vetor(int v[]);
void copia_vetor(int v[], int v2[]);
///Funções Quicksort
void quicksort(int v[], int inicio, int fim);
int particiona(int v[], int inicio,int fim);
void troca(int x[],int y[]);
///Função Shellsort
void shellsort(int v[], int n,int incrmnts[],int numinc);
///Funções Mergesort
void MergeSort(int v[], int inicio, int fim);
void Merge (int v[], int inicio, int meio, int fim);
///Funções Heapsort
void heapsort(int v[], int n);
void criaHeap(int v[], int i, int f);

///Função principal
void main(){
    int v[TAM]; ///Vetor de numeros
    //int vet_temp[]={5,3,1}, numinc = 3; ///Vetor para o shellsort com poucos elementos
    int vet_temp[]={45000,40000,30000,20000,10000,5000,3000,2500,2000,1500,1200,1100,1000,900,800,700,600,500,400,300,200,150,140,130,120,110,100,90,70,55,45,35,22,15,12,10,8,5,3,1}, numinc = 32; ///Vetor para o shellsort com muitos elementos
    clock_t inicio, fim; ///Variavel que marca o tempo;

    menu_vetor(v);

    switch(menu()){
        case 1: printf("\tQuicksort\n");
                printf("Vetor original:\n"); imprime_vetor(v);
                inicio=clock();
                quicksort(v,0,TAM);
                fim=clock();
                printf("\tVetor ordenado:\n"); imprime_vetor(v);
                printf("Tempo de execucao: %g ms\n",(double)fim-(double)inicio);
                break;

        case 2: printf("\tShellsort\n");
                //printf("Vetor original:\n"); imprime_vetor(v);
                inicio=clock();
                shellsort(v,TAM,vet_temp,numinc);
                fim=clock();
                //printf("\tVetor ordenado:\n");imprime_vetor(v);
                printf("Tempo de execucao: %g ms\n",(double)fim-(double)inicio);
                break;

        case 3: printf("\tHeapsort\n");
                //printf("Vetor original:\n"); imprime_vetor(v);
                inicio=clock();
                heapsort(v,TAM);
                fim=clock();
                //printf("\tVetor ordenado:\n"); imprime_vetor(v);
                printf("Tempo de execucao: %g ms\n",(double)fim-(double)inicio);
                break;

        case 4: printf("\tMergesort\n");
                //printf("Vetor original:\n"); imprime_vetor(v);
                inicio=clock();
                MergeSort(v,0,TAM-1);
                fim=clock();
                //printf("\tVetor ordenado:\n"); imprime_vetor(v);
                printf("Tempo de execucao: %g ms\n",(double)fim-(double)inicio);
                break;

        case 5: printf("\tComparacao do tempo dos 4 algoritmos para ordenar vetor de %d elementos:\n",TAM);
                int v2[TAM];
                copia_vetor(v,v2);
                inicio=clock();
                quicksort(v2,0,TAM);
                fim=clock();
                printf("Tempo de execucao quicksort: %g ms\n",(double)fim-(double)inicio);

                copia_vetor(v,v2);
                inicio=clock();
                shellsort(v2,TAM,vet_temp,numinc);
                fim=clock();
                printf("Tempo de execucao shellsort: %g ms\n",(double)fim-(double)inicio);

                copia_vetor(v,v2);
                inicio=clock();
                heapsort(v2,TAM);
                fim=clock();
                printf("Tempo de execucao heapsort: %g ms\n",(double)fim-(double)inicio);

                inicio=clock();
                MergeSort(v,0,TAM-1);
                fim=clock();
                printf("Tempo de execucao mergesort: %g ms\n",(double)fim-(double)inicio);
                break;
    }
    system("pause");
}

///Funções
void menu_vetor(int v[]){ ///Mostra o menu
    int opcao;
    ///Menu preenchimento do vetor
    do{
        printf("Escolha o modo que deseja preencher o vetor de tamanho %d:\n",TAM);
        printf("1- Preencher manualmente\n");
        printf("2- Preencher o vetor com numeros aleatorios\n");
        scanf("%d",&opcao);
        if(opcao==1)
            ler_vetor(v);
        if(opcao==2)
            vetor_aleatorio(v);
    }while(opcao!=1 && opcao !=2);
}

///Menu de escolha de algoritmo
int menu(){ ///Mostra o menu
    int opcao;

    do{
        printf("Escolha o algoritmo que deseja utilizar:\n");
        printf("1- Ordenacao por Quicksort\n");
        printf("2- Ordenacao por Shellsort\n");
        printf("3- Ordenacao por Heapsort\n");
        printf("4- Ordenacao por Mergesort\n");
        printf("5- Comparar tempo dos algoritmos\n");
        printf("Opcao: ");
        scanf("%d",&opcao);

        if(opcao==1 || opcao ==2 || opcao==3 || opcao ==4 || opcao == 5){
            system("cls");
            printf("Opcao: %d\n",opcao);
            break;
        }
        else{
            system("cls");
            printf("\tOpcao invalida!\n");
        }
    }while(1);
    return opcao;
}

void ler_vetor(int v[]){ ///Pega os valores do vetor
    int i;
    printf("Digite os %d valores do vetor:\n",TAM);
    for(i=0;i<TAM;i++){
        scanf("%d",&v[i]);
    }
    system("cls");
    printf("\tVETOR:\n");
    imprime_vetor(v);
}

void vetor_aleatorio(int v[]){ ///Preenche o vetor com numeros aleatórios
    int i;
    srand((unsigned)time(NULL));
    printf("Digite os %d valores do vetor:\n",TAM);
    for(i=0;i<TAM;i++){
        v[i]=rand()%100;
    }
    system("cls");
    //printf("\tVETOR:\n");imprime_vetor(v);
}

void imprime_vetor(int v[]){ ///Imprime o vetor
    int i;
    for(i=0;i<TAM;i++){
        printf("%d ",v[i]);
    }
    printf("\n");
}

void copia_vetor(int v[], int v2[]){///Copia v para v2
    int i;
    for(i=0;i<TAM;i++){
        v2[i]=v[i];
    }
}

///Quicksort
void quicksort(int v[], int inicio, int fim){
    int pivo;
    if(inicio>fim)
        return;
    pivo=particiona(v,inicio,fim); ///Divite o vetor em 2
    quicksort(v,inicio,pivo-1); ///chama a função para as duas metades
    quicksort(v,pivo+1,fim);

}

int particiona(int v[], int inicio,int fim){
    int esq, dir, pivo;
    esq=inicio;
    dir=fim;
    pivo=v[inicio];
    while(esq<dir){
        while(v[esq]<=pivo && esq<fim)
            esq++;  ///Avança posição da esquerda
        while(v[dir]>pivo)
            dir--;  ///Recua posição da direita
        if(esq<dir){
            troca(&v[esq],&v[dir]);
        }
    }
    v[inicio]=v[dir];
    v[dir]=pivo;
    return dir;
}

void troca(int x[],int y[]){
    int t;
    t=*x;
    *x=*y;
    *y=t;
}

///Sherllsort
void shellsort(int v[], int n,int incrmnts[],int numinc){
///v[] é o vetor a ser ordenado
///n = tamanho do vetor
///incrmnts[] é um array contendo os incrementos
///numinc = numero de incrementos do array incremnts

    int incr,j,k,span,temp;

    for(incr=0; incr<numinc; incr++){ /// spam recebe os "incr" incrementos do vetor incrmnts
        span=incrmnts[incr]; ///span é o tamanho do incremento
        for(j=span;j<n;j++){ ///Faz comparações de numeros que estão distantes "spam"
            temp=v[j];
            for(k=j-span;k>=0 && temp<v[k];k=k-span)///Insere elemento v[j] em sua posição correta dentro de seu subvetor
                v[k+span]=v[k];
            v[k+span]=temp;
        }
    }
}

///Mergesort
void MergeSort(int v[], int inicio, int fim){
int meio;

if (inicio < fim){
    meio = floor((inicio+fim)/2);
    MergeSort(v, inicio, meio);
    MergeSort(v, meio+1, fim);
    Merge(v, inicio, meio, fim);
    }
}

void  Merge (int v[], int inicio, int meio, int fim){
   int i, j, k, p1, p2, tamanho;
   int *aux;

   tamanho=fim-inicio+1;
   p1=inicio;
   p2=meio+1;

   aux = (int *) malloc(tamanho*sizeof(int));
    if(aux != NULL){
        for(i=0;i<tamanho;i++){
            if(p1<=meio && p2<=fim){ ///verifica se os vetores ja acabaram
                if(v[p1]<v[p2])
                    aux[i]=v[p1++];
                else
                    aux[i]=v[p2++];
            }
            else{   ///Se um dos sub-vetores acabou, copia oq sobrou..
                if(p1<=meio)
                    aux[i]=v[p1++];
                else
                   aux[i]=v[p2++];

            }
        }
        for(j=0,k=inicio;j<tamanho;j++,k++){
            v[k]=aux[j];
        }
   }
   free(aux);
}

///Heapsort
void heapsort(int v[], int n) {
    int i, aux;
    for(i=(n-1)/2;i>=0;i--){
        criaHeap(v,i,n-1);  ///Cria heap
    }
    for(i=n-1;i>=1;i--){
        aux=v[0];   ///Coloca o maior elemento na posicao correta
        v[0]=v[i];
        v[i]=aux;
        criaHeap(v,0,i-1);  ///Reconstroi heap
    }
}

void criaHeap(int v[], int i, int f){
    int aux = v[i];
    int j= 2*i + 1; ///Calcula o elemento "filho"
    while(j<=f){
        if(j<f){    ///Verifica se ainda esta dentro do vetor
            if(v[j]<v[j+1])///Verifica qual é maior
                j=j+1;  ///Se o segundo for maior, j=j+1
        }
        if(aux<v[j]){ ///Verifica se o pai é menor que o filho
            v[i]=v[j];  ///Se for, filho vira o pai
            i=j;
            j= 2*i + 1; ///calcula o filho
        }
        else
            j=f+1; ///termina
    }
    v[i]=aux; ///Coloca no lugar correto
}
