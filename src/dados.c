#include <stdio.h>
#include <stdlib.h>

double* coletar_dados(int *tamanho) { //quantidade é um int q já existia e q é alterado por essa função

    char nomedoarquivo[260];
    printf("Digite o nome do arquivo .txt (incluindo o .txt) que armazena as amostras coletadas:");
    scanf("%259s", nomedoarquivo); //sabemos o arquivos com os dados
    FILE *f = fopen(nomedoarquivo,"r"); //abrimos o arquivo
    if (f == NULL) { // ve se deu erro
        printf("O arquivo não contém nenhum dado.");
        exit(1);
    }
    double *dados = malloc(1 * sizeof *dados); //cria o malloc inicialmente com só 1 de tamanho
    int i = 0;
    while (fscanf(f, "%f", &dados[i]) != EOF) {
        i++;
        double *temp = realloc(dados, (i+1) * sizeof *dados);//no final o vetor vai ter tamanho 1 a mais que o numero de dados
        if (temp == NULL) {
            free(dados);
            exit(1);
        }
        dados = temp;
    }
    tamanho = i;
    fclose(f);
    return dados;
}

void liberar_dados(double *v){
    free(v);
    v = NULL;
}
