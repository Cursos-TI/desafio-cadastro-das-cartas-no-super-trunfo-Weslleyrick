#include <stdio.h>
#include <string.h>

#define MAX_CIDADES 32 // Limite máximo de cartas cadastradas

// Estrutura que representa uma carta de cidade
typedef struct {
    char estado[20];               // Nome do estado da cidade
    char codigo[4];                // Código identificador da carta (ex: A01)
    char nome[30];                 // Nome da cidade
    int populacao;                 // População total
    float area;                    // Área em km²
    float pib;                     // PIB em milhões
    int pontos_turisticos;        // Quantidade de pontos turísticos
} Cidade;

// Vetor para armazenar cartas cadastradas
Cidade cidades[MAX_CIDADES];
int total_cidades = 0; // Número de cidades cadastradas

// Função para cadastrar uma nova cidade no vetor
void cadastrarCidade() {
    if (total_cidades >= MAX_CIDADES) {
        printf("Limite de cidades atingido!\n");
        return;
    }

    Cidade nova;

    printf("Digite o estado da cidade: ");
    scanf(" %[^\n]", nova.estado); // Lê string com espaços

    printf("Digite o código da cidade (ex: A01): ");
    scanf("%3s", nova.codigo);// Limitar a leitura a 3 caracteres para evitar overflow
    nova.codigo[3] = '\0'; // Garante terminação da string

    printf("Digite o nome da cidade: ");
    scanf(" %[^\n]", nova.nome);

    printf("Digite a população: ");
    scanf("%d", &nova.populacao);

    printf("Digite a área (em km²): ");
    scanf("%f", &nova.area);

    printf("Digite o PIB (em milhões): ");
    scanf("%f", &nova.pib);

    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &nova.pontos_turisticos);

    cidades[total_cidades++] = nova; // Adiciona a cidade ao vetor

    printf("Cidade cadastrada com sucesso!\n");
}

// Exibe os dados de uma cidade formatada
void exibirCidade(Cidade c) {
    printf("Código: %s\n", c.codigo);
    printf("Estado: %s\n", c.estado);
    printf("Cidade: %s\n", c.nome);
    printf("População: %d\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f milhões\n", c.pib);
    printf("Pontos Turísticos: %d\n", c.pontos_turisticos);
    printf("-----------------------------\n");
}

// Busca a cidade pelo código e retorna seu índice no vetor
int buscarCidadePorCodigo(char codigo[4]) {
    for (int i = 0; i < total_cidades; i++) {
        if (strcmp(cidades[i].codigo, codigo) == 0)
            return i;
    }
    return -1; // Não encontrada
}

// Compara duas cidades com base em um atributo escolhido
void compararCartas() {
    if (total_cidades < 2) {
        printf("Cadastre ao menos duas cidades para comparar.\n");
        return;
    }

    // Entrada dos códigos das cartas
    char cod1[4], cod2[4];
    printf("Digite o código da primeira cidade: ");
    scanf("%3s", cod1);
    printf("Digite o código da segunda cidade: ");
    scanf("%3s", cod2);

    // Busca pelos índices
    int idx1 = buscarCidadePorCodigo(cod1);
    int idx2 = buscarCidadePorCodigo(cod2);

    // Verificação se as cidades foram encontradas
    if (idx1 == -1 || idx2 == -1) {
        printf("Erro: Uma ou ambas as cidades não foram encontradas.\n");
        return;
    }

    Cidade c1 = cidades[idx1];
    Cidade c2 = cidades[idx2];

    // Exibe menu de atributos para o jogador escolher
    printf("\nEscolha o atributo para comparar:\n");
    printf("1. População\n");
    printf("2. Área\n");
    printf("3. PIB\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Demográfica (menor vence)\n");
    printf("Opção: ");
    
    int opcao;
    scanf("%d", &opcao);

    // Exibe os dados das duas cidades para o jogador visualizar
    printf("\nCarta 1:\n");
    exibirCidade(c1);
    printf("Carta 2:\n");
    exibirCidade(c2);

    // Lógica de comparação com if-else aninhado
    printf("Resultado da comparação:\n");

    if (opcao == 1) { // População
        printf("População %s: %d\n", c1.nome, c1.populacao);
        printf("População %s: %d\n", c2.nome, c2.populacao);
        if (c1.populacao > c2.populacao)
            printf("Vencedora: %s (maior população)\n", c1.nome);
        else if (c2.populacao > c1.populacao)
            printf("Vencedora: %s (maior população)\n", c2.nome);
        else
            printf("Empate!\n");

    } else if (opcao == 2) { // Área
        printf("Área %s: %.2f km²\n", c1.nome, c1.area);
        printf("Área %s: %.2f km²\n", c2.nome, c2.area);
        if (c1.area > c2.area)
            printf("Vencedora: %s (maior área)\n", c1.nome);
        else if (c2.area > c1.area)
            printf("Vencedora: %s (maior área)\n", c2.nome);
        else
            printf("Empate!\n");

    } else if (opcao == 3) { // PIB
        printf("PIB %s: %.2f milhões\n", c1.nome, c1.pib);
        printf("PIB %s: %.2f milhões\n", c2.nome, c2.pib);
        if (c1.pib > c2.pib)
            printf("Vencedora: %s (maior PIB)\n", c1.nome);
        else if (c2.pib > c1.pib)
            printf("Vencedora: %s (maior PIB)\n", c2.nome);
        else
            printf("Empate!\n");

    } else if (opcao == 4) { // Pontos turísticos
        printf("Pontos turísticos %s: %d\n", c1.nome, c1.pontos_turisticos);
        printf("Pontos turísticos %s: %d\n", c2.nome, c2.pontos_turisticos);
        if (c1.pontos_turisticos > c2.pontos_turisticos)
            printf("Vencedora: %s (mais pontos turísticos)\n", c1.nome);
        else if (c2.pontos_turisticos > c1.pontos_turisticos)
            printf("Vencedora: %s (mais pontos turísticos)\n", c2.nome);
        else
            printf("Empate!\n");

    } else if (opcao == 5) { // Densidade demográfica (menor vence)
        float dens1 = c1.populacao / c1.area;
        float dens2 = c2.populacao / c2.area;
        printf("Densidade %s: %.2f hab/km²\n", c1.nome, dens1);
        printf("Densidade %s: %.2f hab/km²\n", c2.nome, dens2);
        if (dens1 < dens2)
            printf("Vencedora: %s (menor densidade)\n", c1.nome);
        else if (dens2 < dens1)
            printf("Vencedora: %s (menor densidade)\n", c2.nome);
        else
            printf("Empate!\n");

    } else {
        printf("Opção inválida!\n");
    }
}

// Função principal - ponto de entrada do programa
int main() {
    int opcao;

    do {
        // Menu principal
        printf("\n===== Super Trunfo - Cidades =====\n");
        printf("1. Cadastrar Cidade\n");
        printf("2. Comparar Cartas\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // Execução da funcionalidade com base na opção
        switch (opcao) {
            case 1:
                cadastrarCidade();
                break;
            case 2:
                compararCartas();
                break;
            case 3:
                printf("Saindo do sistema... Obrigado por jogar! \n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 3); // Continua até o jogador optar por sair

    return 0;
}
