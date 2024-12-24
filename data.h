#include<stdio.h>

#ifndef extern_
  #define extern_ extern
#endif

#define TEXTLEN 512
#define NSYMBOLS 1024

// variable symbol table
struct symtable {
  char *name; // variable name
};

extern_ int line;
extern_ int Putback; 
extern_ FILE *in_file; // input file
extern_ FILE *fasm; // output file
extern_ struct token Token; // last token scanned
extern_ char Text[TEXTLEN + 1]; // last identifier scanned
extern_ struct symtable global_vars_table[NSYMBOLS];
