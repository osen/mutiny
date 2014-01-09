#ifndef MUTINY_ENGINE_EXCEPTION_H
#define MUTINY_ENGINE_EXCEPTION_H

#include <string>
#include <exception>

namespace mutiny
{

namespace engine
{

class Exception : public std::exception
{
public:
  Exception(std::string message)
  {
    this->message = message;
  }

  virtual ~Exception() throw()
  {

  }

  virtual const char* what() const throw()
  {
    return message.c_str();
  }

private:
  std::string message;

};

}

}

#endif
