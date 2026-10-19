#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "minunit.h"
#include "distribuicao.h"

// informações para testar as funções de distribuição
typedef struct {
    int nf;
    double base; int expoente;
    int n, k; double p;
    int N, R, nh, kh;
    int kp, lambda;
    int fatorial;
    double elevado;
    double combinacao;
    double binomial;
    double geometrica;
    double hipergeometrica;
    double poisson;
} Caso;

#define EXP_Menos1 0.3678794412
#define EXP_Menos2 0.1353352832
#define EXP_Menos3 0.04978706837
#define EXP_Menos4 0.01831563889
#define EXP_Menos5 0.006737946999

// todas as entradas de cada caso e seus resultados esperados
static const Caso casos[] = {
    {4, 2, 10, 4, 2, 0.5, 10, 4, 3, 2, 2, 2, 24, 1024, 6, 0.375, 0.25, 6.0 * 6.0 / 120.0, 2.0 * EXP_Menos2},
    {5, 5, 0, 5, 1, 0.2, 10, 4, 3, 0, 0, 1, 120, 1, 5, 0.4096, 0.2, 20.0 / 120.0, EXP_Menos1},
    {10, 0.5, 3, 10, 3, 0.3, 20, 7, 5, 2, 3, 3, 3628800, 0.125, 120, 0.266827932, 0.147, 21.0 * 286.0 / 15504.0, 4.5 * EXP_Menos3},
    {12, -2, 3, 6, 3, 0.5, 10, 4, 3, 3, 3, 4, 479001600, -8, 20, 0.3125, 0.125, 4.0 / 120.0, (64.0 / 6.0) * EXP_Menos4},
    {0, 1.5, 2, 12, 6, 1.0, 10, 4, 3, 4, 6, 5, 1, 2.25, 924, 0.0, 0.0, 0.0, (15625.0 / 720.0) * EXP_Menos5},
    {1, 0, 5, 1, 1, 0.0, 5, 2, 2, 1, 1, 0, 1, 0, 1, 0.0, 0.0, 6.0 / 10.0, 0.0},
};

#define NUM_CASOS ((int) (sizeof(casos)/sizeof(casos[0])))

// valores inválidos: fatorial retorna -1 e as demais funções retornam NAN
static void teste_valores_invalidos(void) {

    static const Caso invalidos[] = {
        {-1, -1, -1, -1, -1, -1.0, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0},
    };

    printf("  [fatorial n=-1]\n");
    ASSERT_EQ_INT(-1, fatorial(-1));

    printf("  [elevado base=-1 expoente=-1]\n");
    ASSERT_EQ_INT(1, isnan(elevado(-1, -1)) != 0);

    printf("  [combinacao n=-1 k=-1]\n");
    ASSERT_EQ_INT(1, isnan(combinacao(-1, -1)) != 0);

    printf("  [binomial n=-1 k=-1 p=-1]\n");
    ASSERT_EQ_INT(1, isnan(binomial(-1, -1, -1.0)) != 0);

    printf("  [geometrica k=-1 p=-1]\n");
    ASSERT_EQ_INT(1, isnan(geometrica(-1, -1.0)) != 0);

    printf("  [hipergeometrica N=-1 R=-1 n=-1 k=-1]\n");
    ASSERT_EQ_INT(1, isnan(hipergeometrica(-1, -1, -1, -1)) != 0);

    printf("  [poisson k=-1 lambda=-1]\n");
    ASSERT_EQ_INT(1, isnan(poisson(-1, -1)) != 0);
}

// testa a função fatorial
static void teste_fatorial(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%d!]\n", casos[i].nf);
        ASSERT_EQ_INT(casos[i].fatorial, fatorial(casos[i].nf));
    }
}

// testa a função elevado
static void teste_elevado(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [%g^%d]\n", casos[i].base, casos[i].expoente);
        ASSERT_EQ_DOUBLE(casos[i].elevado, elevado(casos[i].base, casos[i].expoente));
    }
}

// testa a função combinação
static void teste_combinacao(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [C(%d,%d)]\n", casos[i].n, casos[i].k);
        ASSERT_EQ_DOUBLE(casos[i].combinacao, combinacao(casos[i].n, casos[i].k));
    }
}

// testa a distribuição binomial
static void teste_binomial(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [binomial n=%d k=%d p=%g]\n", casos[i].n, casos[i].k, casos[i].p);
        ASSERT_EQ_DOUBLE(casos[i].binomial, binomial(casos[i].n, casos[i].k, casos[i].p));
    }
}

// testa a distribuição geométrica (k = número da tentativa do primeiro sucesso)
static void teste_geometrica(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [geometrica n=%d p=%g]\n", casos[i].k, casos[i].p);
        ASSERT_EQ_DOUBLE(casos[i].geometrica, geometrica(casos[i].k, casos[i].p));
    }
}

// testa a distribuição hipergeométrica
static void teste_hipergeometrica(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [hipergeometrica N=%d R=%d n=%d k=%d]\n",
               casos[i].N, casos[i].R, casos[i].nh, casos[i].kh);
        ASSERT_EQ_DOUBLE(casos[i].hipergeometrica,
                         hipergeometrica(casos[i].N, casos[i].R, casos[i].nh, casos[i].kh));
    }
}

// testa a distribuição de Poisson
static void teste_poisson(void) {
    for (int i = 0; i < NUM_CASOS; i++) {
        printf("  [poisson k=%d lambda=%d]\n", casos[i].kp, casos[i].lambda);
        ASSERT_EQ_DOUBLE(casos[i].poisson, poisson(casos[i].kp, casos[i].lambda));
    }
}

// as probabilidades de todos os k possíveis devem somar 1
static void teste_somas(void) {
    double soma = 0;
    for (int k = 0; k <= 10; k++) soma += binomial(10, k, 0.3);
    printf("  [soma binomial n=10 p=0.3]\n");
    ASSERT_EQ_DOUBLE(1.0, soma);

    soma = 0;
    for (int k = 0; k <= 3; k++) soma += hipergeometrica(10, 4, 3, k);
    printf("  [soma hipergeometrica N=10 R=4 n=3]\n");
    ASSERT_EQ_DOUBLE(1.0, soma);

    soma = 0;
    for (int k = 0; k <= 12; k++) soma += poisson(k, 3);
    printf("  [soma poisson lambda=3 (k de 0 a 12)]\n");
    ASSERT_EQ_DOUBLE(0.9999838508, soma);
}

// chama todos os testes (chamado pelo make test)
int main(void) {
    RUN_TESTE(teste_fatorial);
    RUN_TESTE(teste_elevado);
    RUN_TESTE(teste_combinacao);
    RUN_TESTE(teste_binomial);
    RUN_TESTE(teste_geometrica);
    RUN_TESTE(teste_hipergeometrica);
    RUN_TESTE(teste_poisson);
    RUN_TESTE(teste_somas);
    RUN_TESTE(teste_valores_invalidos);
    RESUMO_TESTE();
}