#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "struct_e_param.h"

void ordenarPopulacao(Cromossomo **populacao);
void trocarCromossomos(Cromossomo *a, Cromossomo *b);
int particionar(Cromossomo **populacao, int inicio, int fim);
void quicksort(Cromossomo **populacao, int inicio, int fim);
void bubbleSort(Cromossomo **populacao);

void ordenarPopulacao(Cromossomo **populacao)
{
    // bubbleSort(populacao);
    quicksort(populacao, 0, TAM_POPULACAO - 1);
}

void trocarCromossomos(Cromossomo *a, Cromossomo *b)
{
    Cromossomo temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(Cromossomo **populacao, int inicio, int fim)
{
    double pivo = (*populacao)[inicio].fitness;
    int i = inicio + 1;
    int j = fim;

    while (i <= j)
    {
        while ((*populacao)[i].fitness < pivo && i < j)
            i++;
        while ((*populacao)[j].fitness > pivo && j > i - 1)
            j--;
        if (i < j)
        {
            trocarCromossomos(&(*populacao)[i], &(*populacao)[j]);
            i++;
            j--;
        }
        else
            break;
    }
    if ((*populacao)[j].fitness < pivo)
        trocarCromossomos(&(*populacao)[inicio], &(*populacao)[j]);
    else if ((*populacao)[i].fitness < pivo) // Desnecessário?
        trocarCromossomos(&(*populacao)[inicio], &(*populacao)[i]);
    return j;
}

void quicksort(Cromossomo **populacao, int inicio, int fim)
{
    if (inicio < fim)
    {
        int indicePivo = particionar(populacao, inicio, fim);
        quicksort(populacao, inicio, indicePivo);
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

#endif