/**
 * @file distribuicao.h
 * @brief Interface pública das funções de distribuições de probabilidade
 *        (binomial, geométrica, hipergeométrica e Poisson) e das funções
 *        auxiliares de cálculo (fatorial, potência e combinação).
 *
 * @note A função exponencial e^x é calculada com exp() de math.h, então
 *       a precisão é a de um double. Em caso de entrada inválida, as funções
 *       devolvem NAN e registram o erro por processar_erro().
 */

#ifndef DISTRIBUICAO_H
#define DISTRIBUICAO_H

// função interna, não terá descrição no doxygen
// devolve -1 se o parâmetro for negativo
long fatorial(long n);

// função interna, não terá descrição no doxygen
// devolve NAN se o expoente for negativo
double elevado(double n, int ex);

/**
 * @brief Calcula a combinação de @p n elementos tomados @p k a @p k.
 *
 * @param[in] n Total de elementos.
 * @param[in] k Quantidade de elementos escolhidos.
 *
 * @return O número de combinações. Devolve 0.0 se @p k for maior que @p n
 *         e NAN se @p n ou @p k forem negativos.
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
 *         Devolve NAN se @p n ou @p k forem negativos ou se @p p estiver fora de [0, 1].
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
 *         Devolve NAN se @p n for menor que 1 ou se @p p estiver fora de [0, 1].
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
 *         Devolve 0.0 se o resultado for impossível (k maior que n ou R,
 *         ou mais fracassos na amostra do que existem na população) e NAN se algum
 *         parâmetro for negativo ou se @p R ou @p n forem maiores que @p N.
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
 *         Devolve NAN se @p k ou @p lambda forem negativos.
 *
 * @warning Usa fatorial() internamente, então @p k herda o limite de overflow do fatorial().
 *
 * @see elevado()
 * @see fatorial()
 */

double poisson(int k, double lambda);

#endif