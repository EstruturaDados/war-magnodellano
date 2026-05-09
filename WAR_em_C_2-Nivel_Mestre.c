// ========================================================================================
// PROJETO: MINI WAR ESTRUTURADO EM C
//
// RECURSOS IMPLEMENTADOS:
//
// ✔ Structs
// ✔ Ponteiros
// ✔ Modularização
// ✔ Alocação dinâmica
// ✔ Missões estratégicas
// ✔ Ataque com dados
// ✔ Transferência real de tropas
// ✔ Conquista de territórios
// ✔ Verificação de vitória
// ✔ Liberação de memória
//
// ========================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ========================================================================================
// CONSTANTES
// ========================================================================================

#define TOTAL_TERRITORIOS 5
#define TOTAL_MISSOES 5
#define TAM_STRING 100

// ========================================================================================
// STRUCT DOS TERRITÓRIOS
// ========================================================================================

typedef struct {

    char nome[30];
    char cor[20];
    int tropas;

} Territorio;

// ========================================================================================
// PROTÓTIPOS DAS FUNÇÕES
// ========================================================================================

void inicializarMapa(Territorio *mapa);

void exibirMapa(Territorio *mapa, int tamanho);

void exibirMenu();

void atribuirMissao(char *destino, char *missoes[], int totalMissoes);

void exibirMissao(char *missao);

void atacar(Territorio *atacante, Territorio *defensor);

int verificarMissao(char *missao, Territorio *mapa, int tamanho);

void liberarMemoria(Territorio *mapa, char *missaoJogador);

// ========================================================================================
// FUNÇÃO MAIN
// ========================================================================================

int main() {

    // ------------------------------------------------------------------
    // INICIALIZA RANDOMIZAÇÃO
    // ------------------------------------------------------------------

    srand(time(NULL));

    // ------------------------------------------------------------------
    // ALOCAÇÃO DINÂMICA DO MAPA
    // ------------------------------------------------------------------

    Territorio *mapa =
        (Territorio *) calloc(TOTAL_TERRITORIOS, sizeof(Territorio));

    if (mapa == NULL) {

        printf("Erro ao alocar memoria do mapa.\n");

        return 1;
    }

    // ------------------------------------------------------------------
    // MISSÕES DISPONÍVEIS
    // ------------------------------------------------------------------

    char *missoes[TOTAL_MISSOES] = {

        "Destruir o exercito Verde",

        "Conquistar 3 territorios com pelo menos 5 tropas",

        "Dominar a America e Europa",

        "Eliminar o exercito Vermelho",

        "Possuir 15 tropas no total"
    };

    // ------------------------------------------------------------------
    // ALOCAÇÃO DINÂMICA DA MISSÃO
    // ------------------------------------------------------------------

    char *missaoJogador =
        (char *) malloc(TAM_STRING * sizeof(char));

    if (missaoJogador == NULL) {

        printf("Erro ao alocar memoria da missao.\n");

        free(mapa);

        return 1;
    }

    // ------------------------------------------------------------------
    // INICIALIZA O MAPA
    // ------------------------------------------------------------------

    inicializarMapa(mapa);

    // ------------------------------------------------------------------
    // ATRIBUI MISSÃO ALEATÓRIA
    // ------------------------------------------------------------------

    atribuirMissao(missaoJogador, missoes, TOTAL_MISSOES);

    // ------------------------------------------------------------------
    // EXIBE MISSÃO APENAS UMA VEZ
    // ------------------------------------------------------------------

    printf("\n=====================================\n");
    printf("         SUA MISSAO SECRETA\n");
    printf("=====================================\n");

    exibirMissao(missaoJogador);

    printf("\nPressione ENTER para iniciar...");
    getchar();

    int opcao;

    // ====================================================================================
    // LOOP PRINCIPAL
    // ====================================================================================

    do {

        system("cls");

        exibirMapa(mapa, TOTAL_TERRITORIOS);

        exibirMenu();

        scanf("%d", &opcao);

        // ------------------------------------------------------------------
        // OPÇÃO DE ATAQUE
        // ------------------------------------------------------------------

        if (opcao == 1) {

            int origem;
            int destino;

            printf("\n--- FASE DE ATAQUE ---\n");

            printf("Escolha o territorio atacante (1 a 5): ");
            scanf("%d", &origem);

            printf("Escolha o territorio defensor (1 a 5): ");
            scanf("%d", &destino);

            origem--;
            destino--;

            // --------------------------------------------------------------
            // VALIDAÇÃO DE ÍNDICES
            // --------------------------------------------------------------

            if (origem < 0 || origem >= TOTAL_TERRITORIOS ||
                destino < 0 || destino >= TOTAL_TERRITORIOS) {

                printf("\nTerritorio invalido!\n");
            }

            // --------------------------------------------------------------
            // NÃO PODE ATACAR A SI MESMO
            // --------------------------------------------------------------

            else if (origem == destino) {

                printf("\nVoce nao pode atacar o mesmo territorio!\n");
            }

            // --------------------------------------------------------------
            // NÃO PODE ATACAR MESMA COR
            // --------------------------------------------------------------

            else if (strcmp(mapa[origem].cor,
                             mapa[destino].cor) == 0) {

                printf("\nVoce nao pode atacar um territorio aliado!\n");
            }

            else {

                atacar(&mapa[origem], &mapa[destino]);
            }

            // --------------------------------------------------------------
            // VERIFICA MISSÃO
            // --------------------------------------------------------------

            if (verificarMissao(missaoJogador,
                                mapa,
                                TOTAL_TERRITORIOS)) {

                printf("\n=====================================\n");
                printf("           MISSAO CONCLUIDA!\n");
                printf("              VOCE VENCEU!\n");
                printf("=====================================\n");

                break;
            }
        }

        // ------------------------------------------------------------------
        // VER MISSÃO
        // ------------------------------------------------------------------

        else if (opcao == 2) {

            printf("\n--- SUA MISSAO ---\n");

            exibirMissao(missaoJogador);
        }

        // ------------------------------------------------------------------
        // SAIR
        // ------------------------------------------------------------------

        else if (opcao == 0) {

            printf("\nSaindo do jogo...\n");
        }

        else {

            printf("\nOpcao invalida!\n");
        }

        printf("\nPressione ENTER para continuar...");
        getchar();
        getchar();

    } while (opcao != 0);

    // ====================================================================================
    // LIBERA MEMÓRIA
    // ====================================================================================

    liberarMemoria(mapa, missaoJogador);

    return 0;
}

// ========================================================================================
// FUNÇÃO: inicializarMapa
//
// RESPONSABILIDADE:
// Inicializar os territórios com:
// - nome
// - cor
// - tropas aleatórias
// ========================================================================================

void inicializarMapa(Territorio *mapa) {

    strcpy(mapa[0].nome, "America");
    strcpy(mapa[0].cor, "Verde");
    mapa[0].tropas = rand() % 10 + 1;

    strcpy(mapa[1].nome, "Europa");
    strcpy(mapa[1].cor, "Azul");
    mapa[1].tropas = rand() % 10 + 1;

    strcpy(mapa[2].nome, "Asia");
    strcpy(mapa[2].cor, "Vermelho");
    mapa[2].tropas = rand() % 10 + 1;

    strcpy(mapa[3].nome, "Africa");
    strcpy(mapa[3].cor, "Amarelo");
    mapa[3].tropas = rand() % 10 + 1;

    strcpy(mapa[4].nome, "Oceania");
    strcpy(mapa[4].cor, "Branco");
    mapa[4].tropas = rand() % 10 + 1;
}

// ========================================================================================
// FUNÇÃO: exibirMapa
//
// RESPONSABILIDADE:
// Mostrar o estado atual do mapa
// ========================================================================================

void exibirMapa(Territorio *mapa, int tamanho) {

    printf("=========== MAPA DO MUNDO ===========\n\n");

    for (int i = 0; i < tamanho; i++) {

        printf("%d. %s\t\t",
               i + 1,
               mapa[i].nome);

        printf("(Exercito: %s",
               mapa[i].cor);

        printf(" , Tropas: %d)\n",
               mapa[i].tropas);
    }

    printf("=====================================\n");
}

// ========================================================================================
// FUNÇÃO: exibirMenu
//
// RESPONSABILIDADE:
// Mostrar menu principal
// ========================================================================================

void exibirMenu() {

    printf("\n--- MENU DE ACOES ---\n");

    printf("1 - Atacar\n");

    printf("2 - Ver Missao\n");

    printf("0 - Sair\n");

    printf("Escolha sua acao: ");
}

// ========================================================================================
// FUNÇÃO: atribuirMissao
//
// RESPONSABILIDADE:
// Sortear missão aleatória
// ========================================================================================

void atribuirMissao(char *destino,
                    char *missoes[],
                    int totalMissoes) {

    int indice = rand() % totalMissoes;

    strcpy(destino, missoes[indice]);
}

// ========================================================================================
// FUNÇÃO: exibirMissao
//
// RESPONSABILIDADE:
// Mostrar missão do jogador
// ========================================================================================

void exibirMissao(char *missao) {

    printf("%s\n", missao);
}

// ========================================================================================
// FUNÇÃO: atacar
//
// RESPONSABILIDADE:
//
// Simular batalha entre territórios.
//
// REGRAS:
//
// ✔ atacante joga dado
// ✔ defensor joga dado
//
// ✔ quem perder perde 1 tropa
//
// ✔ se defensor chegar a 0:
//      território muda de dono
//      1 tropa é transferida
//
// ✔ atacante precisa ter > 1 tropas
//
// ========================================================================================

void atacar(Territorio *atacante,
             Territorio *defensor) {

    // ------------------------------------------------------------------
    // VALIDAÇÃO DE TROPAS
    // ------------------------------------------------------------------

    if (atacante->tropas <= 1) {

        printf("\nO atacante nao possui tropas suficientes!\n");

        return;
    }

    // ------------------------------------------------------------------
    // DADOS
    // ------------------------------------------------------------------

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n=====================================\n");

    printf("ATACANTE: %s (%s)\n",
           atacante->nome,
           atacante->cor);

    printf("DEFENSOR: %s (%s)\n",
           defensor->nome,
           defensor->cor);

    printf("\nDado atacante: %d\n",
           dadoAtacante);

    printf("Dado defensor: %d\n",
           dadoDefensor);

    // ------------------------------------------------------------------
    // ATACANTE VENCE
    // ------------------------------------------------------------------

    if (dadoAtacante > dadoDefensor) {

        printf("\nO atacante venceu a rodada!\n");

        // --------------------------------------------------------------
        // DEFENSOR PERDE TROPA
        // --------------------------------------------------------------

        defensor->tropas--;

        printf("Defensor perdeu 1 tropa.\n");

        // --------------------------------------------------------------
        // TERRITÓRIO CONQUISTADO
        // --------------------------------------------------------------

        if (defensor->tropas <= 0) {

            printf("\nTerritorio conquistado!\n");

            // ----------------------------------------------------------
            // MUDA COR
            // ----------------------------------------------------------

            strcpy(defensor->cor, atacante->cor);

            // ----------------------------------------------------------
            // MOVE 1 TROPA
            // ----------------------------------------------------------

            atacante->tropas--;

            defensor->tropas = 1;

            printf("1 tropa foi movida para o territorio conquistado.\n");
        }
    }

    // ------------------------------------------------------------------
    // DEFENSOR VENCE
    // ------------------------------------------------------------------

    else {

        printf("\nO defensor venceu a rodada!\n");

        atacante->tropas--;

        printf("Atacante perdeu 1 tropa.\n");

        // --------------------------------------------------------------
        // EVITA TROPA NEGATIVA
        // --------------------------------------------------------------

        if (atacante->tropas < 1) {

            atacante->tropas = 1;
        }
    }

    // ------------------------------------------------------------------
    // EXIBE RESULTADO
    // ------------------------------------------------------------------

    printf("\n--- RESULTADO DA BATALHA ---\n");

    printf("%s (%s) -> %d tropas\n",
           atacante->nome,
           atacante->cor,
           atacante->tropas);

    printf("%s (%s) -> %d tropas\n",
           defensor->nome,
           defensor->cor,
           defensor->tropas);

    printf("=====================================\n");
}

// ========================================================================================
// FUNÇÃO: verificarMissao
//
// RESPONSABILIDADE:
// Verificar se a missão foi concluída
//
// RETORNO:
// 1 = missão concluída
// 0 = missão não concluída
// ========================================================================================

int verificarMissao(char *missao,
                    Territorio *mapa,
                    int tamanho) {

    // ------------------------------------------------------------------
    // MISSÃO: destruir verde
    // ------------------------------------------------------------------

    if (strcmp(missao,
        "Destruir o exercito Verde") == 0) {

        for (int i = 0; i < tamanho; i++) {

            if (strcmp(mapa[i].cor, "Verde") == 0) {

                return 0;
            }
        }

        return 1;
    }

    // ------------------------------------------------------------------
    // MISSÃO: eliminar vermelho
    // ------------------------------------------------------------------

    if (strcmp(missao,
        "Eliminar o exercito Vermelho") == 0) {

        for (int i = 0; i < tamanho; i++) {

            if (strcmp(mapa[i].cor, "Vermelho") == 0) {

                return 0;
            }
        }

        return 1;
    }

    // ------------------------------------------------------------------
    // MISSÃO: conquistar 3 territórios fortes
    // ------------------------------------------------------------------

    if (strcmp(missao,
        "Conquistar 3 territorios com pelo menos 5 tropas") == 0) {

        int contador = 0;

        for (int i = 0; i < tamanho; i++) {

            if (mapa[i].tropas >= 5) {

                contador++;
            }
        }

        return contador >= 3;
    }

    // ------------------------------------------------------------------
    // MISSÃO: dominar América e Europa
    // ------------------------------------------------------------------

    if (strcmp(missao,
        "Dominar a America e Europa") == 0) {

        if (strcmp(mapa[0].cor, "Azul") == 0 &&
            strcmp(mapa[1].cor, "Azul") == 0) {

            return 1;
        }

        return 0;
    }

    // ------------------------------------------------------------------
    // MISSÃO: possuir 15 tropas
    // ------------------------------------------------------------------

    if (strcmp(missao,
        "Possuir 15 tropas no total") == 0) {

        int soma = 0;

        for (int i = 0; i < tamanho; i++) {

            soma += mapa[i].tropas;
        }

        return soma >= 15;
    }

    return 0;
}

// ========================================================================================
// FUNÇÃO: liberarMemoria
//
// RESPONSABILIDADE:
// Liberar memória dinâmica
// ========================================================================================

void liberarMemoria(Territorio *mapa,
                    char *missaoJogador) {

    free(mapa);

    free(missaoJogador);

    printf("\nMemoria liberada com sucesso.\n");
}
