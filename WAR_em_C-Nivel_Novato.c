#include <stdio.h>
#include <string.h>

// --- Definição da Estrutura (Struct) ---

struct Territorio {
    char nome[50];
    char cor[10];
    int tropas;
};

struct Territorio territorios[5];

// --- Função Principal ---
int main() {

    // Cadastro
    for (int i = 0; i < 5; i++) {
        printf ("--- Cadastrando Territorio %d ---\n", i + 1);

        printf("Nome do Territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Cor do Territorio: ");
        scanf("%s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    printf("\nAqui estao os territorios cadastrados: \n");

    // Mostrar territórios
    for (int i = 0; i < 5; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}

