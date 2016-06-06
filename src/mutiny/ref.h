#ifndef MUTINY_REF_H
#define MUTINY_REF_H

#include "internal/platform.h"

#include <vector>
#include <memory>
#include <string>

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
public:
  std::vector<ref<enable_ref>*> refs;

  enable_ref();
  enable_ref(const enable_ref& other);
  virtual ~enable_ref();
  enable_ref& operator=(const enable_ref& other);

};

template <typename T>
class ref
{
public:
  ref()
  {
    t = NULL;
  }

  ref(const T* t)
  {
    this->t = (T*)t;
    this->t->refs.push_back((ref<enable_ref>*)this);
  }

  ref(const shared<T>& ptr)
  {
    t = ptr.get();
    t->refs.push_back((ref<enable_ref>*)this);
  }

  ~ref()
  {
    release();
  }

  T* get()
  {
    if(t == NULL)
    {
      throw ref_exception("NULL pointer");
    }

    return t;
  }

  T* try_get()
  {
    return t;
  }

  ref& operator= (const T* t)
  {
    if(this->t == t) return *this;

    release();

    this->t = (T*)t;
    this->t->refs.push_back((ref<enable_ref>*)this);

    return *this;
  }

  ref& operator= (const ref& other)
  {
    if(this->t == other.t) return *this;

    release();

    t = other.t;
    t->refs.push_back((ref<enable_ref>*)this);

    return *this;
  }

  ref& operator= (const shared<T>& other)
  {
    if(this->t == other.get()) return *this;

    release();

    t = other.get();
    t->refs.push_back((ref<enable_ref>*)this);

    return *this;
  }

  T* operator->()
  {
    if(t == NULL)
    {
      throw ref_exception("Dereferencing NULL pointer");
    }

    return t;
  }

  bool expired()
  {
    if(t == NULL)
    {
      return true;
    }

    return false;
  }

//private:
  T* t;

  void release()
  {
    if(t == NULL)
    {
      return;
    }

    for(size_t i = 0; i < t->refs.size(); i++)
    {
      if(t->refs.at(i) == (ref<enable_ref>*)this)
      {
        ((T*)t)->refs.erase(t->refs.begin() + i);
        break;
      }
    }

    t = NULL;
  }

};

#endif
