#include <stdio.h>
#include <stdlib.h>



void mudtamvet(double **vetor,int novotamanho) {//mudtamvet recebe a memória de onde ta o ponteiro de dados
            double *temp = realloc(*vetor, (novotamanho) * sizeof **vetor);
        if (temp == NULL) {
        printf("Erro ao redimendionar o vetor dinâmico\n");
            exit(1);
        }
        *vetor = temp;
}

double* novovet(int tamanho){
    double *vetor = malloc(tamanho * sizeof *vetor);
    if (vetor==NULL){
        printf("Erro ao inicializar o vetor dinâmico\n");
        exit(1);
    }
    return vetor;
}

double* coletar_dados(char *nomedoarquivo, int *quantidade) { //quantidade é um int q já existia e q é alterado por essa função

    FILE *f = fopen(nomedoarquivo,"r"); //abrimos o arquivo
    if (f == NULL) { // ve se deu erro
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }
    double *dados = NULL;
    double a;
    int i=0;
    while (fscanf(f, "%lf", &a) == 1) {
        mudtamvet(&dados, i+1);
        dados[i]=a;
        i++;
    }
    *quantidade = i;
    fclose(f);
    return dados;
}



void pedirnomedoarquivo(char *nomedoarquivo){ //precisa ter declarado char nomedoarquivo[260] antes de chamar a função
    printf("Digite o caminho do arquivo ou apenas o nome do arquivo .txt (incluindo o .txt) que armazena as amostras coletadas:");
    scanf(" %259[^\n]", nomedoarquivo); //sabemos o arquivos com os dados
}

void liberar_dados(double **dados){
    free(*dados);
    *dados = NULL;
}

int main()
{
    return 0;
}
