#ifndef CALCULOS_H
#define CALCULOS_H

#include "struct_e_param.h"

double calcularRaizQuadrada(double x);
double calcularDistancia(Coordenada cidadeA, Coordenada cidadeB);

double calcularRaizQuadrada(double x)
{
    if (!x) // x == 0.0
        return x;

    double estimativa = x;
    double erro = PRECISAO; // Precisão desejada
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
    //    return sqrt(pow(cidadeA.x - cidadeB.x, 2) + pow(cidadeA.y - cidadeB.y, 2)); // Pré-otimização
    return sqrt((cidadeA.x - cidadeB.x) * (cidadeA.x - cidadeB.x) + (cidadeA.y - cidadeB.y) * (cidadeA.y - cidadeB.y));
}

#endif