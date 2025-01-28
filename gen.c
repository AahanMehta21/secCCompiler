//#include "definitions.h"
#include "decl.h"
#include "data.h"

static int label(void) {
  // static variable so it holds its value across calls
  static int id = 1;
  return (id++);
}

static int genIFAST(struct ASTnode *node) {
  int Lfalse, Lend;

  Lfalse = label();
  // if there is a false, then node->right exists and then Lend is the end, else Lfalse is the end of the if block
  if (node->right) {
    Lend = label();
  }
  // generate the condition AST
  genAST(node->left, Lfalse, node->operation);
  genfreeregs();

  // generate the true compound statement
  genAST(node->middle, NOREG, node->operation);
  genfreeregs();

  // if there is an else, jump to end after parsing if compound
  if (node->right) {
    cgjump(Lend);
  }
  cglabel(Lfalse);

  // generate false compound statement
  if (node->right) {
    genAST(node->right, NOREG, node->operation);
    genfreeregs();
    cglabel(Lend);
  }

  return (NOREG);
}

// generate assembly code for given AST tree
int genAST(struct ASTnode *node, int reg, int parentASTop) {
  int left_register, right_register;
  switch (node->operation) {
    case A_IF:
      return (genIFAST(node));
    case A_GLUE:
      genAST(node->left, NOREG, node->operation);
      genfreeregs();
      genAST(node->right, NOREG, node->operation);
      genfreeregs();
      return (NOREG);
  }

  if (node->left)
    left_register = genAST(node->left, NOREG, node->operation);
    if (node->right)
    right_register = genAST(node->right, left_register, node->operation);

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
    case A_NE:
    case A_LT:
    case A_GT:
    case A_LE:
    case A_GE:
      if (parentASTop == A_IF) {
        return cgcompare_and_jump(node->operation, left_register, right_register, reg);
      } else {
        return cgcompare_and_set(node->operation, left_register, right_register);
      }
    case A_ASSIGN:
      return right_register;
    case A_PRINT:
      genprintint(left_register);
      genfreeregs();
      return (NOREG);
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
