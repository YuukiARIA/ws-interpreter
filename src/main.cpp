#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include "RuntimeException.h"
#include "Label.h"
#include "WSInput.h"
#include "tree.h"
#include "inst.h"
#include "VM.h"

using namespace std;
using namespace ws;
using namespace ws::exception;

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

bool resolve_labels(vector<Inst> &code, const vector<Label> &labels)
{
  const int n = code.size();
  for (int i = 0; i < n; ++i)
  {
    Inst &inst = code[i];
    if (IS_PARAM_LABEL(inst.get_id()))
    {
      int location = labels[inst.get_operand()].get_location();
      if (location == -1)
      {
        fprintf(stderr, "Error: undefined label.\n");
        return false;
      }
      inst.set_operand(location);
    }
  }
  return true;
}

bool read_input(vector<Inst> &code, const WSInput &in, const Tree *const tree)
{
  const Tree *cur = tree;

  vector<Label> labels;

  int c;
  while ((c = in.read()) != EOF)
  {
    cur = cur->get_subtree(c);
    if (!cur)
    {
      fprintf(stderr, "Error: unknown instruction.\n");
      return false;
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

  return resolve_labels(code, labels);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(stderr, "usage: %s <File>\n", argv[0]);
    return EXIT_FAILURE;
  }

  char *input_file = NULL;
  int vst_size = 256;
  int cst_size = 256;
  int heap_size = 2048;

  for (int i = 1; i < argc; ++i)
  {
    char *arg = argv[i];
    if (arg[0] == '-' && strlen(arg) == 2)
    {
       switch (arg[1])
       {
       case 'v':
         if (i + 1 >= argc)
         {
           fprintf(stderr, "Error: no argument with option '-v'\n");
           return EXIT_FAILURE;
         }
         vst_size = atoi(argv[++i]);
         break;
       case 'c':
         if (i + 1 >= argc)
         {
           fprintf(stderr, "Error: no argument with option '-c'\n");
           return EXIT_FAILURE;
         }
         cst_size = atoi(argv[++i]);
         break;
       case 'h':
         if (i + 1 >= argc)
         {
           fprintf(stderr, "Error: no argument with option '-h'\n");
           return EXIT_FAILURE;
         }
         heap_size = atoi(argv[++i]);
         break;
       }
    }
    else if (!input_file)
    {
      input_file = arg;
    }
  }

  if (!input_file)
  {
    fprintf(stderr, "Error: no input file.\n");
    return EXIT_FAILURE;
  }
  if (vst_size <= 0 || cst_size <= 0 || heap_size <= 0)
  {
    fprintf(stderr, "Error: memory size must be positive.\n");
    return EXIT_FAILURE;
  }

  FILE *in = fopen(input_file, "rb");
  if (!in)
  {
    fprintf(stderr, "Error: failed to open \"%s\"\n", argv[1]);
    return EXIT_FAILURE;
  }

  Tree *root = init_tree();

  vector<Inst> code;
  bool success = read_input(code, WSInput(in), root);

  delete root;
  fclose(in);

  if (!success)
  {
    return EXIT_FAILURE;
  }

  VM vm(code, vst_size, cst_size, heap_size);
  try
  {
    vm.run();
  }
  catch (RuntimeException &e)
  {
    fprintf(stderr, "Error: %s\n", e.get_message());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

