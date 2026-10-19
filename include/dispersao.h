/**
 * @file dispersao.h
 * @brief Funções para cálculo de medidas de dispersão estatística.
 *
 * Contém as funções responsáveis por calcular métricas estatísticas de variabilidade
 * a partir de vetores de @c double, incluindo variância, desvio padrão, amplitude e
 * coeficiente de variação.
 *
 * @note Em caso de dados inválidos (vetor nulo ou tamanho insuficiente), as funções 
 *       registram o erro por meio de processar_erro() e retornam @c NAN.
 */

#ifndef DISPERSAO_H
#define DISPERSAO_H

/**
 * @brief Calcula a variância populacional de um conjunto de dados.
 *
 * @param[in] dataset Ponteiro para o vetor contendo as amostras numéricas.
 * @param[in] tamanho Quantidade de elementos no vetor.
 *
 * @return O valor da variância, ou @c NAN se o vetor for nulo.
 */
double variancia(double* dataset, int tamanho);

    /**
 * @brief Calcula o desvio padrão de um conjunto de dados.
 *
 * Obtém a raiz quadrada da variância calculada sobre o vetor informado.
 *
 * @param[in] dataset Ponteiro para o vetor contendo as amostras numéricas.
 * @param[in] tamanho Quantidade de elementos no vetor.
 *
 * @return O valor do desvio padrão, ou @c NAN se o vetor for nulo.
 */
double desvio_padrao(double* dataset, int tamanho);

/**
 * @brief Calcula a amplitude total de um conjunto de dados.
 *
 * Encontra a diferença entre o valor máximo e o valor mínimo presentes no vetor.
 *
 * @param[in] dataset Ponteiro para o vetor contendo as amostras numéricas.
 * @param[in] tamanho Quantidade de elementos no vetor.
 *
 * @return O valor da amplitude, ou @c NAN se o vetor for nulo ou se o 
 *         @p tamanho for menor ou igual a 0.
 */
double amplitude(double* dataset, int tamanho);

/**
 * @brief Calcula o coeficiente de variação (CV) de um conjunto de dados.
 *
 * Expressa a razão entre o desvio padrão e a média aritmética do vetor.
 *
 * @param[in] dataset Ponteiro para o vetor contendo as amostras numéricas.
 * @param[in] tamanho Quantidade de elementos no vetor.
 *
 * @return O coeficiente de variação como uma fração decimal, ou @c NAN se o 
 *         vetor for nulo, tamanho menor ou igual a zero, ou se a média dos dados for zero 
 *         (evitando divisão por zero).
 */
double coef_variacao(double* dataset, int tamanho);

#endif
