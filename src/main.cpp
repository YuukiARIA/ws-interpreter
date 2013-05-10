#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include "tree.h"
#include "inst.h"
#include "VM.h"

using namespace std;

class FilteredInput
{
public:
  FilteredInput(FILE *in) : in(in) { }

  int read() const
  {
    int c;
    while ((c = fgetc(in)) != EOF)
    {
      if (c == ' ' || c == '\t' || c == '\n') break;
    }
    return c;
  }

  char getc() const
  {
    int c = read();
    if (c == EOF)
    {
      fprintf(stderr, "Error: unexpected EOF.\n");
      exit(EXIT_FAILURE);
    }
    return (char)c;
  }

private:
  FILE *in;
};

class LabelDef
{
public:
  LabelDef(const std::string &str) : str(str), location(-1)
  {
  }

  LabelDef(const LabelDef &label) : str(label.str), location(label.location)
  {
  }

  LabelDef &operator= (const LabelDef &label)
  {
    str = label.str;
    location = label.location;
    return *this;
  }

  bool equals_str(const std::string &str) const
  {
    return this->str == str;
  }

  int get_location() const
  {
    return location;
  }

  void set_location(int location)
  {
    this->location = location;
  }

private:
  std::string str;
  int location;
};

Tree *init_tree()
{
  Tree *tree = new Tree();
  tree->add("SS"  , INST_PUSH);
  tree->add("STS" , INST_COPY);
  tree->add("STL" , INST_SLIDE);
  tree->add("SLS" , INST_DUP);
  tree->add("SLT" , INST_SWAP);
  tree->add("SLL" , INST_POP);
  tree->add("TSSS", INST_ADD);
  tree->add("TSST", INST_SUB);
  tree->add("TSSL", INST_MUL);
  tree->add("TSTS", INST_DIV);
  tree->add("TSTT", INST_MOD);
  tree->add("TTS" , INST_STORE);
  tree->add("TTT" , INST_LOAD);
  tree->add("TLSS", INST_PUTC);
  tree->add("TLST", INST_PUTI);
  tree->add("TLTS", INST_GETC);
  tree->add("TLTT", INST_GETI);
  tree->add("LSS" , INST_LABEL);
  tree->add("LST" , INST_CALL);
  tree->add("LSL" , INST_JMP);
  tree->add("LTS" , INST_JZ);
  tree->add("LTT" , INST_JNEG);
  tree->add("LTL" , INST_RET);
  tree->add("LLL" , INST_HALT);
  return tree;
}

int read_number(const FilteredInput &in)
{
  char c;
  int value = 0;
  while ((c = in.getc()) != '\n')
  {
    if (c == ' ' || c == '\t')
    {
      value = (value << 1) | (c == '\t');
    }
  }
  return value;
}

int read_signed_number(const FilteredInput &in)
{
  int sign = 2 * (in.getc() == ' ') - 1;
  return sign * read_number(in);
}

string read_label(const FilteredInput &in)
{
  string s;
  char c;
  int i = 0;
  while ((c = in.getc()) != '\n')
  {
    if (c == ' ' || c == '\t')
    {
      s += (char)('0' + (c == '\t'));
    }
  }
  return s;
}

int index_of_label(vector<LabelDef> &labels, const string &str)
{
  vector<LabelDef>::iterator itr = labels.begin();
  for (; itr != labels.end(); ++itr)
  {
    const LabelDef &label = *itr;
    if (label.equals_str(str))
    {
      return itr - labels.begin();
    }
  }
  labels.push_back(LabelDef(str));
  return labels.size() - 1;
}

void resolve_labels(vector<Inst> &code, const vector<LabelDef> &labels)
{
  for (int i = 0; i < code.size(); ++i)
  {
    Inst &inst = code[i];
    if (IS_PARAM_LABEL(inst.get_id()))
    {
      inst.set_operand(labels[inst.get_operand()].get_location());
    }
  }
}

void read_input(const FilteredInput &in, const Tree *const tree)
{
  const Tree *cur = tree;

  vector<LabelDef> labels;
  vector<Inst> code;

  int c;
  while ((c = in.read()) != EOF)
  {
    cur = cur->get_subtree(c);
    if (!cur)
    {
      fprintf(stderr, "Error: unknown instruction.\n");
      exit(EXIT_FAILURE);
    }
    else if (cur->is_accept())
    {
      int id = cur->get_value();
      int operand = 0;

      if (IS_PARAM_NUM(id))
      {
        operand = read_signed_number(in);
      }
      else if (IS_PARAM_LABEL(id))
      {
        string labelstr = read_label(in);
        operand = index_of_label(labels, labelstr);
      }

      if (id == INST_LABEL)
      {
        labels[operand].set_location(code.size());
      }
      else
      {
        code.push_back(Inst(id, operand));
      }
      cur = tree;
    }
  }

  resolve_labels(code, labels);

  ws::VM vm(code, 1024, 1024, 4096);
  vm.run();
}

int main(int argc, char *argv[])
{
  FILE *in;
  int c;

  if (argc < 2)
  {
    fprintf(stderr, "file file file!\n");
    return EXIT_FAILURE;
  }

  in = fopen(argv[1], "rb");
  if (!in)
  {
    fprintf(stderr, "failed to open \"%s\"\n", argv[1]);
    return EXIT_FAILURE;
  }

  Tree *root = init_tree();

  read_input(FilteredInput(in), root);

  delete root;

  fclose(in);

  return EXIT_SUCCESS;
}

