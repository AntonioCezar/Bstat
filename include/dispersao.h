#ifndef DISPERSAO_H
#define DISPERSAO_H

double desvio_padrao(const double* dataset, int tamanho);
double valor_absoluto(double num);
double raiz_quadrada(double num);
double variancia(const double* dataset, int tamanho);
double amplitude(const double* dataset, int tamanho);
double coef_variacao(const double* dataset, int tamanho);

#endif