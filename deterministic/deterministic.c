#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

struct City {
    double x;
    double y;
};

double calcularDistancia(struct City cidadeA, struct City cidadeB) {
    double difX = cidadeA.x - cidadeB.x;
    double difY = cidadeA.y - cidadeB.y;
    return sqrt(difX * difX + difY * difY);
}

double calcularComprimentoRota(int* rota, struct City* cidades, int numCidades) {
    double comprimento = 0.0;

    for (int i = 0; i < numCidades - 1; ++i) {
        int cidadeAtual = rota[i];
        int proximaCidade = rota[i + 1];
        comprimento += calcularDistancia(cidades[cidadeAtual], cidades[proximaCidade]);
    }

    int cidadeFinal = rota[numCidades - 1];
    int cidadeInicial = rota[0];
    comprimento += calcularDistancia(cidades[cidadeFinal], cidades[cidadeInicial]);

    return comprimento;
}

void permutar(int* rota, int i, int j) {
    int temp = rota[i];
    rota[i] = rota[j];
    rota[j] = temp;
}

void encontrarRotaOtima(struct City* cidades, int numCidades, int* melhorRota, double* melhorComprimento) {
    int* rotaAtual = (int*)malloc(numCidades * sizeof(int));
    for (int i = 0; i < numCidades; ++i) {
        rotaAtual[i] = i;
    }

    *melhorComprimento = INT_MAX;

    int* rotaTemp = (int*)malloc(numCidades * sizeof(int));

#pragma omp parallel
    {
        int* melhorRotaPriv = (int*)malloc(numCidades * sizeof(int));
        double melhorComprimentoPriv = INT_MAX;

#pragma omp for nowait
        for (int i = 0; i < numCidades; ++i) {
            for (int j = 0; j < numCidades; ++j) {
                melhorRotaPriv[j] = rotaAtual[j];
            }
            for (int k = 0; k < numCidades - 1; ++k) {
                permutar(melhorRotaPriv, i, k);
                double comprimento = calcularComprimentoRota(melhorRotaPriv, cidades, numCidades);
                if (comprimento < melhorComprimentoPriv) {
                    melhorComprimentoPriv = comprimento;
                    for (int j = 0; j < numCidades; ++j) {
                        rotaTemp[j] = melhorRotaPriv[j];
                    }
                }
                permutar(melhorRotaPriv, i, k); // Restaurar a rota original
            }
        }

#pragma omp single
        {
            if (melhorComprimentoPriv < *melhorComprimento) {
                *melhorComprimento = melhorComprimentoPriv;
                for (int j = 0; j < numCidades; ++j) {
                    melhorRota[j] = rotaTemp[j];
                }
            }
        }

        free(melhorRotaPriv);
    }

    free(rotaAtual);
    free(rotaTemp);
}

void lerCoordenadasArquivo(const char* nomeArquivo, struct City** cidades, int* numCidades) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    int capacidade = 10;
    int tamanho = 0;
    *cidades = (struct City*)malloc(capacidade * sizeof(struct City));

    while (fscanf(arquivo, "%lf %lf", &((*cidades)[tamanho].x), &((*cidades)[tamanho].y)) == 2) {
        tamanho++;
        if (tamanho == capacidade) {
            capacidade *= 2;
            *cidades = (struct City*)realloc(*cidades, capacidade * sizeof(struct City));
        }
    }

    fclose(arquivo);
    *numCidades = tamanho;
}

void imprimirRota(int* rota, int numCidades) {
    for (int i = 0; i < numCidades; ++i) {
        printf("%d ", rota[i]);
    }
    printf("\n");
}

int main() {
    struct City* cidades;
    int numCidades;
    const char* nomeArquivo = "C:\\Users\\Arthu\\CLionProjects\\travelling\\coordenadas";

    lerCoordenadasArquivo(nomeArquivo, &cidades, &numCidades);

    int* melhorRota = (int*)malloc(numCidades * sizeof(int));
    double melhorComprimento;

    clock_t inicio = clock();

    encontrarRotaOtima(cidades, numCidades, melhorRota, &melhorComprimento);

    clock_t fim = clock();
    double duracao = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000.0;

    printf("Rota ótima encontrada: ");
    imprimirRota(melhorRota, numCidades);

    printf("Comprimento da rota ótima: %lf\n", melhorComprimento);
    printf("Tempo de execução: %lf ms\n", duracao);

    free(cidades);
    free(melhorRota);

    return 0;
}
