#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inst.h"
#include "tree.h"

static Tree *g_tree;

static
char read_char(FILE *in)
{
  int c;
  if ((c = fgetc(in)) == EOF)
  {
    fprintf(stderr, "Error: unexpected EOF\n");
    exit(EXIT_FAILURE);
  }
  return (char)c;
}

static
int read_number(FILE *in)
{
  char c;
  int value = 0;
  while ((c = read_char(in)) != '\n')
  {
    if (c == ' ' || c == '\t')
    {
      value = (value << 1) | (c == '\t');
    }
  }
  return value;
}

static
int read_signed_number(FILE *in)
{
  int sign = 2 * (read_char(in) == ' ') - 1;
  return sign * read_signed_number(in);
}

static
void read_label(char *buf, FILE *in)
{
  char c;
  int i = 0;
  while ((c = read_char(in)) != '\n')
  {
    if (c == ' ' || c == '\t')
    {
      buf[i] = '0' + (c == '\t');
    }
  }
  buf[i] = 0;
}

static
void read_until_LF(FILE *in)
{
  char c;
  while ((c = read_char(in)) != '\n')
  {
  }
}

void inst_init(void)
{
  g_tree = new Tree();
}

void inst_finalize(void)
{
  delete g_tree;
  g_tree = NULL;
}


Inst::Inst(int opecode) : opecode(opecode)
{
}

Inst::Inst(int opecode, int operand) : opecode(opecode), operand(operand)
{
}

