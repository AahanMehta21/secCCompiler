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
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMI, T_EQUALS, T_IDENT,
  T_PRINT, T_INT
};

// AST nodes:
enum {
  A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT,
  A_IDENT, A_LVIDENT, A_ASSIGN
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
