#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include "Label.h"
#include "WSInput.h"
#include "tree.h"
#include "inst.h"
#include "VM.h"

using namespace std;
using namespace ws;

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

int index_of_label(vector<Label> &labels, const string &str)
{
  const int n = labels.size();
  for (int i = 0; i < n; ++i)
  {
    if (labels[i].equals_str(str))
    {
      return i;
    }
  }
  labels.push_back(Label(str));
  return labels.size() - 1;
}

void resolve_labels(vector<Inst> &code, const vector<Label> &labels)
{
  const int n = code.size();
  for (int i = 0; i < n; ++i)
  {
    Inst &inst = code[i];
    if (IS_PARAM_LABEL(inst.get_id()))
    {
      inst.set_operand(labels[inst.get_operand()].get_location());
    }
  }
}

void read_input(const WSInput &in, const Tree *const tree)
{
  const Tree *cur = tree;

  vector<Label> labels;
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
        operand = in.read_signed_number();
      }
      else if (IS_PARAM_LABEL(id))
      {
        string labelstr = in.read_label();
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

  VM vm(code, 1024, 1024, 4096);
  vm.run();
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "usage: %s <File>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE *in = fopen(argv[1], "rb");
  if (!in)
  {
    fprintf(stderr, "Error: failed to open \"%s\"\n", argv[1]);
    return EXIT_FAILURE;
  }

  Tree *root = init_tree();

  read_input(WSInput(in), root);

  delete root;

  fclose(in);

  return EXIT_SUCCESS;
}

