#include <stdio.h>
#include <string.h> // Para strcspn, strcmp, strcpy, strncpy
#include <math.h>   // Para fabs
#include <stdlib.h> // Para EXIT_SUCCESS, EXIT_FAILURE
#include <ctype.h>  // Para toupper

// Estrutura para armazenar os dados de uma carta de PAÍS
typedef struct {
    char nomePais[50];
    unsigned long int populacao;
    double area;
    double pib_bilhoes;
    double pib_real;
    int num_pontos_turisticos;
    double densidade_demografica;
} CartaPais;

// Estrutura para armazenar os dados de uma carta de ESTADO
typedef struct {
    char nome_do_estado[50];
    char codigo_carta[10];
    char nome_cidade[50];
    int populacao_cidade;
    float area_cidade;
    float pib_bilhoes_estado;
    int num_pontos_turisticos_cidade;
    // char identificador_tipo_estado_ah; // Removido
    double pib_real_estado;
    double densidade_demografica_cidade;
} CartaEstado;


// Constantes para escolhas de atributos (JOGO DOS PAÍSES)
#define ATTR_PAIS_POPULACAO 1
#define ATTR_PAIS_AREA 2
#define ATTR_PAIS_PIB 3
#define ATTR_PAIS_PONTOS_TURISTICOS 4
#define ATTR_PAIS_DENSIDADE_DEMOGRAFICA 5

// Constantes para escolhas de atributos (JOGO DOS ESTADOS)
#define ATTR_EST_POPULACAO_CIDADE 1
#define ATTR_EST_AREA_CIDADE 2
#define ATTR_EST_PIB_ESTADO 3
#define ATTR_EST_PONTOS_TURISTICOS_CIDADE 4
#define ATTR_EST_DENSIDADE_DEMOGRAFICA_CIDADE 5

// --- Protótipos das Funções (Comum) ---
void limparBufferEntrada(void);

// --- Protótipos das Funções (Jogo dos Países) ---
void calcularAtributosDerivadosPais(CartaPais *c);
void lerDadosCartaPais(CartaPais *c, int numeroCarta);
void obterNomeAtributoPais(int escolha, char *nomeAtributo, size_t tamanhoBuffer);
int exibirMenuAtributoPais(const char* tituloMenu, int atributoExcluido);
double obterValorAtributoPais(const CartaPais *c, int escolhaAtributo);
void exibirValorFormatadoPais(const CartaPais *c, int escolhaAtributo);
void compararCartasDoisAtributosPais(const CartaPais *c1, const CartaPais *c2, int attrChoice1, int attrChoice2);
void iniciarJogoDosPaises(void);
void exibirRegrasJogoPaises(void);

// --- Protótipos das Funções (Jogo dos Estados) ---
void calcularAtributosDerivadosEstado(CartaEstado *c);
void lerDadosCartaEstado(CartaEstado *c, int numeroCarta);
void obterNomeAtributoEstado(int escolha, char *nomeAtributo, size_t tamanhoBuffer);
int exibirMenuAtributoEstado(const char* tituloMenu, int atributoExcluido);
double obterValorAtributoEstado(const CartaEstado *c, int escolhaAtributo);
void exibirValorFormatadoEstado(const CartaEstado *c, int escolhaAtributo);
void compararCartasDoisAtributosEstado(const CartaEstado *c1, const CartaEstado *c2, int attrChoice1, int attrChoice2);
void iniciarJogoDosEstados(void);
void exibirRegrasJogoEstados(void);

// --- Protótipos das Funções (Menu de Regras) ---
void gerenciarExibicaoDeRegras(void);


// Função para limpar o buffer de entrada (stdin)
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


// === Implementações Jogo dos Países (sem alterações nesta seção) ===

void calcularAtributosDerivadosPais(CartaPais *c) {
    c->pib_real = c->pib_bilhoes * 1e9;
    if (c->area > 1e-9) {
        c->densidade_demografica = (double)c->populacao / c->area;
    } else {
        c->densidade_demografica = 0;
    }
}

void lerDadosCartaPais(CartaPais *c, int numeroCarta) {
    printf("\n=== DADOS DA CARTA DO PAÍS %d ===\n", numeroCarta);
    printf("Nome do País: ");
    fgets(c->nomePais, 50, stdin);
    c->nomePais[strcspn(c->nomePais, "\n")] = '\0';
    printf("População: ");
    while (scanf("%lu", &c->populacao) != 1) {
        printf("Entrada inválida. Digite um número para População: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();
    printf("Área (km²): ");
    while (scanf("%lf", &c->area) != 1) {
        printf("Entrada inválida. Digite um número para Área: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();
    printf("PIB (em bilhões, ex: 500.75): ");
    while (scanf("%lf", &c->pib_bilhoes) != 1) {
        printf("Entrada inválida. Digite um número para PIB: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();
    printf("Número de Pontos Turísticos: ");
    while (scanf("%d", &c->num_pontos_turisticos) != 1) {
        printf("Entrada inválida. Digite um número para Pontos Turísticos: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();
}

void obterNomeAtributoPais(int escolha, char *nomeAtributo, size_t tamanhoBuffer) {
    switch (escolha) {
        case ATTR_PAIS_POPULACAO: strncpy(nomeAtributo, "População", tamanhoBuffer -1); break;
        case ATTR_PAIS_AREA: strncpy(nomeAtributo, "Área", tamanhoBuffer -1); break;
        case ATTR_PAIS_PIB: strncpy(nomeAtributo, "PIB", tamanhoBuffer -1); break;
        case ATTR_PAIS_PONTOS_TURISTICOS: strncpy(nomeAtributo, "Número de Pontos Turísticos", tamanhoBuffer -1); break;
        case ATTR_PAIS_DENSIDADE_DEMOGRAFICA: strncpy(nomeAtributo, "Densidade Demográfica", tamanhoBuffer -1); break;
        default: strncpy(nomeAtributo, "Desconhecido", tamanhoBuffer -1); break;
    }
    nomeAtributo[tamanhoBuffer-1] = '\0';
}

int exibirMenuAtributoPais(const char* tituloMenu, int atributoExcluido) {
    int escolha;
    char nomeAttrExcluido[50] = "";
    if (atributoExcluido != 0) {
        obterNomeAtributoPais(atributoExcluido, nomeAttrExcluido, sizeof(nomeAttrExcluido));
    }
    printf("\n--- %s (PAÍSES) ---\n", tituloMenu);
    printf("Escolha o atributo:\n");
    if (atributoExcluido != ATTR_PAIS_POPULACAO) printf("1. População\n");
    else printf("1. População (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    if (atributoExcluido != ATTR_PAIS_AREA) printf("2. Área\n");
    else printf("2. Área (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    if (atributoExcluido != ATTR_PAIS_PIB) printf("3. PIB\n");
    else printf("3. PIB (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    if (atributoExcluido != ATTR_PAIS_PONTOS_TURISTICOS) printf("4. Número de Pontos Turísticos\n");
    else printf("4. Número de Pontos Turísticos (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    if (atributoExcluido != ATTR_PAIS_DENSIDADE_DEMOGRAFICA) printf("5. Densidade Demográfica\n");
    else printf("5. Densidade Demográfica (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    printf("Opção: ");
    while (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 5 || escolha == atributoExcluido) {
        printf("Opção inválida ou já escolhida. Tente novamente: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();
    return escolha;
}

double obterValorAtributoPais(const CartaPais *c, int escolhaAtributo) {
    switch (escolhaAtributo) {
        case ATTR_PAIS_POPULACAO: return (double)c->populacao;
        case ATTR_PAIS_AREA: return c->area;
        case ATTR_PAIS_PIB: return c->pib_real;
        case ATTR_PAIS_PONTOS_TURISTICOS: return (double)c->num_pontos_turisticos;
        case ATTR_PAIS_DENSIDADE_DEMOGRAFICA: return c->densidade_demografica;
        default: return 0.0;
    }
}

void exibirValorFormatadoPais(const CartaPais *c, int escolhaAtributo) {
    switch (escolhaAtributo) {
        case ATTR_PAIS_POPULACAO: printf("%lu", c->populacao); break;
        case ATTR_PAIS_AREA: printf("%.2f km²", c->area); break;
        case ATTR_PAIS_PIB: printf("US$ %.2f bilhões", c->pib_bilhoes); break;
        case ATTR_PAIS_PONTOS_TURISTICOS: printf("%d", c->num_pontos_turisticos); break;
        case ATTR_PAIS_DENSIDADE_DEMOGRAFICA: printf("%.2f hab/km²", c->densidade_demografica); break;
        default: printf("N/A"); break;
    }
}

void compararCartasDoisAtributosPais(const CartaPais *c1, const CartaPais *c2, int attrChoice1, int attrChoice2) {
    char nomeAttr1Str[50], nomeAttr2Str[50];
    obterNomeAtributoPais(attrChoice1, nomeAttr1Str, sizeof(nomeAttr1Str));
    obterNomeAtributoPais(attrChoice2, nomeAttr2Str, sizeof(nomeAttr2Str));
    double val_c1_attr1 = obterValorAtributoPais(c1, attrChoice1);
    double val_c2_attr1 = obterValorAtributoPais(c2, attrChoice1);
    double val_c1_attr2 = obterValorAtributoPais(c1, attrChoice2);
    double val_c2_attr2 = obterValorAtributoPais(c2, attrChoice2);
    double soma_c1 = val_c1_attr1 + val_c1_attr2;
    double soma_c2 = val_c2_attr1 + val_c2_attr2;
    printf("\n\n--- RESULTADO DA COMPARAÇÃO (PAÍSES) ---\n");
    printf("Países em comparação: %s vs %s\n", c1->nomePais, c2->nomePais);
    printf("Atributos escolhidos: %s e %s\n\n", nomeAttr1Str, nomeAttr2Str);
    printf("Detalhes dos Atributos:\n");
    printf("  %s:\n", nomeAttr1Str);
    printf("    - %s: ", c1->nomePais); exibirValorFormatadoPais(c1, attrChoice1); printf("\n");
    printf("    - %s: ", c2->nomePais); exibirValorFormatadoPais(c2, attrChoice1); printf("\n");
    printf("  %s:\n", nomeAttr2Str);
    printf("    - %s: ", c1->nomePais); exibirValorFormatadoPais(c1, attrChoice2); printf("\n");
    printf("    - %s: ", c2->nomePais); exibirValorFormatadoPais(c2, attrChoice2); printf("\n\n");
    printf("Soma dos valores dos atributos:\n");
    printf("  %s (Soma: %.2f + %.2f): %.2f\n", c1->nomePais, val_c1_attr1, val_c1_attr2, soma_c1);
    printf("  %s (Soma: %.2f + %.2f): %.2f\n\n", c2->nomePais, val_c2_attr1, val_c2_attr2, soma_c2);
    printf("Resultado Final da Rodada (Países):\n");
    const double EPSILON = 1e-9;
    if (fabs(soma_c1 - soma_c2) < EPSILON) {
        printf("Empate! As somas dos atributos são iguais.\n");
    } else if (soma_c1 > soma_c2) {
        printf("🏆 %s vence a rodada! 🎉\n", c1->nomePais);
    } else {
        printf("🏆 %s vence a rodada! 🎉\n", c2->nomePais);
    }
    printf("----------------------------------------------------------\n");
}

void iniciarJogoDosPaises(void) {
    CartaPais carta1, carta2;
    int escolhaAttr1, escolhaAttr2;

    printf("\n--- CADASTRO DAS CARTAS DE PAÍSES ---\n");
    lerDadosCartaPais(&carta1, 1);
    calcularAtributosDerivadosPais(&carta1);
    lerDadosCartaPais(&carta2, 2);
    calcularAtributosDerivadosPais(&carta2);
    escolhaAttr1 = exibirMenuAtributoPais("ESCOLHA DO PRIMEIRO ATRIBUTO", 0);
    escolhaAttr2 = exibirMenuAtributoPais("ESCOLHA DO SEGUNDO ATRIBUTO", escolhaAttr1);
    compararCartasDoisAtributosPais(&carta1, &carta2, escolhaAttr1, escolhaAttr2);
}

void exibirRegrasJogoPaises(void) {
    printf("\n📜--- REGRAS DO JOGO DOS PAÍSES ---📜\n");
    printf("Bem-vindo ao Jogo dos Países! O objetivo é comparar duas cartas de países\n");
    printf("e determinar qual delas é a vencedora com base em seus atributos.\n\n");
    printf("1. CADASTRO DAS CARTAS: 📝\n");
    printf("   - Você precisará cadastrar os dados para duas cartas de países.\n");
    printf("   - Para cada país, informe: Nome, População, Área (km²), PIB (em bilhões), Número de Pontos Turísticos.\n");
    printf("   - O sistema calculará: PIB Real e Densidade Demográfica.\n\n");
    printf("2. ESCOLHA DOS ATRIBUTOS PARA COMPARAÇÃO: 📊\n");
    printf("   - Você escolherá DOIS atributos DIFERENTES para a disputa.\n");
    printf("   - Atributos: População, Área, PIB, No de Pontos Turísticos, Densidade Demográfica.\n\n");
    printf("3. COMO VENCER A RODADA: 🏆\n");
    printf("   - O sistema soma os valores numéricos dos DOIS atributos escolhidos para cada carta.\n");
    printf("   - A CARTA COM A MAIOR SOMA vence.\n\n");
    printf("Divirta-se jogando!\n");
    printf("----------------------------------------------------------\n");
}

// === Implementações Jogo dos Estados (COM ALTERAÇÕES) ===

void calcularAtributosDerivadosEstado(CartaEstado *c) {
    c->pib_real_estado = c->pib_bilhoes_estado * 1e9;
    if (c->area_cidade > 1e-9) {
        c->densidade_demografica_cidade = (double)c->populacao_cidade / c->area_cidade;
    } else {
        c->densidade_demografica_cidade = 0;
    }
}

void lerDadosCartaEstado(CartaEstado *c, int numeroCarta) {
    printf("\n=== DADOS DA CARTA DO ESTADO %d ===\n", numeroCarta);

    printf("Nome do Estado: ");
    fgets(c->nome_do_estado, 50, stdin);
    c->nome_do_estado[strcspn(c->nome_do_estado, "\n")] = '\0';

    printf("Código da Carta (ex: SP01): ");
    fgets(c->codigo_carta, 10, stdin);
    c->codigo_carta[strcspn(c->codigo_carta, "\n")] = '\0';

    // Removida a leitura do "Identificador de Tipo de Estado (Letra 'A' a 'H')"

    printf("Nome da Cidade Principal: ");
    fgets(c->nome_cidade, 50, stdin);
    c->nome_cidade[strcspn(c->nome_cidade, "\n")] = '\0';

    printf("População da Cidade Principal: ");
    while (scanf("%d", &c->populacao_cidade) != 1 || c->populacao_cidade < 0) {
        printf("Entrada inválida. Digite um número inteiro não negativo: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    printf("Área da Cidade Principal (km²): ");
    while (scanf("%f", &c->area_cidade) != 1 || c->area_cidade < 0) {
        printf("Entrada inválida. Digite um número não negativo: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    printf("PIB do Estado (em bilhões, ex: 50.75): ");
    while (scanf("%f", &c->pib_bilhoes_estado) != 1 || c->pib_bilhoes_estado < 0) {
        printf("Entrada inválida. Digite um número não negativo: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();

    printf("Número de Pontos Turísticos da Cidade Principal: ");
    while (scanf("%d", &c->num_pontos_turisticos_cidade) != 1 || c->num_pontos_turisticos_cidade < 0) {
        printf("Entrada inválida. Digite um número inteiro não negativo: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();
}

void obterNomeAtributoEstado(int escolha, char *nomeAtributo, size_t tamanhoBuffer) {
    switch (escolha) {
        case ATTR_EST_POPULACAO_CIDADE: strncpy(nomeAtributo, "População da Cidade", tamanhoBuffer -1); break;
        case ATTR_EST_AREA_CIDADE: strncpy(nomeAtributo, "Área da Cidade", tamanhoBuffer -1); break;
        case ATTR_EST_PIB_ESTADO: strncpy(nomeAtributo, "PIB do Estado", tamanhoBuffer -1); break;
        case ATTR_EST_PONTOS_TURISTICOS_CIDADE: strncpy(nomeAtributo, "Nº de Pontos Turísticos (Cidade)", tamanhoBuffer -1); break;
        case ATTR_EST_DENSIDADE_DEMOGRAFICA_CIDADE: strncpy(nomeAtributo, "Densidade Demográfica (Cidade)", tamanhoBuffer -1); break;
        default: strncpy(nomeAtributo, "Desconhecido", tamanhoBuffer -1); break;
    }
    nomeAtributo[tamanhoBuffer-1] = '\0';
}

int exibirMenuAtributoEstado(const char* tituloMenu, int atributoExcluido) {
    int escolha;
    char nomeAttrExcluido[50] = "";
    if (atributoExcluido != 0) {
        obterNomeAtributoEstado(atributoExcluido, nomeAttrExcluido, sizeof(nomeAttrExcluido));
    }
    printf("\n--- %s (ESTADOS) ---\n", tituloMenu);
    printf("Escolha o atributo:\n");
    if (atributoExcluido != ATTR_EST_POPULACAO_CIDADE) printf("1. População da Cidade\n");
    else printf("1. População da Cidade (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    if (atributoExcluido != ATTR_EST_AREA_CIDADE) printf("2. Área da Cidade\n");
    else printf("2. Área da Cidade (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    if (atributoExcluido != ATTR_EST_PIB_ESTADO) printf("3. PIB do Estado\n");
    else printf("3. PIB do Estado (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    if (atributoExcluido != ATTR_EST_PONTOS_TURISTICOS_CIDADE) printf("4. Nº de Pontos Turísticos (Cidade)\n");
    else printf("4. Nº de Pontos Turísticos (Cidade) (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    if (atributoExcluido != ATTR_EST_DENSIDADE_DEMOGRAFICA_CIDADE) printf("5. Densidade Demográfica (Cidade)\n");
    else printf("5. Densidade Demográfica (Cidade) (Indisponível: '%s' já foi escolhido)\n", nomeAttrExcluido);
    printf("Opção: ");
    while (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 5 || escolha == atributoExcluido) {
        printf("Opção inválida ou já escolhida. Tente novamente: ");
        limparBufferEntrada();
    }
    limparBufferEntrada();
    return escolha;
}

double obterValorAtributoEstado(const CartaEstado *c, int escolhaAtributo) {
    switch (escolhaAtributo) {
        case ATTR_EST_POPULACAO_CIDADE: return (double)c->populacao_cidade;
        case ATTR_EST_AREA_CIDADE: return (double)c->area_cidade;
        case ATTR_EST_PIB_ESTADO: return c->pib_real_estado;
        case ATTR_EST_PONTOS_TURISTICOS_CIDADE: return (double)c->num_pontos_turisticos_cidade;
        case ATTR_EST_DENSIDADE_DEMOGRAFICA_CIDADE: return c->densidade_demografica_cidade;
        default: return 0.0;
    }
}

void exibirValorFormatadoEstado(const CartaEstado *c, int escolhaAtributo) {
    switch (escolhaAtributo) {
        case ATTR_EST_POPULACAO_CIDADE: printf("%d habitantes", c->populacao_cidade); break;
        case ATTR_EST_AREA_CIDADE: printf("%.2f km²", c->area_cidade); break;
        case ATTR_EST_PIB_ESTADO: printf("US$ %.2f bilhões (Estado)", c->pib_bilhoes_estado); break;
        case ATTR_EST_PONTOS_TURISTICOS_CIDADE: printf("%d", c->num_pontos_turisticos_cidade); break;
        case ATTR_EST_DENSIDADE_DEMOGRAFICA_CIDADE: printf("%.2f hab/km²", c->densidade_demografica_cidade); break;
        default: printf("N/A"); break;
    }
}

void compararCartasDoisAtributosEstado(const CartaEstado *c1, const CartaEstado *c2, int attrChoice1, int attrChoice2) {
    char nomeAttr1Str[50], nomeAttr2Str[50];
    obterNomeAtributoEstado(attrChoice1, nomeAttr1Str, sizeof(nomeAttr1Str));
    obterNomeAtributoEstado(attrChoice2, nomeAttr2Str, sizeof(nomeAttr2Str));
    double val_c1_attr1 = obterValorAtributoEstado(c1, attrChoice1);
    double val_c2_attr1 = obterValorAtributoEstado(c2, attrChoice1);
    double val_c1_attr2 = obterValorAtributoEstado(c1, attrChoice2);
    double val_c2_attr2 = obterValorAtributoEstado(c2, attrChoice2);
    double soma_c1 = val_c1_attr1 + val_c1_attr2;
    double soma_c2 = val_c2_attr1 + val_c2_attr2;
    printf("\n\n--- RESULTADO DA COMPARAÇÃO (ESTADOS) ---\n");
    // Removido "ID Tipo (A-H)" da exibição
    printf("Cartas em comparação: Estado %s (Cidade: %s, Código: %s) vs Estado %s (Cidade: %s, Código: %s)\n",
           c1->nome_do_estado, c1->nome_cidade, c1->codigo_carta,
           c2->nome_do_estado, c2->nome_cidade, c2->codigo_carta);
    printf("Atributos escolhidos: %s e %s\n\n", nomeAttr1Str, nomeAttr2Str);
    printf("Detalhes dos Atributos:\n");
    printf("  %s:\n", nomeAttr1Str);
    printf("    - %s (Estado: %s): ", c1->nome_cidade, c1->nome_do_estado); exibirValorFormatadoEstado(c1, attrChoice1); printf("\n");
    printf("    - %s (Estado: %s): ", c2->nome_cidade, c2->nome_do_estado); exibirValorFormatadoEstado(c2, attrChoice1); printf("\n");
    printf("  %s:\n", nomeAttr2Str);
    printf("    - %s (Estado: %s): ", c1->nome_cidade, c1->nome_do_estado); exibirValorFormatadoEstado(c1, attrChoice2); printf("\n");
    printf("    - %s (Estado: %s): ", c2->nome_cidade, c2->nome_do_estado); exibirValorFormatadoEstado(c2, attrChoice2); printf("\n\n");
    printf("Soma dos valores dos atributos:\n");
    printf("  %s (Estado: %s) (Soma: %.2f + %.2f): %.2f\n", c1->nome_cidade, c1->nome_do_estado, val_c1_attr1, val_c1_attr2, soma_c1);
    printf("  %s (Estado: %s) (Soma: %.2f + %.2f): %.2f\n\n", c2->nome_cidade, c2->nome_do_estado, val_c2_attr1, val_c2_attr2, soma_c2);
    printf("Resultado Final da Rodada (Estados):\n");
    const double EPSILON = 1e-9;
    if (fabs(soma_c1 - soma_c2) < EPSILON) {
        printf("Empate! As somas dos atributos são iguais.\n");
    } else if (soma_c1 > soma_c2) {
        printf("🏆 Carta do Estado %s (Cidade: %s) vence a rodada! 🎉\n", c1->nome_do_estado, c1->nome_cidade);
    } else {
        printf("🏆 Carta do Estado %s (Cidade: %s) vence a rodada! 🎉\n", c2->nome_do_estado, c2->nome_cidade);
    }
    printf("----------------------------------------------------------\n");
}

void iniciarJogoDosEstados(void) {
    CartaEstado carta1, carta2;
    int escolhaAttr1, escolhaAttr2;

    printf("\n--- CADASTRO DAS CARTAS DE ESTADOS ---\n");
    lerDadosCartaEstado(&carta1, 1);
    calcularAtributosDerivadosEstado(&carta1);
    lerDadosCartaEstado(&carta2, 2);
    calcularAtributosDerivadosEstado(&carta2);
    escolhaAttr1 = exibirMenuAtributoEstado("ESCOLHA DO PRIMEIRO ATRIBUTO", 0);
    escolhaAttr2 = exibirMenuAtributoEstado("ESCOLHA DO SEGUNDO ATRIBUTO", escolhaAttr1);
    compararCartasDoisAtributosEstado(&carta1, &carta2, escolhaAttr1, escolhaAttr2);
}

void exibirRegrasJogoEstados(void) {
    printf("\n📜--- REGRAS DO JOGO DOS ESTADOS ---📜\n");
    printf("Bem-vindo ao Jogo dos Estados! O objetivo é comparar duas cartas de estados,\n");
    printf("focando nos dados de suas cidades principais e alguns dados estaduais (como o PIB),\n");
    printf("para determinar qual carta é a vencedora.\n\n");

    printf("1. CADASTRO DAS CARTAS: 📝\n");
    printf("   - Você precisará cadastrar os dados para duas cartas de estados.\n");
    printf("   - Para cada carta, informe:\n");
    printf("     * Nome do Estado (ex: São Paulo)\n");
    printf("     * Código da Carta (ex: SP01)\n");
    // Removida a linha sobre "Identificador de Tipo de Estado (Letra 'A' a 'H')"
    printf("     * Nome da Cidade Principal (ex: São Paulo)\n");
    printf("     * População da Cidade Principal\n");
    printf("     * Área da Cidade Principal (em km²)\n");
    printf("     * PIB do Estado (em bilhões, ex: 1500.75 para R$ 1,5 trilhão)\n");
    printf("     * Número de Pontos Turísticos na Cidade Principal\n");
    printf("   - O sistema calculará automaticamente para cada carta:\n");
    printf("     * PIB Real do Estado (o valor absoluto do PIB informado)\n");
    printf("     * Densidade Demográfica da Cidade (População da Cidade / Área da Cidade)\n\n");

    printf("2. ESCOLHA DOS ATRIBUTOS PARA COMPARAÇÃO: 📊\n");
    printf("   - Após cadastrar as cartas, você escolherá DOIS atributos DIFERENTES para a disputa.\n");
    printf("   - Os atributos disponíveis são:\n");
    printf("     1. População da Cidade\n");
    printf("     2. Área da Cidade\n");
    printf("     3. PIB do Estado\n");
    printf("     4. Número de Pontos Turísticos (Cidade)\n");
    printf("     5. Densidade Demográfica (Cidade)\n");
    printf("   - Primeiro, você escolhe o primeiro atributo.\n");
    printf("   - Em seguida, escolhe o segundo atributo, que não pode ser o mesmo que o primeiro.\n\n");

    printf("3. COMO VENCER A RODADA: 🏆\n");
    printf("   - Para determinar o vencedor, o sistema soma os valores numéricos dos DOIS atributos\n");
    printf("     escolhidos para cada uma das cartas.\n");
    printf("   - A CARTA COM A MAIOR SOMA dos valores desses dois atributos vence a rodada.\n\n");

    printf("4. EMPATE: 🤝\n");
    printf("   - Se a soma dos valores dos atributos escolhidos for EXATAMENTE IGUAL para ambas as cartas,\n");
    printf("     a rodada termina em EMPATE.\n\n");

    printf("Divirta-se jogando o Jogo dos Estados!\n");
    printf("----------------------------------------------------------\n");
}


void gerenciarExibicaoDeRegras(void) {
    int escolhaRegras;
    do {
        printf("\n--- SELEÇÃO DE REGRAS ---\n");
        printf("Qual conjunto de regras você gostaria de ver?\n");
        printf("1. Regras do Jogo dos Países\n");
        printf("2. Regras do Jogo dos Estados\n");
        printf("3. Voltar ao Menu Principal\n");
        printf("Opção (1-3): ");

        if (scanf("%d", &escolhaRegras) != 1) {
            escolhaRegras = 0;
            limparBufferEntrada();
        } else {
            limparBufferEntrada();
        }

        switch (escolhaRegras) {
            case 1:
                exibirRegrasJogoPaises();
                break;
            case 2:
                exibirRegrasJogoEstados();
                break;
            case 3:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção de 1 a 3.\n");
        }
    } while (escolhaRegras != 3);
}

// === Função Main e Menu Principal ===
int main() {
    int escolhaMenu;

    do {
        printf("\n======= MENU PRINCIPAL =======\n");
        printf("🌍 Bem-vindo(a)! 🌏\n");
        printf("===================================\n");
        printf("1. JOGO DOS PAÍSES 🚀\n");
        printf("2. JOGO DOS ESTADOS 🗺️\n");
        printf("3. Ver Regras 📜\n");
        printf("4. Sair 👋\n");
        printf("===================================\n");
        printf("Escolha uma opção (1-4): ");

        if (scanf("%d", &escolhaMenu) != 1) {
            escolhaMenu = 0;
            limparBufferEntrada();
        } else {
            limparBufferEntrada();
        }

        switch (escolhaMenu) {
            case 1:
                iniciarJogoDosPaises();
                break;
            case 2:
                iniciarJogoDosEstados();
                break;
            case 3:
                gerenciarExibicaoDeRegras();
                break;
            case 4:
                printf("\nSaindo do jogo... Até a próxima! 😊\n");
                break;
            default:
                printf("\nOpção inválida. Por favor, escolha uma das opções do menu (1-4).\n");
        }
    } while (escolhaMenu != 4);

    return EXIT_SUCCESS;
}
