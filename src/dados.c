#include <stdio.h>
#include <stdlib.h>

float* coletar_dados(int namostras){
    float *v = malloc(namostras * sizeof *v);
    if (v == NULL) {
        exit(1);
    }
    for (int i = 0; i < namostras; i++) {
        float amostra;
        scanf("%f", &amostra);
        v[i] = amostra;

    }
    
    return v;
}

void liberar_dados(float *v){
    free(v);
    v = NULL;
}


int main()
{
    return 0;
}
