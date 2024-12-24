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
int interpretAST(struct ASTnode *n, int reg);
int genAST(struct ASTnode *node, int reg);
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
void cgpostamble();
int cgloadint (int reg);
int cgadd(int reg1, int reg2);
int cgsub(int reg1, int reg2);
int cgmul(int reg1, int reg2);
int cgdiv(int reg1, int reg2);
void cgprintint(int reg);
int cgloadglobal(char *ident);
int cgstoreglobal(int reg, char *name);
void cgglobalsym(char *ident);

// statement.c
void statements(void);

// misc.c
void match(int t, char *matcher);
void semi(void);
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

