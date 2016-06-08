#ifndef MUTINY_REF_H
#define MUTINY_REF_H

#include "internal/platform.h"

#include <vector>
#include <memory>
#include <string>
#include <iostream>

class ref_exception : public std::exception
{
  std::string message;

public:
  ref_exception(std::string message);
  virtual ~ref_exception() throw();
  virtual const char* what() const throw();
};

template <typename T>
class ref;

class enable_ref
{
  static void dummy(void *ptr);

public:
  shared<void> self;
  enable_ref();
  virtual ~enable_ref();

};

template <typename T>
class ref
{
public:
  weak<void> ptr;

  ref()
  {

  }

  ref(const T* t)
  {
    if(t != NULL)
    {
      ptr = t->self;
    }
  }

  ref(const shared<T>& other)
  {
    if(other.get() != NULL)
    {
      ptr = other.get()->self;
    }
  }

  ~ref()
  {

  }

  T* get()
  {
    if(try_get() == NULL)
    {
      throw ref_exception("NULL pointer");
    }

    return try_get();
  }

  T* try_get()
  {
    return (T*)ptr.lock().get();
  }

  bool valid()
  {
    if(try_get() == NULL)
    {
      return false;
    }

    return true;
  }

  ref& operator= (const T* t)
  {
    ptr.reset();

    if(t != NULL)
    {
      ptr = t->self;
    }

    return *this;
  }

  ref& operator= (const ref& other)
  {
    ptr = other.ptr;

    return *this;
  }

  ref& operator= (const shared<T>& other)
  {
    ptr.reset();

    if(other.get() != NULL)
    {
      ptr = other->self;
    }

    return *this;
  }

  T* operator->()
  {
    if(ptr.lock().get() == NULL)
    {
      throw ref_exception("Dereferencing NULL pointer");
    }

    return (T*)ptr.lock().get();
  }

  bool expired()
  {
    if(ptr.lock().get() == NULL)
    {
      return true;
    }

    return false;
  }

};

#endif
