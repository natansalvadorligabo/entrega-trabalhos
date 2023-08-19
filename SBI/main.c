/* Implemente um sistema que aplique a busca sequencial indexada 
em um arquivo com 1 milhão de registros gerados de forma aleatória.
Deve-se utilizar pelo menos uma tabela (índice) auxiliar para a busca.
*/
/**
 * Autor..: Natan Salvador Ligabô
 * Contato: natan.ligabo@aluno.ifsp.edu.br
*/

#include <stdio.h>
#include <stdlib.h>
#include "uteis.h"
#define TRUE 1
#define FALSE 0
#define TAM 100
#define INDEX_SIZE 10

typedef struct {
    int chave;
    int posicao;
} Index;

void createIndex(Index index[], int size);

int main(int argc, char const *argv[]){
	int arquivo[TAM];
    int searchKey;
	
	carrega_vetor_aleatorio(arquivo, TAM, 4);
	quicksort(arquivo, 0, TAM-1);
    //imprime_vetor(arquivo, TAM);

    Index index[INDEX_SIZE];
    createIndex(index, INDEX_SIZE);

    searchKey = rand() % TAM + 1;
    printf("Buscando a chave: %d\n", searchKey);

    if(busca_sequencial(arquivo, TAM, searchKey) == TRUE){
        printf("A chave %d existe no arquivo.\n", searchKey);
    } else {
        printf("A chave %d NÃO existe no arquivo.\n", searchKey);
    }

    return 0;
}

void createIndex(Index index[], int size){
    int fatias = (TAM / size);
    int i;

    for (i = 0; i < size; i++){
        index[i].chave = i * fatias + 1;
        index[i].posicao = i * fatias;
    }
}