#include "definitions.h"

// scan.c
int scan(struct token *t);

// tree.c
struct ASTnode *makenode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *makeleaf(int op, int intvalue);
struct ASTnode *makeunary(int op, struct ASTnode *left, int intvalue);

// expr.c
struct ASTnode *binexpr(int ptp);

// gen.c
int interpretAST(struct ASTnode *n);
int genAST(struct ASTnode *node);
//int generatecode(struct ASTnode *n);
void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int reg);

//cg.c
void free_all_regs(void);
static int alloc_reg();
static void free_reg(int);
void cgpreamble();
void cgpostamble();
int cgload(int);
int cgadd(int, int);
int cgsub(int, int);
int cgmul(int, int);
int cgdiv(int, int);
void cgprintint(int);

// statement.c
void statements();

// misc.c
void match(int t, char *matcher);
void semi();
