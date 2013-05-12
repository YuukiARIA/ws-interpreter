#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

namespace ws {

template<typename T>
class Stack
{
public:
  Stack(int size) : size(size), sp(0)
  {
    st = new T[size];
  }

  virtual ~Stack()
  {
    delete [] st;
  }

  void clear()
  {
    sp = 0;
  }

  void push(const T v)
  {
    if (sp >= size)
    {
      fprintf(stderr, "Error: can't push.\n");
      exit(EXIT_FAILURE);
    }
    st[sp++] = v;
  }

  T top() const
  {
    return st[sp - 1];
  }

  T pop()
  {
    if (sp <= 0)
    {
      fprintf(stderr, "Error: can't pop.\n");
      exit(EXIT_FAILURE);
    }
    return st[--sp];
  }

  void discard(int n)
  {
    if (sp < n)
    {
      fprintf(stderr, "Error: can't discard.\n");
      exit(EXIT_FAILURE);
    }
    sp -= n;
  }

  void dup()
  {
    push(top());
  }

  void copy(int n)
  {
    push(st[sp - n - 1]);
  }

  void slide(int n)
  {
    T v = pop();
    discard(n);
    push(v);
  }

  void swap()
  {
    T t = st[sp - 1];
    st[sp - 1] = st[sp - 2];
    st[sp - 2] = t;
  }

private:
  T *st;
  int size;
  int sp;
};

} // namespace ws

#endif

