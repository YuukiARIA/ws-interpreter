#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

class Tree
{
public:
  Tree();
  virtual ~Tree();

  Tree *operator[](char sp) const;

private:
  Tree *sub[3];
};

#endif

