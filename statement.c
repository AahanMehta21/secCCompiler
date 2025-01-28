//#include "definitions.h"
#include "decl.h"
#include "data.h"

static struct ASTnode * print_statement(void) {
  struct ASTnode *tree;
  int reg;
  // PRINT
  match(T_PRINT, "print");
  // parses the expression and generates expression tree
  tree = binexpr(0);
  // print sentence is added to expression tree
  tree = makeunary(A_PRINT, tree, 0);
  // ; 
  semi();
  return (tree);
}

static struct ASTnode * assignment_statement(void) {
  struct ASTnode *left, *right, *tree;
  int id;
  // ensure identifier exists in source code
  ident();
  id = findglobal(Text);
  if (id == -1) {
    fatals("Undeclared variable", Text);
  }
  right = makeleaf(A_LVIDENT, id);
  // =
  match(T_ASSIGN, "=");
  // EXPRESSION
  left = binexpr(0);
  tree = makenode(A_ASSIGN, left, NULL, right, 0);
  // ;
  semi();
  return (tree);
}

struct ASTnode * if_statement(void) {
  struct ASTnode *condAST = NULL;
  struct ASTnode *trueAST = NULL;
  struct ASTnode *falseAST = NULL;
  match(T_IF, "if");
  lparen();
  condAST = binexpr(0);
  // checking if the operator is a comparision operator (using enum range)
  if (condAST->operation < A_EQ || condAST->operation > A_GE)
    fatal("Bad comparison operator");
  rparen();
  trueAST = compound_statement();
  if (Token.token == T_ELSE) {
    scan(&Token);
    falseAST = compound_statement();
  }
  return (makenode(A_IF, condAST, trueAST, falseAST, 0));
}

struct ASTnode * compound_statement(void) {
  struct ASTnode *left = NULL;
  struct ASTnode *tree;
  lbrace();
  while(1) {
    switch(Token.token) {
      case T_PRINT:
        tree = print_statement();
        break;
      case T_INT:
        var_declaration();
        tree = NULL; // no tree generated
        break;
      case T_IDENT:
        tree = assignment_statement();
        break;
      case T_IF:
        tree = if_statement();
        break;
      case T_RBRACE:
        rbrace();
        return(left);
      default:
        fatald("Syntax error, token", Token.token);
    }
    if (tree) {
      if (left == NULL) {
        left = tree;
      } else {
        left = makenode(A_GLUE, left, NULL, tree, 0);
      }
    }
  }
}
