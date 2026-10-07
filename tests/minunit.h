#ifndef MINUNIT_H
#define MINUNIT_H
#include <stdio.h>
#include <string.h>

static int testes_run = 0, falhas = 0;

static int quase_igual(double a, double b) {
    double d = a - b;
    if (d < 0) d = -d;
    //Diferença tolerada
    return d < 1e-9;  
}

//Compara doubles
#define ASSERT_EQ_DOUBLE(esperado, obtido) do {                         \
    double es = (esperado), ob = (obtido);                              \
    testes_run++;                                                       \
    if(!quase_igual(es, ob)) {                                          \
        falhas++;                                                       \
        printf(" Erro: %s:linha %d: esperado: %.2f, obtido: %.2f\n",    \
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
    double *es = (esperado), *ob = (obtido);                            \
    int *n = (tamanho);                                                 \
    testes_run++;                                                       \
    for (int i = 0; i < *n; i++) {                                      \
        if (!quase_igual(es[i], ob[i])) {                               \
            falhas++;                                                   \
            printf(" Erro: %s:índice %d: esperado: %f, obtido: %f\n",   \
                 __FILE__, i, es[i], ob[i]);                            \
            break;                                                      \
        }                                                               \
    }                                                                   \
} while (0)                     
    



#define RUN_TESTE(teste) do { printf("*%s\n", #teste); teste(); } while (0)   

#define RESUMO_TESTE() do {                                             \
    printf("Testes: %d, Falhas: %d\n", testes_run, falhas);             \
    return falhas ? 1 : 0;                                              \
} while (0)

#endif