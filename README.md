# sorting_algorithms
Implementação de algoritmos de ordenação em C

## BubbleSort
* Ordenação por bolha;
* Compara pares de elementos adjacentes e os troca de lugar se estiverem na ordem errada
* Esse processo se repete até que mais nenhuma troca seja necessária( elementos já ordenados)
* Melhor caso: N
* Pior caso: N^2
* Não é recomendado para grandes conjuntos de dados

```
void bubbleSort(int *v, int n){
	int i, chave, aux, fim=n;
	do{
		chave=0;
		for(i=0 ; i<fim-1 ; i++){
			if(v[i]>v[i+1]){
				aux=v[i];
				v[i]=v[i+1];
				v[i+1]=aux;
				chave=i;
			}
		}
		fim--;
	}while(chave!=0);
}
```

## Heapsort
* Ordenação usando heap
* heap: vetor que simula uma arvore binaria completa ( exceção do ultimo nivel)
* Todo elemento "pai" do vetor possui dois elementos "filhos"
* "pai"(i) -> "filhos" (2*i+1) e (2*i+2)

```
void heapsort(int *v, int n) {
    int i, aux;
    for(i = (n-1) / 2; i >= 0; i--){
        criaHeap(v,i,n-1);  ///Cria heap
    }
    for(i=n-1;i>=1;i--){
        aux=v[0];   ///Coloca o maior elemento na posicao correta
        v[0]=v[i];
        v[i]=aux;
        criaHeap(v,0,i-1);  ///Reconstroi heap
    }
}

void criaHeap(int *v, int i, int f){
    int aux = v[i];
    int j = 2*i + 1; ///Calcula o elemento "filho"
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
```

## InsertionSort
* Simula a ordenação de cartas de baralho com as mãos
* Pega-se uma carta de cada vez e a coloca em seu devido lugar, sempre deixando as cartas da mão em ordem
* Melhor caso: N
* Pior caso: N^2
* Eficiente para conjuntos de dados pequenos
* Estavel: não altera a ordem de dados iguais
* Capaz de ordenar os dados a medida que os recebe (tempo real)

```
void insertionSort(int *v, int n){
	int i, j, aux;
	for(i=1; i<n ; i++){
		aux=v[i];
		for(j=i ; j>0 && aux<v[j-1] ; j++){
			v[j]=v[j-1];
		}
		v[j]=aux;
	}
}
```

## Mergesort
* Ordenação por mistura / intercalação de elementos
* Divide, recursivamente, o conjunto de dados até que cada subconjunto possua 1 elemento
* Combina 2 subconjuntos de forma a obter 1 conjunto maior e ordenado
* Esse processo se repete até que exista apenas 1 conjunto
* Melhor/pior caso: NlogN
* Estavel: não altera a ordem de dados iguais
* Desvantagem: recursivo e usa um vetor auxiliar durante a ordenação

```
void MergeSort(int *v, int inicio, int fim){
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
        for(i = 0; i < tamanho; i++){
            if(p1 <= meio && p2 <= fim){ ///verifica se os vetores ja acabaram
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
```

## Quicksort
* Ordenação por troca de partições
* Ideia básica: Dividir e conquistar
* Um elemento é escolhido como pivo
* "Particionar": os dados são rearranjados ( valores menores do que o pivo são colocados antes dele e os maiores, depois)
* Recursivamente ordena as 2 partições
* Melhor caso: NlogN
* Pior caso(raro): N^2
* Estavel: não altera a ordem de dados iguais
* Desvantagem: como escolher o pivo?

```
void quicksort(int *v, int inicio, int fim){
    int pivo;
    if(inicio>fim)
        return;
    pivo=particiona(v,inicio,fim); ///Divite o vetor em 2
    quicksort(v,inicio,pivo-1); ///chama a função para as duas metades
    quicksort(v,pivo+1,fim);

}

int particiona(int *v, int inicio,int fim){
    int esq, dir, pivo, aux;
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
void troca(int *x,int *y){
    int t;
    t=*x;
    *x=*y;
    *y=t;
}
```

### SelectionSort
* Cada passo, procura o menor valor do array e o coloca na primeira posição do array
* Descarta-se a primeira posição do array e repete* se o processo para a segunda posição
* Isso é feito para todas as posições do array
* Melhor/pior caso: N^2
* Ineficiente para grandes conjuntos de dados
* Estavel: não altera a ordem de dados iguais

```
void selectionSort(int *v, int n){
	int i, j, menor, troca;
	for(i=0 ; i<n-1 ; i++){
		menor=i;
		for(j=i+1 ; j<n; j++){ ///Procura o menor elemento em relação a i;
			if(v[j]<v[menor])
				menor=j;
		}
		if(i!= menor){  ///Troca os valores da posição atual com o "menor";
			troca=v[i];
			v[i]=v[menor];
			v[menor]=troca;
		}
	}
}
```

## Shellsort
* A ordenação por inserção simples é altamente eficiente sobre uma lista de elementos quase ordenado.
* O algoritmo usa uma seqüência de incrementos e ordena os elementos cujo a distância é igual a este incremento. A cada etapa o incremento vai diminuindo até chegar a 1
* Recomendada para as listas de tamanho moderado, da varias centenas de elementos.
* Melhor caso: 2NlogN
* Pior caso: N^1.5

```
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
```