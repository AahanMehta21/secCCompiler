int scan(struct token *t);
struct ASTnode *makenode(int op, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *makeleaf(int op, int intvalue);
struct ASTnode *makeunary(int op, struct ASTnode *left, int intvalue);
struct ASTnode *binexpr(int ptp);
int interpretAST(struct ASTnode *n);

