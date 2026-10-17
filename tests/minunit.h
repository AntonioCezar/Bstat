#ifndef MINUNIT_H
#define MINUNIT_H
#define COR_AMARELO  "\033[33m"
#define COR_RESET    "\033[0m"
#include <stdio.h>
#include <string.h>
#include "../include/tendencia.h"

static int testes_run = 0, falhas = 0;

//Compara doubles
#define ASSERT_EQ_DOUBLE(esperado, obtido) do {                         \
    double es = (esperado), ob = (obtido);                              \
    testes_run++;                                                       \
    if(!quase_igual(es, ob)) {                                          \
        falhas++;                                                       \
        printf(" Erro: %s:linha %d: esperado: %.10g, obtido: %.10g\n",  \
             __FILE__, __LINE__, es, ob);                               \
    }                                                                   \
} while (0)

//Compara ints
#define ASSERT_EQ_INT(esperado, obtido) do {                            \
    int es = (esperado), ob = (obtido);                                 \
    testes_run++;                                                       \
    if(es != ob) {                                                      \
        falhas++;                                                       \
        printf(" Erro: %s:linha %d: esperado: %d, obtido: %d\n",        \
             __FILE__, __LINE__, es, ob);                               \
    }                                                                   \
} while (0)

//Compara arrays double
#define ASSERT_EQ_ARRAY(esperado, obtido, tamanho) do {                 \
    const double *es = (esperado), *ob = (obtido);                      \
    int n = (tamanho);                                                  \
    testes_run++;                                                       \
    for (int i = 0; i < n; i++) {                                       \
        if (!quase_igual(es[i], ob[i])) {                               \
            falhas++;                                                   \
            printf(" Erro: %s:índice %d: esperado: %f, obtido: %f\n",   \
                 __FILE__, i, es[i], ob[i]);                            \
            break;                                                      \
        }                                                               \
    }                                                                   \
} while (0)                     
    



#define RUN_TESTE(teste) do { printf(COR_AMARELO "*** %s ***" COR_RESET "\n", #teste); teste(); } while (0)   

#define RESUMO_TESTE() do {                                             \
    printf("Testes: %d, Falhas: %d\n", testes_run, falhas);             \
    return falhas ? 1 : 0;                                              \
} while (0)

#endif