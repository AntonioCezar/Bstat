#include <stdio.h>
#include <stdlib.h>
#include "distribuicao.h"
#define e 2.71828

int fatorial(int n){
  int fator = 1; for (n; n > 0; n--) fator *= n; return fator;
}

double elevado(int n, int ex){
  int ele = n; for (ex; ex > 1; ex--) ele *= ele; return ele;
}

double combinacao(int n, int k){
  return fatorial(n) / fatorial(n-k) * fatorial(k);
}

double binomial(int n, int k, int p){
  return combinacao(n, k) * elevado(p, k) * elevado((1 - p), n-k);
}

double geometrica(int n, int k, int p){
  return elevado((1-p), k-1) * p;
}

double hipergeometrica(int N, int R, int r, int n, int k){
  return combinacao(R, k) * combinacao(N-r, n-k) / combinacao(N, n);
}

double poisson(int k, int lambda){
  return elevado(lambda, k) / fatorial(k) * elevado(e, lambda);
}