#include "ref.h"

ref_exception::ref_exception(std::string message)
{
  this->message = message;
}

ref_exception::~ref_exception() throw()
{

}

const char* ref_exception::what() const throw()
{
  return message.c_str();
}

void enable_ref::dummy(void *ptr)
{

}

enable_ref::enable_ref()
{
  self.reset(this, dummy);
}

enable_ref::~enable_ref()
{

}

