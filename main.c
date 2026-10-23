#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILAS 6
#define COLUNAS 8
#define TAM_TITULO 60

// Função auxiliar para limpar o buffer do teclado após leituras com scanf
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 1. Função para ler e validar a string do título
void ler_titulo(char *titulo, int tamanho_max) {
    int valido = 0;
    while (!valido) {
        printf("Digite o titulo da sessao: ");
        if (fgets(titulo, tamanho_max, stdin) != NULL) {
            // Remove o '\n' do final, se existir
            size_t len = strlen(titulo);
            if (len > 0 && titulo[len - 1] == '\n') {
                titulo[len - 1] = '\0';
                len--;
            } else {
                limpar_buffer(); // Limpa o excesso caso o usuário digite além do limite
            }

            // Verifica se a string não está vazia ou só com espaços
            for (size_t i = 0; i < len; i++) {
                if (titulo[i] != ' ' && titulo[i] != '\t') {
                    valido = 1;
                    break;
                }
            }
        }
        if (!valido) {
            printf("[ERRO] O titulo da sessao nao pode ser vazio. Tente novamente.\n");
        }
    }
}

// 2. Função para exibir o mapa da sala
void exibir_mapa(int assentos[MAX_FILAS][COLUNAS], int qtd_filas, const char *titulo) {
    printf("\n========================================\n");
    printf(" SESSAO: %s\n", titulo);
    printf("========================================\n");
    printf("         Assentos (0 = Livre, 1 = Reservado)\n");
    printf("       ");
    for (int j = 0; j < COLUNAS; j++) {
        printf("A%d ", j + 1);
    }
    printf("\n");

    for (int i = 0; i < qtd_filas; i++) {
        printf("Fila %d: ", i + 1);
        for (int j = 0; j < COLUNAS; j++) {
            printf(" %d ", assentos[i][j]);
        }
        printf("\n");
    }
    printf("========================================\n");
}

// 3. Função para reservar (acao = 1) ou cancelar (acao = 0) um assento
void gerenciar_assento(int assentos[MAX_FILAS][COLUNAS], int qtd_filas, int acao) {
    int fila_usr, assento_usr;

    printf("\nInforme a fila (1 a %d): ", qtd_filas);
    if (scanf("%d", &fila_usr) != 1) {
        limpar_buffer();
        printf("[ERRO] Entrada invalida! Digite apenas numeros.\n");
        return;
    }

    printf("Informe o assento (1 a %d): ", COLUNAS);
    if (scanf("%d", &assento_usr) != 1) {
        limpar_buffer();
        printf("[ERRO] Entrada invalida! Digite apenas numeros.\n");
        return;
    }
    limpar_buffer();

    // Validação dos limites da sala
    if (fila_usr < 1 || fila_usr > qtd_filas || assento_usr < 1 || assento_usr > COLUNAS) {
        printf("[ERRO] Posicao fora da sala! Escolha fila entre 1 e %d, e assento entre 1 e %d.\n",
               qtd_filas, COLUNAS);
        return;
    }

    // Conversão da numeração do usuário (inicia em 1) para índices da matriz em C (inicia em 0)
    int idx_fila = fila_usr - 1;
    int idx_col = assento_usr - 1;

    if (acao == 1) { // Reservar
        if (assentos[idx_fila][idx_col] == 1) {
            printf("[AVISO] O assento (Fila %d, Assento %d) ja esta ocupado!\n", fila_usr, assento_usr);
        } else {
            assentos[idx_fila][idx_col] = 1;
            printf("[SUCESSO] Reserva confirmada para Fila %d, Assento %d!\n", fila_usr, assento_usr);
        }
    } else { // Cancelar
        if (assentos[idx_fila][idx_col] == 0) {
            printf("[AVISO] O assento (Fila %d, Assento %d) ja esta livre! Nao ha reserva para cancelar.\n",
                   fila_usr, assento_usr);
        } else {
            assentos[idx_fila][idx_col] = 0;
            printf("[SUCESSO] Reserva cancelada para Fila %d, Assento %d! O assento voltou a ficar livre.\n",
                   fila_usr, assento_usr);
        }
    }
}

// 4. Função que recebe ponteiro e preenche o vetor dinâmico do chamador
void calcular_livres_por_fila(int assentos[MAX_FILAS][COLUNAS], int qtd_filas, int *livres_por_fila) {
    for (int i = 0; i < qtd_filas; i++) {
        // 'cont_livres' é uma variável local (alocada na Stack): nasce a cada iteração e morre ao fim do bloco.
        int cont_livres = 0;
        for (int j = 0; j < COLUNAS; j++) {
            if (assentos[i][j] == 0) {
                cont_livres++;
            }
        }
        // Escreve o resultado na área de memória apontada pelo ponteiro (Heap)
        livres_por_fila[i] = cont_livres;
    }
}

// 5. Função para exibir o resumo da ocupação
void exibir_resumo(int assentos[MAX_FILAS][COLUNAS], int qtd_filas, int *livres_por_fila, const char *titulo) {
    // Atualiza o vetor dinâmico antes de gerar o relatório
    calcular_livres_por_fila(assentos, qtd_filas, livres_por_fila);

    int total_capacidade = qtd_filas * COLUNAS;
    int total_livres = 0;

    printf("\n========================================\n");
    printf(" RESUMO DA SESSAO: %s\n", titulo);
    printf("========================================\n");

    for (int i = 0; i < qtd_filas; i++) {
        printf("Fila %d: %d assentos livres (de %d)\n", i + 1, livres_por_fila[i], COLUNAS);
        total_livres += livres_por_fila[i];
    }

    int total_reservados = total_capacidade - total_livres;

    // Conversão explícita (float) para evitar truncamento por divisão inteira
    float porcentagem_ocupacao = ((float)total_reservados / total_capacidade) * 100.0f;

    printf("----------------------------------------\n");
    printf("Total de assentos da sala : %d\n", total_capacidade);
    printf("Total de assentos livres  : %d\n", total_livres);
    printf("Total de reservados       : %d\n", total_reservados);
    printf("Taxa de ocupacao          : %.2f%%\n", porcentagem_ocupacao);
    printf("========================================\n");
}

int main(void) {
    char titulo[TAM_TITULO];
    int qtd_filas = 0;
    int assentos[MAX_FILAS][COLUNAS];

    printf("=== SISTEMA DE RESERVA DE ASSENTOS DE CINEMA ===\n\n");

    // 1. Solicita e valida o título da sessão
    ler_titulo(titulo, TAM_TITULO);

    // 2. Solicita e valida a quantidade de filas (entre 1 e 6)
    while (qtd_filas < 1 || qtd_filas > MAX_FILAS) {
        printf("Informe a quantidade de filas da sala (1 a %d): ", MAX_FILAS);
        if (scanf("%d", &qtd_filas) != 1) {
            limpar_buffer();
            printf("[ERRO] Entrada invalida! Digite um numero inteiro.\n");
            qtd_filas = 0;
        } else {
            limpar_buffer();
            if (qtd_filas < 1 || qtd_filas > MAX_FILAS) {
                printf("[ERRO] Quantidade fora do limite permitido (1 a %d).\n", MAX_FILAS);
            }
        }
    }

    // 3. Inicializa todos os assentos da matriz como livres (0)
    for (int i = 0; i < qtd_filas; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            assentos[i][j] = 0;
        }
    }

    // 4. Alocação dinâmica na Heap para o vetor de resultados
    int *livres_por_fila = (int *)malloc(qtd_filas * sizeof(int));
    if (livres_por_fila == NULL) {
        fprintf(stderr, "[ERRO CRITICO] Falha ao alocar memoria na Heap.\n");
        return 1;
    }

    // Inicializa o vetor dinâmico antes do uso
    for (int i = 0; i < qtd_filas; i++) {
        livres_por_fila[i] = COLUNAS;
    }

    // 5. Laço do menu principal
    int opcao = 0;
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Exibir mapa de assentos\n");
        printf("2. Reservar um assento\n");
        printf("3. Cancelar uma reserva\n");
        printf("4. Exibir resumo de ocupacao\n");
        printf("5. Encerrar programa\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            printf("[ERRO] Opcao invalida! Digite um numero de 1 a 5.\n");
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:
                exibir_mapa(assentos, qtd_filas, titulo);
                break;
            case 2:
                gerenciar_assento(assentos, qtd_filas, 1);
                break;
            case 3:
                gerenciar_assento(assentos, qtd_filas, 0);
                break;
            case 4:
                exibir_resumo(assentos, qtd_filas, livres_por_fila, titulo);
                break;
            case 5:
                printf("\nEncerrando o sistema... Memoria liberada com sucesso!\n");
                break;
            default:
                printf("[ERRO] Opcao invalida! Escolha entre 1 e 5.\n");
        }
    } while (opcao != 5);

    // 6. Liberação da memória alocada dinamicamente na Heap
    free(livres_por_fila);
    livres_por_fila = NULL;

    return 0;
}