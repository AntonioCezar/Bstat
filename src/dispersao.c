    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "dispersao.h"
    #include "distribuicao.h"
    #include "tendencia.h"
    #include "error.h"

    // se o número for não negativo a função retorna a raiz quadrada do número
    // caso contrário, retorna NAN

    double variancia(double* dataset, int tamanho) {
        if (dataset == NULL || tamanho <= 0) {
            processar_erro(2, "Dataset vazio ou invalido");
            printf("Erro: dataset vazio ou inválido.\n");
            return NAN;
        }

        double med = media(dataset, tamanho);

        double var = 0;
        for (int i = 0; i < tamanho; i++) {
            var += elevado(med - dataset[i], 2);
        }

        return (var / tamanho);
    }

    double desvio_padrao(double* dataset, int tamanho) {
        
        if (dataset == NULL || tamanho <= 0) {
            processar_erro(2, "Dataset vazio ou inválido");
            printf("Erro: dataset vazio ou inválido.\n");
            return NAN;                                         
        }                                   

        double var = variancia(dataset, tamanho);

        // Proteção: Se a variância deu erro (NAN) ou é inválida, pare!
        if (isnan(var) || var < 0) {
            processar_erro(2, "Variancia invalida para calculo do desvio padrao");
            printf("Erro: Variância inválida.\n");
            return NAN;
        }

        return sqrt(var);
    }

    double amplitude(double* dataset, int tamanho) {

        if (dataset == NULL || tamanho <= 0) {
            processar_erro(2, "Dataset vazio ou inválido");
            printf("Erro: dataset vazio ou inválido.\n");
            return NAN;
        }

        double max = dataset[0];
        double min = dataset[0];
        for (int i = 1; i < tamanho; i++) {
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
    // caso contrário retorna NAN 
    double coef_variacao(double* dataset, int tamanho) {
        if (dataset == NULL || tamanho <= 0) {
            processar_erro(2, "Dataset vazio ou inválido");
            printf("Erro: dataset vazio ou inválido.\n");
            return NAN;
        }

        double med = media(dataset, tamanho);
        if (med == 0) {
            processar_erro(2, "Coeficiente de variação não pode ser calculado, pois a média é igual a zero");
            printf("Erro: coeficiente de variação não pode ser calculado, pois a média é igual a zero\n");
            return NAN;
        }
        double desvio = desvio_padrao(dataset, tamanho);

        return (desvio / med);


    }



