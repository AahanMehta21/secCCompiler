/*
  Pratt parsing for operator precedence
*/

//#include "definitions.h"
#include "decl.h"
#include "data.h"

static int opPrec[] = {0,   1, 1, 2, 2, 0};
//                      EOF  +  -  *  /  INT_LIT

static int op_precedence(int);

// return an ASTnode representation of a primary factor
static struct ASTnode *primary() {
  struct ASTnode *node;
  int id;
  // make AST leaf node if INTLIT else error
  switch (Token.token) {
    case T_INTLIT:
      node = makeleaf(A_INTLIT, Token.intvalue);
      break;
    case T_IDENT:
      id = findglobal(Text);
      if (id == -1) {
        fatals("Unknown variable", Text);
      }
      node = makeleaf(A_IDENT, id);
      break;
    default:
      fatald("Syntax error, token", Token.token);
  }
  scan(&Token);
  return (node);
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

// generate an ASTtree
// param: int ptp: previous token's precedencee
struct ASTnode* binexpr(int ptp) {
  int tokentype;
  struct ASTnode *left, *right;

  // load integer literal into left pointer, and fetch next token
  left = primary();
  tokentype = Token.token;
//  printf("token sent to arith_op: %c, %d\n", Token.intvalue, Token.token);
  // no tokens left then return this node
  if (Token.token == T_SEMI) {
    return left;
  }
  while (op_precedence(tokentype) > ptp) {
    scan(&Token);
    // recursively call binexpr with precedence of current token to build AST tree
    right = binexpr(opPrec[tokentype]);
    left = makenode(arithmetic_op(tokentype), left, right, 0);
    tokentype = Token.token;
    if (tokentype == T_SEMI) {
      return left;
    }
  }
  return left;
}

// enforces syntax
static int op_precedence(int tokentype) {
  int prec = opPrec[tokentype];
  if (prec == 0) {
    fprintf(stderr, "syntax error on line %d, token %d\n", line, tokentype);
    exit(1);
  }
  return prec;
}
