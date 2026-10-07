#ifndef MINUNIT_H
#define MINUNIT_H
#include <stdio.h>
#include <string.h>

static int tests_run = 0, tests_failed = 0;

#define ASSERT_EQ_INT(esperado, obtido) do {                            \
    int es = (esperado), ob = (obtido);                                 \
    tests_run++;                                                        \
    if(es != ob) {                                                      \
        tests_failed++;                                                 \
        printf("Teste mal-sucedido: %s:%d: esperado: %d, obtido: %d\n", \
             __FILE__, __LINE__, es, ob);                               \
    }                                                                   \
} while (0)

//#define ASSERT_EQ_DOUBLE(esperado, obtido)

//#define ASSERT_EQ_ARRAY(esperado, obtido)

#define RUN_TESTE(teste) do { printf(" %s\n", #teste); teste(); } while (0)   

#define RESUMO_TESTE() do {                                             \
    printf(" testes: %d, falhas: %d\n", tests_run, tests_failed);       \
    return tests_failed ? 1 : 0;                                        \
} while (0)

#endif