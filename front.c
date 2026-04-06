#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico2.tab.h" // Inclui definições do Bison/Yacc
#include "ast.h"           // Definições da Árvore Sintática Abstrata
#include "symtab.h"        // Definições da Tabela de Símbolos (para semântica)

extern int yylineno;
extern char *yytext;
extern AST *root_ast;
extern int num_errors;

// ➡️ Declarações de Funções Externas (Implementadas em outros arquivos) ⬅️
extern void imprimeAST(AST *node, int nivel);
extern void liberaAST(AST *node);
// ⚠️ Nova Função: A Síntese das Análises
extern void geraCodigoIntermediario(AST *root);

// Função de Tratamento de Erro (Geralmente definida para o Bison)
void yyerror(const char *s) {
    fprintf(stderr, "❌ Erro de sintaxe na linha %d: %s (token: %s)\n", yylineno, s, yytext);
    exit(1);
}

int main(int argc, char **argv) {

    // Inicializa a Tabela de Símbolos (parte da Análise Semântica)
    init_symtab();

    printf("--- INÍCIO DO FRONT-END ---\n");
    printf("1. Análise Léxica, Sintática e Semântica em progresso...\n");

    if (yyparse() == 0) { // Tentativa de análise

        if (num_errors == 0) {

            printf("\n✅ Análise concluída com sucesso. Código livre de erros.\n");

            if (root_ast) {

                // 2. Apresentação da Estrutura (AST)
                printf("\n--- 2. Árvore Sintática Abstrata (AST) ---\n");
                imprimeAST(root_ast, 0);

                // 3. 🎯 SÍNTESE: Geração do Código Intermediário 🎯
                printf("\n--- 3. Geração do Código Intermediário (3AC) ---\n");
                geraCodigoIntermediario(root_ast); // <-- CHAVE DO FRONT-END COMPLETO

                printf("\n--- FIM DO FRONT-END ---\n");
                printf("O Código Intermediário gerado está pronto para o Back-End (Geração X25b).\n");

                liberaAST(root_ast);
            }

        } else {
            fprintf(stderr, "\n⚠️ Falha semântica: %d erros encontrados. Interrompendo.\n", num_errors);
            return 1;
        }

    } else {
        fprintf(stderr, "\n❌ Falha no Front-End devido a erros sintáticos. Interrompendo.\n");
        return 1;
    }

    return 0;
}