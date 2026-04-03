#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Definição da Struct ---
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- Função para cadastrar territórios ---
void cadastrarTerritorios(Territorio *mapa, int total) {
    for (int i = 0; i < total; i++) {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do territorio: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// --- Função para mostrar territórios ---
void mostrarTerritorios(Territorio *mapa, int total) {
    printf("\n===== MAPA ATUAL =====\n");

    for (int i = 0; i < total; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// --- Função de ataque ---
void atacar(Territorio *atacante, Territorio *defensor) {
    // Impede ataque ao mesmo exército
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nNao e possivel atacar um territorio da mesma cor!\n");
        return;
    }

    // Verifica tropas mínimas
    if (atacante->tropas <= 1) {
        printf("\nO atacante precisa ter mais de 1 tropa!\n");
        return;
    }

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\n===== BATALHA =====\n");
    printf("%s atacou %s\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d\n", dadoAtaque);
    printf("Dado defensor: %d\n", dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        printf("\nO atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    } else {
        printf("\nO defensor resistiu!\n");
        atacante->tropas--;
    }
}

// --- Função para liberar memória ---
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

// --- Função principal ---
int main() {
    srand(time(NULL));

    int total;

    printf("Quantos territorios deseja cadastrar? ");
    scanf("%d", &total);

    // Alocação dinâmica
    Territorio *mapa = (Territorio *) malloc(total * sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, total);

    mostrarTerritorios(mapa, total);

    int atk, def;

    printf("\nEscolha o territorio atacante (1 a %d): ", total);
    scanf("%d", &atk);

    printf("Escolha o territorio defensor (1 a %d): ", total);
    scanf("%d", &def);

    atacar(&mapa[atk - 1], &mapa[def - 1]);

    mostrarTerritorios(mapa, total);

    liberarMemoria(mapa);

    return 0;
}