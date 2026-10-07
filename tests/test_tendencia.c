#include "minunit.h"
#include "../include/tendencia.h"

//isso é pra testar o teste
static void teste_soma(void) {
    ASSERT_EQ_INT(5, soma(2, 3));
    ASSERT_EQ_INT(0, soma(-1, 1));     
    ASSERT_EQ_INT(0, soma(0, 0));      
}

//teste média

//teste moda

//teste variância

int main(void) {
    printf("Tendência Central:\n");
    RUN_TESTE(teste_soma);
    RESUMO_TESTE();
}