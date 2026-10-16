#include <stdio.h>
#include <stdlib.h>
#include "../include/transformacao.h"
#include "../include/dispersao.h"
#include "../include/tendencia.h"
#include "../errors/error.h"

// copia o vetor do parametro 1 para o vetor do parametro 2 (passar para utils .c)
void copiar_vetor(const double *dataset, double *copia, int tamanho){
  for (int i = 0; i < tamanho; i++) copia[i] = dataset[i];
}

// faz um insertion sort para organizar os valores em ordem crescente
double* organizar(const double *dataset, int tamanho){
  if (dataset == NULL || tamanho <= 0){
    processar_erro(1, "Dataset vazio passado para organizar\n");
    printf("Dataset vazio passado para organizar\n");
    return NULL;
  }

  double *copia = malloc(tamanho * sizeof(double));

  if (copia == NULL) {
    processar_erro(1, "Erro ao inicializar o vetor dinâmico de valores organizados");
    printf("Erro ao inicializar o vetor dinâmico de valores organizados\n");
    return NULL;
  }

  copiar_vetor(dataset, copia, tamanho);

  for (int i = 1; i < tamanho; i++){
    int n = 0;
    while ((i-n-1) >= 0 && copia[i-n] < copia[i-n-1]){
      double tmp = copia[i-n-1];
      copia[i-n-1] = copia[i-n];
      copia[i-n] = tmp;
      n++;
    }
  }
  return copia;
}

// normaliza os valores em uma escala de 0 a 1
double* normalizar(const double *dataset, int tamanho){
  if (dataset == NULL || tamanho <= 0){
    processar_erro(1, "Dataset vazio passado para normalizar\n");
    printf("Dataset vazio passado para normalizar\n");
    return NULL;
  }

  double min = dataset[0];
  double max = dataset[0];
  for (int i = 0; i < tamanho; i++){
    if (dataset[i] < min) min = dataset[i];
    if (dataset[i] > max) max = dataset[i];
  }

  // checa se os valores não são todos iguais
  if (max == min){
    processar_erro(1, "Todos os valores passados para a função normalizar são iguais!\n");
    printf("Todos os valores são iguais! (normalizar)\n");
    return NULL;
  }

  //cria o novo array para a escala normalizada
  double *normalizado = malloc(tamanho * sizeof *dataset);
  if (normalizado == NULL){
    processar_erro(1, "Erro ao inicializar o vetor dinâmico de valores normalizados");
    printf("Erro ao inicializar o vetor dinâmico de valores normalizados\n");
    return NULL;
  } 

  // normaliza valor a valor na escala
  for (int i = 0; i < tamanho; i++){
    normalizado[i] = (dataset[i] - min) / (max - min);
  }
  return normalizado;
}

// padroniza os valores para que o desvio padrão dê 1 e a média 0
double* padronizar(const double *dataset, int tamanho){
  if (dataset == NULL || tamanho <= 0){
    processar_erro(1, "Dataset vazio passado para padronizar\n");
    printf("Dataset vazio passado para padronizar\n");
    return NULL;
  }

  double md = media(dataset, tamanho); // usa a função que faz a média
  double dp = desvio_padrao(dataset, tamanho); // usa a função que faz o dp

  // checa se os valores não são todos iguais
  if (dp == 0.0){
    processar_erro(1, "Todos os valores passados pelo usuário para a função padronizar são iguais!\n");
    printf("Todos os valores são iguais! (padronizar)\n");
    return NULL;
  }

  //cria o novo array para a escala padronizada
  double *padronizado = malloc(tamanho * sizeof *dataset);
  if (padronizado == NULL){
    processar_erro(1, "Erro ao inicializar o vetor dinâmico de valores padronizados\n");
    printf("Erro ao inicializar o vetor dinâmico de valores padronizados\n");
    return NULL;
  } 

  // padroniza valor a valor na escala
  for (int i = 0; i < tamanho; i++){
    padronizado[i] = (dataset[i] - md) / dp;
  }
  return padronizado;
}

// recebe um percentil do conjunto de dados e retorna o valor que estaria naquele percentil
int percentil(const double *dataset, int tamanho, double porcentagem, double *resultado){
  if (dataset == NULL || tamanho <= 0){
    processar_erro(1, "Dataset vazio passado para percentil\n");
    printf("Dataset vazio passado para percentil\n");
    return 1;
  }

  // checa se passou a porcentagem correta
  if (porcentagem > 100.0 || porcentagem < 0.0){
    processar_erro(1, "Porcentagem invalida, o usuário digitou uma porcentagem que não está entre 0 e 100");
    printf("Porcentagem invalida, a porcentagem deve estar entre 0 e 100\n");
    return 1;
  }

  double *organizado = organizar(dataset, tamanho);
  if (organizado == NULL) return 1;
  double index = (porcentagem/100.0) * (tamanho-1);
  int chao = (int)index;
  int teto = (chao + 1 < tamanho) ? chao + 1 : chao;

  // faz as contas para devolver o valor equivalente a aquele percentil
  double fraq = index - chao; 
  *resultado = ((organizado[teto] - organizado[chao]) * fraq) + organizado[chao];
  free(organizado);
  return 0;
}

// remove do dataset os valores extremos além dos limites superior e inferior (como em um box-plot)
double* filtro_outliers(const double *dataset, int tamanho, int *novo_tamanho){
  if (dataset == NULL || tamanho <= 0){
    processar_erro(1, "Dataset vazio passado para outliers\n");
    printf("Dataset vazio passado para outliers\n");
    return NULL;
  }
  
  *novo_tamanho = -1; // caso retorne NULL deixa o novo tamanho assim, indicando erro
  // faz as contas básicas necessárias para detectar os outliers

  double q3, q1;
  if (percentil(dataset, tamanho, 75.0, &q3) == 1 || percentil(dataset, tamanho, 25.0, &q1) == 1) return NULL;
  double intervalo_J = q3 - q1;
  double min_lim = q1 - (1.5 * intervalo_J);
  double max_lim = q3 + (1.5 * intervalo_J);
  double *valores_formatados = malloc(tamanho * sizeof *dataset);

  if (valores_formatados == NULL){
    processar_erro(1, "Erro ao inicializar o vetor dinâmico valores_formatados\n");
    printf("Erro ao inicializar o vetor dinâmico valores_formatados\n");
    return NULL;
  }

  // conta e grava todos os valores que não são outliers
  int n = 0;
  for (int i = 0; i < tamanho; i++){
    if (dataset[i] <= max_lim && dataset[i] >= min_lim) {
      valores_formatados[n] = dataset[i];
      n++;
    }
  }

  // verifica se todos os valores não são outliers
  if (n == 0) {
    free(valores_formatados);
    processar_erro(1, "Nenhum valor respeita os limites do vetor!\n");
    printf("Nenhum valor respeita os limites!\n");
    return NULL;
  }

  double *temp = realloc(valores_formatados, n * sizeof *valores_formatados);

  if (temp == NULL){
    free(valores_formatados);
    processar_erro(1, "Erro ao criar o arquivo temporário para passar valores para o array valores_formatados\n");
    printf("Erro ao criar o arquivo temporário para passar valores para o array valores_formatados\n");
    return NULL;
  }
  
  // retorna o array com os outliers e atualiza o tamanho do array
  valores_formatados = temp;
  *novo_tamanho = n;
  return valores_formatados;
}
