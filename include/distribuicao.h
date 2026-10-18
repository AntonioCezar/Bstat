/**
 * @file distribuicao.h
 * @brief Interface pública das funções de distribuições de probabilidade
 *        (binomial, geométrica, hipergeométrica e Poisson) e das funções
 *        auxiliares de cálculo (fatorial, potência e combinação).
 *
 * @note O número de Euler é aproximado por 2.71828 nos cálculos que o
 *       utilizam, então os resultados têm precisão limitada.
 */

#ifndef DISTRIBUICAO_H
#define DISTRIBUICAO_H

/**
 * @brief Calcula o fatorial de um número inteiro.
 *
 * @param[in] n Número cujo fatorial será calculado. Para @p n menor ou igual a zero, o resultado é 1.
 *
 * @return O valor de n!.
 *
 * @warning O resultado é um @c long, Acima desse limite ocorre overflow.
 */

long fatorial(long n);

/**
 * @brief Calcula um número elevado a um expoente inteiro não negativo.
 *
 * @param[in] n  Base.
 * @param[in] ex Expoente inteiro. Para @p ex menor ou igual a zero, o resultado é 1.0 (expoentes negativos não são suportados).
 *
 * @return O valor de n elevado a ex.
 */

double elevado(double n, int ex);

/**
 * @brief Calcula a combinação de @p n elementos tomados @p k a @p k.
 *
 * @param[in] n Total de elementos.
 * @param[in] k Quantidade de elementos escolhidos.
 *
 * @return O número de combinações.
 *
 * @warning Usa fatorial() internamente, então herda seu limite de overflow.
 *
 * @see fatorial()
 */

double combinacao(int n, int k);

/**
 * @brief Calcula a probabilidade da distribuição binomial.
 *
 * @param[in] n Número de tentativas.
 * @param[in] k Número de sucessos desejado.
 * @param[in] p Probabilidade de sucesso em cada tentativa, entre 0 e 1.
 *
 * @return A probabilidade de ocorrerem exatamente @p k sucessos em @p n tentativas.
 *
 * @see combinacao()
 * @see elevado()
 */

double binomial(int n, int k, double p);

/**
 * @brief Calcula a probabilidade da distribuição geométrica.
 *
 * @param[in] n Número da tentativa em que ocorre o primeiro sucesso (@p n maior ou igual a 1).
 * @param[in] p Probabilidade de sucesso em cada tentativa, entre 0 e 1.
 *
 * @return A probabilidade de o primeiro sucesso ocorrer na tentativa @p n.
 *
 * @see elevado()
 */

double geometrica(int n, double p);

/**
 * @brief Calcula a probabilidade da distribuição hipergeométrica.
 *
 * @param[in] N Tamanho da população.
 * @param[in] R Quantidade de elementos de interesse (sucessos) na população.
 * @param[in] n Tamanho da amostra retirada.
 * @param[in] k Quantidade de sucessos desejada na amostra.
 *
 * @return A probabilidade de haver exatamente @p k sucessos na amostra.
 *
 * @warning Usa combinacao() internamente, então herda o limite de overflow.
 *
 * @see combinacao()
 */

double hipergeometrica(int N, int R, int n, int k);

/**
 * @brief Calcula a probabilidade da distribuição de Poisson.
 *
 * @param[in] k Número de ocorrências desejado.
 * @param[in] lambda Taxa média de ocorrências lambda.
 *
 * @return A probabilidade de ocorrerem exatamente @p k eventos.
 *
 * @note @p lambda é um @c int porque o cálculo de e elevado a lambda usa elevado(), que só aceita expoentes inteiros.
 * 
 * @warning Usa fatorial() internamente, então @p k herda o limite de overflow do fatorial().
 *
 * @see elevado()
 * @see fatorial()
 */

double poisson(int k, int lambda);

#endif