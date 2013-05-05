#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

struct tree_t
{
  ACTION action;
  TREE   sub[3];
};

static
int to_index(char c)
{
  switch (c)
  {
  case ' ':  return 0;
  case '\t': return 1;
  case '\n': return 2;
  }
#ifdef DEBUG
  fprintf(stderr, "Illegal character '%c'\n", c);
  exit(EXIT_FAILURE);
#endif
  return -1;
}

TREE tree_new(void)
{
  TREE tree = (TREE)calloc(sizeof(*tree), 1);
  return tree;
}

TREE tree_delete(TREE tree)
{
  if (tree)
  {
    tree_delete(tree->sub[0]);
    tree_delete(tree->sub[1]);
    tree_delete(tree->sub[2]);
    free(tree);
  }
}

