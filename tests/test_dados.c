#include "minunit.h"
#include "../include/dados.h"

//Aqui você cria funções de teste usando os asserts do minunit.h

int main(void) {
    printf("Dados:\n");
    //RUN_TESTE(funcao_teste);
    RESUMO_TESTE(); //aqui ele retorna 0 se todos os testes forem bem sucedidos
}