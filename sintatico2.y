%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"

extern int yylex();
extern int yylineno;
extern char *yytext;
void yyerror(const char *s);

AST *root_ast = NULL;

int tipoParaSimbolo(char *tipo) {
    if (strcmp(tipo, "INTEIRO") == 0) return T_INT;
    if (strcmp(tipo, "REAL") == 0) return T_REAL;
    if (strcmp(tipo, "LISTAINT") == 0) return T_LIST_INT;
    if (strcmp(tipo, "LISTAREAL") == 0) return T_LIST_REAL;
    return -1;
}
void declara_ids(AST *no, int tipo) {
    if (!no) return;

    if (no->tipo == N_EXPR_VAR) {
        insert_symbol(no->valor, tipo);
    }
    else if (no->tipo == N_EXPR_LISTA) {
        int size = atoi(no->left->valor);
        insert_symbol_array(no->valor, tipo, size);
    }
    else if (no->tipo == N_CMD_LIST) {
        declara_ids(no->left, tipo);
        declara_ids(no->right, tipo);
    }
}

int tipo_da_expressao(AST *node) {
    if (!node) return T_INT;

    switch (node->tipo) {

        case N_EXPR_INT: return T_INT;
        case N_EXPR_REAL: return T_REAL;

        case N_EXPR_VAR: {
            int idx = lookup_symbol(node->valor);
            if (idx == -1) {
                sem_error("Variável não declarada", yylineno);
                return T_INT;
            }
            return get_symbol_type_by_index(idx);
        }

        case N_EXPR_LISTA: {
            int idx = lookup_symbol(node->valor);
            if (idx == -1) {
                sem_error("Lista não declarada", yylineno);
                return T_LIST_INT;
            }
            return get_symbol_type_by_index(idx);
        }

        case N_EXPR_OP_ARIT:
            return result_type(
                tipo_da_expressao(node->left),
                tipo_da_expressao(node->right)
            );

        case N_EXPR_OP_REL:
        case N_EXPR_OP_LOG:
            return T_INT;
    }
    return T_INT;
}

%}

%token PROGRAMA FIMPROG DECLARACOES ALGORITMO
%token INTEIRO REAL LISTAINT LISTAREAL
%token LEIA ESCREVA
%token SE ENTAO SENAO FIMSE
%token ENQUANTO FACA FIMENQ

%token MAQ MAI MEQ MEI IGU DIF
%token OU E NAO
%token ASSIGN

%token VIRGULA MAIS MENOS MULT DIV ABREPAR FECHAPAR ABRECOL FECHACOL

%left OU
%left E
%right NAO
%left MAQ MAI MEQ MEI IGU DIF
%left MAIS MENOS
%left MULT DIV

%union {
    int ival;
    float fval;
    char *sval;
    struct AST *node;
}

%token <sval> ID NUM REALNUM CADEIA

%type <node> programa opt_declaracoes corpo_opt opt_algoritmo lista_decl declaracao lista_ids tipo
%type <node> lista_comandos comando atribuicao variavel entrada lista_variaveis saida lista_saidas item_saida
%type <node> selecao repeticao expressao rel_simples op_rel expr_rel

%%

programa:
    PROGRAMA corpo_opt FIMPROG
    {
        root_ast = novoNo(N_PROGRAMA, NULL, $2, NULL, NULL);
    }
    ;

corpo_opt:
    opt_declaracoes lista_decl opt_algoritmo lista_comandos
    {
        $$ = novoNo(N_DECLARACOES, NULL, $2, novoNo(N_ALGORITMO, NULL, $4, NULL, NULL), NULL);
    }
    ;

opt_declaracoes:
    DECLARACOES { $$ = NULL; }
  | /* vazio */ { $$ = NULL; } 
  ;

opt_algoritmo:
    ALGORITMO { $$ = NULL; }
  | /* vazio */ { $$ = NULL; } 
  ;

lista_decl:
    declaracao lista_decl
    {
        $$ = novoNo(N_CMD_LIST, NULL, $1, $2, NULL);
    }
    | /* vazio */
    {
        $$ = NULL;
    }
    ;

declaracao:
    tipo lista_ids
    {
        int tipoSimbolo = tipoParaSimbolo($1->valor);
        declara_ids($2, tipoSimbolo);  
        $$ = NULL;
    }


lista_ids:
      ID
        { $$ = novoNo(N_EXPR_VAR, strdup($1), NULL, NULL, NULL); }

    | ID ABRECOL NUM FECHACOL
        {
            $$ = novoNo(N_EXPR_LISTA, strdup($1),
                        novoNo(N_EXPR_INT, strdup($3), NULL, NULL, NULL),
                        NULL,
                        NULL);
        }

    | ID VIRGULA lista_ids
        {
            $$ = novoNo(N_CMD_LIST, NULL,
                        novoNo(N_EXPR_VAR, strdup($1), NULL, NULL, NULL),
                        $3,
                        NULL);
        }

    | ID ABRECOL NUM FECHACOL VIRGULA lista_ids
        {
            AST *arr = novoNo(N_EXPR_LISTA, strdup($1),
                              novoNo(N_EXPR_INT, strdup($3), NULL, NULL, NULL),
                              NULL,
                              NULL);
            $$ = novoNo(N_CMD_LIST, NULL, arr, $6, NULL);
        }
;



tipo:
      INTEIRO    { $$ = novoNo(N_EXPR_VAR, strdup("INTEIRO"), NULL, NULL, NULL); }
    | REAL       { $$ = novoNo(N_EXPR_VAR, strdup("REAL"), NULL, NULL, NULL); }
    | LISTAINT   { $$ = novoNo(N_EXPR_VAR, strdup("LISTAINT"), NULL, NULL, NULL); }
    | LISTAREAL  { $$ = novoNo(N_EXPR_VAR, strdup("LISTAREAL"), NULL, NULL, NULL); }
    ;

lista_comandos:
    comando lista_comandos
    {
        $$ = novoNo(N_CMD_LIST, NULL, $1, $2, NULL);
    }
    | /* vazio */ { $$ = NULL; }
    ;

comando:
      atribuicao
    | entrada
    | saida
    | selecao
    | repeticao
    ;

atribuicao:
    variavel ASSIGN expressao
    {
        int tipoVar = tipo_da_expressao($1);
        int tipoExpr = tipo_da_expressao($3);

        if (!type_compat(tipoVar, tipoExpr))
            sem_error("Tipos incompatíveis na atribuição", yylineno);

        $$ = novoNo(N_CMD_ATRIB, NULL, $1, $3, NULL);
    }
    ;

variavel:
    ID
    {
        if (lookup_symbol($1) == -1)
            sem_error("Variável não declarada", yylineno);

        $$ = novoNo(N_EXPR_VAR, strdup($1), NULL, NULL, NULL);
    }
    | ID ABRECOL expressao FECHACOL
    {
        if (lookup_symbol($1) == -1)
            sem_error("Lista não declarada", yylineno);

        $$ = novoNo(N_EXPR_LISTA, strdup($1), $3, NULL, NULL);
    }
    ;

entrada:
    LEIA lista_variaveis
    {
        $$ = novoNo(N_CMD_LEIA, NULL, $2, NULL, NULL);
    }
    ;

lista_variaveis:
      variavel
    | variavel VIRGULA lista_variaveis
    {
        $$ = novoNo(N_CMD_LIST, NULL, $1, $3, NULL);
    }
    ;

saida:
    ESCREVA lista_saidas
    {
        $$ = novoNo(N_CMD_ESCREVA, NULL, $2, NULL, NULL);
    }
    ;

lista_saidas:
      item_saida
    | item_saida VIRGULA lista_saidas
    {
        $$ = novoNo(N_CMD_LIST, NULL, $1, $3, NULL);
    }
    ;

item_saida:
      variavel
    | CADEIA
    {
        $$ = novoNo(N_EXPR_CADEIA, strdup($1), NULL, NULL, NULL);
    }
    ;

selecao:
    SE expr_rel ENTAO lista_comandos FIMSE
    {
        $$ = novoNo(N_CMD_SE, NULL, $2, $4, NULL);
    }
    | SE expr_rel ENTAO lista_comandos SENAO lista_comandos FIMSE
    {
        $$ = novoNo(N_CMD_SE, NULL, $2, $4, $6);
    }
    ;

repeticao:
    ENQUANTO expr_rel FACA lista_comandos FIMENQ
    {
        $$ = novoNo(N_CMD_ENQUANTO, NULL, $2, $4, NULL);
    }
    ;

expressao:
      expressao MAIS expressao
        { $$ = novoNo(N_EXPR_OP_ARIT, strdup("+"), $1, $3, NULL); }
    | expressao MENOS expressao
        { $$ = novoNo(N_EXPR_OP_ARIT, strdup("-"), $1, $3, NULL); }
    | expressao MULT expressao
        { $$ = novoNo(N_EXPR_OP_ARIT, strdup("*"), $1, $3, NULL); }
    | expressao DIV expressao
        { $$ = novoNo(N_EXPR_OP_ARIT, strdup("/"), $1, $3, NULL); }
    | ABREPAR expressao FECHAPAR
        { $$ = $2; }
    | NUM
        { $$ = novoNo(N_EXPR_INT, strdup($1), NULL, NULL, NULL); }
    | REALNUM
        { $$ = novoNo(N_EXPR_REAL, strdup($1), NULL, NULL, NULL); }
    | variavel
    ;

expr_rel:
      expr_rel OU expr_rel
        { $$ = novoNo(N_EXPR_OP_LOG, strdup(".OU."), $1, $3, NULL); }
    | expr_rel E expr_rel
        { $$ = novoNo(N_EXPR_OP_LOG, strdup(".E."), $1, $3, NULL); }
    | NAO expr_rel
        { $$ = novoNo(N_EXPR_OP_LOG, strdup(".NAO."), $2, NULL, NULL); }
    | rel_simples
    ;

rel_simples:
    expressao op_rel expressao
    {
        $$ = novoNo(N_EXPR_OP_REL, $2->valor, $1, $3, NULL);
    }
    | ABREPAR expr_rel FECHAPAR
    {
        $$ = $2;
    }
    ;

op_rel:
      MAQ { $$ = novoNo(N_EXPR_OP_REL, strdup(".MAQ."), NULL, NULL, NULL); }
    | MAI { $$ = novoNo(N_EXPR_OP_REL, strdup(".MAI."), NULL, NULL, NULL); }
    | MEQ { $$ = novoNo(N_EXPR_OP_REL, strdup(".MEQ."), NULL, NULL, NULL); }
    | MEI { $$ = novoNo(N_EXPR_OP_REL, strdup(".MEI."), NULL, NULL, NULL); }
    | IGU { $$ = novoNo(N_EXPR_OP_REL, strdup(".IGU."), NULL, NULL, NULL); }
    | DIF { $$ = novoNo(N_EXPR_OP_REL, strdup(".DIF."), NULL, NULL, NULL); }
    ;

%%
