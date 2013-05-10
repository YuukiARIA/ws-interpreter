#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

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

  void push(const T &v)
  {
    if (sp >= size)
    {
      fprintf(stderr, "Error: can't push.\n");
      exit(EXIT_FAILURE);
    }
    st[sp++] = v;
  }

  T &top() const
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
    push(get(n));
  }

  void slide(int n)
  {
    const T &v = pop();
    discard(n);
    push(v);
  }

  void swap()
  {
    const T &t = get(0);
    set(0, get(1));
    set(1, t);
  }

private:
  T *st;
  int size;
  int sp;

  int get(int i) const
  {
    return st[sp - i - 1];
  }

  void set(int i, const T &v)
  {
    st[sp - i - 1] = v;
  }
};

} // namespace ws

#endif

