#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "../include/dispersao.h"
#include "../include/dados.h"

// Classe dos casos esperados
typedef struct {                                                            
    const char *arquivo;
    double variancia;
    double desvio_padrao;
    double amplitude;
    double coef_variacao;
    double *dataset;
    int tamanho;
} Caso;

// Vetor que armazena os casos esperados
static Caso casos[] = {
    {"tests/data/tendencia/simples.txt", 283.34190000, 16.83276270, 59.00, 0.59249429},
    {"tests/data/tendencia/multimodal.txt", 832.03040000, 28.84493716, 96.00, 0.58108254},
    {"tests/data/tendencia/decimais.txt", 177.18417275, 13.31105453, 44.61, 4.27527036},
};

// armazena o tamanho do vetor de casos esperados
#define NUM_CASOS ((int) (sizeof(casos)/sizeof(casos[0])))

// prenche o dataset com os dados dos arquivos
static void preencher_dataset(void) {
    int tamanho;
    for (int i = 0; i < NUM_CASOS; i++) {
        casos[i].dataset = coletar_dados(casos[i].arquivo, &tamanho);
        casos[i].tamanho = tamanho;
    }
}

// libera o dataset passado
static void liberar_dataset(void) {
    for (int i = 0; i < NUM_CASOS; i++)
        liberar_dados(casos[i].dataset);
}

// testa a função variancia
static void teste_variancia(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        ASSERT_EQ_DOUBLE(casos[i].variancia, variancia(casos[i].dataset, casos[i].tamanho)); 
    }
}

// testa a função desvio_padrao
static void teste_desvio_padrao(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        ASSERT_EQ_DOUBLE(casos[i].desvio_padrao, desvio_padrao(casos[i].dataset, casos[i].tamanho));
    }
}

// testa a função amplitude 
static void teste_amplitude(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        ASSERT_EQ_DOUBLE(casos[i].amplitude, amplitude(casos[i].dataset, casos[i].tamanho));
    }
}

// testa a função coef_variacao
static void teste_coef_variacao(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        ASSERT_EQ_DOUBLE(casos[i].coef_variacao, coef_variacao(casos[i].dataset, casos[i].tamanho));
    }
}

// roda os testes
int main(void) {
    preencher_dataset();
    RUN_TESTE(teste_variancia);
    RUN_TESTE(teste_desvio_padrao);
    RUN_TESTE(teste_amplitude);
    RUN_TESTE(teste_coef_variacao);
    liberar_dataset();
    RESUMO_TESTE();
}
