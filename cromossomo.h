#ifndef CROMOSSOMO_H
#define CROMOSSOMO_H

#include "calculos.h"
#include "ordenacao.h"

void lerCoordenadas(Coordenada **cidades);
double calcularFitness(Cromossomo *cromossomo, Coordenada **cidades);
void inicializarPopulacao(Cromossomo **populacao, Coordenada **cidades);
void realizarCrossover(Cromossomo *pai1, Cromossomo *pai2, Cromossomo *filho);
void realizarMutacao(Cromossomo *cromossomo);
void imprimirMelhorCromossomo(Cromossomo *cromossomo);

void lerCoordenadas(Coordenada **cidades)
{
    int i;
//    FILE *arquivo = fopen("coordenadas", "r");
      FILE* arquivo = fopen("C:\\Users\\Arthu\\CLionProjects\\travelling-salesman-problem\\coordenadas", "r");

    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo. \n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < NUM_CIDADES; i++)
    {
        if (!fscanf(arquivo, "%lf %lf", &(*cidades)[i].x, &(*cidades)[i].y))
        {
            printf("Erro na leitura do arquivo.\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(arquivo);
}

void inicializarPopulacao(Cromossomo **populacao, Coordenada **cidades)
{
    int i, j, randIndex, temp;
    for (i = 0; i < TAM_POPULACAO; i++)
    {
        for (j = 0; j < NUM_CIDADES; j++) // Pré-otimização
            (*populacao)[i].genes[j] = j;
        //(*populacao)[i].genes = {j};

        // Embaralhar os genes do cromossomo
        for (j = NUM_CIDADES - 1; j > 0; j--)
        {
            randIndex = rand() % (j + 1);
            temp = (*populacao)[i].genes[j];
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

        for (i = 0; i < NUM_CIDADES - 1; i++) {
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
