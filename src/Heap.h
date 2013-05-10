#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

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

  T &operator[] (int i)
  {
    return p[i];
  }

  const T &operator[] (int i) const
  {
    return p[i];
  }

private:
  T *p;
  int size;
};

} // namespace ws

#endif

