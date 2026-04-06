#ifndef SYMTAB_H
#define SYMTAB_H

#define T_INT 1
#define T_REAL 2
#define T_LIST_INT 3
#define T_LIST_REAL 4

void init_symtab(void);
int insert_symbol(const char *name, int tipo);
int insert_symbol_array(const char *name, int tipo, int size);
int lookup_symbol(const char *name);
int get_symbol_type_by_index(int idx);
void dump_symtab(void);

int type_compat(int vtipo, int etipo);
int result_type(int t1, int t2);

extern int num_errors;
extern int current_decl_tipo;

void sem_error(const char *msg, int lineno);
int is_array_name(const char *s);

#endif
