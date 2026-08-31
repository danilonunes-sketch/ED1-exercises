#include <stdio.h>
#include <stdlib.h>

int main(){
    int linha = 3;
    int coluna = 3;
    int *matriz = (int)malloc(linha*sizeof(int));
    for(int i=0; i<linha; i++){
        matriz[i] = (int*)malloc(coluna*sizeof(int*));
    }
    for(int i=0; i<linha; i++){
        for(int j=0; j<coluna; j++){
            matriz[i][j] = i*3 + j;
            printf("%d \t", matriz[i][j]);
        }
        printf("\n");
    }
    return 0;
}