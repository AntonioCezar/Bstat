#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "distribuicao.h"
#include "error.h"

// calcula fatorial de n
long fatorial(long n){
  if (n < 0) {
    processar_erro(5, "Fatorial: número negativo passado pelo usuário");
    printf("Erro: Não existe fatorial de número negativo\n");
    return -1;
  }
  if (n > 20) {
    processar_erro(5, "Fatorial: número maior que 20 estoura limite de long");
    printf("Erro: fatorial de n > 20 estoura limite de long\n");
    return -1;
  }
  long fator = 1; for (; n > 0; n--) fator *= n; return fator;
}

//calcula um numero n elevado a ex
double elevado(double n, int ex){
  if (ex < 0) {
    processar_erro(5, "Exponenciação: tentativa de elevar por um expoente negativo");
    printf("Erro: tentativa de elevar por um expoente negativo");
    return NAN;
  }
  double ele = 1.0; for (int i = 0; i < ex; i++) ele *= n; return ele;
}

// faz a combinação de (n ,k)
double combinacao(int n, int k){
  if (n < 0 || k < 0) {
    processar_erro(5, "Combinação: Número negativo passado pelo usuário");
    printf("Erro: combinação não aceita números negativos\n");
    return NAN;
  }
  if (k > n) return 0.0;
  return fatorial(n) / (fatorial(n-k) * fatorial(k));
}

// calcula distribuição binomial usando a formula
double binomial(int n, int k, double p){
  if (n < 0 || k < 0 || p < 0 || p > 1) {
    processar_erro(5, "Binomial: Número inválido passado pelo usuário");
    printf("Erro: número inválido passado para função de distribuição binomial\n");
    return NAN;
  }
  return combinacao(n, k) * elevado(p, k) * elevado((1 - p), n-k);
}

// calcula distribuição geometrica usando a formula
double geometrica(int n, double p){
  if (n < 1 || p < 0 || p > 1) {
    processar_erro(5, "Geometrica: Número inválido passado pelo usuário");
    printf("Erro: número inválido passado para função de distribuição geometrica\n");
    return NAN;
  }
  return elevado((1-p), n-1) * p;
}

// calcula distribuição hipergeometrica usando a formula
double hipergeometrica(int N, int R, int n, int k){
  if (n < 0 || k < 0 || N < 0 || R < 0) {
    processar_erro(5, "Hipergeometrica: Número negativo passado pelo usuário");
    printf("Erro: distribuição hipergeometrica não aceita números negativos\n");
    return NAN;
  }

  if (R > N || n > N) {
  processar_erro(5, "Hipergeometrica: parâmetros inconsistentes (R > N ou n > N)");
  return NAN;
  }

  if (k > n || k > R || (n - k) > (N - R)) return 0.0;
  return combinacao(R, k) * combinacao(N-R, n-k) / combinacao(N, n);
}

// calcula distribuição poisson usando a formula
double poisson(int k, double lambda){
  if (lambda < 0 || k < 0) {
    processar_erro(5, "Poisson: Número negativo passado pelo usuário");
    printf("Erro: distribuição poisson não aceita números negativos\n");
    return NAN;
  }
  return elevado(lambda, k) / (fatorial(k) * exp(lambda)); // exp(lambda) calcula e^lambda
}