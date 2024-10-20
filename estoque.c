// Caio Passos Torkst Ferreira
// João Guilherme de Oliveira Ribeiro Kongevold

#include <stdio.h>
#include <string.h>

struct _Produto {
    char descricao[40];
    int qt_estoque;
    int min_estoque;
    float preco_venda;
};

typedef struct _Produto Produto;

void incluir_produto(Produto p, FILE *f);
void registrar_venda(int codigo, int qt, FILE *f);
void buscar_codigo(int codigo, FILE *f);
void buscar_descricao(char *descricao, FILE *f);
void relatorio_abaixo_min(FILE *f);
void exibe_produto(Produto p);

int main(void) {
    printf("Controle de Estoque\n");
    FILE *arquivo = fopen("registros.txt", "rb+");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int x = 0, codigo, qt;
    while (x != -1) {
        printf("1. Incluir Produto\n2. Registrar Venda\n3. Buscar por Código\n4. Buscar por Descrição\n5. Relatório de Produtos com Estoque Abaixo do Mínimo\n6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &x);
        switch (x) {
            case 1: {
                Produto p;
                printf("Descrição, Qt. Estoque, Min. Estoque, Preço Venda: ");
                scanf("%s %d %d %f", p.descricao, &p.qt_estoque, &p.min_estoque, &p.preco_venda);
                incluir_produto(p, arquivo);
                break;
            }
            case 2:
                printf("Código e Qt. Vendida: ");
                scanf("%d %d", &codigo, &qt);
                registrar_venda(codigo, qt, arquivo);
                break;
            case 3:
                printf("Código do Produto: ");
                scanf("%d", &codigo);
                buscar_codigo(codigo, arquivo);
                break;
            case 4: {
                char descricao[40];
                printf("Descrição a buscar: ");
                scanf("%s", descricao);
                buscar_descricao(descricao, arquivo);
                break;
            }
            case 5:
                relatorio_abaixo_min(arquivo);
                break;
            case 6:
                x = -1;
                break;
            default:
                printf("Opção Inválida!\n");
                break;
        }
    }
    fclose(arquivo);
    return 0;
}

void exibe_produto(Produto p) {
    printf("Produto: %s, Estoque: %d, Mínimo: %d, Preço: %.2f\n", p.descricao, p.qt_estoque, p.min_estoque, p.preco_venda);
}

void incluir_produto(Produto p, FILE *f) {
    fseek(f, 0, SEEK_END);
    fwrite(&p, sizeof(Produto), 1, f);
}

void registrar_venda(int codigo, int qt, FILE *f) {
    fseek(f, codigo * sizeof(Produto), SEEK_SET);
    Produto temp;
    fread(&temp, sizeof(Produto), 1, f);
    if (temp.qt_estoque >= qt) {
        temp.qt_estoque -= qt;
        fseek(f, codigo * sizeof(Produto), SEEK_SET);
        fwrite(&temp, sizeof(Produto), 1, f);
    } else {
        printf("Estoque insuficiente para a venda.\n");
    }
}

void buscar_codigo(int codigo, FILE *f) {
    fseek(f, codigo * sizeof(Produto), SEEK_SET);
    Produto p;
    if (fread(&p, sizeof(Produto), 1, f)) {
        exibe_produto(p);
    } else {
        printf("Produto não encontrado.\n");
    }
}

void buscar_descricao(char *descricao, FILE *f) {
    fseek(f, 0, SEEK_SET);
    Produto temp;
    while (fread(&temp, sizeof(Produto), 1, f)) {
        if (strstr(temp.descricao, descricao)) {
            exibe_produto(temp);
        }
    }
}

void relatorio_abaixo_min(FILE *f) {
    fseek(f, 0, SEEK_SET);
    Produto temp;
    while (fread(&temp, sizeof(Produto), 1, f)) {
        if (temp.qt_estoque < temp.min_estoque) {
            exibe_produto(temp);
        }
    }
}
