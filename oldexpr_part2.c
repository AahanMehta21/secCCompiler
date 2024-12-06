#include "definitions.h"
#include "data.h"
#include "decl.h"

// return an ASTnode representation of a primary factor
static struct ASTnode *primary() {
  struct ASTnode *node;
  // make AST leaf node if INTLIT else error
  switch (Token.token) {
    case T_INTLIT:
//      printf("current token: %c, %d\n", Token.intvalue, Token.token);
      node = makeleaf(A_INTLIT, Token.intvalue);
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
      fprintf(stderr, "unknown token %d in arithmetic_op() on line %d\n", token, line);
      exit(1);
  }
}

struct ASTnode* binexpr() {
  int nodetype;
  struct ASTnode *node, *left, *right;

  // load integer literal into left pointer, and fetch next token
  left = primary();
//  printf("token sent to arith_op: %c, %d\n", Token.intvalue, Token.token);
  // no tokens left then return this node
  if (Token.token == T_EOF) {
    return left;
  }

  nodetype = arithmetic_op(Token.token);

  scan(&Token);

  right = binexpr();

  node = makenode(nodetype, left, right, 0);

  return node;
}
