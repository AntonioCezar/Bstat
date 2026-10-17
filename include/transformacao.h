/**
 * @file transformacao.h
 * @brief Interface pública das funções de transformação de datasets
 *        (ordenação, normalização, padronização, percentil e filtro de
 *        outliers).
 *
 * Todas as funções recebem um vetor de @c double e não modificam o vetor
 * original: trabalham sempre sobre cópias.
 *
 * @note Todas as funções que retornam ponteiro devolvem um vetor NOVO,
 *       alocado com @c malloc. Quem chamar é responsável por liberá-lo com
 *       @c free. Em caso de erro, essas funções retornam @c NULL.
 *
 * @see dispersao.h
 * @see tendencia.h
 * @see error.h
 */

#ifndef TRANSFORMACAO_H
#define TRANSFORMACAO_H

/**
 * @brief Organiza os valores de um dataset em ordem crescente.
 *
 * Cria uma cópia do vetor original e a ordena usando o algoritmo
 * insertion sort. O vetor original permanece inalterado.
 *
 * @param[in] dataset Vetor de valores a ser organizado.
 * @param[in] tamanho Quantidade de elementos do vetor.
 *
 * @return Ponteiro para um novo vetor alocado dinamicamente, com os valores
 *         em ordem crescente. Retorna @c NULL se @p dataset for @c NULL,
 *         se @p tamanho for menor ou igual a zero, ou se a alocação falhar.
 *
 * @warning O chamador deve liberar o vetor retornado com @c free.
 *
 * @note Em caso de erro, a função registra a mensagem via processar_erro()
 *       e também a imprime na saída padrão.
 */

// Retorna uma cópia do vetor ordenada em ordem crescente.
double* organizar(const double *dataset, int tamanho);

/**
 * @brief Normaliza os valores de um dataset para a escala de 0 a 1.
 *
 * Aplica a normalização em escala 0 a 1 a cada elemento.
 *
 * @param[in] dataset Vetor de valores a ser normalizado.
 * @param[in] tamanho Quantidade de elementos do vetor.
 *
 * @return Ponteiro para um novo vetor alocado dinamicamente com os valores
 *         normalizados. Retorna @c NULL se:
 *         - @p dataset for @c NULL ou @p tamanho for menor ou igual a zero;
 *         - todos os valores forem iguais (divisão por zero);
 *         - a alocação de memória falhar.
 *
 * @warning O chamador deve liberar o vetor retornado com @c free.
 *
 * @note Em caso de erro, a função registra a mensagem via processar_erro()
 *       e também a imprime na saída padrão.
 */

// Normaliza os valores para escala de [0, 1]. Retorna NULL se todos forem iguais.
double* normalizar(const double *dataset, int tamanho);

/**
 * @brief Padroniza os valores de um dataset.
 *
 * Transforma cada elemento de modo que o conjunto resultante tenha média 0 e desvio padrão 1.
 *
 * Utiliza as funções media() e desvio_padrao() para calcular.
 *
 * @param[in] dataset Vetor de valores a ser padronizado.
 * @param[in] tamanho Quantidade de elementos do vetor.
 *
 * @return Ponteiro para um novo vetor alocado dinamicamente com os valores
 *         padronizados. Retorna @c NULL se:
 *         - @p dataset for @c NULL ou @p tamanho for menor ou igual a zero;
 *         - o desvio padrão for zero (todos os valores iguais);
 *         - a alocação de memória falhar.
 *
 * @warning O chamador deve liberar o vetor retornado com @c free.
 *
 * @note Em caso de erro, a função registra a mensagem via processar_erro()
 *       e também a imprime na saída padrão.
 *
 * @see media()
 * @see desvio_padrao()
 */

// Padroniza para média 0 e desvio padrão 1. Retorna NULL se todos forem iguais.
double* padronizar(const double *dataset, int tamanho);

/**
 * @brief Calcula o valor correspondente a um percentil do dataset.
 *
 * Ordena uma cópia do dataset com organizar() e calcula o valor que estaria naquele percentil.
 *
 * @param[in]  dataset     Vetor de valores.
 * @param[in]  tamanho     Quantidade de elementos do vetor.
 * @param[in]  porcentagem Percentil desejado, entre 0 e 100.
 *
 * @return O valor localizado no percentil passado no parâmetro porcentagem.
 *         retorna NAN se:
 *         - Dataset estiver vazio;
 *         - Porcentagem estiver fora do intervalo [0, 100];
 *         - Falha ao organizar o vetor.
 *
 * @note Em caso de erro, a função registra a mensagem via processar_erro()
 *       e também a imprime na saída padrão.
 *
 * @see organizar()
 */

// retorna o valor naquele percentil
double percentil(const double *dataset, int tamanho, double porcentagem);

/**
 * @brief Remove os outliers de um dataset usando o critério do box-plot.
 *
 * Calcula o primeiro quartil (Q1) e o terceiro quartil (Q3) com percentil()
 * e o intervalo interquartil. São mantidos apenas os valores dentro dos limites:
 * - limite inferior: @f$ Q1 - 1{,}5 \cdot IQR @f$
 * - limite superior: @f$ Q3 + 1{,}5 \cdot IQR @f$
 *
 * @param[in]  dataset       Vetor de valores a ser filtrado.
 * @param[in]  tamanho       Quantidade de elementos do vetor.
 * @param[out] novo_tamanho  Ponteiro onde será gravada a quantidade de
 *                           elementos do vetor retornado. Recebe @c -1 caso
 *                           a função retorne @c NULL após a validação
 *                           inicial (indicando erro).
 *
 * @return Ponteiro para um novo vetor alocado dinamicamente contendo apenas
 *         os valores que não são outliers. Retorna @c NULL se:
 *         - @p dataset for @c NULL ou @p tamanho for menor ou igual a zero
 *           (nesse caso @p novo_tamanho não é alterado);
 *         - o cálculo dos quartis falhar;
 *         - nenhum valor respeitar os limites;
 *         - a alocação ou realocação de memória falhar.
 *
 * @warning O chamador deve liberar o vetor retornado com @c free.
 *
 * @note Em caso de erro, a função registra a mensagem via processar_erro()
 *       e também a imprime na saída padrão.
 *
 * @see percentil()
 */

// Remove outliers (1.5 * quartil 3 - quartil 1) e salva em *novo_tamanho a quantidade que sobrou.
// Em erro retorna NULL e *novo_tamanho = -1.
double* filtro_outliers(const double *dataset, int tamanho, int *novo_tamanho);

#endif