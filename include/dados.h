#ifndef DADOS_H
#define DADOS_H

void mudtamvet(double **vetor,int novotamanho);

double* novovet(int tamanho);

double* coletar_dados(const char *nomedoarquivo, int *quantidade);

void pedirnomedoarquivo(char *nomedoarquivo);

void liberar_dados(double *dados);

#endif