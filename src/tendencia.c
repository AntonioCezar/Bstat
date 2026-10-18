#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/tendencia.h"
#include "../include/dados.h"
#include "../errors/error.h"
#include "../include/transformacao.h"

int quase_igual(double a, double b) {
    double d = a - b;
    if (d < 0) d = -d;
    //Diferença tolerada
    return d < 1e-9;  
}

static int validar_tamanho(int tamanho) {
    if (tamanho <= 0) {
        processar_erro(1, "Tamanho inválido para o array");
        printf("Erro: tamanho inválido para o array\n");
        return 0;
    }
    return 1;
}

double media(const double *dataset, int tamanho) {
    if(!validarvetor(dataset) || !validar_tamanho(tamanho))
        return NAN;

    double soma = 0;

    for (int i = 0; i < tamanho; i++) {
        soma += dataset[i];
    }

    double media = (soma / tamanho);
    return media;
}

double mediana(const double *dataset, int tamanho) {
    if (!validarvetor(dataset) || !validar_tamanho(tamanho)) 
        return NAN;

    double *copia = organizar(dataset, tamanho);
    if (copia == NULL) return NAN;

    int i = (tamanho/2);
    double mediana;

    if (tamanho%2 == 0) {
        mediana = ( copia[i] + copia[i-1] ) / 2.0; 
    }
    else {
        mediana = copia[i];
    }

    liberar_dados(copia);
    
    return mediana;
}

static double* pegar_moda(double *copia, int tamanho, int maior_freq, int qtd_modas, int *apont_qtd_modas) {

    double *modas = novovet(qtd_modas);
    if (modas == NULL) {
        processar_erro(1, "Falha ao alocar o vetor de modas");
        printf("Falha ao alocar o vetor de modas\n");
        return NULL;
    }

    //Percorre o vetor das modas
    int idx_modas = 0, freq_atual = 1;

    for (int i = 1; i < tamanho; i++) {

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
        modas[idx_modas] = copia[tamanho-1];
    }

    *apont_qtd_modas = qtd_modas;
    return modas;
}

double* moda(const double *dataset, int tamanho, int *apont_qtd_modas) {
    if (apont_qtd_modas == NULL) {
        processar_erro(1, "Ponteiro de quantidade de modas inválido"); 
        printf("Ponteiro de quantidade de modas inválido\n");
        return NULL;
    }    
    *apont_qtd_modas = 0;

    if (!validarvetor(dataset) || !validar_tamanho(tamanho)) return NULL;

    double *copia = organizar(dataset, tamanho);
    if (copia == NULL) return NULL;

    int maior_freq = 1, freq_atual = 1, qtd_modas = 0;

    //Identifica o número de repetições da moda e a quantidade de modas
    for(int i = 1; i < tamanho; i++) {

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

    //Caso amodal
    if ((tamanho > 1) && (qtd_modas == tamanho)) {
        liberar_dados(copia);
        return NULL;
    }

    //Seleciona os valores que mais se repetem
    double *moda_array = pegar_moda(copia, tamanho, maior_freq, qtd_modas, apont_qtd_modas);

    liberar_dados(copia);

    return moda_array;
}