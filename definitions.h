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
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INTLIT, T_SEMI, T_PRINT
};

// AST nodes:
enum {
  A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
};

struct ASTnode {
  int operation;
  struct ASTnode *left;
  struct ASTnode *right;
  int intvalue; // if its a T_INTLIT
};
