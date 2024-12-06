int scan(struct token *t);
struct ASTnode *makenode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *makeleaf(int op, int intvalue);
struct ASTnode *makeunary(int op, struct ASTnode *left, int intvalue);
struct ASTnode *binexpr(int ptp);
int interpretAST(struct ASTnode *n);
int generatecode(struct ASTnode *n);

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

