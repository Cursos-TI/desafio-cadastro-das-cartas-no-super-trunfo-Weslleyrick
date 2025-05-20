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
    nova.codigo[3] = '\0'; // Garante a terminação da string

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

// Função para obter valor de atributo com base em código
float obterAtributo(Cidade c, int atributo) {
    switch (atributo) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return c.pib;
        case 4: return (float)c.pontos_turisticos;
        case 5: return c.area == 0 ? 0 : c.populacao / c.area;
        default: return 0;
    }
}

// Nome do atributo (para exibição)
const char* nomeAtributo(int atributo) {
    switch (atributo) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Demográfica";
        default: return "Desconhecido";
    }
}

// Função para comparar cartas com dois atributos
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

    int atr1, atr2;
    printf("Escolha o primeiro atributo (1-5): ");
    scanf("%d", &atr1);
    printf("Escolha o segundo atributo (1-5): ");
    scanf("%d", &atr2);

    float val1a = obterAtributo(c1, atr1);
    float val1b = obterAtributo(c1, atr2);
    float val2a = obterAtributo(c2, atr1);
    float val2b = obterAtributo(c2, atr2);

    // Exibição de cartas
    printf("\nCarta 1:\n");
    exibirCidade(c1);
    printf("Carta 2:\n");
    exibirCidade(c2);

    // Resultado da comparação com lógica avançada
    printf("\nResultado da comparação:\n");

    // Decisão por pontos acumulados
    int pontos_c1 = 0;
    int pontos_c2 = 0;

    // Operadores ternários: maior é melhor, exceto densidade
    pontos_c1 += (atr1 == 5) ? (val1a < val2a ? 1 : val2a < val1a ? 0 : 0) : (val1a > val2a ? 1 : val2a > val1a ? 0 : 0);
    pontos_c2 += (atr1 == 5) ? (val2a < val1a ? 1 : val1a < val2a ? 0 : 0) : (val2a > val1a ? 1 : val1a > val2a ? 0 : 0);

    pontos_c1 += (atr2 == 5) ? (val1b < val2b ? 1 : val2b < val1b ? 0 : 0) : (val1b > val2b ? 1 : val2b > val1b ? 0 : 0);
    pontos_c2 += (atr2 == 5) ? (val2b < val1b ? 1 : val1b < val2b ? 0 : 0) : (val2b > val1b ? 1 : val1b > val2b ? 0 : 0);

    // Mensagem final com ternário
    printf("%s venceu com %d pontos!\n", 
        pontos_c1 > pontos_c2 ? c1.nome : 
        pontos_c2 > pontos_c1 ? c2.nome : 
        "Empate");

    if (pontos_c1 == pontos_c2) {
        printf("Parabéns! Ambas as cidades são impressionantes!\n");
    }
}

// Função principal - ponto de entrada do programa
int main() {
    int opcao;

    do {
        // Menu principal
        printf("\n===== Super Trunfo - Cidades (Nível Mestre) =====\n");
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
                printf("Saindo do sistema... Obrigado por jogar!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 3); // Continua até o jogador optar por sair

    return 0;
}
