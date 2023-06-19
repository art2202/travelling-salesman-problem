#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_CIDADES 10
#define TAM_POPULACAO 50
#define NUM_GERACOES 10000
#define TAXA_MUTACAO 0.1

typedef struct {
    int genes[NUM_CIDADES];
    double fitness;
} Cromossomo;

typedef struct {
    double x;
    double y;
} Coordenada;

Coordenada cidades[NUM_CIDADES] = {
        {0, 0},   // Cidade 0
        {1, 1},   // Cidade 1
        {2, 3},   // Cidade 2
        {5, 2},   // Cidade 3
        {6, 3},   // Cidade 4
        {7, 7},   // Cidade 5
        {8, 5},   // Cidade 6
        {9, 6},   // Cidade 7
        {3, 8},   // Cidade 8
        {4, 4}    // Cidade 9
};



double calcularDistancia(Coordenada cidadeA, Coordenada cidadeB) {
    double distancia = sqrt(pow(cidadeA.x - cidadeB.x, 2) + pow(cidadeA.y - cidadeB.y, 2));
    return distancia;
}

double calcularFitness(Cromossomo *cromossomo) {
    double fitness = 0;
    int i;
    for (i = 0; i < NUM_CIDADES - 1; i++) {
        int cidadeA = cromossomo->genes[i];
        int cidadeB = cromossomo->genes[i + 1];
        fitness += calcularDistancia(cidades[cidadeA], cidades[cidadeB]);
    }
    // Adiciona a distância entre a última cidade e a primeira cidade
    int cidadeA = cromossomo->genes[NUM_CIDADES - 1];
    int cidadeB = cromossomo->genes[0];
    fitness += calcularDistancia(cidades[cidadeA], cidades[cidadeB]);

    cromossomo->fitness = fitness;
    return fitness;
}

void inicializarPopulacao(Cromossomo populacao[]) {
    int i, j;
    for (i = 0; i < TAM_POPULACAO; i++) {
        for (j = 0; j < NUM_CIDADES; j++) {
            populacao[i].genes[j] = j;
        }
        // Embaralhar os genes do cromossomo
        for (j = NUM_CIDADES - 1; j > 0; j--) {
            int randIndex = rand() % (j + 1);
            int temp = populacao[i].genes[j];
            populacao[i].genes[j] = populacao[i].genes[randIndex];
            populacao[i].genes[randIndex] = temp;
        }
        populacao[i].fitness = calcularFitness(&populacao[i]);
    }
}

void ordenarPopulacao(Cromossomo populacao[]) {
    int i, j;
    for (i = 0; i < TAM_POPULACAO - 1; i++) {
        for (j = 0; j < TAM_POPULACAO - i - 1; j++) {
            if (populacao[j].fitness > populacao[j + 1].fitness) {
                Cromossomo temp = populacao[j];
                populacao[j] = populacao[j + 1];
                populacao[j + 1] = temp;
            }
        }
    }
}

void realizarCrossover(Cromossomo *pai1, Cromossomo *pai2, Cromossomo *filho) {
    int pontoCorte = rand() % NUM_CIDADES;

    int i;
    for (i = 0; i < pontoCorte; i++) {
        filho->genes[i] = pai1->genes[i];
    }

    int indexFilho = pontoCorte;
    for (i = 0; i < NUM_CIDADES; i++) {
        int gene = pai2->genes[i];
        int j;
        for (j = 0; j < pontoCorte; j++) {
            if (filho->genes[j] == gene) {
                break;
            }
        }
        if (j == pontoCorte) {
            filho->genes[indexFilho++] = gene;
        }
    }
}

void realizarMutacao(Cromossomo *cromossomo) {
    int i;
    for (i = 0; i < NUM_CIDADES; i++) {
        if ((double)rand() / RAND_MAX < TAXA_MUTACAO) {
            int j = rand() % NUM_CIDADES;
            int temp = cromossomo->genes[i];
            cromossomo->genes[i] = cromossomo->genes[j];
            cromossomo->genes[j] = temp;
        }
    }
}

void imprimirMelhorCromossomo(Cromossomo *cromossomo) {
    printf("Melhor cromossomo (Fitness: %lf): ", cromossomo->fitness);
    int i;
    for (i = 0; i < NUM_CIDADES; i++) {
        printf("%d ", cromossomo->genes[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    Cromossomo melhorCromossomo;

    Cromossomo populacao[TAM_POPULACAO];
    Cromossomo novaPopulacao[TAM_POPULACAO];

    inicializarPopulacao(populacao);

    int geracao;
    melhorCromossomo = populacao[0];
    for (geracao = 0; geracao < NUM_GERACOES; geracao++) {
        int i;

        // Avaliar o fitness de cada cromossomo
        for (i = 0; i < TAM_POPULACAO; i++) {
            calcularFitness(&populacao[i]);
        }

        // Ordenar a população pelo fitness
        ordenarPopulacao(populacao);

        // Imprimir o melhor cromossomo da geração atual
//        imprimirMelhorCromossomo(&populacao[0]);

        if(populacao[0].fitness < melhorCromossomo.fitness){
            melhorCromossomo = populacao[0];
        }

        // Realizar crossover e mutação para criar a nova população
        for (i = 0; i < TAM_POPULACAO; i += 2) {
            Cromossomo *pai1 = &populacao[i];
            Cromossomo *pai2 = &populacao[i + 1];
            Cromossomo *filho1 = &novaPopulacao[i];
            Cromossomo *filho2 = &novaPopulacao[i + 1];

            realizarCrossover(pai1, pai2, filho1);
            realizarCrossover(pai2, pai1, filho2);

            realizarMutacao(filho1);
            realizarMutacao(filho2);
        }

        // Atualizar a população atual com a nova população
        for (i = 0; i < TAM_POPULACAO; i++) {
            populacao[i] = novaPopulacao[i];
        }
    }

    imprimirMelhorCromossomo(&melhorCromossomo);
    return 0;
}
