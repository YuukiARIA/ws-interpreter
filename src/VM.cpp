#include <stdio.h>
#include "VM.h"
#include "inst.h"

#define ARITH(OP)    {int y=vst.pop(); int x=vst.pop();vst.push(x OP y);}

using namespace ws;

namespace {

int geti()
{
  int v;
  scanf("%d", &v);
  return v;
}

} // namespace anonymous

VM::VM(std::vector<Inst> code, int vst_size, int cst_size, int heap_size)
  : vst(Stack<int>(vst_size)), cst(Stack<int>(cst_size)), heap(Heap<int>(heap_size))
{
  this->code = code;
}

VM::~VM()
{
}

void VM::reset()
{
  pc = 0;
  vst.clear();
  cst.clear();
}

void VM::run()
{
  const int length = code.size();

  reset();
  while (1)
  {
    if (pc >= length)
    {
      fprintf(stderr, "Error: out of bounds.\n");
      break;
    }

    const Inst &inst = code[pc++];

    if (inst.get_id() == INST_HALT) break;

    switch (inst.get_id())
    {
    case INST_PUSH:    vst.push(inst.get_operand());  break;
    case INST_COPY:    vst.copy(inst.get_operand());  break;
    case INST_SLIDE:   vst.slide(inst.get_operand()); break;
    case INST_DUP:     vst.dup();                     break;
    case INST_SWAP:    vst.swap();                    break;
    case INST_POP:     vst.pop();                     break;
    case INST_ADD:     ARITH(+);                      break;
    case INST_SUB:     ARITH(-);                      break;
    case INST_MUL:     ARITH(*);                      break;
    case INST_DIV:     ARITH(/);                      break;
    case INST_MOD:     ARITH(%);                      break;
    case INST_STORE:   heap_store();                  break;
    case INST_LOAD:    heap_load();                   break;
    case INST_PUTC:    putchar((char)vst.pop());      break;
    case INST_PUTI:    printf("%d", vst.pop());       break;
    case INST_GETC:    heap[vst.pop()] = getchar();   break;
    case INST_GETI:    heap[vst.pop()] = geti();      break;
    case INST_CALL:
      cst.push(pc);
    case INST_JMP:
      pc = inst.get_operand();
      break;
    case INST_JZ:
      if (vst.pop() == 0)
      {
        pc = inst.get_operand();
      }
      break;
    case INST_JNEG:
      if (vst.pop() < 0)
      {
        pc = inst.get_operand();
      }
      break;
    case INST_RET:
      pc = cst.pop();
      break;
    }
  }
}

void VM::heap_store()
{
  int v = vst.pop();
  int a = vst.pop();
  heap[a] = v;
}

void VM::heap_load()
{
  int a = vst.pop();
  vst.push(heap[a]);
}

