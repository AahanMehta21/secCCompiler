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

void ident(void) {
  match(T_IDENT, "identifier");
}

void fatal(char *s) {
  fprintf(stderr, "%s on line %d\n", s, line); exit(1);
}

void fatals(char *s1, char *s2) {
  fprintf(stderr, "%s:%s on line %d\n", s1, s2, line); exit(1);
}

void fatald(char *s, int d) {
  fprintf(stderr, "%s:%d on line %d\n", s, d, line); exit(1);
}

void fatalc(char *s, int c) {
  fprintf(stderr, "%s:%c on line %d\n", s, c, line); exit(1);
}

