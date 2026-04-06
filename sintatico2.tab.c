/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintatico2.y"

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


#line 149 "sintatico2.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "sintatico2.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAMA = 3,                   /* PROGRAMA  */
  YYSYMBOL_FIMPROG = 4,                    /* FIMPROG  */
  YYSYMBOL_DECLARACOES = 5,                /* DECLARACOES  */
  YYSYMBOL_ALGORITMO = 6,                  /* ALGORITMO  */
  YYSYMBOL_INTEIRO = 7,                    /* INTEIRO  */
  YYSYMBOL_REAL = 8,                       /* REAL  */
  YYSYMBOL_LISTAINT = 9,                   /* LISTAINT  */
  YYSYMBOL_LISTAREAL = 10,                 /* LISTAREAL  */
  YYSYMBOL_LEIA = 11,                      /* LEIA  */
  YYSYMBOL_ESCREVA = 12,                   /* ESCREVA  */
  YYSYMBOL_SE = 13,                        /* SE  */
  YYSYMBOL_ENTAO = 14,                     /* ENTAO  */
  YYSYMBOL_SENAO = 15,                     /* SENAO  */
  YYSYMBOL_FIMSE = 16,                     /* FIMSE  */
  YYSYMBOL_ENQUANTO = 17,                  /* ENQUANTO  */
  YYSYMBOL_FACA = 18,                      /* FACA  */
  YYSYMBOL_FIMENQ = 19,                    /* FIMENQ  */
  YYSYMBOL_MAQ = 20,                       /* MAQ  */
  YYSYMBOL_MAI = 21,                       /* MAI  */
  YYSYMBOL_MEQ = 22,                       /* MEQ  */
  YYSYMBOL_MEI = 23,                       /* MEI  */
  YYSYMBOL_IGU = 24,                       /* IGU  */
  YYSYMBOL_DIF = 25,                       /* DIF  */
  YYSYMBOL_OU = 26,                        /* OU  */
  YYSYMBOL_E = 27,                         /* E  */
  YYSYMBOL_NAO = 28,                       /* NAO  */
  YYSYMBOL_ASSIGN = 29,                    /* ASSIGN  */
  YYSYMBOL_VIRGULA = 30,                   /* VIRGULA  */
  YYSYMBOL_MAIS = 31,                      /* MAIS  */
  YYSYMBOL_MENOS = 32,                     /* MENOS  */
  YYSYMBOL_MULT = 33,                      /* MULT  */
  YYSYMBOL_DIV = 34,                       /* DIV  */
  YYSYMBOL_ABREPAR = 35,                   /* ABREPAR  */
  YYSYMBOL_FECHAPAR = 36,                  /* FECHAPAR  */
  YYSYMBOL_ABRECOL = 37,                   /* ABRECOL  */
  YYSYMBOL_FECHACOL = 38,                  /* FECHACOL  */
  YYSYMBOL_ID = 39,                        /* ID  */
  YYSYMBOL_NUM = 40,                       /* NUM  */
  YYSYMBOL_REALNUM = 41,                   /* REALNUM  */
  YYSYMBOL_CADEIA = 42,                    /* CADEIA  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_programa = 44,                  /* programa  */
  YYSYMBOL_corpo_opt = 45,                 /* corpo_opt  */
  YYSYMBOL_opt_declaracoes = 46,           /* opt_declaracoes  */
  YYSYMBOL_opt_algoritmo = 47,             /* opt_algoritmo  */
  YYSYMBOL_lista_decl = 48,                /* lista_decl  */
  YYSYMBOL_declaracao = 49,                /* declaracao  */
  YYSYMBOL_lista_ids = 50,                 /* lista_ids  */
  YYSYMBOL_tipo = 51,                      /* tipo  */
  YYSYMBOL_lista_comandos = 52,            /* lista_comandos  */
  YYSYMBOL_comando = 53,                   /* comando  */
  YYSYMBOL_atribuicao = 54,                /* atribuicao  */
  YYSYMBOL_variavel = 55,                  /* variavel  */
  YYSYMBOL_entrada = 56,                   /* entrada  */
  YYSYMBOL_lista_variaveis = 57,           /* lista_variaveis  */
  YYSYMBOL_saida = 58,                     /* saida  */
  YYSYMBOL_lista_saidas = 59,              /* lista_saidas  */
  YYSYMBOL_item_saida = 60,                /* item_saida  */
  YYSYMBOL_selecao = 61,                   /* selecao  */
  YYSYMBOL_repeticao = 62,                 /* repeticao  */
  YYSYMBOL_expressao = 63,                 /* expressao  */
  YYSYMBOL_expr_rel = 64,                  /* expr_rel  */
  YYSYMBOL_rel_simples = 65,               /* rel_simples  */
  YYSYMBOL_op_rel = 66                     /* op_rel  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   119

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  101

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   114,   114,   121,   128,   129,   133,   134,   138,   143,
     149,   158,   161,   169,   177,   190,   191,   192,   193,   197,
     201,   205,   206,   207,   208,   209,   213,   226,   233,   243,
     250,   251,   258,   265,   266,   273,   274,   281,   285,   292,
     299,   301,   303,   305,   307,   309,   311,   313,   317,   319,
     321,   323,   327,   331,   338,   339,   340,   341,   342,   343
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAMA", "FIMPROG",
  "DECLARACOES", "ALGORITMO", "INTEIRO", "REAL", "LISTAINT", "LISTAREAL",
  "LEIA", "ESCREVA", "SE", "ENTAO", "SENAO", "FIMSE", "ENQUANTO", "FACA",
  "FIMENQ", "MAQ", "MAI", "MEQ", "MEI", "IGU", "DIF", "OU", "E", "NAO",
  "ASSIGN", "VIRGULA", "MAIS", "MENOS", "MULT", "DIV", "ABREPAR",
  "FECHAPAR", "ABRECOL", "FECHACOL", "ID", "NUM", "REALNUM", "CADEIA",
  "$accept", "programa", "corpo_opt", "opt_declaracoes", "opt_algoritmo",
  "lista_decl", "declaracao", "lista_ids", "tipo", "lista_comandos",
  "comando", "atribuicao", "variavel", "entrada", "lista_variaveis",
  "saida", "lista_saidas", "item_saida", "selecao", "repeticao",
  "expressao", "expr_rel", "rel_simples", "op_rel", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-35)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       8,    25,    13,   -35,    22,    64,   -35,   -35,   -35,   -35,
     -35,   -35,    11,    64,     6,   -35,    12,   -35,    17,   -35,
       9,   -30,     3,     3,    20,   -35,    12,   -35,    30,   -35,
     -35,   -35,   -35,     6,    10,    72,   -35,   -35,   -35,   -35,
      78,     3,     3,   -35,   -35,   -35,    61,    -7,   -35,   -12,
      21,   -35,    21,   -35,    53,     9,   -30,   -35,    44,     1,
     -35,   -35,   -35,   -35,   -35,   -35,    21,    21,    21,    21,
      21,    12,     3,     3,    12,    21,    65,    56,    82,   -35,
     -35,   -35,   -35,    67,    67,   -35,   -35,    56,    95,    86,
     -35,    96,    73,   -35,     6,    12,   -35,   -35,   -35,    98,
     -35
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     0,     4,     0,     9,     1,     2,    15,    16,
      17,    18,     7,     9,     0,     6,    20,     8,    11,    10,
       0,     0,     0,     0,    27,     3,    20,    21,     0,    22,
      23,    24,    25,     0,     0,    30,    29,    36,    35,    32,
      33,     0,     0,    45,    46,    47,     0,     0,    51,     0,
       0,    19,     0,    13,     0,     0,     0,    50,     0,     0,
      54,    55,    56,    57,    58,    59,     0,     0,     0,     0,
       0,    20,     0,     0,    20,     0,     0,    26,    12,    31,
      34,    44,    53,    40,    41,    42,    43,    52,     0,    48,
      49,     0,     0,    28,     0,    20,    37,    39,    14,     0,
      38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -35,   -35,   -35,   -35,   -35,   103,   -35,   -31,   -35,   -25,
     -35,   -35,   -16,   -35,    62,   -35,    63,   -35,   -35,   -35,
     -34,   -20,   -35,   -35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     4,     5,    16,    12,    13,    19,    14,    25,
      26,    27,    45,    29,    36,    30,    39,    40,    31,    32,
      46,    47,    48,    70
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      28,    51,    53,    49,    35,    38,    74,    71,    58,    24,
      28,     1,    37,     6,    72,    73,    76,    15,    77,    72,
      73,    57,    59,    20,    21,    22,     7,    72,    73,    23,
       3,    41,    83,    84,    85,    86,    87,    82,    42,    35,
      38,    92,    24,    43,    44,    18,    88,    33,    24,    91,
      54,    24,    89,    90,    34,    28,    75,    50,    28,    52,
      24,    43,    44,    98,    60,    61,    62,    63,    64,    65,
      99,     8,     9,    10,    11,    66,    67,    68,    69,    28,
      81,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    78,    66,    67,    68,    69,    66,    67,    68,    69,
      68,    69,    55,    93,    66,    67,    68,    69,    56,    81,
      95,    96,    94,    73,   100,    97,    17,    79,     0,    80
};

static const yytype_int8 yycheck[] =
{
      16,    26,    33,    23,    20,    21,    18,    14,    42,    39,
      26,     3,    42,     0,    26,    27,    50,     6,    52,    26,
      27,    41,    42,    11,    12,    13,     4,    26,    27,    17,
       5,    28,    66,    67,    68,    69,    70,    36,    35,    55,
      56,    75,    39,    40,    41,    39,    71,    30,    39,    74,
      40,    39,    72,    73,    37,    71,    35,    37,    74,    29,
      39,    40,    41,    94,    20,    21,    22,    23,    24,    25,
      95,     7,     8,     9,    10,    31,    32,    33,    34,    95,
      36,    20,    21,    22,    23,    24,    25,    31,    32,    33,
      34,    38,    31,    32,    33,    34,    31,    32,    33,    34,
      33,    34,    30,    38,    31,    32,    33,    34,    30,    36,
      15,    16,    30,    27,    16,    19,    13,    55,    -1,    56
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    44,     5,    45,    46,     0,     4,     7,     8,
       9,    10,    48,    49,    51,     6,    47,    48,    39,    50,
      11,    12,    13,    17,    39,    52,    53,    54,    55,    56,
      58,    61,    62,    30,    37,    55,    57,    42,    55,    59,
      60,    28,    35,    40,    41,    55,    63,    64,    65,    64,
      37,    52,    29,    50,    40,    30,    30,    64,    63,    64,
      20,    21,    22,    23,    24,    25,    31,    32,    33,    34,
      66,    14,    26,    27,    18,    35,    63,    63,    38,    57,
      59,    36,    36,    63,    63,    63,    63,    63,    52,    64,
      64,    52,    63,    38,    30,    15,    16,    19,    50,    52,
      16
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    46,    46,    47,    47,    48,    48,
      49,    50,    50,    50,    50,    51,    51,    51,    51,    52,
      52,    53,    53,    53,    53,    53,    54,    55,    55,    56,
      57,    57,    58,    59,    59,    60,    60,    61,    61,    62,
      63,    63,    63,    63,    63,    63,    63,    63,    64,    64,
      64,    64,    65,    65,    66,    66,    66,    66,    66,    66
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     4,     1,     0,     1,     0,     2,     0,
       2,     1,     4,     3,     6,     1,     1,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     3,     1,     4,     2,
       1,     3,     2,     1,     3,     1,     1,     5,     7,     5,
       3,     3,     3,     3,     3,     1,     1,     1,     3,     3,
       2,     1,     3,     3,     1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: PROGRAMA corpo_opt FIMPROG  */
#line 115 "sintatico2.y"
    {
        root_ast = novoNo(N_PROGRAMA, NULL, (yyvsp[-1].node), NULL, NULL);
    }
#line 1274 "sintatico2.tab.c"
    break;

  case 3: /* corpo_opt: opt_declaracoes lista_decl opt_algoritmo lista_comandos  */
#line 122 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_DECLARACOES, NULL, (yyvsp[-2].node), novoNo(N_ALGORITMO, NULL, (yyvsp[0].node), NULL, NULL), NULL);
    }
#line 1282 "sintatico2.tab.c"
    break;

  case 4: /* opt_declaracoes: DECLARACOES  */
#line 128 "sintatico2.y"
                { (yyval.node) = NULL; }
#line 1288 "sintatico2.tab.c"
    break;

  case 5: /* opt_declaracoes: %empty  */
#line 129 "sintatico2.y"
                { (yyval.node) = NULL; }
#line 1294 "sintatico2.tab.c"
    break;

  case 6: /* opt_algoritmo: ALGORITMO  */
#line 133 "sintatico2.y"
              { (yyval.node) = NULL; }
#line 1300 "sintatico2.tab.c"
    break;

  case 7: /* opt_algoritmo: %empty  */
#line 134 "sintatico2.y"
                { (yyval.node) = NULL; }
#line 1306 "sintatico2.tab.c"
    break;

  case 8: /* lista_decl: declaracao lista_decl  */
#line 139 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_CMD_LIST, NULL, (yyvsp[-1].node), (yyvsp[0].node), NULL);
    }
#line 1314 "sintatico2.tab.c"
    break;

  case 9: /* lista_decl: %empty  */
#line 143 "sintatico2.y"
    {
        (yyval.node) = NULL;
    }
#line 1322 "sintatico2.tab.c"
    break;

  case 10: /* declaracao: tipo lista_ids  */
#line 150 "sintatico2.y"
    {
        int tipoSimbolo = tipoParaSimbolo((yyvsp[-1].node)->valor);
        declara_ids((yyvsp[0].node), tipoSimbolo);  
        (yyval.node) = NULL;
    }
#line 1332 "sintatico2.tab.c"
    break;

  case 11: /* lista_ids: ID  */
#line 159 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_VAR, strdup((yyvsp[0].sval)), NULL, NULL, NULL); }
#line 1338 "sintatico2.tab.c"
    break;

  case 12: /* lista_ids: ID ABRECOL NUM FECHACOL  */
#line 162 "sintatico2.y"
        {
            (yyval.node) = novoNo(N_EXPR_LISTA, strdup((yyvsp[-3].sval)),
                        novoNo(N_EXPR_INT, strdup((yyvsp[-1].sval)), NULL, NULL, NULL),
                        NULL,
                        NULL);
        }
#line 1349 "sintatico2.tab.c"
    break;

  case 13: /* lista_ids: ID VIRGULA lista_ids  */
#line 170 "sintatico2.y"
        {
            (yyval.node) = novoNo(N_CMD_LIST, NULL,
                        novoNo(N_EXPR_VAR, strdup((yyvsp[-2].sval)), NULL, NULL, NULL),
                        (yyvsp[0].node),
                        NULL);
        }
#line 1360 "sintatico2.tab.c"
    break;

  case 14: /* lista_ids: ID ABRECOL NUM FECHACOL VIRGULA lista_ids  */
#line 178 "sintatico2.y"
        {
            AST *arr = novoNo(N_EXPR_LISTA, strdup((yyvsp[-5].sval)),
                              novoNo(N_EXPR_INT, strdup((yyvsp[-3].sval)), NULL, NULL, NULL),
                              NULL,
                              NULL);
            (yyval.node) = novoNo(N_CMD_LIST, NULL, arr, (yyvsp[0].node), NULL);
        }
#line 1372 "sintatico2.tab.c"
    break;

  case 15: /* tipo: INTEIRO  */
#line 190 "sintatico2.y"
                 { (yyval.node) = novoNo(N_EXPR_VAR, strdup("INTEIRO"), NULL, NULL, NULL); }
#line 1378 "sintatico2.tab.c"
    break;

  case 16: /* tipo: REAL  */
#line 191 "sintatico2.y"
                 { (yyval.node) = novoNo(N_EXPR_VAR, strdup("REAL"), NULL, NULL, NULL); }
#line 1384 "sintatico2.tab.c"
    break;

  case 17: /* tipo: LISTAINT  */
#line 192 "sintatico2.y"
                 { (yyval.node) = novoNo(N_EXPR_VAR, strdup("LISTAINT"), NULL, NULL, NULL); }
#line 1390 "sintatico2.tab.c"
    break;

  case 18: /* tipo: LISTAREAL  */
#line 193 "sintatico2.y"
                 { (yyval.node) = novoNo(N_EXPR_VAR, strdup("LISTAREAL"), NULL, NULL, NULL); }
#line 1396 "sintatico2.tab.c"
    break;

  case 19: /* lista_comandos: comando lista_comandos  */
#line 198 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_CMD_LIST, NULL, (yyvsp[-1].node), (yyvsp[0].node), NULL);
    }
#line 1404 "sintatico2.tab.c"
    break;

  case 20: /* lista_comandos: %empty  */
#line 201 "sintatico2.y"
                  { (yyval.node) = NULL; }
#line 1410 "sintatico2.tab.c"
    break;

  case 26: /* atribuicao: variavel ASSIGN expressao  */
#line 214 "sintatico2.y"
    {
        int tipoVar = tipo_da_expressao((yyvsp[-2].node));
        int tipoExpr = tipo_da_expressao((yyvsp[0].node));

        if (!type_compat(tipoVar, tipoExpr))
            sem_error("Tipos incompatíveis na atribuição", yylineno);

        (yyval.node) = novoNo(N_CMD_ATRIB, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 1424 "sintatico2.tab.c"
    break;

  case 27: /* variavel: ID  */
#line 227 "sintatico2.y"
    {
        if (lookup_symbol((yyvsp[0].sval)) == -1)
            sem_error("Variável não declarada", yylineno);

        (yyval.node) = novoNo(N_EXPR_VAR, strdup((yyvsp[0].sval)), NULL, NULL, NULL);
    }
#line 1435 "sintatico2.tab.c"
    break;

  case 28: /* variavel: ID ABRECOL expressao FECHACOL  */
#line 234 "sintatico2.y"
    {
        if (lookup_symbol((yyvsp[-3].sval)) == -1)
            sem_error("Lista não declarada", yylineno);

        (yyval.node) = novoNo(N_EXPR_LISTA, strdup((yyvsp[-3].sval)), (yyvsp[-1].node), NULL, NULL);
    }
#line 1446 "sintatico2.tab.c"
    break;

  case 29: /* entrada: LEIA lista_variaveis  */
#line 244 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_CMD_LEIA, NULL, (yyvsp[0].node), NULL, NULL);
    }
#line 1454 "sintatico2.tab.c"
    break;

  case 31: /* lista_variaveis: variavel VIRGULA lista_variaveis  */
#line 252 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_CMD_LIST, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 1462 "sintatico2.tab.c"
    break;

  case 32: /* saida: ESCREVA lista_saidas  */
#line 259 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_CMD_ESCREVA, NULL, (yyvsp[0].node), NULL, NULL);
    }
#line 1470 "sintatico2.tab.c"
    break;

  case 34: /* lista_saidas: item_saida VIRGULA lista_saidas  */
#line 267 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_CMD_LIST, NULL, (yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 1478 "sintatico2.tab.c"
    break;

  case 36: /* item_saida: CADEIA  */
#line 275 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_EXPR_CADEIA, strdup((yyvsp[0].sval)), NULL, NULL, NULL);
    }
#line 1486 "sintatico2.tab.c"
    break;

  case 37: /* selecao: SE expr_rel ENTAO lista_comandos FIMSE  */
#line 282 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_CMD_SE, NULL, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
    }
#line 1494 "sintatico2.tab.c"
    break;

  case 38: /* selecao: SE expr_rel ENTAO lista_comandos SENAO lista_comandos FIMSE  */
#line 286 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_CMD_SE, NULL, (yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 1502 "sintatico2.tab.c"
    break;

  case 39: /* repeticao: ENQUANTO expr_rel FACA lista_comandos FIMENQ  */
#line 293 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_CMD_ENQUANTO, NULL, (yyvsp[-3].node), (yyvsp[-1].node), NULL);
    }
#line 1510 "sintatico2.tab.c"
    break;

  case 40: /* expressao: expressao MAIS expressao  */
#line 300 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_OP_ARIT, strdup("+"), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1516 "sintatico2.tab.c"
    break;

  case 41: /* expressao: expressao MENOS expressao  */
#line 302 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_OP_ARIT, strdup("-"), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1522 "sintatico2.tab.c"
    break;

  case 42: /* expressao: expressao MULT expressao  */
#line 304 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_OP_ARIT, strdup("*"), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1528 "sintatico2.tab.c"
    break;

  case 43: /* expressao: expressao DIV expressao  */
#line 306 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_OP_ARIT, strdup("/"), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1534 "sintatico2.tab.c"
    break;

  case 44: /* expressao: ABREPAR expressao FECHAPAR  */
#line 308 "sintatico2.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 1540 "sintatico2.tab.c"
    break;

  case 45: /* expressao: NUM  */
#line 310 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_INT, strdup((yyvsp[0].sval)), NULL, NULL, NULL); }
#line 1546 "sintatico2.tab.c"
    break;

  case 46: /* expressao: REALNUM  */
#line 312 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_REAL, strdup((yyvsp[0].sval)), NULL, NULL, NULL); }
#line 1552 "sintatico2.tab.c"
    break;

  case 48: /* expr_rel: expr_rel OU expr_rel  */
#line 318 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_OP_LOG, strdup(".OU."), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1558 "sintatico2.tab.c"
    break;

  case 49: /* expr_rel: expr_rel E expr_rel  */
#line 320 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_OP_LOG, strdup(".E."), (yyvsp[-2].node), (yyvsp[0].node), NULL); }
#line 1564 "sintatico2.tab.c"
    break;

  case 50: /* expr_rel: NAO expr_rel  */
#line 322 "sintatico2.y"
        { (yyval.node) = novoNo(N_EXPR_OP_LOG, strdup(".NAO."), (yyvsp[0].node), NULL, NULL); }
#line 1570 "sintatico2.tab.c"
    break;

  case 52: /* rel_simples: expressao op_rel expressao  */
#line 328 "sintatico2.y"
    {
        (yyval.node) = novoNo(N_EXPR_OP_REL, (yyvsp[-1].node)->valor, (yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 1578 "sintatico2.tab.c"
    break;

  case 53: /* rel_simples: ABREPAR expr_rel FECHAPAR  */
#line 332 "sintatico2.y"
    {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1586 "sintatico2.tab.c"
    break;

  case 54: /* op_rel: MAQ  */
#line 338 "sintatico2.y"
          { (yyval.node) = novoNo(N_EXPR_OP_REL, strdup(".MAQ."), NULL, NULL, NULL); }
#line 1592 "sintatico2.tab.c"
    break;

  case 55: /* op_rel: MAI  */
#line 339 "sintatico2.y"
          { (yyval.node) = novoNo(N_EXPR_OP_REL, strdup(".MAI."), NULL, NULL, NULL); }
#line 1598 "sintatico2.tab.c"
    break;

  case 56: /* op_rel: MEQ  */
#line 340 "sintatico2.y"
          { (yyval.node) = novoNo(N_EXPR_OP_REL, strdup(".MEQ."), NULL, NULL, NULL); }
#line 1604 "sintatico2.tab.c"
    break;

  case 57: /* op_rel: MEI  */
#line 341 "sintatico2.y"
          { (yyval.node) = novoNo(N_EXPR_OP_REL, strdup(".MEI."), NULL, NULL, NULL); }
#line 1610 "sintatico2.tab.c"
    break;

  case 58: /* op_rel: IGU  */
#line 342 "sintatico2.y"
          { (yyval.node) = novoNo(N_EXPR_OP_REL, strdup(".IGU."), NULL, NULL, NULL); }
#line 1616 "sintatico2.tab.c"
    break;

  case 59: /* op_rel: DIF  */
#line 343 "sintatico2.y"
          { (yyval.node) = novoNo(N_EXPR_OP_REL, strdup(".DIF."), NULL, NULL, NULL); }
#line 1622 "sintatico2.tab.c"
    break;


#line 1626 "sintatico2.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 346 "sintatico2.y"

