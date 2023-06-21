#include "cromossomo.h"
#include <omp.h>

int main()
{

    clock_t start = clock();
    unsigned long seed = mix(clock(), time(NULL), getpid());
    srand(seed);

    Coordenada *cidades = (Coordenada *)malloc(sizeof(Coordenada) * NUM_CIDADES);
    Cromossomo *populacao = (Cromossomo *)malloc(sizeof(Cromossomo) * TAM_POPULACAO);
    Cromossomo *novaPopulacao = (Cromossomo *)malloc(sizeof(Cromossomo) * TAM_POPULACAO);
    Cromossomo melhorCromossomo;

    if (!cidades || !populacao || !novaPopulacao)
    {
        printf("Deu ruim na alocação.\n");
        exit(EXIT_FAILURE);
    }

    lerCoordenadas(&cidades);
    inicializarPopulacao(&populacao, &cidades);

    melhorCromossomo = populacao[0];

    for (int geracao = 0; geracao < NUM_GERACOES; geracao++)
    {
        // Avaliar o fitness de cada cromossomo
        for (int i = 0; i < TAM_POPULACAO; i++)
            calcularFitness(&populacao[i], &cidades);

        // Ordenar a população pelo fitness
        ordenarPopulacao(&populacao);

        if (populacao[0].fitness < melhorCromossomo.fitness)
            melhorCromossomo = populacao[0];

        // Realizar crossover e mutação para criar a nova população
        for (int i = 0; i < TAM_POPULACAO; i += 2)
        {
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
        for (int i = 0; i < TAM_POPULACAO; i++)
            populacao[i] = novaPopulacao[i];
    }

    imprimirMelhorCromossomo(&melhorCromossomo);

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTempo: %.5f segundos\n", elapsed);
    return 0;
}
