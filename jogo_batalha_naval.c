/**
 * @file batalha_naval_final.c // Nome do arquivo atualizado para refletir o estado final
 * @brief Programa em C para o jogo Batalha Naval com título.
 * Este programa posiciona quatro navios (2 H/V, 2 Diagonais) e três habilidades
 * especiais (Cone, Cruz, Octaedro) com áreas de efeito em um tabuleiro 10x10.
 * Exibe um título no início da execução.
 * Demonstra manipulação de matrizes, loops aninhados, condicionais e sobreposição de efeitos.
 * @version 3.2 // Versão incrementada
 */

#include <stdio.h>
#include <stdlib.h> // Para abs()
#include <string.h> // Para memset()

// --- Constantes Globais ---
#define TAMANHO_LINHA 10             ///< Número de linhas do tabuleiro principal.
#define TAMANHO_COLUNA 10            ///< Número de colunas do tabuleiro principal.
#define TAMANHO_NAVIO 3              ///< Tamanho fixo de cada navio.
#define VALOR_AGUA 0                 ///< Valor na matriz que representa água.
#define VALOR_NAVIO 3                ///< Valor na matriz que representa parte de um navio.
#define TOTAL_NAVIOS 4               ///< Total de navios a posicionar.

#define TAMANHO_MATRIZ_HABILIDADE 5  ///< Tamanho (lado) das matrizes de habilidade (ex: 5x5).
#define VALOR_HABILIDADE_AFETADO 1   ///< Valor na matriz de habilidade que indica área afetada.
#define VALOR_HABILIDADE_NAO_AFETADO 0 ///< Valor na matriz de habilidade que indica área não afetada.
#define VALOR_TABULEIRO_AFETADO_HABILIDADE 5 ///< Valor no tabuleiro principal para área afetada por habilidade.

// --- Protótipos das Funções ---

void inicializarTabuleiro(int tabuleiro[TAMANHO_LINHA][TAMANHO_COLUNA]);
void exibirTabuleiro(int tabuleiro[TAMANHO_LINHA][TAMANHO_COLUNA]);
int posicionarNavio(int tabuleiro[TAMANHO_LINHA][TAMANHO_COLUNA],
                     const int navioModelo[], int tamanhoNavio,
                     int linhaInicial, int colunaInicial, char orientacao);
void criarMatrizCone(int matriz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE]);
void criarMatrizCruz(int matriz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE]);
void criarMatrizOctaedro(int matriz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE]);
void sobreporHabilidade(int tabuleiro[TAMANHO_LINHA][TAMANHO_COLUNA],
                         const int matrizHabilidade[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE],
                         int origemLinhaTabuleiro, int origemColunaTabuleiro);


// --- Função Principal ---
int main() {
    // Adiciona o título no início da execução
    printf("===================================\n");
    printf("          BATALHA NAVAL          \n");
    printf("===================================\n\n");

    int tabuleiro[TAMANHO_LINHA][TAMANHO_COLUNA];
    int navioModelo[TAMANHO_NAVIO];
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        navioModelo[i] = VALOR_NAVIO;
    }

    inicializarTabuleiro(tabuleiro);
    // Palavra "Avançado" removida da próxima linha
    printf("Iniciando Batalha Naval\n");
    printf("Posicionando %d navios (tamanho %d)...\n\n", TOTAL_NAVIOS, TAMANHO_NAVIO);

    // --- Posicionamento dos Navios ---
    posicionarNavio(tabuleiro, navioModelo, TAMANHO_NAVIO, 1, 1, 'H'); // Navio 1: Horizontal em (1,1)
    posicionarNavio(tabuleiro, navioModelo, TAMANHO_NAVIO, 3, 1, 'V'); // Navio 2: Vertical em (3,1)
    posicionarNavio(tabuleiro, navioModelo, TAMANHO_NAVIO, 1, 4, 'D'); // Navio 3: Diagonal Principal em (1,4)
    posicionarNavio(tabuleiro, navioModelo, TAMANHO_NAVIO, 5, 5, 'A'); // Navio 4: Anti-Diagonal em (5,5)
    printf("Navios posicionados.\n\n");

    // --- Criação e Sobreposição das Habilidades ---
    printf("Preparando e aplicando habilidades especiais...\n");

    int matrizCone[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];
    int matrizCruz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];
    int matrizOctaedro[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];

    criarMatrizCone(matrizCone);
    criarMatrizCruz(matrizCruz);
    criarMatrizOctaedro(matrizOctaedro);
    printf("Matrizes de habilidade criadas.\n");

    printf("Aplicando Habilidade Cone em (2,3) do tabuleiro...\n");
    sobreporHabilidade(tabuleiro, matrizCone, 2, 3);

    printf("Aplicando Habilidade Cruz em (5,2) do tabuleiro...\n");
    sobreporHabilidade(tabuleiro, matrizCruz, 5, 2);

    printf("Aplicando Habilidade Octaedro em (7,6) do tabuleiro...\n");
    sobreporHabilidade(tabuleiro, matrizOctaedro, 7, 6);

    printf("Habilidades aplicadas.\n\n");

    // --- Exibir Tabuleiro Final ---
    exibirTabuleiro(tabuleiro);

    return 0; // Sucesso
}

// --- Implementação das Funções ---

void inicializarTabuleiro(int tabuleiro[TAMANHO_LINHA][TAMANHO_COLUNA]) {
    memset(tabuleiro, VALOR_AGUA, sizeof(int) * TAMANHO_LINHA * TAMANHO_COLUNA);
}

void exibirTabuleiro(int tabuleiro[TAMANHO_LINHA][TAMANHO_COLUNA]) {
    printf("\n## Tabuleiro Batalha Naval (%dx%d) ##\n", TAMANHO_LINHA, TAMANHO_COLUNA);
    printf("   ");
    for (int j = 0; j < TAMANHO_COLUNA; j++) printf("%2d ", j);
    printf("\n  +-");
    for (int j = 0; j < TAMANHO_COLUNA; j++) printf("---");
    printf("+\n");

    for (int i = 0; i < TAMANHO_LINHA; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < TAMANHO_COLUNA; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("|\n");
    }
    printf("  +-");
    for (int j = 0; j < TAMANHO_COLUNA; j++) printf("---");
    printf("+\n");
    printf("\nLegenda: %d=Água, %d=Navio, %d=Área de Efeito da Habilidade\n",
           VALOR_AGUA, VALOR_NAVIO, VALOR_TABULEIRO_AFETADO_HABILIDADE);
}

int posicionarNavio(int tabuleiro[TAMANHO_LINHA][TAMANHO_COLUNA],
                     const int navioModelo[], int tamanhoNavio,
                     int linhaInicial, int colunaInicial, char orientacao) {
    switch (orientacao) {
        case 'H': case 'h':
            if (linhaInicial < 0 || linhaInicial >= TAMANHO_LINHA ||
                colunaInicial < 0 || (colunaInicial + tamanhoNavio) > TAMANHO_COLUNA) return 0;
            for (int i = 0; i < tamanhoNavio; i++) tabuleiro[linhaInicial][colunaInicial + i] = navioModelo[i];
            break;
        case 'V': case 'v':
            if (colunaInicial < 0 || colunaInicial >= TAMANHO_COLUNA ||
                linhaInicial < 0 || (linhaInicial + tamanhoNavio) > TAMANHO_LINHA) return 0;
            for (int i = 0; i < tamanhoNavio; i++) tabuleiro[linhaInicial + i][colunaInicial] = navioModelo[i];
            break;
        case 'D': case 'd': 
            if (linhaInicial < 0 || (linhaInicial + tamanhoNavio) > TAMANHO_LINHA ||
                colunaInicial < 0 || (colunaInicial + tamanhoNavio) > TAMANHO_COLUNA) return 0;
            for (int i = 0; i < tamanhoNavio; i++) tabuleiro[linhaInicial + i][colunaInicial + i] = navioModelo[i];
            break;
        case 'A': case 'a': 
            if (linhaInicial < 0 || (linhaInicial + tamanhoNavio) > TAMANHO_LINHA ||
                colunaInicial < (tamanhoNavio - 1) || colunaInicial >= TAMANHO_COLUNA) return 0;
            for (int i = 0; i < tamanhoNavio; i++) tabuleiro[linhaInicial + i][colunaInicial - i] = navioModelo[i];
            break;
        default: return 0; 
    }
    return 1; 
}

void criarMatrizCone(int matriz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE]) {
    memset(matriz, VALOR_HABILIDADE_NAO_AFETADO, sizeof(int) * TAMANHO_MATRIZ_HABILIDADE * TAMANHO_MATRIZ_HABILIDADE);
    int coneTipRowLocal = 0;
    int coneTipColLocal = TAMANHO_MATRIZ_HABILIDADE / 2;

    for (int rOffset = 0; rOffset < 3; rOffset++) {
        int linhaAtualNaMatriz = coneTipRowLocal + rOffset;
        if (linhaAtualNaMatriz < TAMANHO_MATRIZ_HABILIDADE) {
            for (int c = coneTipColLocal - rOffset; c <= coneTipColLocal + rOffset; c++) {
                if (c >= 0 && c < TAMANHO_MATRIZ_HABILIDADE) {
                    matriz[linhaAtualNaMatriz][c] = VALOR_HABILIDADE_AFETADO;
                }
            }
        }
    }
}

void criarMatrizCruz(int matriz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE]) {
    memset(matriz, VALOR_HABILIDADE_NAO_AFETADO, sizeof(int) * TAMANHO_MATRIZ_HABILIDADE * TAMANHO_MATRIZ_HABILIDADE);
    int centro = TAMANHO_MATRIZ_HABILIDADE / 2;

    for (int r = 0; r < TAMANHO_MATRIZ_HABILIDADE; r++) {
        for (int c = 0; c < TAMANHO_MATRIZ_HABILIDADE; c++) {
            if (r == centro || c == centro) {
                matriz[r][c] = VALOR_HABILIDADE_AFETADO;
            }
        }
    }
}

void criarMatrizOctaedro(int matriz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE]) {
    memset(matriz, VALOR_HABILIDADE_NAO_AFETADO, sizeof(int) * TAMANHO_MATRIZ_HABILIDADE * TAMANHO_MATRIZ_HABILIDADE);
    int centro = TAMANHO_MATRIZ_HABILIDADE / 2;

    for (int r = 0; r < TAMANHO_MATRIZ_HABILIDADE; r++) {
        for (int c = 0; c < TAMANHO_MATRIZ_HABILIDADE; c++) {
            if (abs(r - centro) + abs(c - centro) <= centro) {
                matriz[r][c] = VALOR_HABILIDADE_AFETADO;
            }
        }
    }
}

void sobreporHabilidade(int tabuleiro[TAMANHO_LINHA][TAMANHO_COLUNA],
                         const int matrizHabilidade[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE],
                         int origemLinhaTabuleiro, int origemColunaTabuleiro) {
    
    int centroHabilidade = TAMANHO_MATRIZ_HABILIDADE / 2;

    for (int rHab = 0; rHab < TAMANHO_MATRIZ_HABILIDADE; rHab++) {
        for (int cHab = 0; cHab < TAMANHO_MATRIZ_HABILIDADE; cHab++) {
            if (matrizHabilidade[rHab][cHab] == VALOR_HABILIDADE_AFETADO) {
                int rTab = origemLinhaTabuleiro + (rHab - centroHabilidade);
                int cTab = origemColunaTabuleiro + (cHab - centroHabilidade);

                if (rTab >= 0 && rTab < TAMANHO_LINHA && cTab >= 0 && cTab < TAMANHO_COLUNA) {
                    tabuleiro[rTab][cTab] = VALOR_TABULEIRO_AFETADO_HABILIDADE;
                }
            }
        }
    }
}
