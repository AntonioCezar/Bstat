#ifndef TENDENCIA_H
#define TENDENCIA_H

//As 3 primeiras funções são cópias provisórias pra testes
int soma (int a, int b);

double* organizar(double *dataset, int *tamanho);

double* copia_dataset(double *dataset, int *tamanho);

int quase_igual(double a, double b);

double esperanca(double *dataset, int *tamanho);

double mediana(double *dataset, int *tamanho);

double* pegar_moda(double *copia, int *tamanho, int maior_freq, int qtd_modas, int *apont_qtd_modas);

double* moda(double *dataset, int *tamanho, int *apont_qtd_modas);

#endif
