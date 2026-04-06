#ifndef AST_H
#define AST_H

typedef enum {
    N_PROGRAMA,
    N_DECLARACOES,
    N_DECL,
    N_ALGORITMO,
    N_CMD_LIST,
    N_CMD_ATRIB,
    N_CMD_LEIA,
    N_CMD_ESCREVA,
    N_CMD_SE,
    N_CMD_ENQUANTO,

    /* EXPRESSÕES */
    N_EXPR_INT,
    N_EXPR_REAL,
    N_EXPR_CADEIA,
    N_EXPR_VAR,
    N_EXPR_LISTA,
    N_EXPR_OP_ARIT,
    N_EXPR_OP_REL,
    N_EXPR_OP_LOG
} NodeType;

typedef struct AST {
    NodeType tipo;
    char *valor;             // para números, variáveis e cadeias
    struct AST *left;        // uso geral
    struct AST *right;       // uso geral
    struct AST *extra;       // uso em casos de SE/SENAO, listas, etc
} AST;

/* Funções utilitárias */
AST *novoNo(NodeType t, char *val, AST *l, AST *r, AST *e);

#endif
