#include <stdio.h>
#include <string.h> // Para strcspn
#include <math.h>   // Para fabs (comparação de floats/doubles, se necessário para empate)

// Estrutura para armazenar os dados de uma carta
typedef struct {
    char estado;
    char codigo[4];
    char cidade[50];
    unsigned long int populacao; // Modificado para unsigned long int
    double area;                 // Modificado para double para maior precisão
    double pib_bilhoes;          // PIB em bilhões (valor de entrada)
    double pib_real;             // PIB em valor absoluto (para cálculos)
    int num_pontos_turisticos;
    double densidade_populacional;
    double pib_per_capita;
    float super_poder;
} Carta;

// Função para calcular a Densidade Populacional e o PIB per Capita
void calcularValoresIniciais(Carta *c) {
    // Calcular PIB Real a partir de PIB em Bilhões
    c->pib_real = c->pib_bilhoes * 1e9; // 1e9 = 1 bilhão

    if (c->area > 0) {
        c->densidade_populacional = (double)c->populacao / c->area;
    } else {
        c->densidade_populacional = 0; // Evitar divisão por zero
    }

    if (c->populacao > 0) {
        c->pib_per_capita = c->pib_real / c->populacao; // Usa pib_real
    } else {
        c->pib_per_capita = 0; // Evitar divisão por zero
    }
}

// Função para calcular o Super Poder
void calcularSuperPoder(Carta *c) {
    double inverso_densidade_populacional = 0;
    if (c->densidade_populacional > 1e-9) { // Evitar divisão por zero ou por valor muito pequeno
        inverso_densidade_populacional = 1.0 / c->densidade_populacional;
    }

    // Atenção à conversão de tipos ao somar
    // Usar pib_real para o Super Poder, não pib_bilhoes
    c->super_poder = (float)c->populacao +
                     (float)c->area +
                     (float)c->pib_real + // Importante: usar o valor real do PIB
                     (float)c->num_pontos_turisticos +
                     (float)c->pib_per_capita +
                     (float)inverso_densidade_populacional;
}

// Função para ler os dados de uma carta do usuário
void lerDadosCarta(Carta *c, int numeroCarta) {
    printf("\n=== CARTA %d ===\n", numeroCarta);
    printf("Estado (A-H): ");
    scanf(" %c", &c->estado); // Adicionado espaço antes de %c para consumir newlines pendentes
    getchar(); // Consome o newline após o char

    printf("Codigo (ex: A01): ");
    scanf("%3s", c->codigo);
    getchar(); // Consome o newline após o scanf de string limitada

    printf("Nome da Cidade: ");
    fgets(c->cidade, 50, stdin);
    c->cidade[strcspn(c->cidade, "\n")] = '\0'; // Remove o newline do fgets

    printf("Populacao: ");
    scanf("%lu", &c->populacao); // %lu para unsigned long int
    printf("Area (km²): ");
    scanf("%lf", &c->area); // %lf para double
    printf("PIB (em bilhões): ");
    scanf("%lf", &c->pib_bilhoes); // %lf para double
    printf("Pontos Turisticos: ");
    scanf("%d", &c->num_pontos_turisticos);
    getchar(); // Consome o newline pendente do último scanf numérico
}

int main() {
    Carta carta1, carta2;

    // Adiciona o título do jogo
    printf("=======================\n");
    printf("    JOGO DOS ESTADOS   \n");
    printf("=======================\n");

    // Entrada e Cálculos Carta 1
    lerDadosCarta(&carta1, 1);
    calcularValoresIniciais(&carta1);
    calcularSuperPoder(&carta1);

    // Entrada e Cálculos Carta 2
    lerDadosCarta(&carta2, 2);
    calcularValoresIniciais(&carta2);
    calcularSuperPoder(&carta2);

    // Exibição dos Dados Finais e Calculados (para conferência)
    printf("\n\n--- DADOS FINAIS E CÁLCULOS ---\n");
    printf("\nCarta 1:\n");
    printf("Estado: %c\n", carta1.estado);
    printf("Codigo: %s\n", carta1.codigo);
    printf("Cidade: %s\n", carta1.cidade);
    printf("População: %lu\n", carta1.populacao);
    printf("Área: %.2f km²\n", carta1.area);
    printf("PIB: %.2f bilhões (Valor Real: %.2f)\n", carta1.pib_bilhoes, carta1.pib_real);
    printf("Pontos Turísticos: %d\n", carta1.num_pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta1.densidade_populacional);
    printf("PIB per capita: R$ %.2f\n", carta1.pib_per_capita);
    printf("Super Poder: %.2f\n", carta1.super_poder);

    printf("\nCarta 2:\n");
    printf("Estado: %c\n", carta2.estado);
    printf("Codigo: %s\n", carta2.codigo);
    printf("Cidade: %s\n", carta2.cidade);
    printf("População: %lu\n", carta2.populacao);
    printf("Área: %.2f km²\n", carta2.area);
    printf("PIB: %.2f bilhões (Valor Real: %.2f)\n", carta2.pib_bilhoes, carta2.pib_real);
    printf("Pontos Turísticos: %d\n", carta2.num_pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta2.densidade_populacional);
    printf("PIB per capita: R$ %.2f\n", carta2.pib_per_capita);
    printf("Super Poder: %.2f\n", carta2.super_poder);


    // Comparar as cartas e exibir resultados das comparações
    printf("\n\n--- COMPARAÇÃO DE CARTAS ---\n");

    int carta1Vence; // 1 se carta1 vence, 0 se carta2 vence/empata

    // População: maior vence
    carta1Vence = (carta1.populacao > carta2.populacao);
    printf("População: Carta 1 venceu (%d)\n", carta1Vence);

    // Área: maior vence
    carta1Vence = (carta1.area > carta2.area);
    printf("Área: Carta 1 venceu (%d)\n", carta1Vence);

    // PIB (comparando o valor real): maior vence
    carta1Vence = (carta1.pib_real > carta2.pib_real);
    printf("PIB: Carta 1 venceu (%d)\n", carta1Vence);

    // Número de Pontos Turísticos: maior vence
    carta1Vence = (carta1.num_pontos_turisticos > carta2.num_pontos_turisticos);
    printf("Número de Pontos Turísticos: Carta 1 venceu (%d)\n", carta1Vence);

    // Densidade Populacional: MENOR vence
    // Tratamento para o caso de uma das densidades ser zero (que seria o "menor")
    if (fabs(carta1.densidade_populacional - 0.0) < 1e-9 && fabs(carta2.densidade_populacional - 0.0) < 1e-9) {
        carta1Vence = 0; // Empate se ambas são zero (ou muito próximas de zero)
    } else if (fabs(carta1.densidade_populacional - 0.0) < 1e-9) {
        carta1Vence = 1; // Carta 1 vence se sua densidade é zero e a da carta 2 não é
    } else if (fabs(carta2.densidade_populacional - 0.0) < 1e-9) {
        carta1Vence = 0; // Carta 2 vence se sua densidade é zero e a da carta 1 não é
    } else {
        carta1Vence = (carta1.densidade_populacional < carta2.densidade_populacional);
    }
    printf("Densidade Populacional: Carta 1 venceu (%d)\n", carta1Vence);

    // PIB per Capita: maior vence
    carta1Vence = (carta1.pib_per_capita > carta2.pib_per_capita);
    printf("PIB per Capita: Carta 1 venceu (%d)\n", carta1Vence);

    // Super Poder: maior vence
    carta1Vence = (carta1.super_poder > carta2.super_poder);
    printf("Super Poder: Carta 1 venceu (%d)\n", carta1Vence);

    return 0;
}
