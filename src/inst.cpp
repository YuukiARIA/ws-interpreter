#include "inst.h"

#ifdef ENABLE_OPCODE_STRING

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

#endif

Inst::Inst(int id) : id(id)
{
}

Inst::Inst(int id, int operand) : id(id), operand(operand)
{
}

Inst &Inst::operator= (const Inst &inst)
{
  id = inst.id;
  operand = inst.operand;
  return *this;
}

int Inst::get_id() const
{
  return id;
}

int Inst::get_operand() const
{
  return operand;
}

void Inst::set_operand(int operand)
{
  this->operand = operand;
}

