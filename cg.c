//#include "definitions.h"
#include "data.h"
#include "decl.h"

static int freereg[4];
static char *regStk[4]= { "%r8", "%r9", "%r10", "%r11" };
static char *byteRegStk[4] = {"%r8b", "%r9b", "%r10b", "%r11b"};

// set all registers as available
void free_all_regs() {
  freereg[0] = 1;
  freereg[1] = 1;
  freereg[2] = 1;
  freereg[3] = 1;
}

// allocates a free register. if no free registers, end program
static int alloc_reg() {
  for (int i = 0; i < 4; i++) {
    if (freereg[i] == 1) {
      freereg[i]= 0;
      return(i);
    }
  }
  fprintf(stderr, "Out of registers!\n");
  exit(1);
}

// free a register
static void free_reg(int reg) {
  if (freereg[reg] != 0) {
    fprintf(stderr, "Error trying to free register %d, %s\n", reg, regStk[reg]);
    exit(1);
  }
  freereg[reg] = 1;
}

  // Print out the assembly preamble
void cgpreamble()
{
  free_all_regs();
  fputs(
	"\t.text\n"
	".LC0:\n"
	"\t.string \"%d\\n\"\n"
  "\t.globl printint\n"
	"printint:\n"
	"\tpushq %rbp\n"
	"\tmovq %rsp, %rbp\n"
	"\tsubq $16, %rsp\n"
	"\tmovl %edi, -4(%rbp)\n"
	"\tmovl -4(%rbp), %eax\n"
	"\tmovl %eax, %esi\n"
	"\tleaq	.LC0(%rip), %rdi\n"
	"\tmovl	$0, %eax\n"
	"\tcall	printf@PLT\n"
	"\tnop\n"
	"\tleave\n"
	"\tret\n"
	"\n",
  fasm);
}

// print function preamble
void cgfuncpreamble(char *funcname) {
  fprintf(fasm,
	  "\t.text\n"
	  "\t.globl %s\n"
	  "\t.type\t%s, @function\n"
	  "%s:\n" 
    "\tpushq\t%%rbp\n"
	  "\tmovq\t%%rsp, %%rbp\n", funcname, funcname, funcname);
}

// prints postable
void cgfuncpostamble()
{
  fputs(
	"\txorl %eax, %eax\n"
	"\tpopq %rbp\n"
	"\tret\n",
  fasm);
}

// load an integer value into next available register and return register id (number)
int cgloadint(int value) {
    int curr_reg = alloc_reg();
    fprintf(fasm, "\tmovq $%d, %s\n", value, regStk[curr_reg]);
    return curr_reg;
}

// load global variable value into next available register
int cgloadglobal(char *name) {
  int reg = alloc_reg();
  fprintf(fasm, "\tmovq %s(%%rip), %s\n", name, regStk[reg]);
  return (reg);
}

// store a register's value into global variable specified
int cgstoreglobal(int reg, char *name) {
  fprintf(fasm, "\tmovq %s, %s(%%rip)\n", regStk[reg], name);
  return (reg);
}

// declare global variable
void cgglobalsym(char *sym) {
  fprintf(fasm, "\t.comm\t%s,8,8\n", sym);
}

// add two given registers, free one register and store the result in the other register and return its id
int cgadd(int reg1, int reg2) {
  fprintf(fasm, "\taddq %s, %s\n", regStk[reg1], regStk[reg2]);
  free_reg(reg1);
  return (reg2);
}

// same as cgadd but subtract
int cgsub(int reg1, int reg2) {
  fprintf(fasm, "\tsubq %s, %s\n", regStk[reg2], regStk[reg1]);
  free_reg(reg2);
  return (reg1);
}

// same as cgadd but multiply
int cgmul(int reg1, int reg2) {
  fprintf(fasm, "\timulq %s, %s\n", regStk[reg1], regStk[reg2]);
  free_reg(reg1);
  return (reg2);
}

// same as cgadd but divide
int cgdiv(int reg1, int reg2) {
  fprintf(fasm, "\tmovq %s, %%rax\n", regStk[reg1]);
  fprintf(fasm, "\tcqo;\n");
  fprintf(fasm, "\tidivq %s\n", regStk[reg2]);
  fprintf(fasm, "\tmovq %%rax, %s\n", regStk[reg1]);
  free_reg(reg2);
  return (reg1);
}

//call printint() with the current integer
void cgprintint(int curr_reg) {
  fprintf(fasm, "\tmovq %s, %%rdi\n", regStk[curr_reg]);
  fprintf(fasm, "\tcall printint\n");
  free_reg(curr_reg);
}

//                             A_EQ,    A_NE,   A_LT,   A_GT,    A_LE,   A_GE
static char *cmplist[] =    { "sete", "setne", "setl", "setg", "setle", "setge" };
static char *invcmplist[] = { "jne",  "je",    "jge",  "jle",  "jg",    "jl" };

int cgcompare_and_set (int ASTop, int reg1, int reg2) {
  if (ASTop < A_EQ || ASTop > A_GE) {
    fatal("Bad ASTop in cgcompare_and_set()");
  }

  fprintf(fasm, "\tcmpq %s, %s\n", regStk[reg2], regStk[reg1]);
  fprintf(fasm, "\t%s %s\n", cmplist[ASTop - A_EQ], byteRegStk[reg2]);
  fprintf(fasm, "\tmovzbq %s, %s\n", byteRegStk[reg2], regStk[reg2]);
  free_reg(reg1);
  return (reg2);
}

void cglabel(int label) {
  fprintf(fasm, "L%d:\n", label);
}

void cgjump(int label) {
  fprintf(fasm, "\tjmp L%d\n", label);
}

int cgcompare_and_jump (int ASTop, int reg1, int reg2, int label) {
  if (ASTop < A_EQ || ASTop > A_GE) {
    fatal("Bad ASTop in cgcompare_and_jump()");
  }
  fprintf(fasm, "\tcmpq %s, %s\n", regStk[reg2], regStk[reg1]);
  fprintf(fasm, "\%s L%d\n", invcmplist[ASTop - A_EQ], label);
  free_all_regs();
  return (NOREG);
}
