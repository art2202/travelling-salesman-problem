#ifndef CALCULOS_H
#define CALCULOS_H

#include "struct_e_param.h"

double calcularRaizQuadrada(double x);
double calcularDistancia(Coordenada cidadeA, Coordenada cidadeB);
unsigned long mix(unsigned long a, unsigned long b, unsigned long c);

double calcularRaizQuadrada(double x)
{
    if (!x) // x == 0.0
        return x;

    double estimativa = x;
    double erro = PRECISAO;
    double diferenca;

    do
    {
        double novaEstimativa = (estimativa + x) / (estimativa * 2.0);
        diferenca = novaEstimativa - estimativa;
        estimativa = novaEstimativa;
    } while (diferenca > erro || diferenca < -erro);

    return estimativa;
}

double calcularDistancia(Coordenada cidadeA, Coordenada cidadeB)
{
    //  return sqrt(pow(cidadeA.x - cidadeB.x, 2) + pow(cidadeA.y - cidadeB.y, 2)); // Pré-otimização
    return sqrt((cidadeA.x - cidadeB.x) * (cidadeA.x - cidadeB.x) + (cidadeA.y - cidadeB.y) * (cidadeA.y - cidadeB.y));
    //  return calcularRaizQuadrada((cidadeA.x - cidadeB.x) * (cidadeA.x - cidadeB.x) + (cidadeA.y - cidadeB.y) * (cidadeA.y - cidadeB.y)); // NÃO ESTÁ FUNCIONANDO
}

unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a = a - b;
    a = a - c;
    a = a ^ (c >> 13);
    b = b - c;
    b = b - a;
    b = b ^ (a << 8);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 13);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 12);
    b = b - c;
    b = b - a;
    b = b ^ (a << 16);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 5);
    a = a - b;
    a = a - c;
    a = a ^ (c >> 3);
    b = b - c;
    b = b - a;
    b = b ^ (a << 10);
    c = c - a;
    c = c - b;
    c = c ^ (b >> 15);
    return c;
}

#endif