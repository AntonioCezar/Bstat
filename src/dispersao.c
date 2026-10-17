#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dispersao.h"
#include "distribuicao.h"
#include "tendencia.h"
#include "error.h"

double valor_absoluto(double num) {
    if (num < 0) return -num;
    else return num;
}

// se o número for não negativo a função retorna a raiz quadrada do número
// caso contrário, retorna 1
double raiz_quadrada(double num) {
    if (num < 0) return -1;
    if (num == 0) return 0;

    double palpite = num / 2.0;
    double margem_de_erro = 0.000001; 
    double diferença;

    while (valor_absoluto((palpite * palpite) - num) > margem_de_erro) {
        palpite = 0.5 * (palpite + (num / palpite));
    }

    return palpite;
}

double variancia(double* dataset, int tamanho) {
    if (dataset == NULL || tamanho <= 0) {
        processar_erro(1, "Dataset vazio ou invalido");
        printf("Erro: dataset vazio ou inválido.\n");
        return NAN;
    }

    double med = media(dataset, tamanho);

    double var = 0;
    for (int i = 0; i < tamanho; i++) {
        var += pow(med - dataset[i], 2);
    }

    return (var / tamanho);
}

double desvio_padrao(double* dataset, int tamanho) {
    
    if (dataset == NULL || tamanho <= 0) {
        processar_erro(1, "Dataset vazio ou inválido");
        printf("Erro: dataset vazio ou inválido.\n");
        return NAN;
    }
    
    double var = variancia(dataset, tamanho);
    return raiz_quadrada(var);
}

double amplitude(double* dataset, int tamanho) {

    if (dataset == NULL || tamanho <= 0) {
        processar_erro(1, "Dataset vazio ou inválido");
        printf("Erro: dataset vazio ou inválido.\n");
        return NAN;
    }

    double max = dataset[0];
    double min = dataset[0];
    for (int i = 0; i < tamanho; i++) {
        if (dataset[i] > max) {
            max = dataset[i];
        }

        if (dataset[i] < min) {
            min = dataset[i];
        }
    }

    return max - min;
}

// Caso a média seja diferente de 0 calcula o coeficiente de variação
// caso contrário retorna -1 
double coef_variacao(double* dataset, int tamanho) {
    if (dataset == NULL || tamanho <= 0) {
        processar_erro(1, "Dataset vazio ou inválido");
        printf("Erro: dataset vazio ou inválido.\n");
        return NAN;
    }

    double med = media(dataset, tamanho);
    if (med == 0) {
        processar_erro(1, "coeficiente de variação não pode ser calculado, pois a média é igual a zero");
        printf("Erro: coeficiente de variação não pode ser calculado, pois a média é igual a zero\n");
        return NAN;
    }
    double desvio = desvio_padrao(dataset, tamanho);

    return (desvio / med);


}



