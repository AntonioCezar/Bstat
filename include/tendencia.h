#ifndef TENDENCIA_H
#define TENDENCIA_H

double media(const double *dataset, int tamanho);

double mediana(double *dataset, int tamanho);

double* moda(double *dataset, int tamanho, int *apont_qtd_modas);

int quase_igual(double a, double b);

#endif
