#include <stdio.h>
#include <stdlib.h>

double* organizar(double *dataset, int *tamanho){
  for (int i = 1; i < *tamanho; i++){
    int n = 0;
    while ((i-n-1) >= 0 && dataset[i-n] < dataset[i-n-1]){
      double tmp = dataset[i-n-1];
      dataset[i-n-1] = dataset[i-n];
      dataset[i-n] = tmp;
      n++;
    }
  }
  return dataset;
}

double* copia_dataset(double *dataset, int *tamanho) {
    if (dataset == NULL || tamanho == NULL || *tamanho <= 0) {
        printf("Erro: dataset vazio ou inválido.\n");
        exit(1);
    }

    double *copia = malloc(*tamanho * sizeof *dataset);
    if (copia == NULL) {
        printf("Erro ao inicializar o vetor dinâmico da cópia do array");
        printf("Erro ao inicializar o vetor dinâmico da cópia do array\n");
        return dataset;
    }

    for (int i = 0; i < *tamanho; i++) {
        copia[i] = dataset[i];
    }

    return copia;
}

double esperanca(double *dataset, int *tamanho) {
    //tenho que ajustar o retorno de erro
    if (dataset == NULL || tamanho == NULL || *tamanho <= 0) {
        printf("Erro: dataset vazio ou inválido.\n");
        exit(1);
    }

    else {
        double soma = 0;

        for (int i = 0; i < *tamanho; i++) {
            soma += dataset[i];
        }

        double media = (soma / *tamanho);
        return media;
    }
}

double mediana(double *dataset, int *tamanho) {
    if (dataset == NULL || tamanho == NULL || *tamanho <= 0) {
        printf("Erro: dataset vazio ou inválido.\n");
        exit(1);
    }

    else {
        double *copia = copia_dataset(dataset, tamanho);
        copia = organizar(copia, tamanho);

        int i = (*tamanho/2);
        double mediana;

        if (*tamanho%2 == 0) {
            mediana = ( copia[i] + copia[i-1] ) / 2.0; 
        }
        else {
            mediana = copia[i];
        }

        free(copia);
        
        return mediana;
    }
}

double* pegar_moda(double *valores, int *repets, int j, int maior, int *qtd_modas) {

    double *modas = malloc(sizeof *modas);
    int k = 0;

    for (int i = 0; i <= j; i++) {
        if (repets[i] == maior) {
            
            double *tmp = realloc(modas, (k+1) * sizeof *modas);
            if (tmp == NULL) {
                free(modas);
                printf("Erro na criação de vetor dinâmico.\n");
                exit(1);
            }
            modas = tmp;

            modas[k] = valores[i];
            k += 1;

        }
    }

    *qtd_modas = k;
    return modas;
}

double* moda(double *dataset, int *tamanho, int *qtd_modas) {
    if (dataset == NULL || tamanho == NULL || *tamanho <= 0) {
        printf("Erro: dataset vazio ou inválido.\n");
        exit(1);
    }  

    double *copia = copia_dataset(dataset, tamanho);
    copia = organizar(copia, tamanho);

    double *modas = malloc(sizeof *modas);
    double *valores = malloc(sizeof *valores);
    int *repets = malloc(sizeof *repets);

    valores[0] = copia[0];
    repets[0] = 1;

    int maior = repets[0];

    int j = 0;

    for(int i = 1; i < *tamanho; i++) {

        if (copia[i] != copia[i-1]) {
            j += 1;

            double *tmp_val = realloc(valores, (j+1) * sizeof *valores);
            if (tmp_val == NULL) {
                free(valores);
                printf("Erro na criação de vetor dinâmico.\n");
                exit(1);
            }
            valores = tmp_val;

            int *tmp_rep = realloc(repets, (j+1) * sizeof *repets);
            if (tmp_rep == NULL) {
                free(repets);
                printf("Erro na criação de vetor dinâmico.\n");
                exit(1);
            }
            repets = tmp_rep;

            valores[j] = copia[i];
            repets[j] = 1;
        }

        else {
            repets[j] += 1;
        }

        if (repets[j] > maior) {
            maior = repets[j];
        }

    }

    double *moda_array = pegar_moda(valores, repets, j, maior, qtd_modas);

    return moda_array;
}

int main() {
    int tamanho = 3;
    double dataset[3] = {2,2,1}; // Pode inicializar diretamente assim
    int qtd_modas = 0;

    // printf("Mediana: %.2f\n", calcular_mediana(dataset, &tamanho));

    double *modas = moda(dataset, &tamanho, &qtd_modas);

    for (int i = 0; i < qtd_modas; i++) {
        printf("%.2f ", modas[i]);
    }

    return 0;
}