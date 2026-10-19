/**
 * @file main.c
 * @brief Programa de demonstração da biblioteca Bstat.
 *
 * Lê um arquivo de amostras numéricas, mostra um resumo estatístico e
 * exercita as funções de tendência central, dispersão e transformação.
 *
 * Adicionalmente, lê parâmetros do usuário e exercita as funções de distribuição.
 *
 * Uso: ./bin/bstat [arquivo_de_dados]
 * Se o arquivo não for informado, o nome é pedido ao usuário.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/dados.h"
#include "../include/tendencia.h"
#include "../include/transformacao.h"
#include "../include/dispersao.h"
#include "../include/distribuicao.h" 

int rotina(double* dataset, int qtd) {
    if (!validarvetor(dataset)) return 1;
    imprimir_dados(dataset, qtd);
    printf("(...) \n");
    liberar_dados(dataset);
    printf("\n");
    return 0;
}

int main(int argc, char *argv[]) {
    char nomedoarquivo[260];
    char *caminho;
    int qtd = 0;

    //Descobrir qual arquivo ler
    if (argc >= 2) {
        caminho = argv[1];
    } else {
        pedirnomedoarquivo(nomedoarquivo);
        caminho = nomedoarquivo;
    }

    //Carregar os dados
    double *dataset = coletar_dados(caminho, &qtd);
    if (dataset == NULL || qtd <= 0) {
        fprintf(stderr, "Nao foi possivel carregar dados de '%s'.\n", caminho);
        liberar_dados(dataset);
        return 1;
    }

    printf("=== Bstat: resumo estatístico ===\n");
    printf("Arquivo:           %s\n", caminho);
    printf("Tamanho:           %d\n", qtd);

    //Tendência central
    printf("\n--- Tendência central ---\n");
        printf("**Media:                    %.4f\n", media(dataset, qtd));
        printf("**Mediana:                  %.4f\n", mediana(dataset, qtd));

        int qtd_modas = 0;
        double *modas = moda(dataset, qtd, &qtd_modas);

        printf("**Moda(s):                  ");
        if (qtd_modas == 0) printf("Não há moda");
        imprimir_dados(modas, qtd_modas);
        
        printf("\n");
        liberar_dados(modas);

    //Dispersão
    double *copia;
    printf("\n--- Dispersão ---\n");
        printf("**Desvio padrão:            %.4f\n", desvio_padrao(dataset, qtd));
        printf("**Variância:                %.4f\n", variancia(dataset, qtd));
        printf("**Amplitude:                %.4f\n", amplitude(dataset, qtd));
        printf("**Coeficiente de variação:  %.4f\n", coef_variacao(dataset, qtd));
        printf("\n");

    //Transformação
    printf("\n--- Transformação ---\n");
        printf("**Organizar:\n");
        printf("***Dataset em ordem crescente:\n");
        copia = organizar(dataset, qtd);
        rotina(copia, 5);

        printf("**Normalizar:\n");
        printf("***Dataset normalizado em [0,1]:\n");
        copia = normalizar(dataset, qtd);
        rotina(copia, 5);
        
        printf("**Padronizar:\n");
        printf("***Dataset padronizado para média 0 e desvio padrão 1\n");
        copia  = padronizar(dataset, qtd);
        rotina(copia, 5);

        printf("**Percentil:\n");
        printf("***Retorna o valor naquele percentil\n");
        printf("***Percentil 25:            %.4f\n", percentil(dataset, qtd, 25.0));
        printf("***Percentil 75:            %.4f\n", percentil(dataset, qtd, 75.0));

        printf("\n");

        printf("**Filtro de outliers:\n");
        printf("***Dataset sem outliers:\n");
        int novo_qtd = 0;
        copia = filtro_outliers(dataset, qtd, &novo_qtd);
        rotina(copia, 5);

    //Distribuição
    printf("\n--- Distribuição ---\n");
        int N, R, n, k;
        double lambda, p;

        printf("**Combinação (n escolhe k):\n");
        printf("  Digite n e k, respectivamente: ");
        scanf("%d %d", &n, &k);
        printf("  Resultado: %.4f\n", combinacao(n, k));

        printf("**Binomial:\n");
        printf("  Digite n, k e p, respectivamente: ");
        scanf("%d %d %lf", &n, &k, &p);
        printf("  Resultado: %.4f\n", binomial(n, k, p));

        printf("**Geométrica:\n");
        printf("  Digite n e p, respectivamente: ");
        scanf("%d %lf", &n, &p);
        printf("  Resultado: %.4f\n", geometrica(n, p));

        printf("**Hipergeométrica:\n");
        printf("  Digite N, R, n e k, respectivamente: ");
        scanf("%d %d %d %d", &N, &R, &n, &k);
        printf("  Resultado: %.4f\n", hipergeometrica(N, R, n, k));

        printf("**Poisson:\n");
        printf("  Digite k e lambda, respectivamente: ");
        scanf("%d %lf", &k, &lambda);
        printf("  Resultado: %.4f\n", poisson(k, lambda));
     
    printf("\n=== Bstat: fim da demonstração ===\n");

    //Limpeza
    liberar_dados(dataset);
    return 0;
}