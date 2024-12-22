#include "decl.h"
#include "data.h"
//#include "definitions.h"

void match(int t, char *matcher) {
  if (Token.token == t) {
    scan(&Token);
  } else {
    printf("%s expected on line %d\n", matcher, line);
    exit(1);
  }
}

void semi(void) {
  match(T_SEMI, ";");
}
