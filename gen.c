//#include "definitions.h"
#include "decl.h"
#include "data.h"

// generate assembly code for given AST tree
int genAST(struct ASTnode *node, int reg) {
  int left_register, right_register;
  if (node->left)
    left_register = genAST(node->left, -1);
  if (node->right)
    right_register = genAST(node->right, left_register);

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
      return (cgloadint(node->v.intvalue));
    case A_IDENT:
      return (cgloadglobal(global_vars_table[node->v.id].name));
    case A_LVIDENT:
      return (cgstoreglobal(reg, global_vars_table[node->v.id].name));
    case A_EQ:
      return (cgequal(left_register, right_register));
    case A_NE:
      return (cgnotequal(left_register, right_register));
    case A_LT:
      return (cglessthan(left_register, right_register));
    case A_GT:
      return (cggreaterthan(left_register, right_register));
    case A_LE:
      return (cglessequal(left_register, right_register));
    case A_GE:
      return (cggreaterequal(left_register, right_register));
    case A_ASSIGN:
      return right_register;
    default:
      fatald("Unknown AST operator", node->operation);
      exit(1);
  }
}

void genpreamble(void) {
  cgpreamble();
}
void genpostamble(void) {
  cgpostamble();
}
void genfreeregs(void) {
  free_all_regs();
}
void genprintint(int reg) {
  cgprintint(reg);
}
void genglobalsym(char *s) {
  cgglobalsym(s);
}

/*
int generatecode(struct ASTnode *node) {
  int result_register;

  cgpreamble();
  result_register = genAST(node);
  cgprintint(result_register);
  cgpostamble();

  return 0;
}*/
