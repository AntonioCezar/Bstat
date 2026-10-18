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

void teste_dados(){
    for (int i = 0; i < numerodecasos; i++)
    {
        printf("tesetando o arquivo  [%s]\n", casos[i].arquivo);
        if(i == 3)  printf("como tem char no arquivo txt, ele deve retornar erro");
        int quantidade = 0;
        double* dataset = coletar_dados(casos[i].arquivo, &quantidade);
        ASSERT_EQ_INT(casos[i].tamanho, quantidade);
        ASSERT_EQ_ARRAY(casos[i].dados, dataset, quantidade); 
        liberar_dados(dataset);
    }
    
}

void teste_liberar_vetor(){
    printf(COR_AMARELO "*** teste da função liberar_dados ***" COR_RESET "\n");
    double* teste0 = NULL;
    teste0 = novovet(5);
    for (int i = 0; i < 5; i++)
    {
        teste0[i]=i;
    }
    
    printf( "Elementos do vetor antes de liberar os dados:\n");
    imprimir_dados(teste0,5);
    liberar_dados(teste0);
    printf( "Vetor liberado!\n");
    printf( "Teste com vetor nulo\n");
    double* teste1 = NULL;
    liberar_dados(teste1);
    printf( "Vetor liberado!\n");
    printf("Testes da função finalizados!\n");
}

void teste_validar_vetor(){
    printf(COR_AMARELO "*** teste da função validarvetor ***" COR_RESET "\n");
    double* teste0 = NULL;
    teste0 = novovet(5);
    for (int i = 0; i < 5; i++)
    {
        teste0[i]=i;
    }
    double* teste1 = NULL;
    if (validarvetor(teste0)!= NULL) printf("Teste com vetor não nulo bem sucedido\n");
    else printf("O teste falhou\n");
    printf("Teste com vetor nulo:\n");
    if (validarvetor(teste1)== NULL) printf("Teste com vetor nulo bem sucedido (não válido)!\n");
    else printf("O teste falhou\n");
    liberar_dados(teste0);
    printf("Testes da função finalizados!\n");
}


int main(void) {
    teste_liberar_vetor();
    teste_validar_vetor();
        RUN_TESTE(teste_dados);
    RESUMO_TESTE(); //aqui ele retorna 0 se todos os testes forem bem sucedidos

}