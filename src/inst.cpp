#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inst.h"

static const char *g_opcode_names[] =
{
  "undef",
  "push" ,  "copy" ,  "slide",  "dup"  ,  "swap" ,  "pop"  ,  "add"  ,  "sub"  ,
  "mul"  ,  "div"  ,  "mod"  ,  "store",  "load" ,  "putc" ,  "puti" ,  "getc" ,
  "geti" ,  "label",  "call" ,  "jmp"  ,  "jz"   ,  "jneg" ,  "ret"  ,  "halt"
};

const char *get_opcode_string(int id)
{
  int opcode = OPCODE(id);
  if (opcode < 1 || 24 < opcode)
  {
    opcode = 0;
  }
  return g_opcode_names[opcode];
}

Inst::Inst(int opcode) : opcode(opcode)
{
}

Inst::Inst(int opcode, int operand) : opcode(opcode), operand(operand)
{
}

