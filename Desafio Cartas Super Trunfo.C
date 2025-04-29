#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CIDADES 32 // 8 estados * 4 cidades

typedef struct {
    char codigo[4]; // Código da carta (ex: A01)
    int populacao;
    float area; // em km²
    float pib; // em milhões
    int pontos_turisticos;
} Cidade;

Cidade cidades[MAX_CIDADES];
int total_cidades = 0;

void cadastrarCidade() {
    if (total_cidades >= MAX_CIDADES) {
        printf("Limite de cidades atingido!\n");
        return;
    }

    Cidade novaCidade;
    printf("Digite o código da cidade (ex: A01): ");
    scanf("%3s", novaCidade.codigo); // Limitar a leitura a 3 caracteres para evitar overflow
    novaCidade.codigo[3] = '\0'; // Garantir que o código seja uma string válida

    printf("Digite a população: ");
    scanf("%d", &novaCidade.populacao);

    printf("Digite a área (em km²): ");
    scanf("%f", &novaCidade.area);

    printf("Digite o PIB (em milhões): ");
    scanf("%f", &novaCidade.pib);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &novaCidade.pontos_turisticos);

    cidades[total_cidades] = novaCidade;
    total_cidades++;

    printf("Cidade cadastrada com sucesso!\n");
}

void exibirCidades() {
    if (total_cidades == 0) {
        printf("Nenhuma cidade cadastrada.\n");
        return;
    }

    printf("\nCidades cadastradas:\n");
    for (int i = 0; i < total_cidades; i++) {
        printf("Código: %s\n", cidades[i].codigo);
        printf("População: %d\n", cidades[i].populacao);
        printf("Área: %.2f km²\n", cidades[i].area);
        printf("PIB: %.2f milhões\n", cidades[i].pib);
        printf("Pontos Turísticos: %d\n", cidades[i].pontos_turisticos);
        printf("-------------------------\n");
    }
}

int main() {
    int opcao;

    do {
        printf("Menu:\n");
        printf("1. Cadastrar Cidade\n");
        printf("2. Exibir Cidades\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCidade();
                break;
            case 2:
                exibirCidades();
                break;
            case 3:
                printf("Saindo do sistema... Obrigado por jogar! \n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 3);

    return 0;
}
