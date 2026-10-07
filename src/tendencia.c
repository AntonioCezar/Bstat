#include <stdio.h>
#include <stdlib.h>

double* copia_dataset(double *dataset, int *tamanho) {
    if (dataset == NULL || tamanho == NULL || *tamanho <= 0) {
        printf("Erro: dataset vazio ou inválido.\n");
        exit(1);
    }

    double *copia = malloc(*tamanho * sizeof *dataset);
    if (copia == NULL) {
        printf("Erro ao inicializar o vetor dinâmico da cópia do array");
        return dataset;
    }

    for (int i = 0; i < *tamanho; i++) {
        copia[i] = dataset[i];
    }

    return copia;
}

static int quase_igual(double a, double b) {
    double d = a - b;
    if (d < 0) d = -d;
    //Diferença tolerada
    return d < 1e-9;  
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

static double* pegar_moda(double *copia, int *tamanho, int maior_freq, int qtd_modas, int *apont_qtd_modas) {

    double *modas = malloc(qtd_modas * sizeof *modas);
    if (modas == NULL) {
        printf("Erro ao inicializar o vetor dinâmico\n");
        return NULL;
    }

    //Percorre o vetor das modas
    int idx_modas = 0, freq_atual = 1;

    for (int i = 1; i < *tamanho; i++) {

        if (quase_igual(copia[i-1],copia[i])) {
            freq_atual += 1;
        }   
        else {
            if (freq_atual == maior_freq) {
                modas[idx_modas] = copia[i-1];
                idx_modas += 1;
            } 
            freq_atual = 1;
        }
    }

    //Processa o último grupo após o término do loop
    if (freq_atual == maior_freq) {
        modas[idx_modas] = copia[*tamanho-1];
    }

    *apont_qtd_modas = qtd_modas;
    return modas;
}

double* moda(double *dataset, int *tamanho, int *apont_qtd_modas) {
    if (dataset == NULL || tamanho == NULL || *tamanho <= 0) {
        printf("Erro: dataset vazio ou inválido.\n");
        exit(1);
    }  

    double *copia = copia_dataset(dataset, tamanho);
    copia = organizar(copia, tamanho);

    int maior_freq = 1, freq_atual = 1, qtd_modas = 0;

    //Identifica o número de repetições da moda e a quantidade de modas
    for(int i = 1; i < *tamanho; i++) {

        if (quase_igual(copia[i], copia[i-1])) {
            freq_atual += 1;
        }
        else {
            if (freq_atual > maior_freq) {
                maior_freq = freq_atual;
                qtd_modas = 1;
            }
            else if (freq_atual == maior_freq) {
                qtd_modas += 1;
            }
            freq_atual = 1;
        }

    }

    //Processa o último grupo após o término do loop
    if (freq_atual > maior_freq) {
        maior_freq = freq_atual;
        qtd_modas = 1;
    } else if (freq_atual == maior_freq) {
        qtd_modas += 1;
    }

    //Seleciona os valores que mais se repetem
    double *moda_array = pegar_moda(copia, tamanho, maior_freq, qtd_modas, apont_qtd_modas);

    free(copia);

    return moda_array;
}

int main() {
    int tamanho = 1;
    double dataset[1] = {10};
    int num_modas = 0;

    double *modas = moda(dataset, &tamanho, &num_modas);

    for (int i = 0; i < num_modas; i++) {
        printf("%.2f\n", modas[i]);
    }

    return 0;
}