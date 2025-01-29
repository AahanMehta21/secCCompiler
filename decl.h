#include "definitions.h"

// scan.c
int scan(struct token *t);

// tree.c
struct ASTnode *makenode(int op, struct ASTnode *left, struct ASTnode *middle, struct ASTnode *right, int intvalue);
struct ASTnode *makeleaf(int op, int intvalue);
struct ASTnode *makeunary(int op, struct ASTnode *left, int intvalue);

// expr.c
struct ASTnode *binexpr(int ptp);

// gen.c
int genAST(struct ASTnode *node, int reg, int parentASTop);
//int generatecode(struct ASTnode *n);
void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int);
void genglobalsym(char *);

//cg.c
void free_all_regs(void);
static int alloc_reg(void);
static void free_reg(int reg);
void cgpreamble();
void cgfuncpreamble(char *funcname);
void cgfuncpostamble();
int cgloadint (int reg);
int cgadd(int reg1, int reg2);
int cgsub(int reg1, int reg2);
int cgmul(int reg1, int reg2);
int cgdiv(int reg1, int reg2);
void cgprintint(int reg);
int cgloadglobal(char *ident);
int cgstoreglobal(int reg, char *name);
void cgglobalsym(char *ident);
int cgcompare_and_set(int ASTop, int reg1, int reg2);
int cgcompare_and_jump(int ASTop, int reg1, int reg2, int label);
void cglabel(int label);
void cgjump(int label);

// statement.c
struct ASTnode *compound_statement(void);

// misc.c
void match(int t, char *matcher);
void semi(void);
void lbrace(void);
void rbrace(void);
void lparen(void);
void rparen(void);
void ident(void);
void fatal(char *s);
void fatals(char *s1, char *s2);
void fatald(char *s, int d);
void fatalc(char *s, int c);

// sym.c
int findglobal(char *s);
int addglobal(char *name);

// decl.c
void var_declaration(void);
struct ASTnode *function_declaration(void);
