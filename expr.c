/*
  Pratt parsing for operator precedence
*/

//#include "definitions.h"
#include "decl.h"
#include "data.h"

static int opPrec[] = {
  0, 1, 1,        // T_EOF, T_PLUS, T_MINUS
  2, 2,           // T_STAR, T_SLASH
  3, 3,           // T_EQ, T_NE
  4, 4, 4, 4    // T_LT, T_GT, T_LE, T_GE
};

static int op_precedence(int);

// return an ASTnode representation of a primary factor
static struct ASTnode *primary() {
  struct ASTnode *node;
  int id;
  // make AST leaf node if INTLIT else error
  switch (Token.token) {
    case T_INTLIT:
      if ((Token.intvalue) >= 0 && (Token.intvalue < 256)) {
        node = makeleaf(A_INTLIT, P_CHAR, Token.intvalue);
      }
      else {
        node = makeleaf(A_INTLIT, P_INT, Token.intvalue);
      }
      break;
    case T_IDENT:
      id = findglobal(Text);
      if (id == -1) {
        fatals("Unknown variable", Text);
      }
      node = makeleaf(A_IDENT, global_vars_table[id].type, id);
      break;
    default:
      fatald("Syntax error, token", Token.token);
  }
  scan(&Token);
  return (node);
}

// Convert a token into an AST operation.
int arithmetic_op(int token) {
  if (token > T_EOF && token < T_INTLIT)
    return (token);
  fatald("Syntax error, token", token);
}

// generate an ASTtree
// param: int ptp: previous token's precedencee
struct ASTnode* binexpr(int ptp) {
  int tokentype, lefttype, righttype;
  struct ASTnode *left, *right;

  // load integer literal into left pointer, and fetch next token
  left = primary();
  tokentype = Token.token;
//  printf("token sent to arith_op: %c, %d\n", Token.intvalue, Token.token);
  // no tokens left then return this node
  if (Token.token == T_SEMI || Token.token == T_RPAREN) {
    return left;
  }
  while (op_precedence(tokentype) > ptp) {
    scan(&Token);
    // recursively call binexpr with precedence of current token to build AST tree
    right = binexpr(opPrec[tokentype]);
    lefttype = left->type;
    righttype = right->type;
    if (!type_compatible(&lefttype, &righttype, 0)) {
      fatal("Incompatible types");
    }
    if (lefttype) {
      left = makeunary(lefttype, right->type, left, 0);
    }
    if (righttype) {
      right = makeunary(righttype, left->type, right, 0);
    }
    left = makenode(arithmetic_op(tokentype), left->type, left, NULL, right, 0);
    tokentype = Token.token;
    if (tokentype == T_SEMI || tokentype == T_RPAREN) {
      return (left);
    }
  }
  return (left);
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
