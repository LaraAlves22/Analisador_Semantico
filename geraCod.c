// Arquivo: geraCod.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h" // Inclui a definição da sua estrutura AST

// Definição de constantes de controle
static int temp_counter = 0; // Contador para variáveis temporárias (t0, t1, t2, ...)
static int label_counter = 0; // Contador para rótulos (L0, L1, L2, ...)

// Funções auxiliares (invariantes)
char* new_temp() {
    char *temp = (char*)malloc(10);
    sprintf(temp, "t%d", temp_counter++);
    return temp;
}

char* new_label() {
    char *label = (char*)malloc(10);
    sprintf(label, "L%d", label_counter++);
    return label;
}

// ----------------------------------------------------
// Função que gera 3AC para EXPRESSÕES (retorna o nome da variável/temporário que contém o resultado)
// ----------------------------------------------------
char* gerarCodigoExp(AST *node) {
    if (!node) {
        return NULL;
    }

    // 1. Caso Base: Nó Folha (Variáveis, Constantes)
    // Usando N_EXPR_VAR, N_EXPR_INT, N_EXPR_REAL, N_EXPR_CADEIA conforme o seu ast.h
    if (node->tipo == N_EXPR_VAR || node->tipo == N_EXPR_INT ||
        node->tipo == N_EXPR_REAL || node->tipo == N_EXPR_CADEIA) {

        // Retorna o próprio valor/nome
        return strdup(node->valor);
    }

    // 2. Caso Recursivo: Expressões de Operadores (Aritméticos)
    // Usando N_EXPR_OP_ARIT, N_EXPR_OP_REL, N_EXPR_OP_LOG
    if (node->tipo == N_EXPR_OP_ARIT) {

        // O valor do nó N_EXPR_OP_ARIT deve conter o símbolo do operador ("+", "-", etc.)
        char *op_symbol = node->valor;

        // Gera código para os operandos esquerdo e direito (recursão)
        char *left_result = gerarCodigoExp(node->left);
        char *right_result = gerarCodigoExp(node->right);

        // Aloca uma nova variável temporária para armazenar o resultado da operação
        char *result_temp = new_temp();

        // 🎯 IMPRESSÃO DO CÓDIGO INTERMEDIÁRIO (3AC)
        printf("%s = %s %s %s\n", result_temp, left_result, op_symbol, right_result);

        // Libera a memória alocada para os resultados temporários dos filhos
        free(left_result);
        free(right_result);
        return result_temp; // Retorna o nome do temporário que contém o resultado
    }

    // **Nota:** Você deve adicionar lógica similar aqui para N_EXPR_OP_REL e N_EXPR_OP_LOG
    // Eles também chamariam gerarCodigoExp nos filhos e gerariam instruções condicionais/lógicas.

    return NULL;
}

// ----------------------------------------------------
// Função principal que percorre a AST e gera o Código Intermediário para Comandos
// ----------------------------------------------------
void geraCodigoIntermediario(AST *root) {
    if (!root) {
        return;
    }

    // A lógica deve começar processando os comandos na lista de comandos (N_CMD_LIST) ou no N_PROGRAMA
    // Vamos tratar recursivamente a lista de comandos e comandos individuais:

    // Processa o nó atual (se for um comando)
    switch (root->tipo) {

        // ➡️ COMANDO DE ATRIBUIÇÃO
        case N_CMD_ATRIB: {
            // O lado esquerdo é a variável de destino (N_EXPR_VAR)
            char *target_id = root->left->valor;

            // O lado direito é a Expressão (recursivamente gera o código da expressão)
            char *exp_result = gerarCodigoExp(root->right);

            // 🎯 IMPRESSÃO DA ATRIBUIÇÃO FINAL
            printf("%s = %s\n", target_id, exp_result);

            free(exp_result);
            break;
        }

        // ➡️ COMANDO SE/ENTAO/SENAO
        case N_CMD_SE: {
            char *label_end = new_label();
            char *label_else = new_label();

            // 1. Condição (root->left)
            char *condition_result = gerarCodigoExp(root->left);

            // Se for SE/SENAO (root->extra != NULL), usa label_else. Se for só SE, usa label_end.
            char *label_target = (root->extra != NULL) ? label_else : label_end;

            // IF NOT condition_result GOTO label_target
            printf("IF NOT %s GOTO %s\n", condition_result, label_target);

            // 2. Bloco do SE (root->right) - Geração recursiva
            geraCodigoIntermediario(root->right);

            // 3. Bloco do SENAO (root->extra)
            if (root->extra != NULL) {
                // Pula o ELSE se o IF executou
                printf("GOTO %s\n", label_end);
                // Rótulo do ELSE
                printf("%s:\n", label_else);
                // Geração recursiva do ELSE
                geraCodigoIntermediario(root->extra);
            }

            // 4. Fim do Comando SE
            printf("%s:\n", label_end);

            free(condition_result);
            free(label_end);
            free(label_else);
            break;
        }

        // ➡️ COMANDO ENQUANTO
        case N_CMD_ENQUANTO: {
            char *label_start = new_label();
            char *label_end = new_label();

            printf("%s:\n", label_start); // Rótulo de início do loop

            // 1. Condição (root->left)
            char *condition_result = gerarCodigoExp(root->left);

            // IF NOT condition_result GOTO label_end
            printf("IF NOT %s GOTO %s\n", condition_result, label_end);

            // 2. Corpo do ENQUANTO (root->right) - Geração recursiva
            geraCodigoIntermediario(root->right);

            // 3. Volta para o início da condição
            printf("GOTO %s\n", label_start);

            // 4. Fim do ENQUANTO
            printf("%s:\n", label_end);

            free(condition_result);
            free(label_start);
            free(label_end);
            break;
        }

        // ➡️ COMANDOS DE E/S (Ex: ESCREVA)
        case N_CMD_ESCREVA: {
            // Assume que N_CMD_ESCREVA tem a expressão a ser impressa em 'left'
            char *exp_result = gerarCodigoExp(root->left);
            printf("WRITE %s\n", exp_result);
            free(exp_result);
            break;
        }

        // ➡️ OUTROS NÓS (Programa, Declarações, Lista de Comandos, etc.)
        case N_PROGRAMA:
        case N_DECLARACOES:
        case N_CMD_LIST:
        case N_DECL:
        default:
            // Continua o percurso recursivamente nos filhos principais
            geraCodigoIntermediario(root->left);
            geraCodigoIntermediario(root->right);
            geraCodigoIntermediario(root->extra);
            break;
    }

    // Processa o próximo comando sequencialmente (se houver)
    // Se o seu analisador sintático usa 'next' para encadear comandos, você deve fazer:
    // geraCodigoIntermediario(root->next);
    // Como sua AST não tem 'next', estamos usando 'right' ou 'extra' para encadeamento,
    // mas se for uma lista de comandos (N_CMD_LIST), o percurso já trata a sequência.
}