#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

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

Tree::Tree()
{
  sub[0] = sub[1] = sub[2] = NULL;
}

Tree::~Tree()
{
  delete sub[0];
  delete sub[1];
  delete sub[2];
}

void Tree::add(const char *s, int v)
{
  char c = *s;
  if (c)
  {
    int i = to_index(c);
    if (!sub[i])
    {
      sub[i] = new Tree();
    }
    sub[i]->add(s + 1, v);
  }
  else
  {
    value = v;
    accept = true;
  }
}

Tree *Tree::get_subtree(char sp) const
{
  int i = to_index(sp);
  if (i != -1)
  {
    return sub[i];
  }
  return NULL;
}

bool Tree::is_accept() const
{
  return accept;
}

int Tree::get_value() const
{
  return value;
}

