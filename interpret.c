//#include "definitions.h"
#include "data.h"
#include "decl.h"

static char *ASTop[] = { "+", "-", "*", "/" };

// interpret AST tree and return result
int interpretAST(struct ASTnode *node) {
  int leftval, rightval;

  if (node->left) {
    leftval = interpretAST(node->left);
  }
  if (node->right) {
    rightval = interpretAST(node->right);
  }
  /* this was for debugging purposes it prints as it processes arithmetic ops
  if (node->operation == A_INTLIT) {
    printf("int %d\n", node->intvalue);
  } else {
    printf("%d %s %d\n", leftval, ASTop[node->operation], rightval);
  } */
  switch (node->operation) {
    case A_ADD:
      return (leftval + rightval);
    case A_SUBTRACT:
      return (leftval - rightval);
    case A_MULTIPLY:
      return (leftval * rightval);
    case A_DIVIDE:
      return (leftval / rightval);
    case A_INTLIT:
      return (node->intvalue);
    default:
      fprintf(stderr, "Unknown AST operator %d at line %d\n", node->operation, line);
      exit(1);
  }
}
