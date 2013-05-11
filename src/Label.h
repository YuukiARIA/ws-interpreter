#ifndef LABEL_H_INCLUDED
#define LABEL_H_INCLUDED

#include <string>

namespace ws {

class Label
{
public:
  Label(const std::string &str) : str(str), location(-1)
  {
  }

  Label &operator= (const Label &label)
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

} // namespace ws

#endif

