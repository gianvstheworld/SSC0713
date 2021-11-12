#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define TAMPOP 10

float MutTax = 2; // No máximo 5%
double crom[TAMPOP]; // vetor com o TAMANHO DA POPULAÇÃO, tendo cada gene dos indivíduos
double fit[TAMPOP]; // vetor com o TAMANHO DA POPULAÇÃO, tendo o fitness de cada um dos indivíduos
int gen = 0;

void initPopulation(){ // cria população
    for (int i = 0; i < TAMPOP; i++){
        crom[i] = (double) (rand() % 1000); // define cada cromossomo do invíduo como um número aleatório 
    }
}

// essa função que torna o AG pesado, então quanto melhor ela está melhor o AG ficará
void fitnessFunction(){
    float aux0, aux1, function;

	printf("Generation %d\n",gen);

    for(int i = 0; i < TAMPOP; i++){
        aux0 = crom[i];
        float aux1 = aux0;

        if(aux0 > 500)
            aux1 = (2*cos(0.039*aux0) + 5*sin(0.05*aux0) + 0.5*cos(0.01*aux0))*10+500;

        fit[i] = aux1;

        printf("\tFitness %d - Cromossomo %f = %f\n", i, crom[i], fit[i]);
    }
}

// nunca perder o melhor invíduo; método de seleção pela melhor transa de todas - elitismo
void selection(){
    double maxFit = 0;
    int maxIteration = 0;

    maxFit = fit[0];

    for(int i = 1; i <= TAMPOP; i++){ // buscando pelo melhor indivíduo
        if(fit[i] > maxFit){
            maxFit = fit[i];
            maxIteration = i;
        }

        if(i != maxIteration) // Protegendo o melhor indivíduo
            break;
        
        // Crossover - melhores genes introduzido aos indivíduos
        // caso seja assexuado, não é necessário o Crossover
        crom[i] = (crom[i] + crom[maxIteration]) / 2.0;

        // Mutação 
        crom[i] = crom[i] + ((double) (rand() % 1000) - 500) * MutTax / 100.0;

        if(crom[i] > 1000)
            crom[i] = 1000;
        
        if(crom[i] < 0)
            crom[i] *= -1.0;
    }
}

int main(){

    srand(time(NULL));

    initPopulation();
    fitnessFunction();
    selection();
    gen++;

    return 0;
}