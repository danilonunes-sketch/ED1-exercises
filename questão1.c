#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGURA_JANELA 800
#define ALTURA_JANELA 600

// Estrutura para representar uma posição (x, y)
typedef struct {
    float x;
    float y;
} Vector2;

// Estrutura para representar uma cor
typedef struct {
    int r;
    int g;
    int b;
} Color;

// Estrutura Bola
typedef struct {
    Vector2 pos;
    Vector2 vel;
    float raio;
    Color cor;
} Bola;


// Função para criar uma matriz dinâmica
int **criarMatriz(int linhas, int colunas) {

    int **matriz = malloc(linhas * sizeof(int *));

    for (int i = 0; i < linhas; i++) {

        matriz[i] = malloc(colunas * sizeof(int));

        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = rand() % 2;
        }
    }

    return matriz;
}


// Função para liberar a matriz
void liberarMatriz(int **matriz, int linhas) {

    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }

    free(matriz);
}


// Função para criar várias bolas
Bola *criarBolas(int quantidade) {

    Bola *bolas = malloc(quantidade * sizeof(Bola));

    for (int i = 0; i < quantidade; i++) {

        Bola *b = bolas + i;

        // Posição aleatória
        b->pos.x = 50 + rand() % (LARGURA_JANELA - 100);
        b->pos.y = 50 + rand() % (ALTURA_JANELA - 100);

        // Velocidade
        b->vel.x = (rand() % 10) - 5;
        b->vel.y = (rand() % 10) - 5;

        // Evita velocidade 0
        if (b->vel.x == 0) {
            b->vel.x = 1;
        }

        if (b->vel.y == 0) {
            b->vel.y = 1;
        }

        // Raio
        b->raio = 10 + rand() % 20;

        // Cor aleatória
        b->cor.r = rand() % 256;
        b->cor.g = rand() % 256;
        b->cor.b = rand() % 256;
    }

    return bolas;
}


// Função para atualizar uma bola
void atualizarBola(Bola *b) {

    // Atualiza posição
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;

    // Verifica paredes esquerda e direita
    if (b->pos.x - b->raio < 0 ||
        b->pos.x + b->raio > LARGURA_JANELA) {

        b->vel.x *= -1;
    }

    // Verifica paredes superior e inferior
    if (b->pos.y - b->raio < 0 ||
        b->pos.y + b->raio > ALTURA_JANELA) {

        b->vel.y *= -1;
    }
}


// Função para imprimir uma bola
void imprimirBola(Bola *b, int numero) {

    printf("Bola %d:\n", numero);

    printf("Posicao: (%.1f, %.1f)\n",
           b->pos.x,
           b->pos.y);

    printf("Velocidade: (%.1f, %.1f)\n",
           b->vel.x,
           b->vel.y);

    printf("Raio: %.1f\n", b->raio);

    printf("\n");
}


// Programa principal
int main() {

    srand(time(NULL));

    // =========================
    // TESTE DA MATRIZ
    // =========================

    int linhas = 3;
    int colunas = 4;

    int **matriz = criarMatriz(linhas, colunas);

    printf("MATRIZ:\n\n");

    for (int i = 0; i < linhas; i++) {

        for (int j = 0; j < colunas; j++) {
            printf("%d ", matriz[i][j]);
        }

        printf("\n");
    }

    liberarMatriz(matriz, linhas);


    // =========================
    // TESTE DAS BOLAS
    // =========================

    int quantidadeBolas = 3;

    Bola *bolas = criarBolas(quantidadeBolas);

    printf("\n\nBOLAS ANTES DA ATUALIZACAO:\n\n");

    for (int i = 0; i < quantidadeBolas; i++) {
        imprimirBola(bolas + i, i);
    }


    // Atualiza todas as bolas
    for (int i = 0; i < quantidadeBolas; i++) {
        atualizarBola(bolas + i);
    }


    printf("BOLAS DEPOIS DA ATUALIZACAO:\n\n");

    for (int i = 0; i < quantidadeBolas; i++) {
        imprimirBola(bolas + i, i);
    }


    // Libera memória das bolas
    free(bolas);

    return 0;
}