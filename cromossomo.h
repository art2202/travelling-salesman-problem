#ifndef CROMOSSOMO_H
#define CROMOSSOMO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_CIDADES 50
#define TAM_POPULACAO 4950
#define NUM_GERACOES 5000
#define TAXA_MUTACAO 0.0000001

typedef struct Cromossomo
{
    int genes[NUM_CIDADES];
    double fitness;
} Cromossomo;

typedef struct Coordenada
{
    double x;
    double y;
} Coordenada;

void lerCoordenadas(Coordenada **cidades);
double calcularRaizQuadrada(double x);
double calcularDistancia(Coordenada cidadeA, Coordenada cidadeB);
double calcularFitness(Cromossomo *cromossomo, Coordenada **cidades);
void inicializarPopulacao(Cromossomo **populacao, Coordenada **cidades);
void trocarCromossomos(Cromossomo *a, Cromossomo *b);
int particionar(Cromossomo **populacao, int inicio, int fim);
void quicksort(Cromossomo **populacao, int inicio, int fim);
void bubbleSort(Cromossomo **populacao);
void ordenarPopulacao(Cromossomo **populacao);
void realizarCrossover(Cromossomo *pai1, Cromossomo *pai2, Cromossomo *filho);
void realizarMutacao(Cromossomo *cromossomo);
void imprimirMelhorCromossomo(Cromossomo *cromossomo);

void lerCoordenadas(Coordenada **cidades)
{
    int i;
    FILE *arquivo = fopen("coordenadas", "r");
    //  FILE* arquivo = fopen("C:\\Users\\Arthu\\CLionProjects\\travelling-salesman-problem\\coordenadas", "r");

    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo. \n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < NUM_CIDADES; i++)
        fscanf(arquivo, "%lf %lf", &(*cidades)[i].x, &(*cidades)[i].y);

    fclose(arquivo);
}

double calcularRaizQuadrada(double x)
{
    if (x == 0.0)
    {
        return 0.0;
    }

    double estimativa = x;
    double erro = 1e-6; // Precisão desejada
    double diferenca;

    do
    {
        double novaEstimativa = (estimativa + x / estimativa) / 2.0;
        diferenca = novaEstimativa - estimativa;
        estimativa = novaEstimativa;
    } while (diferenca > erro || diferenca < -erro);

    return estimativa;
}

double calcularDistancia(Coordenada cidadeA, Coordenada cidadeB)
{
    //    return sqrt(pow(cidadeA.x - cidadeB.x, 2) + pow(cidadeA.y - cidadeB.y, 2));
    return sqrt((cidadeA.x - cidadeB.x) * (cidadeA.x - cidadeB.x) + (cidadeA.y - cidadeB.y) * (cidadeA.y - cidadeB.y));
}
void inicializarPopulacao(Cromossomo **populacao, Coordenada **cidades)
{
    int i, j;
    for (i = 0; i < TAM_POPULACAO; i++)
    {
        for (j = 0; j < NUM_CIDADES; j++)
        {
            (*populacao)[i].genes[j] = j;
        }
        // Embaralhar os genes do cromossomo
        for (j = NUM_CIDADES - 1; j > 0; j--)
        {
            int randIndex = rand() % (j + 1);
            int temp = (*populacao)[i].genes[j];
            (*populacao)[i].genes[j] = (*populacao)[i].genes[randIndex];
            (*populacao)[i].genes[randIndex] = temp;
        }
        (*populacao)[i].fitness = calcularFitness(&(*populacao)[i], cidades);
    }
}

double calcularFitness(Cromossomo *cromossomo, Coordenada **cidades)
{
    double fitness = 0;
    int i;
    for (i = 0; i < NUM_CIDADES - 1; i++)
    {
        int cidadeA = cromossomo->genes[i];
        int cidadeB = cromossomo->genes[i + 1];
        fitness += calcularDistancia((*cidades)[cidadeA], (*cidades)[cidadeB]);
    }
    // Adiciona a distância entre a última cidade e a primeira cidade
    int cidadeA = cromossomo->genes[NUM_CIDADES - 1];
    int cidadeB = cromossomo->genes[0];
    fitness += calcularDistancia((*cidades)[cidadeA], (*cidades)[cidadeB]);

    cromossomo->fitness = fitness;
    return fitness;
}

void trocarCromossomos(Cromossomo *a, Cromossomo *b)
{
    Cromossomo temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(Cromossomo **populacao, int inicio, int fim)
{
    int pivo = (*populacao)[fim].fitness;
    int i = inicio - 1;
    int j;

    for (j = inicio; j <= fim - 1; j++)
    {
        if ((*populacao)[j].fitness <= pivo)
        {
            i++;
            trocarCromossomos(&(*populacao)[i], &(*populacao)[j]);
        }
    }

    trocarCromossomos(&(*populacao)[i + 1], &(*populacao)[fim]);
    return (i + 1);
}

void quicksort(Cromossomo **populacao, int inicio, int fim)
{
    if (inicio < fim)
    {
        int indicePivo = particionar(populacao, inicio, fim);
        quicksort(populacao, inicio, indicePivo - 1);
        quicksort(populacao, indicePivo + 1, fim);
    }
}

void bubbleSort(Cromossomo **populacao)
{
    int i, j;
    for (i = 0; i < TAM_POPULACAO - 1; i++)
    {
        for (j = 0; j < TAM_POPULACAO - i - 1; j++)
        {
            if ((*populacao)[j].fitness > (*populacao)[j + 1].fitness)
            {
                Cromossomo temp = (*populacao)[j];
                (*populacao)[j] = (*populacao)[j + 1];
                (*populacao)[j + 1] = temp;
            }
        }
    }
}

void ordenarPopulacao(Cromossomo **populacao)
{
    //    bubbleSort(populacao);
    quicksort(populacao, 0, TAM_POPULACAO - 1);
}

void realizarCrossover(Cromossomo *pai1, Cromossomo *pai2, Cromossomo *filho)
{
    int pontoCorte = rand() % NUM_CIDADES;

    int i;
    for (i = 0; i < pontoCorte; i++)
    {
        filho->genes[i] = pai1->genes[i];
    }

    int indexFilho = pontoCorte;
    for (i = 0; i < NUM_CIDADES; i++)
    {
        int gene = pai2->genes[i];
        int j;
        for (j = 0; j < pontoCorte; j++)
        {
            if (filho->genes[j] == gene)
            {
                break;
            }
        }
        if (j == pontoCorte)
        {
            filho->genes[indexFilho++] = gene;
        }
    }
}

void realizarMutacao(Cromossomo *cromossomo)
{
    int i;
    for (i = 0; i < NUM_CIDADES; i++)
    {
        if ((double)rand() / RAND_MAX < TAXA_MUTACAO)
        {
            int j = rand() % NUM_CIDADES;
            int temp = cromossomo->genes[i];
            cromossomo->genes[i] = cromossomo->genes[j];
            cromossomo->genes[j] = temp;
        }
    }
}

void imprimirMelhorCromossomo(Cromossomo *cromossomo)
{
    printf("Melhor cromossomo (Fitness: %lf): ", cromossomo->fitness);
    int i;
    for (i = 0; i < NUM_CIDADES; i++)
    {
        printf("%d ", cromossomo->genes[i]);
    }
    printf("\n");
}

#endif // CROMOSSOMO_H
