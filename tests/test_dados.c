#include "minunit.h"
#include "../include/dados.h"

//Aqui você cria funções de teste usando os asserts do minunit.h

//Classe dos casos esperados
typedef struct {
    char *arquivo;
    double *dados;
    int tamanho;
} Caso;


//Cada objeto do array é um caso esperado
double inteiros[] = {13,-13,-10,1,0,2323,13131313,-98389,9236473,-29833,-1,-32323,-109475};
double naturais[] = {1,2,10,13,13,13,20,30,21,127317264312,198263192,364213,12312};
double reais[] = {13.13131333,9,1,32732873,1232.4454,67.67,0.0001,93102.839012,31.13};

 Caso casos[] = {
    {"tests/data/dados/inteiros.txt", inteiros,13},
    {"tests/data/dados/naturais.txt", naturais, 13},
    {"tests/data/dados/reais.txt", reais, 9},
    {"tests/data/dados/palavras.txt", NULL, 0},
};

int numerodecasos = 4;

void teste(){
    for (int i = 0; i < numerodecasos; i++)
    {
        int quantidade = 0;
        double* dataset = coletar_dados(casos[i].arquivo, &quantidade);
        ASSERT_EQ_INT(casos[i].tamanho, quantidade);
        ASSERT_EQ_ARRAY(casos[i].dados, dataset, quantidade); 
        liberar_dados(dataset);
    }
    
}

int main(void) {
        RUN_TESTE(teste);
    RESUMO_TESTE(); //aqui ele retorna 0 se todos os testes forem bem sucedidos
}