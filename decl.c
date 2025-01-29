#include "decl.h"
#include "data.h"

void var_declaration(void) {
  // INT WORD {
  match(T_INT, "int");
  ident();
  addglobal(Text);
  genglobalsym(Text);
  // } ;
  semi();
}

struct ASTnode * function_declaration(void) {
  struct ASTnode *tree;
  int func_id;
  // no return data type just yet
  match(T_VOID, "void");
  ident();
  func_id = addglobal(Text);
  lparen();
  // no arguments just yet
  rparen();

  tree = compound_statement();
  
  return (makeunary(A_FUNCTION, tree, func_id));
}

