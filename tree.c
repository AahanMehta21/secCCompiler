/ builds AST trees

#include "definitions.h"
#include "data.h"
#include "decl.h"

struct ASTnode makenode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue) {
  struct ASTnode *node = NULL;
  node = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (node == NULL) {
    fprintf(stderr, "Unable to malloc in makenode()\n"#include "definitions.h"
    exit(1);
  }
  node->op = op;
  node->left = left;
  node->right = right;
  node->intvalue = intvalue;
  return node;
}

struct ASTnode makeleaf(int op, int intvalue) {
  return makenode(op, NULL, NULL, intvalue);
}

struct ASTnode makeunary(int op, struct ASTnode *left, int intvalue) {
  return makenode(op, left, NULL, intvalue);
}

