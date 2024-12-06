#include "definitions.h"
#include "decl.h"
#include "data.h"

// generate assembly code for given AST tree
static int genAST(struct ASTnode *node) {
  int left_register, right_register;
  if (node->left)
    left_register = genAST(node->left);
  if (node->right)
    right_register = genAST(node->right);

    switch (node->operation) {
    case A_ADD:
      return (cgadd(left_register, right_register));
    case A_SUBTRACT:
      return (cgsub(left_register, right_register));
    case A_MULTIPLY:
      return (cgmul(left_register, right_register));
    case A_DIVIDE:
      return (cgdiv(left_register, right_register));
    case A_INTLIT:
      return (cgload(node->intvalue));
    default:
      fprintf(stderr, "Unknown AST operator %d\n", node->operation);
      exit(1);
  }
}

int generatecode(struct ASTnode *node) {
  int result_register;

  cgpreamble();
  result_register = genAST(node);
  cgprintint(result_register);
  cgpostamble();

  return 0;
}
