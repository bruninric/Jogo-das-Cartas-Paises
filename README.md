# Arquivo do TCC

Este repositório contém o seguinte arquivo:

- Jogo das Cartas - Países e Estados
- Jogo de Xadrez

## Descrição

Atividades relacionadas ao desafio **Super Trunfo**.

Todos os trabalhos contidos neste repositório integram o desenvolvimento do **Trabalho de Conclusão de Curso (TCC).**

## Explicações

Ao todo, serão explicados 4 códigos:

Primeira explicação: sobre o Jogo das Cartas - Países e Estados.

Segunda explicação: sobre o Jogo de Xadrez.

Terceira explicação:

Quarta explicação:

# Primeira explicação: Análise do Desenvolvimento do Código (Jogo das Cartas - Países e Estados)

Este código em C foi desenvolvido para criar um programa interativo que simula dois jogos de cartas distintos: um "Jogo dos Países" e um "Jogo dos Estados". A estrutura do código revela um desenvolvimento modular e incremental.

## Desenvolvimento e Estrutura do Código

1.  **Definição das Estruturas de Dados:**
    * Primeiramente, foram definidas as estruturas (`struct`) `CartaPais` e `CartaEstado`. Essas estruturas servem como moldes para armazenar os dados específicos de cada tipo de carta, como nome, população, área, PIB, etc.
    * Campos para atributos derivados, como `pib_real` e `densidade_demografica`, foram incluídos para serem calculados posteriormente. Notavelmente, um campo `identificador_tipo_estado_ah` foi removido da `CartaEstado`, indicando uma possível refatoração ou mudança de requisitos durante o desenvolvimento.

2.  **Constantes para Atributos:**
    * Foram usadas diretivas `#define` para criar constantes simbólicas (ex: `ATTR_PAIS_POPULACAO`) representando os diferentes atributos que podem ser escolhidos nos jogos. Isso melhora a legibilidade e a manutenção do código, evitando o uso de "números mágicos".

3.  **Modularização com Funções:**
    * O código é bem dividido em funções, cada uma com uma responsabilidade clara. Isso é evidenciado pelos protótipos de funções declarados no início, separados por categorias: "Comum", "Jogo dos Países", "Jogo dos Estados" e "Menu de Regras".

4.  **Implementação do "Jogo dos Países":**
    * **Entrada de Dados:** A função `lerDadosCartaPais` é responsável por solicitar ao usuário as informações de cada carta de país. Inclui validação básica para garantir que os dados numéricos sejam inseridos corretamente.
    * **Cálculo de Atributos:** `calcularAtributosDerivadosPais` processa os dados brutos para calcular o PIB real e a densidade demográfica.
    * **Interação com o Usuário:** Funções como `exibirMenuAtributoPais` permitem que o usuário escolha os atributos para comparação, impedindo a seleção do mesmo atributo duas vezes. `obterNomeAtributoPais` e `exibirValorFormatadoPais` auxiliam na apresentação clara das informações.
    * **Lógica de Comparação:** `compararCartasDoisAtributosPais` implementa a regra central do jogo: soma os valores de dois atributos escolhidos para cada carta e determina o vencedor. Utiliza uma pequena tolerância (`EPSILON`) para comparações de ponto flutuante, o que é uma boa prática.
    * **Fluxo do Jogo:** `iniciarJogoDosPaises` orquestra todas as etapas do jogo de países.

5.  **Implementação do "Jogo dos Estados":**
    * Seguindo um padrão similar ao "Jogo dos Países", foram desenvolvidas funções análogas para o "Jogo dos Estados" (`lerDadosCartaEstado`, `calcularAtributosDerivadosEstado`, `exibirMenuAtributoEstado`, etc.).
    * As adaptações necessárias foram feitas para refletir os atributos específicos das cartas de estado (focando em dados da cidade principal e PIB estadual).
    * Como mencionado, a entrada e o processamento do "Identificador de Tipo de Estado" foram removidos, simplificando a estrutura da `CartaEstado` e as funções relacionadas.

6.  **Funcionalidades Comuns e de Suporte:**
    * `limparBufferEntrada`: Uma função utilitária essencial em C para limpar o buffer de entrada (`stdin`) após leituras com `scanf`, prevenindo comportamentos inesperados em leituras subsequentes, especialmente com `fgets`.
    * **Gerenciamento de Regras:** `gerenciarExibicaoDeRegras`, `exibirRegrasJogoPaises`, e `exibirRegrasJogoEstados` fornecem ao usuário a opção de visualizar as instruções de cada jogo.

7.  **Menu Principal e Fluxo do Programa:**
    * A função `main` atua como o ponto de entrada e controla o fluxo principal do programa.
    * Apresenta um menu com opções para jogar cada um dos jogos, ver as regras ou sair.
    * Utiliza um loop `do-while` para manter o menu ativo até que o usuário escolha sair e uma estrutura `switch-case` para direcionar a execução com base na escolha do usuário.
    * Inclui tratamento básico para entradas inválidas no menu.

Em resumo, o código foi desenvolvido de forma estruturada, começando pela modelagem dos dados, seguido pela implementação da lógica de cada jogo de forma modular, e culminando na criação de uma interface de usuário baseada em menus de texto. A reutilização de conceitos e a adaptação de código entre os dois jogos (Países e Estados) são evidentes, sugerindo um processo de desenvolvimento eficiente. A atenção à validação de entrada e à clareza da interface contribui para a usabilidade do programa.


# Segunda explicação: Simulação de Movimentos de Peças de Xadrez em C (Jogo de Xadrez)

Este código em C foi projetado para simular, de forma simplificada, os movimentos de algumas peças de xadrez: Torre, Bispo, Rainha e Cavalo. O desenvolvimento seguiu uma abordagem estruturada, focada em atender a requisitos específicos de demonstração de diferentes estruturas de controle e saídas de dados.

## Principais Etapas do Desenvolvimento

1.  **Definição de Requisitos e Constantes:**
    * Foram estabelecidos requisitos funcionais para cada peça, como o número de "casas" que cada uma deveria se mover e a direção. Esses números foram definidos como constantes (`#define`) no início do código para fácil visualização e modificação (ex: `MOVIMENTOS_TORRE`, `CAVALO_PASSOS_PARA_BAIXO`).
    * Requisitos não funcionais, como legibilidade, documentação e simplicidade (adequada para um nível básico/intermediário), também guiaram o desenvolvimento, como indicado nos comentários do código.

2.  **Estrutura Modular com Funções:**
    * Para cada peça, uma função específica de simulação de movimento foi criada (`simularMovimentoTorre`, `simularMovimentoBispo`, `simularMovimentoRainha`, `simularMovimentoCavalo`). Isso torna o código organizado e fácil de entender.
    * Os protótipos dessas funções foram declarados no início do arquivo.

3.  **Implementação dos Movimentos das Peças:**
    * **Torre, Bispo e Rainha:** Para as três primeiras peças, foi seguido o requisito de utilizar uma estrutura de repetição diferente para cada uma:
        * `simularMovimentoTorre()`: Utiliza um loop `for` para simular o movimento da torre.
        * `simularMovimentoBispo()`: Utiliza um loop `while` para o movimento do bispo.
        * `simularMovimentoRainha()`: Utiliza um loop `do-while` para o movimento da rainha, com uma verificação para garantir que o loop só execute se o número de movimentos for maior que zero.
    * **Cavalo:** A simulação do movimento do cavalo (`simularMovimentoCavalo()`) foi implementada para seguir um padrão em "L" específico (duas casas para baixo, uma para a esquerda). Conforme um requisito implícito pela estrutura do código, utilizou-se loops aninhados: um loop `for` externo (que executa apenas uma vez para representar o único movimento em "L" solicitado) contendo um loop `for` para os movimentos verticais ("Baixo") e um loop `while` para o movimento horizontal ("Esquerda").

4.  **Função Principal (`main`):**
    * A função `main` orquestra a simulação, chamando cada uma das funções de movimento em sequência.
    * Inclui mensagens de `printf` para indicar o início e o fim da simulação, e para separar a saída de cada peça, incluindo uma linha em branco específica antes do movimento do cavalo, conforme solicitado.

5.  **Documentação:**
    * O código foi extensivamente comentado para explicar a lógica de cada parte, os requisitos funcionais e não funcionais atendidos, e as simplificações adotadas. Isso inclui comentários de cabeçalho para funções (estilo Doxygen) e explicações inline.

## Resumo

Em resumo, o código foi desenvolvido com um foco didático, demonstrando o uso de diferentes estruturas de loop (`for`, `while`, `do-while`) e loops aninhados, dentro de um contexto simples de simulação de movimentos de peças de xadrez. A clareza, a organização em funções e a documentação foram aspectos importantes considerados durante sua criação.

