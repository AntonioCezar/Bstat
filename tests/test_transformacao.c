#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "../include/transformacao.h"
#include "../include/dados.h"

#define MAX_VALORES 64
#define NUM_PERCENTIS 5

typedef struct {
    const char *arquivo;
    double organizado[MAX_VALORES];
    double normalizado[MAX_VALORES];
    double padronizado[MAX_VALORES];
    double percentis[NUM_PERCENTIS];
    double filtrado[MAX_VALORES];
    int qtd_filtrado;
    double *dataset;
    int tamanho;
} Caso;

// Porcentagens testadas em todos os casos (cobre os extremos 0 e 100)
static const double Porcentagens[NUM_PERCENTIS] = {0, 25, 50, 75, 100};

static Caso casos[] = {
    {"tests/data/transformacoes/desorganizado.txt",
     {0, 1, 2, 5, 6, 7, 10},
     {0.5, 1, 0, 0.7, 0.2, 0.6, 0.1},
     {0.1714985851, 1.672111205, -1.329114035, 0.7717436331, -0.7288689869, 0.4716211091, -1.028991511},
     {0, 1.5, 5, 6.5, 10},
     {5, 10, 0, 7, 2, 6, 1}, 7},
    {"tests/data/transformacoes/valores.txt",
     {12, 15, 18, 20, 22, 25, 30, 35, 40, 45},
     {0, 0.09090909091, 0.1818181818, 0.2424242424, 0.303030303, 0.3939393939, 0.5454545455, 0.696969697, 0.8484848485, 1},
     {-1.361613175, -1.07394842, -0.7862836643, -0.5945071608, -0.4027306573, -0.1150659021, 0.3643753566, 0.8438166153, 1.323257874, 1.802699133},
     {12, 18.5, 23.5, 33.75, 45},
     {12, 15, 18, 20, 22, 25, 30, 35, 40, 45}, 10},
    {"tests/data/transformacoes/valores_decimais.txt",
     {0.5, 1.25, 2.5, 3.5, 4.75, 6.125, 8.75},
     {0.3636363636, 0.09090909091, 1, 0.2424242424, 0.6818181818, 0, 0.5151515152},
     {-0.1538332491, -0.9965719178, 1.812556978, -0.5283837685, 0.8293618645, -1.277484807, 0.3143549002},
     {0.5, 1.875, 3.5, 5.4375, 8.75},
     {3.5, 1.25, 8.75, 2.5, 6.125, 0.5, 4.75}, 7},
    {"tests/data/transformacoes/outliers.txt",
     {-50, 10, 10, 11, 11, 12, 12, 12, 13, 100},
     {0.4, 0.4133333333, 0.4066666667, 0.42, 0.4133333333, 0.4066666667, 0.4, 0.4133333333, 1, 0},
     {-0.1206148444, -0.06177833496, -0.0911965897, -0.03236008022, -0.06177833496, -0.0911965897, -0.1206148444, -0.06177833496, 2.527028082, -1.885710129},
     {-50, 10.25, 11.5, 12, 100},
     {10, 12, 11, 13, 12, 11, 10, 12}, 8},
};

#define NUM_CASOS ((int) (sizeof(casos)/sizeof(casos[0])))

static void preencher_dataset(void) {
    int tamanho;
    for (int i = 0; i < NUM_CASOS; i++) {
        casos[i].dataset = coletar_dados(casos[i].arquivo, &tamanho);
        casos[i].tamanho = tamanho;
    }
}

static void liberar_dataset(void) {
    for (int i = 0; i < NUM_CASOS; i++)
        liberar_dados(casos[i].dataset);
}

static void teste_organizar(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        double *obtido = organizar(casos[i].dataset, casos[i].tamanho);
        ASSERT_EQ_INT(1, obtido != NULL);
        if (obtido != NULL) ASSERT_EQ_ARRAY(casos[i].organizado, obtido, casos[i].tamanho);
        free(obtido);
    }
}

// testa casos de erro de organizar
static void teste_organizar_invalido(void) {
    double v[1] = {1.0};
    ASSERT_EQ_INT(1, organizar(v, 0) == NULL);
    ASSERT_EQ_INT(1, organizar(v, -3) == NULL);
    ASSERT_EQ_INT(1, organizar(NULL, 3) == NULL);
}

static void teste_normalizar(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        double *obtido = normalizar(casos[i].dataset, casos[i].tamanho);
        ASSERT_EQ_INT(1, obtido != NULL);
        if (obtido != NULL)
            ASSERT_EQ_ARRAY(casos[i].normalizado, obtido, casos[i].tamanho);
        free(obtido);
    }
}

static void teste_padronizar(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        double *obtido = padronizar(casos[i].dataset, casos[i].tamanho);
        ASSERT_EQ_INT(1, obtido != NULL);
        if (obtido != NULL)
            ASSERT_EQ_ARRAY(casos[i].padronizado, obtido, casos[i].tamanho);
        free(obtido);
    }
}

// Valores todos iguais: normalizar e padronizar devem retornar NULL
static void teste_valores_constantes(void) {
    const char *arquivo = "tests/data/transformacoes/constantes.txt";
    printf("  [%s]\n", arquivo);
    int tamanho;
    double *data = coletar_dados(arquivo, &tamanho);
    ASSERT_EQ_INT(1, normalizar(data, tamanho) == NULL);
    ASSERT_EQ_INT(1, padronizar(data, tamanho) == NULL);
    liberar_dados(data);
}

static void teste_percentil(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        for (int k = 0; k < NUM_PERCENTIS; k++) {
            printf("  [%s] p=%.0f\n", casos[i].arquivo, Porcentagens[k]);
            double obtido = 0;
            ASSERT_EQ_INT(0, percentil(casos[i].dataset, casos[i].tamanho, Porcentagens[k], &obtido));
            ASSERT_EQ_DOUBLE(casos[i].percentis[k], obtido);
        }
    }
}

// testa casos de erro de percentil
static void teste_percentil_invalido(void) {
    double obtido;
    ASSERT_EQ_INT(1, percentil(casos[0].dataset, casos[0].tamanho, 150.0, &obtido));
    ASSERT_EQ_INT(1, percentil(casos[0].dataset, casos[0].tamanho, -5.0, &obtido));
    ASSERT_EQ_INT(1, percentil(casos[0].dataset, 0, 50.0, &obtido));
}

static void teste_filtro_outliers(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        int qtd = 0;
        double *obtido = filtro_outliers(casos[i].dataset, casos[i].tamanho, &qtd);
        ASSERT_EQ_INT(casos[i].qtd_filtrado, qtd);
        ASSERT_EQ_INT(1, obtido != NULL);
        if (obtido != NULL && qtd == casos[i].qtd_filtrado)
            ASSERT_EQ_ARRAY(casos[i].filtrado, obtido, qtd);
        free(obtido);
    }
}

int main(void) {
    printf("Testes do Módulo de Transformação:\n");
    preencher_dataset();
    RUN_TESTE(teste_organizar);
    RUN_TESTE(teste_organizar_invalido);
    RUN_TESTE(teste_normalizar);
    RUN_TESTE(teste_padronizar);
    RUN_TESTE(teste_valores_constantes);
    RUN_TESTE(teste_percentil);
    RUN_TESTE(teste_percentil_invalido);
    RUN_TESTE(teste_filtro_outliers);
    liberar_dataset();
    RESUMO_TESTE();
}