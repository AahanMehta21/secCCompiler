#include "definitions.h"
#include "data.h"
#include "decl.h"

// return an ASTnode representation of a primary factor
tatic struct ASTnode *primary(void) {
  struct ASTnode *node;
  // make AST leaf node if INTLIT else error
  switch (Token.token) {
    case T_INTLIT:
      node = mkastleaf(A_INTLIT, Token.intvalue);
      scan(&Token);
      return node;
    default:
      fprintf(stderr, "syntax error on line %d\n", line);
      exit(1);
  }
}

// Convert a token into an AST operation.
int arithmetic_op(int token) {
  switch (token) {
    case T_PLUS:
      return (A_ADD);
    case T_MINUS:
      return (A_SUBTRACT);
    case T_STAR:
      return (A_MULTIPLY);
    case T_SLASH:
      return (A_DIVIDE);
    default:
      fprintf(stderr, "unknown token in arithmetic_op() on line %d\n", line);
      exit(1);
  }
}
