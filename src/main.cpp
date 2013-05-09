#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "inst.h"

Tree *init_tree()
{
  Tree *tree = new Tree();
  tree->add("SS"  , INST_PUSH);
  tree->add("STS" , INST_COPY);
  tree->add("STL" , INST_SLIDE);
  tree->add("SLS" , INST_DUP);
  tree->add("SLT" , INST_SWAP);
  tree->add("SLL" , INST_POP);
  tree->add("TSSS", INST_ADD);
  tree->add("TSST", INST_SUB);
  tree->add("TSSL", INST_MUL);
  tree->add("TSTS", INST_DIV);
  tree->add("TSTT", INST_MOD);
  tree->add("TTS" , INST_STORE);
  tree->add("TTT" , INST_LOAD);
  tree->add("TLSS", INST_PUTC);
  tree->add("TLST", INST_PUTI);
  tree->add("TLTS", INST_GETC);
  tree->add("TLTT", INST_GETI);
  tree->add("LSS" , INST_LABEL);
  tree->add("LST" , INST_CALL);
  tree->add("LSL" , INST_JMP);
  tree->add("LTS" , INST_JZ);
  tree->add("LTT" , INST_JNEG);
  tree->add("LTL" , INST_RET);
  tree->add("LLL" , INST_HALT);
  return tree;
}

int is_ws(char c)
{
  return c == ' ' || c == '\t' || c == '\n';
}

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

int read_signed_number(FILE *in)
{
  int sign = 2 * (read_char(in) == ' ') - 1;
  return sign * read_signed_number(in);
}

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

void discard_until_LF(FILE *in)
{
  while (read_char(in) != '\n');
}

int main(int argc, char *argv[])
{
  FILE *in;
  int c;

  if (argc < 2)
  {
    fprintf(stderr, "file file file!\n");
    return EXIT_FAILURE;
  }

  in = fopen(argv[1], "rb");
  if (!in)
  {
    fprintf(stderr, "failed to open \"%s\"\n", argv[1]);
    return EXIT_FAILURE;
  }

  Tree *root = init_tree();
  Tree *cur = root;
  int pc = 0;
  while ((c = fgetc(in)) != EOF)
  {
    if (!is_ws(c)) continue;

    cur = cur->get_subtree(c);
    if (!cur)
    {
      fprintf(stderr, "Error: unknown instruction.\n");
      fclose(in);
      exit(EXIT_FAILURE);
    }
    else if (cur->is_accept())
    {
      int id = cur->get_value();
      if (HAS_PARAM(id))
      {
        discard_until_LF(in);
      }
      if (id != INST_LABEL)
      {
        printf("%03d: %8s\n", pc, get_opcode_string(id));
        ++pc;
      }
      cur = root;
    }
  }

  delete root;

  fclose(in);

  return EXIT_SUCCESS;
}

