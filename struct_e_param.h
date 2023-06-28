#ifndef STRUCT_E_PARAM_H
#define STRUCT_E_PARAM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define NUM_CIDADES 200
#define TAM_POPULACAO 600
#define NUM_GERACOES 600
#define TAXA_MUTACAO 0.1
#define PRECISAO 1e-2
#define NUM_THREADS 12

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