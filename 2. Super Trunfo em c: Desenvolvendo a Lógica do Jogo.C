#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CIDADES 32 // 8 estados * 4 cidades

// Estrutura que representa uma carta de cidade no Super Trunfo
typedef struct {
    char estado[3];              // Sigla do estado (ex: SP)
    char codigo[4];              // Código da carta (ex: A01)
    char nome[50];               // Nome da cidade
    int populacao;               // População total
    float area;                  // Área em km²
    float pib;                   // PIB em milhões
    int pontos_turisticos;      // Número de pontos turísticos
    float densidade;            // Calculado: População / Área
    float pib_per_capita;       // Calculado: PIB / População
} Cidade;

Cidade cidades[MAX_CIDADES];
int total_cidades = 0;

// Função para cadastrar uma cidade
void cadastrarCidade() {
    if (total_cidades >= MAX_CIDADES) {
        printf("Limite de cidades atingido!\n");
        return;
    }

    Cidade novaCidade;

    printf("Digite o estado (ex: SP): ");
    scanf("%2s", novaCidade.estado);
    novaCidade.estado[2] = '\0';

    printf("Digite o código da cidade (ex: A01): ");
    scanf("%3s", novaCidade.codigo);
    novaCidade.codigo[3] = '\0';

    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", novaCidade.nome); // Lê com espaços

    printf("Digite a população: ");
    scanf("%d", &novaCidade.populacao);

    printf("Digite a área (em km²): ");
    scanf("%f", &novaCidade.area);

    printf("Digite o PIB (em milhões): ");
    scanf("%f", &novaCidade.pib);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &novaCidade.pontos_turisticos);

    // Cálculos automáticos
    novaCidade.densidade = novaCidade.populacao / novaCidade.area;
    novaCidade.pib_per_capita = novaCidade.pib * 1e6 / novaCidade.populacao;

    cidades[total_cidades] = novaCidade;
    total_cidades++;

    printf("Cidade cadastrada com sucesso!\n\n");
}

// Função para exibir todas as cidades cadastradas
void exibirCidades() {
    if (total_cidades == 0) {
        printf("Nenhuma cidade cadastrada.\n");
        return;
    }

    printf("\nCidades cadastradas:\n");
    for (int i = 0; i < total_cidades; i++) {
        printf("[%d] %s (%s)\n", i + 1, cidades[i].nome, cidades[i].estado);
        printf("  Código: %s\n", cidades[i].codigo);
        printf("  População: %d\n", cidades[i].populacao);
        printf("  Área: %.2f km²\n", cidades[i].area);
        printf("  PIB: %.2f milhões\n", cidades[i].pib);
        printf("  Pontos Turísticos: %d\n", cidades[i].pontos_turisticos);
        printf("  Densidade Populacional: %.2f hab/km²\n", cidades[i].densidade);
        printf("  PIB per capita: %.2f R$\n", cidades[i].pib_per_capita);
        printf("-----------------------------\n");
    }
}

// Função para comparar duas cartas pelo atributo escolhido
void compararCartas() {
    if (total_cidades < 2) {
        printf("Cadastre pelo menos duas cidades para comparar.\n");
        return;
    }

    Cidade c1 = cidades[0];
    Cidade c2 = cidades[1];

    // Escolher o atributo para comparação diretamente aqui:
    char atributo[] = "População";

    printf("\nComparação de cartas (Atributo: %s):\n\n", atributo);
    printf("Carta 1 - %s (%s): %d\n", c1.nome, c1.estado, c1.populacao);
    printf("Carta 2 - %s (%s): %d\n", c2.nome, c2.estado, c2.populacao);

    if (c1.populacao > c2.populacao) {
        printf("Resultado: Carta 1 (%s) venceu!\n", c1.nome);
    } else if (c2.populacao > c1.populacao) {
        printf("Resultado: Carta 2 (%s) venceu!\n", c2.nome);
    } else {
        printf("Resultado: Empate!\n");
    }
}

// Função principal
int main() {
    // Cadastro de duas cidades (pré-requisito para comparação)
    printf("Cadastro de duas cartas para o jogo Super Trunfo:\n\n");

    cadastrarCidade();
    cadastrarCidade();

    exibirCidades();

    compararCartas();

    return 0;
}
