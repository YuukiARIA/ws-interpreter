#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

class Tree
{
public:
  Tree();
  virtual ~Tree();

  void add(const char *s, int v);
  Tree *get_subtree(char sp) const;
  bool is_accept() const;
  int get_value() const;

private:
  Tree *sub[3];
  bool  accept;
  int   value;
};

#endif

