#ifndef RUNTIMEEXCEPTION_H_INCLUDED
#define RUNTIMEEXCEPTION_H_INCLUDED

namespace ws {
namespace exception {

class RuntimeException
{
public:
  RuntimeException(const char *message) : message(message)
  {
  }

  const char *get_message() const
  {
    return message;
  }

private:
  const char *message;
};

} // namespace ws::exception
} // namespace ws

#endif

