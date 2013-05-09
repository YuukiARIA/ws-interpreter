#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

class Tree
{
public:
  Tree();
  virtual ~Tree();

  void add(const char *s, int v);

  Tree *operator[](char sp) const;

private:
  Tree *sub[3];
  bool  accept;
  int   value;
};

#endif

