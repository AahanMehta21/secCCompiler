#include<stdio.h>

#ifndef extern_
  #define extern_ extern
#endif

extern_ int line;
extern_ int Putback;
extern_ FILE *in_file;
struct token Token;
