#ifndef VM_H_INCLUDED
#define VM_H_INCLUDED

#include <vector>
#include "inst.h"
#include "Stack.h"
#include "Heap.h"

namespace ws {

class VM
{
public:
  VM(std::vector<Inst> code, int vst_size, int cst_size, int heap_size);
  virtual ~VM();

  void reset();
  void run();

private:
  std::vector<Inst> code;
  Stack<int> vst;
  Stack<int> cst;
  Heap<int> heap;
  int pc;

  void heap_store();
  void heap_load();
};

} // namespace ws

#endif

