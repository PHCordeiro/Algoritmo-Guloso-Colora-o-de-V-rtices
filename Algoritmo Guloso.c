//Pedro Henrique de Souza Seabra Mattos Cordeiro, Yann Matias Dutra, Lucas Rangel Berenger, Gabriel Moço Pessanha, Caio Gomes Rangel
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

void colorirVertices(int grafo[MAX_VERTICES][MAX_VERTICES], int numVertices);

int main() {
    FILE *arquivo;
    int grafo[MAX_VERTICES][MAX_VERTICES];
    int numVertices, numArestas;

    // Abre o arquivo contendo o grafo
    arquivo = fopen("grafo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Le o numero de vertices e arestas
    fscanf(arquivo, "%d %d", &numVertices, &numArestas);

    // Le a matriz de adjacencia do grafo
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            fscanf(arquivo, "%d", &grafo[i][j]);
        }
    }

    // Fecha o arquivo
    fclose(arquivo);

    // Chama o algoritmo de coloracao de vertices
    colorirVertices(grafo, numVertices);

    return 0;
}

void colorirVertices(int grafo[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int cores[MAX_VERTICES];
    int i, j, cor;

    // Inicializa todas as cores como -1 (nao atribuidas)
    for (i = 0; i < numVertices; i++) {
        cores[i] = -1;
    }

    // Atribui cores aos vertices
    for (i = 0; i < numVertices; i++) {
        // Inicializa todas as cores disponiveis como verdadeiras
        int disponiveis[MAX_VERTICES];
        for (j = 0; j < numVertices; j++) {
            disponiveis[j] = 1;
        }

        // Verifica as cores dos vertices adjacentes
        for (j = 0; j < numVertices; j++) {
            if (grafo[i][j] && cores[j] != -1) {
                disponiveis[cores[j]] = 0;
            }
        }

        // Encontra a primeira cor disponivel
        for (cor = 0; cor < numVertices; cor++) {
            if (disponiveis[cor]) {
                break;
            }
        }

        // Atribui a cor ao vertice i
        cores[i] = cor;
    }

    // Encontra o numero maximo de cores utilizadas
    int numCores = 0;
    for (i = 0; i < numVertices; i++) {
        if (cores[i] > numCores) {
            numCores = cores[i];
        }
    }

    // Imprime as cores atribuidas aos vertices
    printf("Cores atribuidas aos vertices:\n");
    for (i = 0; i < numVertices; i++) {
        printf("Vertice %d: Cor %d\n", i+1, cores[i]+1);
    }

    printf("Numero minimo de cores necessarias: %d\n", numCores + 1);
}