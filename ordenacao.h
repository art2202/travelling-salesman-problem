#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "struct_e_param.h"

void trocarCromossomos(Cromossomo *a, Cromossomo *b);
int particionar(Cromossomo **populacao, int inicio, int fim);
void quicksort(Cromossomo **populacao, int inicio, int fim);
void bubbleSort(Cromossomo **populacao);
void ordenarPopulacao(Cromossomo **populacao);

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

#endif