#include "data.h"
#include "definitions.h"

static int chrpos(const char *s, int ch) {
  char *substr = strchr(s, ch);
  return (substr == NULL) ? -1 : substr -s;
}

//gets the next character from the in_file
static int next() {
  int ch;
  if (Putback) {
    ch = Putback;
    Putback = 0;
    return ch;
  }
  ch = fgetc(in_file);
  if (ch == '\n') {
    line++;
  }
  return ch;
}

// puts back unwanted character
static void putback(int ch) {
  Putback = ch;
}

// skips to next non whitespace character
static int skip() {
  int ch;
  ch = next();
  while(isspace(ch)) {
    ch = next();
  }
  return ch;
}

// scans the integer literal and returns it
int scanint(int ch) {
  int int_val;
  int literal_val = 0;

  // Convert each character into an int value
  while ((int_val = chrpos("0123456789", ch)) >= 0) {
    literal_val = literal_val * 10 + int_val;
    ch = next();
  }

  // non-integer character, put it back.
  putback(ch);
  return literal_val;
}

// scans and returns next token found in the input
// 0: no token found
// 1: token found
int scan(struct token *t) {
  //skip to next non whitespace character
  int ch = skip();
  //printf("scanned: %c, %d\n", ch, ch);

  // determine token type:
  switch (ch) {
    case EOF:
      t->token = T_EOF;
      return 0;
    case '+':
      t->token = T_PLUS;
      break;
    case '-':
      t->token = T_MINUS;
      break;
    case '*':
      t->token = T_STAR;
      break;
    case '/':
      t->token = T_SLASH;
      break;
    default:
      // if it is a digit, then its an integer literal, we scan and store the integer value
      if (isdigit(ch)) {
          t->intvalue = scanint(ch);
          t->token = T_INTLIT;
          break;
      }
      // else unrecognized character:
      printf("Unrecognised character %c on line %d\n", ch, line);
      exit(1);
  } 
  return 1;
}


