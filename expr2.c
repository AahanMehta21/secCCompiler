/*
  this is a Recursive Descent Parser for operator precendence but is very inefficient
  because of the constant recursive calls and there are a lot of function calls that
  need to be made to reach the highest level of precedence
*/

#include "definitions.h"
#include "data.h"
#include "decl.h"

struct ASTnode *additive_expr(void);
struct ASTnode *multiplicative_expr(void);

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

struct ASTnode* binexpr(int nothing) {
  return additive_expr();
}

// returns an AST tree whose root is + or -
struct ASTnode *additive_expr(void) {
  struct ASTnode *left, *right;
  int tokentype;

  // get the left subtree of higher precedence
  left = multiplicative_expr();

  tokentype = Token.token;
  // if no more tokens return left
  if (tokentype == T_EOF)
    return (left);

  while (1) {
    // fetch the next token
    scan(&Token);
    right = multiplicative_expr();
    left = makenode(arithmetic_op(tokentype), left, right, 0);
    tokentype = Token.token;
    if (tokentype == T_EOF) {
      break;
    }
  }
  return left;
}

struct ASTnode* multiplicative_expr() {
  struct ASTnode *left, *right;
  int tokentype;

  // get integer literal on left and read in next token
  left = primary();

  tokentype = Token.token;
  if (tokentype == T_EOF) {
    return left;
  }
  
  while ((tokentype == T_STAR) || (tokentype == T_SLASH)) {
    scan(&Token);
    right = primary();

    left =  makenode(arithmetic_op(tokentype), left, right, 0);

    tokentype = Token.token;
    if (tokentype == T_EOF) {
      break;
    }
  }
  return left;
}
