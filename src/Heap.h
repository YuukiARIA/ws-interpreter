#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "RuntimeException.h"

namespace ws {

template<typename T>
class Heap
{
public:
  Heap(int size) : size(size)
  {
    p = new T[size];
    for (int i = 0; i < size; ++i) p[i] = T(0);
  }

  virtual ~Heap()
  {
    delete [] p;
  }

  T &operator[] (int i) throw(exception::RuntimeException)
  {
    check_range(i);
    return p[i];
  }

  const T &operator[] (int i) const throw(exception::RuntimeException)
  {
    check_range(i);
    return p[i];
  }

private:
  T *p;
  int size;

  void check_range(int i) const throw(exception::RuntimeException)
  {
    if (i < 0 || size <= i)
    {
      throw exception::RuntimeException("heap access out of bounds.");
    }
  }
};

} // namespace ws

#endif

