#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

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

