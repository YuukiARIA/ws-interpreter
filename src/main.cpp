#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "inst.h"

static Tree *g_tree;

void init_tree()
{
  g_tree = new Tree();
  g_tree->add("SS"  , INST_PUSH);
  g_tree->add("STS" , INST_COPY);
  g_tree->add("STL" , INST_SLIDE);
  g_tree->add("SLS" , INST_DUP);
  g_tree->add("SLT" , INST_SWAP);
  g_tree->add("SLL" , INST_POP);
  g_tree->add("TSSS", INST_ADD);
  g_tree->add("TSST", INST_SUB);
  g_tree->add("TSSL", INST_MUL);
  g_tree->add("TSTS", INST_DIV);
  g_tree->add("TSTT", INST_MOD);
  g_tree->add("TTS" , INST_STORE);
  g_tree->add("TTT" , INST_LOAD);
  g_tree->add("TLSS", INST_PUTC);
  g_tree->add("TLST", INST_PUTI);
  g_tree->add("TLTS", INST_GETC);
  g_tree->add("TLTT", INST_GETI);
  g_tree->add("LSS" , INST_LABEL);
  g_tree->add("LST" , INST_CALL);
  g_tree->add("LSL" , INST_JMP);
  g_tree->add("LTS" , INST_JZ);
  g_tree->add("LTT" , INST_JNEG);
  g_tree->add("LTL" , INST_RET);
  g_tree->add("LLL" , INST_HALT);
}

int is_ws(char c)
{
  return c == ' ' || c == '\t' || c == '\n';
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

  while ((c = fgetc(in)) != EOF)
  {
    if (!is_ws(c)) continue;

    switch (c)
    {
    case ' ':
      printf("S "); break;
    case '\t':
      printf("T\t"); break;
    case '\n':
      printf("L\n"); break;
    }
  }

  fclose(in);

  return EXIT_SUCCESS;
}

