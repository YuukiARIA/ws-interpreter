#ifndef WSINPUT_H_INCLUDED
#define WSINPUT_H_INCLUDED

#include <stdio.h>
#include <string>

namespace ws {

class WSInput
{
public:
  WSInput(FILE *in) : in(in) { }

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

  int read_number() const
  {
    char c;
    int value = 0;
    while ((c = getc()) != '\n')
    {
      value = (value << 1) | (c == '\t');
    }
    return value;
  }

  int read_signed_number() const
  {
    int sign = 2 * (getc() == ' ') - 1;
    return sign * read_number();
  }

  std::string read_label() const
  {
    std::string s;
    char c;
    while ((c = getc()) != '\n')
    {
      s += (char)('0' + (c == '\t'));
    }
    return s;
  }

private:
  FILE *in;
};

} // namespace ws

#endif

