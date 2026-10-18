/**
 * @file tendencia.h
 * @brief Interface pública das medidas de tendência central (média, mediana
 *        e moda).
 *
 * Todas as funções recebem um vetor de @c double e não modificam o vetor
 * original: quando precisam ordenar os valores, trabalham sobre uma cópia
 * feita com organizar().
 *
 * @note Em caso de erro, as funções registram a mensagem via processar_erro()
 *       e também a imprimem na saída padrão.
 *
 * @see transformacao.h
 * @see dados.h
 * @see error.h
 */

#ifndef TENDENCIA_H
#define TENDENCIA_H

/**
 * @brief Compara dois números reais usando uma tolerância fixa.
 *
 * Considera @p a e @p b iguais quando a diferença absoluta entre eles é
 * menor que @c 1e-9. Serve para evitar os problemas de comparar @c double
 * diretamente com @c ==.
 *
 * @param[in] a Primeiro valor.
 * @param[in] b Segundo valor.
 *
 * @return 1 se @f$ |a - b| < 10^{-9} @f$, ou 0 caso contrário.
 *
 * @note A tolerância é absoluta, não relativa. Para valores muito grandes ou
 *       muito pequenos, ela pode não ser adequada.
 */
int quase_igual(double a, double b);

/**
 * @brief Calcula a média aritmética de um dataset.
 *
 * Soma todos os elementos e divide pela quantidade de elementos.
 *
 * @param[in] dataset Vetor de valores.
 * @param[in] tamanho Quantidade de elementos do vetor.
 *
 * @return A média dos valores. Retorna @c NAN se:
 *         - @p dataset for @c NULL;
 *         - @p tamanho for menor ou igual a zero.
 *
 * @note Em caso de erro, a função registra a mensagem via processar_erro()
 *       e também a imprime na saída padrão.
 */
double media(const double *dataset, int tamanho);

/**
 * @brief Calcula a mediana de um dataset.
 *
 * Ordena uma cópia do vetor com organizar() e devolve o elemento central.
 * Se a quantidade de elementos for par, devolve a média dos dois elementos
 * centrais. O vetor original permanece inalterado.
 *
 * @param[in] dataset Vetor de valores.
 * @param[in] tamanho Quantidade de elementos do vetor.
 *
 * @return A mediana dos valores. Retorna @c NAN se:
 *         - @p dataset for @c NULL;
 *         - @p tamanho for menor ou igual a zero;
 *         - a cópia ordenada não puder ser criada (falha de alocação).
 *
 * @note Em caso de erro, a função registra a mensagem via processar_erro()
 *       e também a imprime na saída padrão.
 *
 * @see organizar()
 */
double mediana(const double *dataset, int tamanho);

/**
 * @brief Encontra a(s) moda(s) de um dataset.
 *
 * Ordena uma cópia do vetor com organizar() e agrupa os valores iguais
 * (comparados com quase_igual()). A moda é o valor, ou os valores, de maior
 * frequência. Se houver empate, todos os valores empatados são retornados em
 * ordem crescente.
 *
 * @param[in]  dataset          Vetor de valores.
 * @param[in]  tamanho          Quantidade de elementos do vetor.
 * @param[out] apont_qtd_modas  Recebe a quantidade de modas encontradas.
 *                              Só é atualizado quando a função tem sucesso.
 *
 * @return Ponteiro para um novo vetor alocado dinamicamente contendo as modas
 *         em ordem crescente. Retorna @c NULL se:
 *         - @p apont_qtd_modas for @c NULL;
 *         - @p dataset for @c NULL ou @p tamanho for menor ou igual a zero;
 *         - a alocação de memória falhar.
 *
 * @warning O chamador deve liberar o vetor retornado com liberar_dados() ou
 *          @c free.
 *
 * @warning Se todos os valores se repetirem com a mesma frequência e mais de 1 vez,
 * todos eles serão considerados modas
 *
 * @note Em caso de erro, a função registra a mensagem via processar_erro()
 *       e também a imprime na saída padrão.
 *
 * @see organizar()
 * @see quase_igual()
 */
double* moda(const double *dataset, int tamanho, int *apont_qtd_modas);

#endif