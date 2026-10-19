# Biblioteca de Cálculos Estatísticos Básicos (Bstat)

## Integrantes

- Antônio Cezar de Castro Ramos
- Jefferson Junior Medeiros de Mesquita
- Rafael Yugo Caballero Tamaki
- Henrique de Assunção Ferreira

## Pré-requisitos

- GCC
- Sistema Linux ou WSL Para Execução no Windows

## Estrutura do Projeto

```
Bstat/
├── src/
├── include/
├── errors/
│   ├── error.c
│   └── error.h
├── tests/
├── app/
│   └── main.c
├── build/
├── lib/  
├── bin/
├── Makefile
└── README.md
```

## Gestão de dados central

- Criar Dataset

```c
coletar_dados(caminho_do_arquivo_txt, ponteiro_para_int_que_guardara_tamanho_do_vetor_criado)
```
  
- Liberar Dataset

```c
liberar_dataset(vetor_dataset)
```

- Validar Dataset

```c
validar(vetor_dataset)
```

A função *coletar_dados* (Criar Dataset) coletará os valores de um arquivo com extensão `.txt` com valores separados por uma quebra de linha. A função usa alocação dinâmica de espaço para guardar as informações que o usuário passar.

Já a função *validar* (Validar Dataset) tem o objetivo de checar se o vetor dinâmico passado pelo usuário na utilização direta da biblioteca em seu código é válido para a utilização nas funções disponíveis da BStat.

## Medidas de tendência central

- Média

```c
media(vetor_dataset, tamanho_do_vetor)
```

- Mediana

```c
mediana(vetor_dataset, tamanho_do_vetor)
```

- Moda

```c
moda(vetor_dataset, tamanho_do_vetor, quantidade_modas)
```

## Medidas de dispersão

- Variância

```c
variancia(vetor_dataset, tamanho_do_vetor)
```

- Desvio Padrão

```c
desvio_padrao(vetor_dataset, tamanho_do_vetor)
```

- Amplitude

```c
amplitude(vetor_dataset, tamanho_do_vetor)
```

- Coeficiente de Variação

```c
coef_variacao(vetor_dataset, tamanho_do_vetor)
```

## Transformações

- Normalizar Escala

```c
normalizar(vetor_dataset, tamanho_do_vetor)
```

- Padronização

```c
padronizar(vetor_dataset, tamanho_do_vetor)
```

- Percentil

```c
percentil(vetor_dataset, tamanho_do_vetor, percentil_desejado, vetor_para_guardar_retorno_da_funcao)
```

- Remoção de Outliers

```c
filtro_outliers(vetor_dataset, tamanho_do_vetor, vetor_para_guardar_novo_tamanho_sem_outliers)
```

## Makefile

```bash
make
```

Exibe para o usuário os principais comandos para a utilização do makefile.

### Instalar

```bash
make install PREFIX=$HOME/.local
```

Instala a biblioteca para ser utilizada no sistema do usuário.

### Compilar

```bash
make all
```

Compila todos os arquivos .c da biblioteca.

### Testar

```bash
make test
```

Testa o programa com casos de teste base para garantir o pleno funcionamento da bibioteca.

### Executar

```bash
make run
```

Compila, caso necessário, e executa o programa .c com todas as bibliotecas

### Limpar

```bash
make clean
```

Limpa todos os artefatos gerados na compilação das bibliotecas.

## Tratamento de Erros

Módulo de erro central que lida com possibilidades de erro de todos os módulos em apenas um script, visando deixar o tratamento padronizado e organizado para todo o projeto.

O módulo recebe a mensagem de erro e o código, abaixo estão listado os códigos dos principais erros tratados:

- erro 1 (desc)
- erro 2 (desc)
- erro 3 (desc)

## Estratégia no Git

Há no projeto uma branch para cada um dos 4 principais módulos:

- Gestão de dados
- Medidas de tendência central
- Medidas de dispersão
- Transformações

Além de uma branch adicional para auxiliar na comunicação entre os módulos durante o projeto:

- develop

Os merges para a `main` são feitos de forma incremental, conforme cada módulo é finalizado e testado.
