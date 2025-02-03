#include "decl.h"
#include "data.h"

static int nglobal = 0;

// returns position of global variable in the table
int findglobal(char *s) {
  int i;
  for (i = 0; i < nglobal; i++) {
    if (*s == *global_vars_table[i].name && !strcmp(s, global_vars_table[i].name)) {
      return i;
    }
  }
  return -1;
}

// get position of next slot available and if not, die
static int newglobal(void) {
  int p;
  if ((p = nglobal++) >= NSYMBOLS)
    fatal("Global variable limit exceeded");
  return p;
}

// add a new symbol to the global variables table
int addglobal(char *name, int type, int stype) {
  int pos;
  if ((pos = findglobal(name)) != -1) {
    return pos;
  }
  pos = newglobal();
  global_vars_table[pos].name = strdup(name);
  global_vars_table[pos].type = type;
  global_vars_table[pos].stype = stype;
  return pos;
}
