#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minunit.h"
#include "../include/tendencia.h"
#include "../include/dados.h"

#define MAX_MODAS 64

//Classe dos casos esperados
typedef struct {
    const char *arquivo;
    double media;
    double mediana;
    double modas[MAX_MODAS];
    int qtd_modas;
    double *dataset;
    int tamanho;
} Caso;

//Cada objeto do array é um caso esperado
static Caso casos[] = {
    {"tests/data/tendencia/simples.txt",    28.41,  27.5,  {17.0},             1},
    {"tests/data/tendencia/multimodal.txt", 49.64,  49.5,  {12.0, 47.0, 80.0}, 3},
    {"tests/data/tendencia/decimais.txt",   3.1135, 5.425, {24.75},            1},
};

//Pega o tamanho do array casos
#define NUM_CASOS ((int) (sizeof(casos)/sizeof(casos[0])))

//Preenche o campo dataset dos objetos
static void preencher_dataset(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        casos[i].dataset = coletar_dados(casos[i].arquivo, &(casos[i].tamanho));
    }
}

//Libera todos os datasets
static void liberar_dataset(void) {
    for (int i = 0; i < NUM_CASOS; i++)
        liberar_dados(casos[i].dataset);
}

//Teste da função media
static void teste_media(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        //Aqui eu comparo média esperada com média obtida
        ASSERT_EQ_DOUBLE(casos[i].media, media(casos[i].dataset, casos[i].tamanho)); 
    }
}

//Testa a função média quando o retorno é inválido
static void teste_media_invalido(void) {
    double *v = NULL;
    int tamanho = 0;
    ASSERT_EQ_DOUBLE(1, isnan(media(v, tamanho)));
}

static void teste_mediana(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        //Aqui eu comparo mediana esperada com mediana obtida
        ASSERT_EQ_DOUBLE(casos[i].mediana, mediana(casos[i].dataset, casos[i].tamanho)); 
    }
}

static void teste_moda(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%s]\n", casos[i].arquivo);
        //Armazena a tamanho de valores do array moda_obtida
        int qtd;
        double *moda_obtida = moda(casos[i].dataset, casos[i].tamanho, &qtd);
        //Verifico se a moda esperada e a moda obtida têm a mesma tamanho de valores
        ASSERT_EQ_INT(casos[i].qtd_modas, qtd);
        if (qtd == casos[i].qtd_modas) //Evita ler fora do array
            //Aqui eu comparo moda esperada com moda obtida
            ASSERT_EQ_ARRAY(casos[i].modas, moda_obtida, casos[i].qtd_modas); 
        free(moda_obtida);
    }
}

//Testa a função moda quando o retorno é inválido
static void teste_moda_invalido(void) {
    double *v = NULL;
    int tamanho = 0, qtd = 0;
    ASSERT_EQ_DOUBLE(1, (moda(v, tamanho, &qtd)) == NULL);
}

int main(void) {
    preencher_dataset();
    RUN_TESTE(teste_media);
    RUN_TESTE(teste_media_invalido);
    RUN_TESTE(teste_mediana);
    RUN_TESTE(teste_moda);
    RUN_TESTE(teste_moda_invalido);
    liberar_dataset();
    RESUMO_TESTE();
}