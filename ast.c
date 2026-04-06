#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

AST *novoNo(NodeType t, char *val, AST *l, AST *r, AST *e) {
    AST *node = (AST *)malloc(sizeof(AST));
    if (!node) {
        perror("Erro de alocação de memória para AST");
        exit(1);
    }
    node->tipo = t;
    node->valor = (val != NULL) ? strdup(val) : NULL;
    node->left = l;
    node->right = r;
    node->extra = e;
    return node;
}

const char *getNomeTipoNo(NodeType t) {
    switch (t) {
        case N_PROGRAMA: return "PROGRAMA";
        case N_DECLARACOES: return "DECLARACOES";
        case N_DECL: return "DECL";
        case N_ALGORITMO: return "ALGORITMO";
        case N_CMD_LIST: return "CMD_LIST";
        case N_CMD_ATRIB: return "ATRIBUICAO";
        case N_CMD_LEIA: return "LEIA";
        case N_CMD_ESCREVA: return "ESCREVA";
        case N_CMD_SE: return "SE";
        case N_CMD_ENQUANTO: return "ENQUANTO";
        case N_EXPR_INT: return "CONST_INT";
        case N_EXPR_REAL: return "CONST_REAL";
        case N_EXPR_CADEIA: return "CONST_CADEIA";
        case N_EXPR_VAR: return "VARIAVEL_SIMPLES";
        case N_EXPR_LISTA: return "VARIAVEL_LISTA";
        case N_EXPR_OP_ARIT: return "OP_ARIT";
        case N_EXPR_OP_REL: return "OP_REL";
        case N_EXPR_OP_LOG: return "OP_LOG";
        default: return "UNKNOWN";
    }
}

void imprimeAST(AST *node, int nivel) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    printf("-> %s", getNomeTipoNo(node->tipo));
    if (node->valor) {
        printf(" (%s)\n", node->valor);
    } else {
        printf("\n");
    }

    imprimeAST(node->left, nivel + 1);
    imprimeAST(node->right, nivel + 1);
    imprimeAST(node->extra, nivel + 1);
}

void liberaAST(AST *node) {
    if (node == NULL) {
        return;
    }
    liberaAST(node->left);
    liberaAST(node->right);
    liberaAST(node->extra);
    if (node->valor) {
        free(node->valor);
    }
    free(node);
}