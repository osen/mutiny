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

enable_ref::enable_ref()
{

}

enable_ref::enable_ref(const enable_ref& other)
{
  // Do nothing. We want to keep references to this
}

enable_ref::~enable_ref()
{
  // Tell all the references to drop
  while(refs.size() > 0)
  {
    refs.at(0)->release();
  }
}

enable_ref& enable_ref::operator=(const enable_ref& other)
{
  // Do nothing. We want to keep references to this
  return *this;
}

