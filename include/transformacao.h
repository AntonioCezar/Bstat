#ifndef TRANSFORMACAO_H
#define TRANSFORMACAO_H

// Todas as funções que retornam ponteiro devolvem um vetor NOVO (alocado com malloc).
// Quem chamar é responsável por dar free. Retornam NULL em caso de erro.

// Retorna uma cópia do vetor ordenada em ordem crescente.
double* organizar(const double *dataset, int tamanho);

// Normaliza os valores para escala de [0, 1]. Retorna NULL se todos forem iguais.
double* normalizar(const double *dataset, int tamanho);

// Padroniza para média 0 e desvio padrão 1. Retorna NULL se todos forem iguais.
double* padronizar(const double *dataset, int tamanho);

// Grava em *resultado o valor do percentil (0 a 100).
// Retorna 0 em sucesso e 1 em erro.
int percentil(const double *dataset, int tamanho, double porcentagem, double *resultado);

// Remove outliers (1.5 * quartil 3 - quartil 1) e salva em *novo_tamanho a quantidade que sobrou.
// Em erro retorna NULL e *novo_tamanho = -1.
double* filtro_outliers(const double *dataset, int tamanho, int *novo_tamanho);

#endif