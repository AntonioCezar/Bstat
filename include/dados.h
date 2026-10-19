
/**
 * @file dados.c
 * @brief Funções para leitura e gerenciamento de vetores dinâmicos de dados.
 *
 * Contém as rotinas responsáveis por alocar, redimensionar, validar e liberar
 * vetores de @c double, além de ler amostras numéricas de um arquivo de texto
 * e pedir ao usuário o nome do arquivo, se necessário.
 *
 * @note Em caso de falha, as funções registram o erro por meio de
 *       processar_erro() e também imprimem umamensagem na saída
 *       padrão.
 */
 
#ifndef DADOS_H
#define DADOS_H

/**
 * @brief Redimensiona um vetor dinâmico de @c double.
 *
 * Usa @c realloc para alterar o tamanho do vetor apontado por @p vetor. Se a
 * realocação falhar, o vetor original é mantido intacto e o erro é registrado.
 *
 * @param[in,out] vetor        Endereço do ponteiro que armazena o vetor. É
 *                             atualizado para o novo bloco de memória em caso
 *                             de sucesso.
 * @param[in]     novotamanho  Novo tamanho do vetor, em número de elementos
 *                             (não em bytes).
 *
 * @warning Se a realocação falhar, @p *vetor não é alterado e a função apenas
 *          retorna; quem chama deve estar atento a essa situação, pois a função
 *          não devolve código de erro.
 */
void mudtamvet(double **vetor,int novotamanho);

 
/**
 * @brief Cria um novo vetor dinâmico de @c double.
 *
 * Aloca com @c malloc um vetor com espaço para @p tamanho elementos. O
 * conteúdo do vetor não é inicializado.
 *
 * @param[in] tamanho Quantidade de elementos do vetor.
 *
 * @return Ponteiro para o vetor alocado, ou @c NULL se a alocação falhar.
 *
 * @note O vetor retornado deve ser liberado com liberar_dados().
 */
double* novovet(int tamanho);
 
/**
 * @brief Valida se o vetor informado é válido.
 *
 * Verifica se o ponteiro do vetor é diferente de NULL.
 * Caso seja NULL, registra e exibe uma mensagem de erro.
 *
 * @param vetor Ponteiro para o vetor de valores do tipo double.
 *
 * @return 1 se o vetor for válido.
 * @return 0 se o vetor for NULL.
 */
int validarvetor(double *vetor);
 
/**
 * @brief Lê números reais de um arquivo de texto e os guarda em um vetor
 *        dinâmico.
 *
 * Abre o arquivo @p nomedoarquivo e lê valores @c double separados por espaços
 * ou quebras de linha até o fim do arquivo, redimensionando o vetor a cada
 * valor lido. Se, depois dos números, sobrar qualquer caractere que não seja
 * numérico, a leitura é considerada inválida e a memória alocada é liberada.
 *
 * @param[in]  nomedoarquivo Caminho (ou nome) do arquivo de texto a ser lido.
 * @param[out] quantidade    Recebe o número de valores lidos. Só é atualizado
 *                           quando a leitura termina com sucesso.
 *
 * @return Ponteiro para o vetor com os dados lidos, ou @c NULL se o arquivo não
 *         puder ser aberto ou se ele contiver caracteres inválidos.
 *
 * @note O vetor retornado deve ser liberado com liberar_dados().
 * @warning Se o arquivo estiver vazio, o retorno é @c NULL com
 *          @p *quantidade igual a 0, e nenhuma mensagem de erro é emitida.
 * @warning Se mudtamvet() falhar durante a leitura, a função não interrompe o
 *          laço, o que pode causar acesso inválido à memória.
 */
double* coletar_dados(const char *nomedoarquivo, int *quantidade);
 
/**
 * @brief Pede ao usuário o nome (ou caminho) do arquivo com as amostras.
 *
 * Exibe uma mensagem na tela e lê uma linha inteira da entrada padrão (inclusive
 * com espaços), limitada a 259 caracteres.
 *
 * @param[out] nomedoarquivo Buffer onde o nome digitado é armazenado.
 *
 * @pre @p nomedoarquivo deve apontar para um buffer com pelo menos 260 bytes,
 *      por exemplo: @code char nomedoarquivo[260]; @endcode
 */
void pedirnomedoarquivo(char *nomedoarquivo);
/**
 * @brief Libera a memória de um vetor de dados.
 *
 * @param[in] dados Vetor alocado dinamicamente (por novovet(), coletar_dados()
 *                  ou mudtamvet()). Pode ser @c NULL, caso em que nada acontece.
 *
 * @warning Depois da chamada, o ponteiro @p dados não deve mais ser usado.
 */
void liberar_dados(double *dados);

/**
 * @brief Imprime os dados armazenados em um vetor.
 *
 * Percorre o vetor e imprime cada elemento no formato de ponto flutuante,
 * com uma quebra de linha após cada valor.
 *
 * @param dados Ponteiro para o vetor de valores do tipo double.
 * @param tamanho Quantidade de elementos do vetor.
 */
void imprimir_dados(double *dados, int tamanho);

#endif

