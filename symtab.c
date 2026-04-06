#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

typedef struct sym {
    char *name;
    int tipo;
    int is_array;
    int size;
    struct sym *next;
} sym;

static sym *table = NULL;
int num_errors = 0;
int current_decl_tipo = 0;

void init_symtab(void) {
    table = NULL;
}

int insert_symbol(const char *name, int tipo) {
    sym *s = malloc(sizeof(sym));
    s->name = strdup(name);
    s->tipo = tipo;
    s->is_array = 0;
    s->size = 0;
    s->next = table;
    table = s;
    return 0;
}

int insert_symbol_array(const char *name, int tipo, int size) {
    sym *s = malloc(sizeof(sym));
    s->name = strdup(name);
    s->tipo = tipo;
    s->is_array = 1;
    s->size = size;
    s->next = table;
    table = s;
    return 0;
}

int lookup_symbol(const char *name) {
    sym *p = table;
    int idx = 0;
    while (p) {
        if (strcmp(p->name, name) == 0) return idx;
        p = p->next;
        idx++;
    }
    return -1;
}

int get_symbol_type_by_index(int idx) {
    sym *p = table;
    int i = 0;
    while (p) {
        if (i == idx) return p->tipo;
        p = p->next;
        i++;
    }
    return T_INT; // fallback
}

void dump_symtab(void) {
    printf("---Tabela de simbolos---\n");
    sym *p = table;
    while (p) {
        printf("%s : tipo=%d array=%d size=%d\n", p->name, p->tipo, p->is_array, p->size);
        p = p->next;
    }
}

// Verifica se é permitido usar expr numa variável
int type_compat(int vtipo, int etipo) {
    if (vtipo == etipo) return 1;
    if (vtipo == T_REAL && etipo == T_INT) return 1; // conversão implícita int → real
    return 0;
}

// Tipo resultante de uma operação aritmética
int result_type(int t1, int t2) {
    if (t1 == T_REAL || t2 == T_REAL) return T_REAL;
    return T_INT;
}

void sem_error(const char *msg, int lineno) {
    fprintf(stderr, "Erro semantico (linha %d): %s\n", lineno, msg);
    num_errors++;
}

int is_array_name(const char *s) {
    return strchr(s, '[') != NULL;
}
