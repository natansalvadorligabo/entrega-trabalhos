#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define TAM 1000000
#define INDEX_SIZE 1000

void quicksort(int x[], int lb, int ub);
void partition(int x[], int lb, int ub, int *j);
int busca_sequencial(int colecao[], int tamanho, int key);
void carrega_vetor_aleatorio(int colecao[], int tamanho, int qtd_digitos);
void imprime_vetor(int colecao[], int tamanho);

// QUICKSORT
void quicksort(int x[], int lb, int ub){
    int j = -1;

    if(lb >= ub)
        return;                   

    partition(x, lb, ub, &j);       

    quicksort(x, lb, j-1);          

    quicksort(x, j+1, ub);          
}

void partition(int x[], int lb, int ub, int *j){
    int a, down, up, temp;
    
    a = x[lb];

    up = ub;
    down = lb;

    while(down < up){
        while(x[down] <= a && down < ub){
            down++;
        }
        while(x[up] > a){
            up--;
        }
        if(down < up){
            temp = x[down];
            x[down] = x[up];
            x[up] = temp;
        }
    }
    x[lb] = x[up];
    x[up] = a;
    *j = up;
}

// BUSCA
int busca_sequencial(int colecao[], int tamanho, int key){
    int found = FALSE;
    for(int i = 0; i < tamanho && found == FALSE; i++){
        if(colecao[i] == key){
            found = TRUE;
        }
    }
    return found;
}

// UTEIS
void carrega_vetor_aleatorio(int colecao[], int tamanho, int qtd_digitos){
	int i, digitos;
	
	for(i=1, digitos = 10; i < qtd_digitos; i++){
		digitos *= 10;
	}
	
	srand( (unsigned) time(NULL) );
	for(i=0; i < tamanho; i++){
		colecao[i] = rand() % digitos;
	}
	
}

void imprime_vetor(int colecao[], int tamanho){
	int i = 0;
	for(i = 0; i < tamanho; i++){
		printf("[%d] - %d\n", i, colecao[i]);
	}
}
