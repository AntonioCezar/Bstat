#include <stdio.h>
#include <stdlib.h>
#include "distribuicao.h"
#define e 2.71828

// calcula fatorial de n
long fatorial(long n){
  long fator = 1; for (; n > 0; n--) fator *= n; return fator;
}

//calcula um numero n elevado a ex
double elevado(double n, int ex){
  double ele = 1.0; for (int i = 0; i < ex; i++) ele *= n; return ele;
}

// faz a combinação de (n ,k)
double combinacao(int n, int k){
  return fatorial(n) / (fatorial(n-k) * fatorial(k));
}

// calcula distribuição binomial usando a formula
double binomial(int n, int k, double p){
  return combinacao(n, k) * elevado(p, k) * elevado((1 - p), n-k);
}

// calcula distribuição geometrica usando a formula
double geometrica(int n, double p){
  return elevado((1-p), n-1) * p;
}

// calcula distribuição hipergeometrica usando a formula
double hipergeometrica(int N, int R, int n, int k){
  return combinacao(R, k) * combinacao(N-R, n-k) / combinacao(N, n);
}

// calcula distribuição poisson usando a formula
double poisson(int k, int lambda){
  return elevado(lambda, k) / (fatorial(k) * elevado(e, lambda));
}