# ITP - Segunda Avaliação: Reserva de Assentos de uma Sessão

## Identificação
* **Estudante:** Lucas Gabriel Pinto
* **Opção escolhida:** Opção 3 - Reserva de assentos de uma sessão

## Descrição do Projeto
Este programa resolve o problema de gerenciamento e controle de disponibilidade de assentos em uma pequena sala de cinema.

**Funcionalidades implementadas:**
* Leitura e validação do título da sessão (impedindo entradas vazias e respeitando o limite do vetor de caracteres) e da quantidade de filas (entre 1 e 6, com 8 assentos cada).
* Representação da sala através de uma matriz de inteiros (`0` para assento livre e `1` para reservado), iniciada integralmente com assentos livres.
* Menu interativo contendo opções para exibir o mapa da sala, reservar assento, cancelar reserva, exibir resumo de ocupação e encerrar o programa.
* Conversão de coordenadas amigáveis ao usuário (iniciando em 1) para os índices internos da matriz em C (iniciando em 0).
* Validação completa de limites e estados: bloqueia acessos fora das dimensões da sala, impede reservas de assentos já ocupados e evita o cancelamento de assentos que já estão livres.
* Alocação dinâmica na *Heap* (`malloc`) de um vetor de resultados para contabilizar os assentos livres por fila, preenchido através de uma função que manipula ponteiros, com verificação de alocação e liberação de memória (`free`) ao encerrar.
* Cálculo de estatísticas gerais da sessão (total de assentos, livres, reservados e taxa percentual de ocupação precisa utilizando ponto flutuante).

## Compilação e Execução
No terminal do Linux (com o compilador GCC instalado), navegue até a pasta do repositório e execute os comandos abaixo para compilar o código-fonte respeitando o padrão C11 e ativando os avisos de verificação:

```bash
gcc -std=c11 -Wall -Wextra main.c -o programa
./programa
```

## Exemplos de Testes

### Teste 1: Funcionamento Normal (Reserva, Resumo e Cancelamento)
* **Entradas fornecidas:**
  * Título da sessão: `Interestelar IMAX`
  * Quantidade de filas: `3`
  * Menu Opção `2` (Reservar): Fila `1`, Assento `2`
  * Menu Opção `4` (Exibir resumo)
  * Menu Opção `3` (Cancelar): Fila `1`, Assento `2`
  * Menu Opção `1` (Exibir mapa)
  * Menu Opção `5` (Encerrar)
* **Resultado esperado:**
  * O programa confirma a reserva do assento (Fila 1, Assento 2).
  * No resumo, exibe que a Fila 1 possui 7 assentos livres (de 8), e as Filas 2 e 3 possuem 8 assentos livres. O total apresenta 23 livres, 1 reservado e taxa de ocupação de `4.17%`.
  * Ao cancelar a reserva da Fila 1, Assento 2, o sistema confirma que o lugar voltou a ficar livre (`0` no mapa).

### Teste 2: Entradas Inválidas e Situações de Limite
* **Entradas fornecidas:**
  * Título da sessão: `[Enter vazio]` -> Em seguida: `Sessao Teste`
  * Quantidade de filas: `8` -> Em seguida: `2`
  * Menu Opção `2` (Reservar): Fila `1`, Assento `2` (Sucesso)
  * Menu Opção `2` (Reservar novamente o mesmo lugar): Fila `1`, Assento `2`
  * Menu Opção `2` (Reservar fora da sala): Fila `5`, Assento `9`
  * Menu Opção `3` (Cancelar assento já livre): Fila `1`, Assento `1`
* **Resultado esperado:**
  * O programa rejeita o título vazio e solicita novamente.
  * O programa rejeita a quantidade de filas `8` (fora do limite de 1 a 6) e solicita novamente até receber `2`.
  * Na tentativa de reservar novamente a Fila 1, Assento 2, exibe `[AVISO] O assento (Fila 1, Assento 2) ja esta ocupado!`.
  * Na tentativa de acessar a Fila 5, Assento 9, exibe `[ERRO] Posicao fora da sala!`.
  * Na tentativa de cancelar a Fila 1, Assento 1, exibe `[AVISO] O assento (Fila 1, Assento 1) ja esta livre! Nao ha reserva para cancelar.`.

## Vídeo de Apresentação
* **Link do vídeo no YouTube:** 
[Assistir apresentação no YouTube](https://youtu.be/GFY5Cl35KnM)

## Referências
* Material de aula da disciplina de Introdução às Técnicas de Programação (IMD/UFRN) — Aulas 6 a 11 (Matrizes, Tipos de Dados, Strings, Estrutura de Memória, Memória Estática/Heap, Ponteiros e Alocação Dinâmica).