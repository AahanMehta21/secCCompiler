#include "decl.h"
#include "data.h"

int parse_type(int token) {
  switch (token) {
    case T_CHAR:
      return (P_CHAR);
    case T_INT:
      return (P_INT);
    case T_VOID:
      return (P_VOID);
  }
  fatald("Illegal type, token", token);
}

void var_declaration(void) {
  int id, type;
  type = parse_type(Token.token);
  scan(&Token);
  ident();
  id = addglobal(Text, type, S_VARIABLE);
  genglobalsym(id);

  semi();
}

struct ASTnode * function_declaration(void) {
  struct ASTnode *tree;
  int func_id;
  // no return data type just yet
  match(T_VOID, "void");
  ident();
  func_id = addglobal(Text, P_VOID, S_FUNCTION);
  lparen();
  // no arguments just yet
  rparen();

  tree = compound_statement();
  
  return (makeunary(A_FUNCTION, P_VOID, tree, func_id));
}

