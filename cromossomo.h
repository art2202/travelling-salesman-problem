#ifndef CROMOSSOMO_H
#define CROMOSSOMO_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_CIDADES 200
#define TAM_POPULACAO 600
#define NUM_GERACOES 600
#define TAXA_MUTACAO 0.1
typedef struct {
    int genes[NUM_CIDADES];
    double fitness;
} Cromossomo;

typedef struct {
    double x;
    double y;
} Coordenada;

extern Coordenada cidades[NUM_CIDADES];

void lerCoordenadas();
double calcularRaizQuadrada(double x);
double calcularDistancia(Coordenada cidadeA, Coordenada cidadeB);
double calcularFitness(Cromossomo *cromossomo);
void inicializarPopulacao(Cromossomo populacao[]);
void trocarCromossomos(Cromossomo *a, Cromossomo *b);
int particionar(Cromossomo populacao[], int inicio, int fim);
void quicksort(Cromossomo populacao[], int inicio, int fim);
void bubbleSort(Cromossomo populacao[]);
void ordenarPopulacao(Cromossomo populacao[]);
void realizarCrossover(Cromossomo *pai1, Cromossomo *pai2, Cromossomo *filho);
void realizarMutacao(Cromossomo *cromossomo);
void imprimirMelhorCromossomo(Cromossomo *cromossomo);

#endif  // CROMOSSOMO_H
