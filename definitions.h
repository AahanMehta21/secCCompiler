#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define NOREG -1 // indicates no register returned by ASTtree

// token structure
struct token {
  int token;
  int intvalue;
};


// tokens:
enum {
  T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH,
  //0     1         2        3       4
  T_EQ, T_NE, T_LT, T_GT, T_LE, T_GE,
  //5    6      7     8     9     10
  T_INTLIT, T_SEMI, T_ASSIGN, T_IDENT,
  // 11       12       13         14
  T_LBRACE, T_RBRACE, T_LPAREN, T_RPAREN,
  // 15        16        17        18
  T_PRINT, T_INT, T_IF, T_ELSE
  // 19      20    21     22
};

// AST nodes:
enum {
  A_ADD=1, A_SUBTRACT, A_MULTIPLY, A_DIVIDE,
  //  1        2          3          4
  A_EQ, A_NE, A_LT, A_GT, A_LE, A_GE,
  // 5    6    7    8       9    10
  A_INTLIT, A_IDENT, A_LVIDENT, A_ASSIGN, A_PRINT, A_GLUE, A_IF
  // 11        12        13          14      15     16      17
};

struct ASTnode {
  int operation;
  struct ASTnode *left;
  struct ASTnode *middle;
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
