#ifndef INST_H_INCLUDED
#define INST_H_INCLUDED

#define ATTR_NUM             ( 1 << 6 )
#define ATTR_LABEL           ( 1 << 7 )
#define ATTR_PARAM           ( ATTR_NUM | ATTR_LABEL )

#define INST_UNDEF           (  0 )
#define INST_PUSH            (  1 | ATTR_NUM )
#define INST_COPY            (  2 | ATTR_NUM )
#define INST_SLIDE           (  3 | ATTR_NUM )
#define INST_DUP             (  4 )
#define INST_SWAP            (  5 )
#define INST_POP             (  6 )
#define INST_ADD             (  7 )
#define INST_SUB             (  8 )
#define INST_MUL             (  9 )
#define INST_DIV             ( 10 )
#define INST_MOD             ( 11 )
#define INST_STORE           ( 12 )
#define INST_LOAD            ( 13 )
#define INST_PUTC            ( 14 )
#define INST_PUTI            ( 15 )
#define INST_GETC            ( 16 )
#define INST_GETI            ( 17 )
#define INST_LABEL           ( 18 | ATTR_LABEL )
#define INST_CALL            ( 19 | ATTR_LABEL )
#define INST_JMP             ( 20 | ATTR_LABEL )
#define INST_JZ              ( 21 | ATTR_LABEL )
#define INST_JNEG            ( 22 | ATTR_LABEL )
#define INST_RET             ( 23 )
#define INST_HALT            ( 24 )

#define HAS_PARAM(X)         ( (X) & ATTR_PARAM )
#define IS_PARAM_NUM(X)      ( (X) & ATTR_NUM )
#define IS_PARAM_LABEL(X)    ( (X) & ATTR_LABEL )
#define OPCODE(X)            ( (X) & 0x3F )

class Inst
{
public:
  Inst(int id);
  Inst(int id, int operand);

  Inst &operator= (const Inst &inst);

  int get_id() const;
  int get_operand() const;
  void set_operand(int operand);

private:
  int id;
  int operand;
};

#ifdef ENABLE_OPCODE_STRING
const char *get_opcode_string(int id);
#endif

#endif

