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
#include <time.h>
#include "uteis.h" 

#define TRUE 1
#define FALSE 0
#define TAM 1000000
#define INDEX_SIZE 1000

typedef struct {
    int key;
    int position;
} Index;

void createIndex(Index index[], int size);

int main(int argc, char const *argv[]) {
    int arquivo[TAM];
    int arquivoAuxiliar[INDEX_SIZE];
    int searchKey, startIndex, endIndex;
    int found = FALSE;
    int blockIndex = -1;

    carrega_vetor_aleatorio(arquivo, TAM, 4);
    quicksort(arquivo, 0, TAM - 1);
    //imprime_vetor(arquivo, TAM);

    Index index[INDEX_SIZE];
    createIndex(index, INDEX_SIZE);

    for(int i = 0; i < INDEX_SIZE; i++){
        arquivoAuxiliar[i] = index[i].key;
    }

    quicksort(arquivoAuxiliar, 0, INDEX_SIZE - 1);

    for(int i = 0; i < INDEX_SIZE; i++){
        index[i].key = arquivoAuxiliar[i];
    }

    printf("Índice criado:\n");
    for (int i = 0; i < INDEX_SIZE; i++) {
        printf("Index %d: Chave %d, Posição %d\n", i, index[i].key, index[i].position);
    }

    searchKey = rand() % TAM + 1;
    printf("\nBuscando a chave: %d\n", searchKey);

    for (int i = 0; i < INDEX_SIZE && found == FALSE; i++) {
        if (index[i].key >= searchKey) {
            blockIndex = i - 1;
            found = TRUE;
        }
    }

    if (blockIndex == -1) {
        blockIndex = INDEX_SIZE - 1;
    }

    printf("A chave %d pertence ao bloco %d.\n", searchKey, blockIndex);

    printf("Realizando busca no bloco...\n");
    startIndex = index[blockIndex].position + 1;
    endIndex = (blockIndex == INDEX_SIZE - 1) ? TAM - 1 : index[blockIndex + 1].position - 1;

    if (busca_sequencial(arquivo + startIndex, endIndex - startIndex + 1, searchKey) == TRUE) {
        printf("A chave %d existe no bloco %d.\n", searchKey, blockIndex);
    } else {
        printf("A chave %d NÃO existe no bloco %d.\n", searchKey, blockIndex);
    }

    return 0;
}

void createIndex(Index index[], int size) {
    srand((unsigned) time(NULL));
    int indexIncrement = TAM / size;
    for (int i = 0; i < size; i++) {
        index[i].key = rand() % 999 + 1;
        index[i].position = i * indexIncrement;
    }
}
