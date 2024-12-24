//#include "definitions.h"
#include "decl.h"
#include "data.h"

void print_statement(void) {
  struct ASTnode *tree;
  int reg;
  // PRINT
  match(T_PRINT, "print");
  // EXPRESSION
  tree = binexpr(0);
  reg = genAST(tree, -1);
  genprintint(reg);
  genfreeregs();
  // ; 
  semi();
}

void assignment_statement(void) {
  struct ASTnode *left, *right, *tree;
  int id;
  // IDENTIFIER
  ident();
  id = findglobal(Text);
  if (id == -1) {
    fatals("Undeclared variable", Text);
  }
  right = makeleaf(A_LVIDENT, id);
  // =
  match(T_EQUALS, "=");
  // EXPRESSION
  left = binexpr(0);
  tree = makenode(A_ASSIGN, left, right, 0);
  genAST(tree, -1);
  genfreeregs();
  // ;
  semi();
}

void statements(void) {
  while(1) {
    switch(Token.token) {
      case T_PRINT:
        print_statement();
        break;
      case T_INT:
        var_declaration();
        break;
      case T_IDENT:
        assignment_statement();
        break;
      case T_EOF:
        return;
      default:
        fatald("Syntax error, token", Token.token);
    }
  }
}
