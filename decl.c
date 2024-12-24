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
