#include <stdio.h>
#include <windows.h>

// Estrutura que define as características de um produto
struct produto {
    char nome[50];       // Nome do produto
    float valorCompra;   // Valor de compra do produto
    float valorVenda;    // Valor de venda do produto
    float lucro;         // Lucro obtido com a venda do produto
    int qtdVendas;       // Quantidade de vendas do produto
};

int main() {
    printf("=============================================\n");
    printf("              SISTEMA DE ESTOQUE             \n");
    printf("=============================================\n");

    // Pergunta quantos produtos o Usuário deseja cadastrar
    int qtdProdutos = 0;
    do {
        printf(" > Quantos produtos deseja cadastrar?\n");
        scanf("%d", &qtdProdutos);
        getchar(); // Limpa o buffer de entrada

        if (qtdProdutos == 0) {
            printf("\n -> Valor invalido!\n\n");
        }
    } while (qtdProdutos == 0);

    system("cls"); // Limpa a tela

    // Define o tamanho do vetor de produtos
    struct produto produtos[qtdProdutos];

    printf("=============================================\n");
    printf("             CADASTRO DE PRODUTOS            \n");
    printf("=============================================\n");
    printf("\n-> Iniciando cadastro de %d produto(s)...\n\n", qtdProdutos);
    Sleep(2000); // Pausa de 2 segundos
    system("cls"); // Limpa a tela

    // Cadastro dos Produtos
    for (int i = 0; i < qtdProdutos; i++) {
        // Reseta as variáveis
        float valorCompra = -1;
        float valorVenda = -1;
        float qtdVf = -1;
        int qtd = -1;

        printf("=============================================\n");
        printf("                 PRODUTO %d/%d               \n", i + 1, qtdProdutos);
        printf("=============================================\n");

        // Nome do Produto
        do {
            printf(" > Digite o nome do produto: ");
            if (fgets(produtos[i].nome, sizeof(produtos[i].nome), stdin) != NULL) {
                size_t len = strlen(produtos[i].nome);
                if (len > 0 && produtos[i].nome[len - 1] == '\n') {
                    produtos[i].nome[len - 1] = '\0'; // Remove a nova linha
                }
            }

            // Verifica se foi digitado um nome
            if (strlen(produtos[i].nome) == 0) {
                printf("\n -> Digite um Nome!\n\n");
            }
        } while (strlen(produtos[i].nome) == 0);

        // Coleta os valores de compra, venda e quantidade
        while (valorCompra < 0 || valorVenda < 0 || qtd < 0) {
            // Valor de Compra
            if (valorCompra < 0) {
                printf(" > Digite o valor de compra do(a) %s: ", produtos[i].nome);
                if (scanf("%f", &valorCompra) == 1 && valorCompra >= 0) {
                    produtos[i].valorCompra = valorCompra; // Armazena o valor de compra
                } else {
                    printf("\n -> Valor de compra invalido!\n\n");
                    valorCompra = -1; // Reinicia o valor
                }
                while (getchar() != '\n'); // Limpa o buffer
            }
            // Valor de Venda
            else if (valorVenda < 0) {
                printf(" > Digite o valor de venda do(a) %s: ", produtos[i].nome);
                if (scanf("%f", &valorVenda) == 1 && valorVenda >= 0) {
                    produtos[i].valorVenda = valorVenda; // Armazena o valor de venda
                } else {
                    printf("\n -> Valor de venda invalido!\n\n");
                    valorVenda = -1; // Reinicia o valor
                }
                while (getchar() != '\n'); // Limpa o buffer
            }
            // Quantidade do Produto
            else if (qtd < 0) {
                printf(" > Digite a quantidade vendida de %s(s): ", produtos[i].nome);
                if (scanf("%f", &qtdVf) == 1 && qtdVf >= 0) {
                    qtd = (int)qtdVf; // Converte para inteiro
                    produtos[i].qtdVendas = qtd; // Armazena a quantidade de vendas
                } else {
                    printf("\n -> Quantidade vendida invalida!\n\n");
                    qtd = -1; // Reinicia a quantidade
                }
                while (getchar() != '\n'); // Limpa o buffer
            }
        }

        // Lucro do Produto
        produtos[i].lucro = produtos[i].valorVenda - produtos[i].valorCompra;
        printf("\n");
        system("cls"); // Limpa a tela
    }

    Sleep(1000); // Pausa antes de mostrar os produtos
    system("cls"); // Limpa a tela

    // Exibe os produtos cadastrados
    printf("=============================================\n");
    printf("             PRODUTOS CADASTRADOS            \n");
    printf("=============================================\n");
   
    for (int i = 0; i < qtdProdutos; i++) {
        printf(" -> NOME: %s\n", produtos[i].nome);
        printf(" -> VALOR DE COMPRA: %.2f\n", produtos[i].valorCompra);
        printf(" -> VALOR DE VENDA: %.2f\n", produtos[i].valorVenda);
        printf(" -> QUANTIDADE VENDAS: %d\n", produtos[i].qtdVendas);
        printf("_____________________________________________\n");
        Sleep(300); // Pausa entre a exibição dos produtos
    }

    printf("\n-> %d Produto(s) foi/foram cadastrados!\n\n", qtdProdutos);
    system("pause"); // Pausa até que o usuário pressione uma tecla
    system("cls"); // Limpa a tela

    // Ordena os produtos por lucro em ordem decrescente
    for (int i = 0; i < qtdProdutos - 1; i++) {
        if (produtos[i].lucro < produtos[i + 1].lucro) {
            struct produto aux = produtos[i + 1];
            produtos[i + 1] = produtos[i];
            produtos[i] = aux;
            i = -1; // Reinicia o loop para garantir a ordenação correta
        }
    }

    // Exibe os produtos ordenados por lucro
    printf("=============================================\n");
    printf("                     LUCRO                   \n");
    printf("=============================================\n");

    for (int i = 0; i < qtdProdutos; i++) {
        printf(" %d. R$%.2f - %s\n", i + 1, produtos[i].lucro, produtos[i].nome);
        Sleep(300); // Pausa entre a exibição dos produtos
    }

    printf("\n");

    // Verifica se todos os produtos têm o mesmo lucro
    if (produtos[0].lucro == produtos[qtdProdutos - 1].lucro) {
        printf(" Mesmo lucro:\n");
        for (int i = 0; i < qtdProdutos; i++) {
            printf(" -> R$%.2f - %s\n", produtos[i].lucro, produtos[i].nome);
            Sleep(300);
        }
    } else {
        // Exibe o produto com menor lucro
        printf(" Menor lucro:\n -> R$%.2f - %s\n", produtos[qtdProdutos - 1].lucro, produtos[qtdProdutos - 1].nome);
        for (int i = 0; i < qtdProdutos - 1; i++) {
            if (produtos[i].lucro == produtos[qtdProdutos - 1].lucro) {
                printf(" -> R$%.2f - %s\n", produtos[i].lucro, produtos[i].nome);
                Sleep(300);
            }
        }
        Sleep(300);
        // Exibe o produto com maior lucro
        printf(" Maior lucro:\n -> R$%.2f - %s\n", produtos[0].lucro, produtos[0].nome);
        for (int i = 1; i < qtdProdutos; i++) {
            if (produtos[i].lucro == produtos[0].lucro) {
                printf(" -> R$%.2f - %s\n", produtos[i].lucro, produtos[i].nome);
                Sleep(300);
            }
        }
    }

    printf("_____________________________________________\n +\n");
    Sleep(300); // Pausa antes de ordenar os produtos por quantidade vendida

    // Ordena os produtos por quantidade vendida em ordem decrescente
    for (int i = 0; i < qtdProdutos - 1; i++) {
        if (produtos[i].qtdVendas < produtos[i + 1].qtdVendas) {
            struct produto aux = produtos[i + 1];
            produtos[i + 1] = produtos[i];
            produtos[i] = aux;
            i = -1; // Reinicia o loop para garantir a ordenação correta
        }
    }

    Sleep(500); // Pausa antes de mostrar as vendas
    printf("=============================================\n");
    printf("                    VENDAS                   \n");
    printf("=============================================\n");

    for (int i = 0; i < qtdProdutos; i++) {
        printf(" %d. %d unidade(s) - %s\n", i + 1, produtos[i].qtdVendas, produtos[i].nome);
        Sleep(300); // Pausa entre a exibição dos produtos
    }

    printf("\n");

    // Verifica se todos os produtos têm a mesma quantidade vendida
    if (produtos[0].qtdVendas == produtos[qtdProdutos - 1].qtdVendas) {
        printf(" Mesma quantidade:\n");
        for (int i = 0; i < qtdProdutos; i++) {
            printf(" -> %d unidade(s) - %s\n", produtos[i].qtdVendas, produtos[i].nome);
            Sleep(300);
        }
    } else {
        // Exibe o produto com menor quantidade vendida
        printf(" Menor quantidade:\n -> %d unidade(s) - %s\n", produtos[qtdProdutos - 1].qtdVendas, produtos[qtdProdutos - 1].nome);
        for (int i = 0; i < qtdProdutos - 1; i++) {
            if (produtos[i].qtdVendas == produtos[qtdProdutos - 1].qtdVendas) {
                printf(" -> %d unidade(s) - %s\n", produtos[i].qtdVendas, produtos[i].nome);
                Sleep(300);
            }
        }
        Sleep(300);
        // Exibe o produto com maior quantidade vendida
        printf(" Maior quantidade:\n -> %d unidade(s) - %s\n", produtos[0].qtdVendas, produtos[0].nome);
        for (int i = 1; i < qtdProdutos; i++) {
            if (produtos[i].qtdVendas == produtos[0].qtdVendas) {
                printf(" -> %d unidade(s) - %s\n", produtos[i].qtdVendas, produtos[i].nome);
                Sleep(300);
            }
        }
    }

    printf("_____________________________________________\n");
    Sleep(300); // Pausa final antes de encerrar o programa

    return 0;
}
