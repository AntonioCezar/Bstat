#include <stdio.h>
#include <stdlib.h>
#include "transformacao.h"
#include <error.h>

// faz um insertion sort para organizar os valores em ordem crescente
double* organizar(double *dataset, int *tamanho){
  for (int i = 1; i < *tamanho; i++){
    int n = 0;
    while ((i-n-1) >= 0 && dataset[i-n] < dataset[i-n-1]){
      double tmp = dataset[i-n-1];
      dataset[i-n-1] = dataset[i-n];
      dataset[i-n] = tmp;
      n++;
    }
  }
  return dataset;
}

// normaliza os valores em uma escala de 0 a 1 (ordena o dataset original - avisar user)
double* normalizar(double *dataset, int *tamanho){
  organizar(dataset, tamanho);
  double min = dataset[0];
  double max = dataset[*tamanho-1];
  // checa se os valores não são todos iguais
  if (max == min){
    printf("Todos os valores são iguais!\n");
    return dataset;
  }
  //cria o novo array para a escala normalizada
  double *normalizado = malloc(*tamanho * sizeof *dataset);
  if (normalizado == NULL){
    processar_erro(1, "Erro ao inicializar o vetor dinâmico de valores normalizados");
    printf("Erro ao inicializar o vetor dinâmico de valores normalizados\n");
    return dataset;
  } 
  // normaliza valor a valor na escala
  for (int i = 0; i < *tamanho; i++){
    normalizado[i] = (dataset[i] - min) / (max - min);
  }
  return normalizado;
}

// padroniza os valores para que o desvio padrão dê 1 e a média 0
double* padronizar(double *dataset, int *tamanho){
  double media = esperanca(dataset, tamanho); // usa a função que faz a média
  double dp = desvio_padrao(dataset, tamanho); // usa a função que faz o dp
  // checa se os valores não são todos iguais
  if (dp == 0.0){
    processar_erro(1, "Todos os valores passados pelo usuário são iguais!");
    printf("Todos os valores são iguais!\n");
    return dataset;
  }
  //cria o novo array para a escala padronizada
  double *padronizado = malloc(*tamanho * sizeof *dataset);
  if (padronizado == NULL){
    processar_erro(1, "Erro ao inicializar o vetor dinâmico de valores padronizados");
    printf("Erro ao inicializar o vetor dinâmico de valores padronizados\n");
    return dataset;
  } 
  // padroniza valor a valor na escala
  for (int i = 0; i < *tamanho; i++){
    padronizado[i] = (dataset[i] - media) / dp;
  }
  return padronizado;
}

// recebe um percentil do conjunto de dados e retorna o valor que estaria naquele percentil
double percentil(double *dataset, int *tamanho, double porcentagem){
  // checa se passou a porcentagem correta
  if (porcentagem > 100.0 || porcentagem < 0.0){
    processar_erro(1, "Porcentagem invalida, o usuário digitou uma porcentagem que não está entre 0 e 100");
    printf("Porcentagem invalida, digite um valor entre 0 e 100\n");
    exit(1);
  }
  organizar(dataset, tamanho);
  double ponto;
  double teto, chao;
  double index = (porcentagem/100.0) * (*tamanho-1);
  // checa se index já é ou não inteiro
  if (index == (int)index) {
    teto = dataset[(int)index];
    chao = teto;
  } else {
    teto = dataset[(int)index + 1];
    chao = dataset[(int)index];
  }
  // faz as contas para devolver o valor equivalente a aquele percentil
  double fraq = index - (int)index; 
  ponto = ((teto - chao) * fraq) + chao;
  return ponto;
}

// remove do dataset os valores extremos além dos limites superior e inferior (como em um box-plot)
double* filtro_outliers(double *dataset, int *tamanho){
  // faz as contas básicas necessárias para detectar os outliers
  double q3 = percentil(dataset, tamanho, 75.0);
  double q1 = percentil(dataset, tamanho, 25.0);
  double intervalo_J = q3 - q1;
  double min_lim = q1 - (1.5 * intervalo_J);
  double max_lim = q3 + (1.5 * intervalo_J);
  double *valores_formatados = malloc(*tamanho * sizeof *dataset);
  if (valores_formatados == NULL){
    printf("Erro ao inicializar o vetor dinâmico valores_formatados\n");
    exit(1);
  }
  // conta e grava todos os valores que não são outliers
  int n = 0;
  for (int i = 0; i < *tamanho; i++){
    if (dataset[i] <= max_lim && dataset[i] >= min_lim) {
      valores_formatados[n] = dataset[i];
      n++;
    }
  }
  // verifica se todos os valores não são outliers
  if (n == 0) {
    free(valores_formatados);
    printf("Nenhum valor respeita os limites!\n");
    exit(1);
  }
  double *temp = realloc(valores_formatados, n * sizeof *valores_formatados);
  if (temp == NULL){
    free(valores_formatados);
    printf("Erro ao criar o arquivo temporário para passar valores para o array valores_formatados\n");
    exit(1);
  }
  // retorna o array com os outliers e atualiza o tamanho do array
  valores_formatados = temp;
  *tamanho = n;
  return valores_formatados;
}