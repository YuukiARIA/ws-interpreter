#include <stdio.h>
#include "VM.h"
#include "inst.h"

using namespace ws;

namespace {

int op_add(int x, int y) { return x + y; }
int op_sub(int x, int y) { return x - y; }
int op_mul(int x, int y) { return x * y; }
int op_div(int x, int y) { return x / y; }
int op_mod(int x, int y) { return x % y; }

int geti()
{
  int v;
  scanf("%d", &v);
  return v;
}

} // namespace anonymous

VM::VM(std::vector<Inst> code, int vst_size, int cst_size, int heap_size)
{
  this->code = code;
  vst = new Stack<int>(vst_size);
  cst = new Stack<int>(cst_size);
  heap = new Heap<int>(heap_size);
}

VM::~VM()
{
  delete vst;
  delete cst;
  delete heap;
}

void VM::run()
{
  int pc = 0;

  while (1)
  {
    if (pc >= code.size())
    {
      fprintf(stderr, "Error: out of bounds.\n");
      break;
    }

    const Inst &inst = code[pc++];

    if (inst.get_id() == INST_HALT) break;

    switch (inst.get_id())
    {
    case INST_PUSH:    vst->push(inst.get_operand()); break;
    case INST_COPY:    vst->copy(inst.get_operand()); break;
    case INST_SLIDE:   vst->slide(inst.get_operand()); break;
    case INST_DUP:     vst->dup(); break;
    case INST_SWAP:    vst->swap(); break;
    case INST_POP:     vst->pop(); break;
    case INST_ADD:     arith(op_add); break;
    case INST_SUB:     arith(op_sub); break;
    case INST_MUL:     arith(op_mul); break;
    case INST_DIV:     arith(op_div); break;
    case INST_MOD:     arith(op_mod); break;
    case INST_STORE:   heap_store(); break;
    case INST_LOAD:    heap_load(); break;
    case INST_PUTC:    putchar((char)vst->pop()); break;
    case INST_PUTI:    printf("%d", vst->pop()); break;
    case INST_GETC:    (*heap)[vst->pop()] = getchar(); break;
    case INST_GETI:    (*heap)[vst->pop()] = geti(); break;
    case INST_CALL:
      cst->push(pc);
    case INST_JMP:
      pc = inst.get_operand();
      break;
    case INST_JZ:
      if (vst->pop() == 0)
      {
        pc = inst.get_operand();
      }
      break;
    case INST_JNEG:
      if (vst->pop() < 0)
      {
        pc = inst.get_operand();
      }
      break;
    case INST_RET:
      pc = cst->pop();
      break;
    }
  }
}

void VM::heap_store()
{
  int v = vst->pop();
  int a = vst->pop();
  (*heap)[a] = v;
}

void VM::heap_load()
{
  int a = vst->pop();
  vst->push((*heap)[a]);
}

void VM::arith(int (*f)(int, int))
{
  int y = vst->pop();
  int x = vst->pop();
  vst->push(f(x, y));
}

