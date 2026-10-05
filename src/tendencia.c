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

double calcular_media(double *dataset, int *tamanho) {
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

double calcular_mediana(double *dataset, int *tamanho) {
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