#include "definitions.h"
#include "decl.h"
#define extern_
#include "data.h"
#undef extern_
#include<errno.h>

// initialize vars from data.h
static void init() {
  line = 1;
  Putback = '\n';
}

// prints out error
static void usage(char *prog) {
  fprintf(stderr, "Usage %s infile\n", prog);
  exit(1);
}

char *tokstr[] = {"+", "-", "*", "/", "intlit"};

/* are we not using this?
// scan tokens and print details of token
static void scanfile() {
  struct token T;
  while (scan(&T)) {
    printf("Token %s", tokstr[T.token]);
    if (T.token == T_INTLIT)
      printf(", value %d",  T.intvalue);
    printf("\n");
  }
}
*/

void main(int argc, char *argv[]) {
  struct ASTnode *node;

  if (argc != 2) {
    usage(argv[0]);
  }

  init();

  if ((in_file = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
    exit(1);
  }

  if ((fasm = fopen("out.s", "w")) == NULL) {
    fprintf(stderr, "Unable to create out.s: %s\n", strerror(errno));
    exit(1);
  }
  //scanfile(); are we not using this?

  scan(&Token);
  node = binexpr(0);
  printf("%d\n", interpretAST(node));
  generatecode(node);

  fclose(fasm);
  fasm = NULL;
  exit(0);
}
