#ifndef STRUCT_E_PARAM_H
#define STRUCT_E_PARAM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define NUM_CIDADES 50
#define TAM_POPULACAO 4950
#define NUM_GERACOES 5000
#define TAXA_MUTACAO 0.0
#define PRECISAO 1e-6

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

#endif