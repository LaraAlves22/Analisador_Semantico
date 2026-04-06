%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintatico2.tab.h" 

int yywrap();

%}

%%

[ \t\r]+             ; 
\n                    { yylineno++; }

"{"([^}]|\n)*"}"      {
                         /* Conta \n manualmente */
                         for (char *p = yytext; *p; p++)
                             if (*p == '\n') yylineno++;
                         /* ignora completamente */
                      }


"PROGRAMA"             { return PROGRAMA; }
"FIMPROG"              { return FIMPROG; }
"DECLARACOES"          { return DECLARACOES; }
"ALGORITMO"            { return ALGORITMO; }

"INTEIRO"              { return INTEIRO; }
"REAL"                 { return REAL; }
"LISTAINT"             { return LISTAINT; }
"LISTAREAL"            { return LISTAREAL; }

"LEIA"                 { return LEIA; }
"ESCREVA"              { return ESCREVA; }

"SE"                   { return SE; }
"ENTAO"                { return ENTAO; }
"SENAO"                { return SENAO; }
"FIMSE"                { return FIMSE; }

"ENQUANTO"             { return ENQUANTO; }
"FACA"                 { return FACA; }
"FIMENQ"               { return FIMENQ; }


","                    { return VIRGULA; }
"+"                    { return MAIS; }
"-"                    { return MENOS; }
"*"                    { return MULT; }
"/"                    { return DIV; }
"("                    { return ABREPAR; }
")"                    { return FECHAPAR; }
"["                    { return ABRECOL; }
"]"                    { return FECHACOL; }

".MAQ."                { return MAQ; }
".MAI."                { return MAI; }
".MEQ."                { return MEQ; }
".MEI."                { return MEI; }
".IGU."                { return IGU; }
".DIF."                { return DIF; }

".OU."                 { return OU; }
".E."                  { return E; }
".NAO."                { return NAO; }

":="                   { return ASSIGN; }


[0-9]+                 {
                           yylval.sval = strdup(yytext);
                           return NUM;
                       }

[0-9]+"."[0-9]+         {
                           yylval.sval = strdup(yytext);
                           return REALNUM;
                       }

"'"([^'\n]|"\\'")*"'"  {
                           yylval.sval = strdup(yytext);
                           return CADEIA;
                       }

[A-Za-z][A-Za-z0-9]{0,7} {
                           yylval.sval = strdup(yytext);
                           return ID;
                       }
                       

. { 
    fprintf(stderr, "Erro léxico: Caractere inválido: %s (linha %d)\n", yytext, yylineno);
    exit(1);
}

%%

int yywrap() {
    return 1;
}
