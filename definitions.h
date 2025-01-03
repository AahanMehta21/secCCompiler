#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

// token structure
struct token {
  int token;
  int intvalue;
};


// tokens:
enum {
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH,
  T_EQ, T_NE, T_LT, T_GT, T_LE, T_GE,
  T_INTLIT, T_SEMI, T_ASSIGN, T_IDENT,
  T_LBRACE, T_RBRACE, T_LPAREN, T_RPAREN,
  T_PRINT, T_INT, T_IF, T_ELSE
};

// AST nodes:
enum {
  A_ADD=1, A_SUBTRACT, A_MULTIPLY, A_DIVIDE,
  A_EQ, A_NE, A_LT, A_GT, A_LE, A_GE,
  A_INTLIT, A_IDENT, A_LVIDENT, A_ASSIGN, A_PRINT, A_GLUE, A_IF
};

struct ASTnode {
  int operation;
  struct ASTnode *left;
  struct ASTnode *right;
  union {
    int intvalue; // if its a T_INTLIT integer value
    int id; // for A_IDENT, the number in the symbol table
  } v;
};

// variable symbol table defined in data.h cuz it wasnt working otherwise
/* struct symtable {
  char *name; // variable name
}; */
