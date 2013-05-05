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
  case ' ':  case 'S': return 0;
  case '\t': case 'T': return 1;
  case '\n': case 'L': return 2;
  }
#ifdef DEBUG
  fprintf(stderr, "ERROR: illegal character '%c'\n", c);
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

TREE tree_get_subtree(TREE tree, char sp)
{
  int i = to_index(sp);
  if (i != -1)
  {
    return tree->sub[i];
  }
  return NULL;
}

int tree_has_action(TREE tree)
{
  return tree->action != NULL;
}

void tree_do_action(TREE tree)
{
#ifdef DEBUG
  if (!tree->action)
  {
    fprintf(stderr, "ERROR: action is not set\n");
    exit(EXIT_FAILURE);
  }
#endif
  tree->action();
}

