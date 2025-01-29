//#include "definitions.h"
#include "decl.h"
#include "data.h"

static struct ASTnode *single_statement(void);

static struct ASTnode * print_statement(void) {
  struct ASTnode *tree;
  int reg;
  // PRINT
  match(T_PRINT, "print");
  // parses the expression and generates expression tree
  tree = binexpr(0);
  // print sentence is added to expression tree
  tree = makeunary(A_PRINT, tree, 0);

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

  return (tree);
}

static struct ASTnode * while_statement(void) {
  struct ASTnode *condAST, *bodyAST;

  match(T_WHILE, "while");
  lparen();

  condAST = binexpr(0);
  if (condAST->operation < A_EQ || condAST->operation > A_GE) {
    fatal("Bad comparision operator");
  }
  rparen();

  bodyAST = compound_statement();

  return (makenode(A_WHILE, condAST, NULL, bodyAST, 0));
}

static struct ASTnode *for_statement(void) {
  struct ASTnode *condAST, *bodyAST;
  struct ASTnode *preopAST, *postopAST;
  struct ASTnode *tree;

  match(T_FOR, "for");
  lparen();

  preopAST = single_statement();
  semi();

  condAST = binexpr(0);
  if (condAST->operation < A_EQ || condAST->operation > A_GE) {
    fatal("Bad comparision operator");
  }
  semi();

  postopAST = single_statement();
  rparen();
  bodyAST = compound_statement();

  // for loop is treated as a disfigured while loop.

  tree = makenode(A_GLUE, bodyAST, NULL, postopAST, 0);
  tree = makenode(A_WHILE, condAST, NULL, tree, 0);
  return (makenode(A_GLUE, preopAST, NULL, tree, 0));
}

static struct ASTnode *if_statement(void) {
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

static struct ASTnode *single_statement(void) {
  switch(Token.token) {
    case T_PRINT:
      return (print_statement());
    case T_INT:
      var_declaration();
      return (NULL); // no tree generated
    case T_IDENT:
      return (assignment_statement());
    case T_IF:
      return (if_statement());
    case T_WHILE:
      return (while_statement());
    case T_FOR:
      return (for_statement());
    default:
      fatald("Syntax error, token", Token.token); 
  }
}

struct ASTnode * compound_statement(void) {
  struct ASTnode *left = NULL;
  struct ASTnode *tree;
  lbrace();
  while(1) {
   tree = single_statement();

  if (tree != NULL && (tree->operation == A_PRINT || tree->operation == A_ASSIGN)) {
    semi();
  }

   if (tree != NULL) {
      if (left == NULL) {
        left = tree;
      } else {
        left = makenode(A_GLUE, left, NULL, tree, 0);
      }
    }
    if (Token.token == T_RBRACE) {
      rbrace();
      return (left);
    }
  }
}
