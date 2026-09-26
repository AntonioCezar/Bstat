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
- Liberar Dataset
- Obter Tamanho
- Validar Dataset

Coleta de dados para o dataset mudará de acordo com a função que será chamada e usará alocação dinâmica de espaçi para guardar as informações que o usuário passar.

## Medidas de tendência central

- Média
- Mediana
- Moda
- Máximo
- Mínimo

## Medidas de dispersão

- Variância
- Desvio Padrão
- Amplitude

## Transformações

- Normalizar Escala
- Padronização
- Percentil

## Comandos

- Comando 1
- Comando 2
- Comando 3

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

## Estratégia no Git

Existirá uma branch para cada um dos 4 principais módulos:

- Gestão de dados
- Medidas de tendência central
- Medidas de dispersão
- Transformações

Além de branchs adicionais para a adição de outros módulos importantes como:

- Makefile
- ErrorHandler

Os merges para a `main` são feitos de forma incremental, conforme cada módulo é finalizado e testado.