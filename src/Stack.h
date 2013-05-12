#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "RuntimeException.h"

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

  void push(const T v) throw(exception::RuntimeException)
  {
    if (sp >= size)
    {
      throw exception::RuntimeException("can't push.");
    }
    st[sp++] = v;
  }

  T top() const
  {
    return st[sp - 1];
  }

  T pop() throw(exception::RuntimeException)
  {
    if (sp <= 0)
    {
      throw exception::RuntimeException("can't pop.");
    }
    return st[--sp];
  }

  void discard(int n) throw(exception::RuntimeException)
  {
    if (sp < n)
    {
      throw exception::RuntimeException("can't discard.");
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

