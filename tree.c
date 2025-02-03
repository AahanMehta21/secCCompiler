// builds AST trees

//#include "definitions.h"
#include "decl.h"
#include "data.h"

struct ASTnode* makenode(int operation, int type, struct ASTnode *left,struct ASTnode *middle, struct ASTnode *right, int intvalue) {
  struct ASTnode *node = NULL;
  node = (struct ASTnode *) malloc(sizeof(struct ASTnode));
  if (node == NULL) {
    fprintf(stderr, "Unable to malloc in makenode()\n");
    exit(1);
  }
  node->operation = operation;
  node->type = type;
  node->left = left;
  node->middle = middle;
  node->right = right;
  node->v.intvalue = intvalue;
  return node;
}

struct ASTnode* makeleaf(int op, int type,  int intvalue) {
  return makenode(op, type, NULL, NULL, NULL, intvalue);
}

struct ASTnode* makeunary(int op, int type, struct ASTnode *left, int intvalue) {
  return makenode(op, type, left, NULL, NULL, intvalue);
}

