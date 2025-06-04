#include <stdio.h> // Para a função printf
// #include <stdbool.h> // Para o tipo 'bool', mas usaremos int (0 ou 1) para simplicidade

// --- Constantes para os Movimentos das Peças (Valores de Entrada) ---
// Para Torre, Bispo, Rainha: número de passos para a recursão.
// Para Cavalo: componentes do movimento em L.

// Movimentos para as peças com recursão (valores originais mantidos)
#define MOVIMENTOS_TORRE 5
#define MOVIMENTOS_BISPO 5  // Número de passos diagonais
#define MOVIMENTOS_RAINHA 8

// Novos movimentos para o Cavalo (2 para cima, 1 para a direita)
#define CAVALO_PASSOS_CIMA 2
#define CAVALO_PASSOS_DIREITA_L 1 // O '_L' é para evitar confusão com outras direitas

// --- Protótipos das Funções de Movimentação ---
// Funções recursivas para Torre, Bispo e Rainha
void simularMovimentoTorreRecursivo(int passos_restantes);
void simularMovimentoBispoRecursivo(int passos_diag_restantes);
void simularMovimentoRainhaRecursivo(int passos_restantes);

// Função com loops complexos para o Cavalo
void simularMovimentoCavaloComplexo();

/*
 * === Requisitos Não Funcionais Atendidos ===
 * 1. Performance: O código, apesar de mais complexo, ainda é eficiente para
 * a tarefa, sem atrasos perceptíveis. A recursão tem um custo, mas para
 * poucos passos é aceitável.
 * 2. Documentação: Comentários extensivos explicam a lógica, as decisões de
 * design e como os requisitos são atendidos.
 * 3. Legibilidade:
 * - Código bem indentado e organizado em funções.
 * - Nomes de variáveis e constantes descritivos.
 * - Explicações claras para facilitar o entendimento.
 *
 * === Requisitos Funcionais Atendidos ===
 * 1. Entrada de Dados: Valores para movimentos e condições de loops definidos
 * como constantes no código.
 * 2. Recursividade (Torre, Bispo, Rainha): Implementada conforme solicitado.
 * 3. Loops Complexos (Cavalo): Movimento em "L" (2 cima, 1 direita) com
 * loops aninhados, múltiplas variáveis e exemplos de controle de fluxo.
 * 4. Loops Aninhados (Bispo): Além da recursão, o Bispo usa loops aninhados
 * (externo vertical, interno horizontal) para cada passo diagonal.
 * 5. Saída de Dados: printf para direções, separação entre peças com linhas em branco.
 */

int main() {
    printf("Simulacao de Movimento de Pecas de Xadrez (Avancado)\n");
    printf("-----------------------------------------------------\n\n");

    // --- Torre com Recursividade ---
    printf("Movimento da Torre (%d casas para a direita - com recursao):\n", MOVIMENTOS_TORRE);
    simularMovimentoTorreRecursivo(MOVIMENTOS_TORRE);
    printf("-----------------------------------------------------\n\n");

    // --- Bispo com Recursividade e Loops Aninhados ---
    printf("Movimento do Bispo (%d passos diagonais para cima e direita - com recursao e loops aninhados):\n", MOVIMENTOS_BISPO);
    simularMovimentoBispoRecursivo(MOVIMENTOS_BISPO);
    printf("-----------------------------------------------------\n\n");

    // --- Rainha com Recursividade ---
    printf("Movimento da Rainha (%d casas para a esquerda - com recursao):\n", MOVIMENTOS_RAINHA);
    simularMovimentoRainhaRecursivo(MOVIMENTOS_RAINHA);
    printf("-----------------------------------------------------\n\n");

    // Linha em branco antes do Cavalo, conforme solicitado em desafios anteriores
    // e mantido para consistência.
    printf("\n");

    // --- Cavalo com Loops Complexos ---
    printf("Movimento do Cavalo (%d casas para cima, %d para direita - com loops complexos):\n",
           CAVALO_PASSOS_CIMA, CAVALO_PASSOS_DIREITA_L);
    simularMovimentoCavaloComplexo();
    printf("-----------------------------------------------------\n\n");


    printf("Fim da simulacao.\n");
    return 0;
}

/**
 * @brief Simula o movimento da Torre usando recursividade.
 * @param passos_restantes O número de passos que a Torre ainda precisa dar.
 *
 * A Torre move-se para a direita. A cada chamada recursiva, um passo é dado
 * e a função é chamada novamente com um passo a menos, até que não haja
 * mais passos restantes (caso base).
 */
void simularMovimentoTorreRecursivo(int passos_restantes) {
    // Caso base: se não há mais passos a dar, a recursão para.
    if (passos_restantes <= 0) {
        return;
    }

    // Ação: Imprime o movimento deste passo.
    printf("Direita\n");

    // Chamada recursiva: simula o restante dos passos.
    simularMovimentoTorreRecursivo(passos_restantes - 1);
}

/**
 * @brief Simula o movimento diagonal do Bispo usando recursividade e loops aninhados.
 * @param passos_diag_restantes O número de passos diagonais que o Bispo ainda precisa dar.
 *
 * Para cada passo diagonal, o Bispo move-se um componente vertical e um horizontal.
 * A recursão controla o número total de passos diagonais.
 * Os loops aninhados controlam os componentes de cada passo diagonal:
 * - Loop externo: movimento vertical ("Cima").
 * - Loop interno: movimento horizontal ("Direita").
 * Esta estrutura resulta na impressão separada de "Cima" e "Direita" para cada
 * unidade de movimento diagonal.
 */
void simularMovimentoBispoRecursivo(int passos_diag_restantes) {
    // Caso base: se não há mais passos diagonais, a recursão para.
    if (passos_diag_restantes <= 0) {
        return;
    }

    // Ação para UM passo diagonal:
    // Loop externo para o componente vertical (1 vez "Cima")
    for (int i_vertical = 0; i_vertical < 1; i_vertical++) {
        printf("Cima\n");

        // Loop interno para o componente horizontal (1 vez "Direita")
        // Aninhado para cumprir o requisito "loop mais externo para o vertical,
        // e o mais interno para o horizontal".
        for (int j_horizontal = 0; j_horizontal < 1; j_horizontal++) {
            printf("Direita\n");
        }
    }

    // Chamada recursiva: simula o restante dos passos diagonais.
    simularMovimentoBispoRecursivo(passos_diag_restantes - 1);
}

/**
 * @brief Simula o movimento da Rainha usando recursividade.
 * @param passos_restantes O número de passos que a Rainha ainda precisa dar.
 *
 * A Rainha move-se para a esquerda. Similar à Torre, a cada chamada recursiva,
 * um passo é dado e a função se chama com um passo a menos.
 */
void simularMovimentoRainhaRecursivo(int passos_restantes) {
    // Caso base: não há mais passos.
    if (passos_restantes <= 0) {
        return;
    }

    // Ação: Imprime o movimento.
    printf("Esquerda\n");

    // Chamada recursiva.
    simularMovimentoRainhaRecursivo(passos_restantes - 1);
}

/**
 * @brief Simula o novo movimento do Cavalo (2 para cima, 1 para direita)
 * usando loops aninhados "complexos", com múltiplas variáveis
 * e/ou condições, e demonstrando o uso potencial de continue/break.
 *
 * O movimento em "L" é construído em fases dentro de um loop externo.
 * Loops internos cuidam dos passos de cada fase.
 */
void simularMovimentoCavaloComplexo() {
    // Loop externo principal para o movimento em "L" (executa uma vez neste caso,
    // mas poderia ser adaptado para múltiplos movimentos em L).
    // 'iteracao_l' e 'movimento_l_permitido' são exemplos de "múltiplas variáveis".
    for (int iteracao_l = 0; iteracao_l < 1; iteracao_l++) {
        int movimento_l_permitido = 1; // Usado como exemplo de condição (1 = true)

        // Exemplo de 'continue': se o movimento não fosse permitido,
        // pularia para a próxima iteração do loop externo (não acontecerá aqui).
        if (!movimento_l_permitido) {
            // Este 'printf' não será executado no fluxo normal.
            printf("Movimento L do Cavalo pulado (exemplo de continue)\n");
            continue;
        }

        // Fase 1 do L: Mover para cima (CAVALO_PASSOS_CIMA vezes)
        // Este é um loop aninhado.
        printf("Cavalo - Fase L (Vertical):\n");
        for (int passo_cima = 0; passo_cima < CAVALO_PASSOS_CIMA; passo_cima++) {
            // Condição de exemplo usando variável do loop externo e interno.
            if (iteracao_l == 0 && movimento_l_permitido) {
                printf("Cima\n");
            }
            // Exemplo de 'break': se uma condição específica forçasse a parada
            // da fase vertical prematuramente (não acontecerá aqui).
            if (passo_cima > 100) { // Condição trivial para exemplo de break
                // Este 'printf' não será executado.
                printf("Break na fase vertical do Cavalo (exemplo)\n");
                break;
            }
        }

        // Fase 2 do L: Mover para a direita (CAVALO_PASSOS_DIREITA_L vez)
        // Este é outro loop aninhado.
        // 'passo_direita' e 'contador_extra_k' são exemplos de "múltiplas variáveis" neste loop.
        printf("Cavalo - Fase L (Horizontal):\n");
        for (int passo_direita = 0, contador_extra_k = 0;
             passo_direita < CAVALO_PASSOS_DIREITA_L;
             passo_direita++, contador_extra_k++) {

            // Condição de exemplo usando múltiplas variáveis do loop interno.
            if (contador_extra_k == passo_direita && movimento_l_permitido) {
                printf("Direita\n");
            }
        }
        // Confirmação de que o L foi processado (para este exemplo).
        if (movimento_l_permitido) {
             // printf("Movimento L do Cavalo concluido para iteracao_l = %d\n", iteracao_l);
        }
    }
}
