#include <stdio.h>
#include <stdlib.h>
#include "dados.h"

void mudtamvet(double **vetor,int novotamanho) {//mudtamvet recebe a memória de onde ta o ponteiro de dados
            double *temp = realloc(*vetor, (novotamanho) * sizeof **vetor);
        if (temp == NULL) {
            processar_erro(1, "Erro ao redimendionar o vetor dinâmico");
            printf("Erro ao redimendionar o vetor dinâmico\n");
            return;
        }
        *vetor = temp;
        return;
}

double* novovet(int tamanho){
    double *vetor = malloc(tamanho * sizeof *vetor);
    if (vetor==NULL){
        processar_erro(1, "Erro ao inicializar o vetor dinâmico ");
        printf("Erro ao inicializar o vetor dinâmico\n");
        return NULL;;
    }
    return vetor;
}

double* validarvetor(double *vetor){
    if(vetor == NULL) {
        processar_erro(1, "Vetor não válido");
        printf("Vetor não válido\n");
        return NULL;
    };
    return vetor;
}

double* coletar_dados(const char *nomedoarquivo, int *quantidade) { //quantidade é um int q já existia e q é alterado por essa função

    FILE *f = fopen(nomedoarquivo,"r"); //abrimos o arquivo
    if (f == NULL) { // ve se deu erro
        processar_erro(1, "Erro ao abrir o arquivo.");
        printf("Erro ao abrir o arquivo.\n");
        return NULL;;
    }
    double *dados = NULL;
    double a;
    int i = 0;
    while (fscanf(f, "%lf", &a) == 1) {
        mudtamvet(&dados, i+1);
        dados[i]=a;
        i++;
    }
    char ch;
    if (fscanf(f, " %c", &ch)==1) {
        free(dados);
        fclose(f);
        processar_erro(1, "Erro: O arquivo contém chars.");
        printf("Erro: O arquivo contém chars.\n");
        return NULL;
    }
    *quantidade = i;
    fclose(f);
    return dados;
}

void pedirnomedoarquivo(char *nomedoarquivo){ //precisa ter declarado char nomedoarquivo[260] antes de chamar a função
    printf("Digite o caminho do arquivo ou apenas o nome do arquivo .txt (incluindo o .txt) que armazena as amostras coletadas:");
    scanf(" %259[^\n]", nomedoarquivo); //sabemos o arquivos com os dados
}

void liberar_dados(double *dados){ free(dados); }
