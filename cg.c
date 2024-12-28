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
	"\n"
	"\t.globl main\n"
	"\t.type main, @function\n"
	"main:\n"
	"\tpushq %rbp\n"
	"\tmovq %rsp, %rbp\n",
  fasm);
}

// prints postable
void cgpostamble()
{
  fputs(
	"\txorl %eax, %eax\n"
	"\tpopq %rbp\n"
	"\tret\n",
  fasm);
  free_all_regs();
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

static int cgcompare(int reg1, int reg2, char *how) {
  fprintf(fasm, "\tcmpq %s, %s\n", regStk[reg2], regStk[reg1]);
  fprintf(fasm, "\tmovq $0, %s\n", regStk[reg2]);
  fprintf(fasm, "\t%s %s\n", how, byteRegStk[reg2]);
  free_reg(reg1);
  return (reg2);
}

int cgequal(int r1, int r2) { return(cgcompare(r1, r2, "sete")); }
int cgnotequal(int r1, int r2) { return(cgcompare(r1, r2, "setne")); }
int cglessthan(int r1, int r2) { return(cgcompare(r1, r2, "setl")); }
int cggreaterthan(int r1, int r2) { return(cgcompare(r1, r2, "setg")); }
int cglessequal(int r1, int r2) { return(cgcompare(r1, r2, "setle")); }
int cggreaterequal(int r1, int r2) { return(cgcompare(r1, r2, "setge")); }

