#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "error.h"

void processar_erro(int codigo, char *mensagem){

  // pega o horário atual e coloca em um struct com as informações que vem do localtime
  time_t tempo_bruto;
  struct tm *info_tempo;
  time(&tempo_bruto);
  info_tempo = localtime(&tempo_bruto);

  // cria o array de chars nome_arquivo e coloca as informações de tempo e codigo de erro nele
  char nome_arquivo[64];
  snprintf(nome_arquivo, sizeof(nome_arquivo), "Log_Hora_%02d-%02d-%02d_Cod_%d", info_tempo->tm_hour, info_tempo->tm_min, info_tempo->tm_sec, codigo);

  // cria o arquivo de log
  FILE *arquivo;
  arquivo = fopen(nome_arquivo, "a");

  if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de log!\n");
        exit(2);
    }
  
  // coloca informações no arquivo de log
  fprintf(arquivo, "Código de erro: %d\n", codigo);
  fprintf(arquivo, "Mensagem de erro: %s\n\n", mensagem);

  printf("Log de erro criado no diretório atual!\n");
  
  fclose(arquivo);
}