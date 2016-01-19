#ifndef MUTINY_ARC_H
#define MUTINY_ARC_H

#include "internal/platform.h"

#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>

#ifdef HAS_TR1_NAMESPACE
  #include <tr1/memory>
#endif

template <class T>
class arc
{
public:
  static arc<T> arc_from_ptr(void* ptr)
  {
    arc<T> rtn;

    for(int i = 0; i < arcs().size(); i++)
    {
      if(arcs().at(i)->get() == ptr)
      {
        rtn = *arcs().at(i);
        break;
      }
    }

    return rtn;
  }

  static arc<T> alloc()
  {
    arc<T> rtn;

    rtn.shared.reset(new(calloc(1, sizeof(T))) T(), _arc);

    return rtn;
  }

  arc()
  {
    if(arcs == NULL) arcs = new std::vector<arc<T>*>();
    arcs->push_back(this);
  }

  arc(T* t)
  {
    reset(t);
    if(arcs == NULL) arcs = new std::vector<arc<T>*>();
	arcs->push_back(this);
  }

  arc(const arc<T>& other)
  {
    shared = other.shared;
    weak = other.weak;

    if(arcs == NULL) arcs = new std::vector<arc<T>*>();
	arcs->push_back(this);
  }

  ~arc()
  {
    for(size_t i = 0; i < arcs->size(); i++)
    {
      if(arcs->at(i) == this)
      {
        arcs->erase(arcs->begin() + i);
        break;
      }
    }

    if(arcs->size() <= 0)
    {
      delete arcs;
      arcs = NULL;
    }
  }

  arc<T>& operator=(const arc<T>& other)
  {
    shared = other.shared;
    weak = other.weak;

    return *this;
  }

  template <class R>
  arc<R> cast()
  {
    arc<R> rtn;

    rtn.shared = shared;
    rtn.weak = weak;

    return rtn;
  }

  template <class R>
  arc<R> dynamicCast()
  {
    arc<R> rtn;

#ifdef HAS_TR1_NAMESPACE
    rtn.shared = std::tr1::dynamic_pointer_cast<R>(shared);
    rtn.weak = std::tr1::dynamic_pointer_cast<R>(weak.lock());
#else
    rtn.shared = std::dynamic_pointer_cast<R>(shared);
    rtn.weak = std::dynamic_pointer_cast<R>(weak.lock());
#endif

    return rtn;
  }

  void reset(T* t)
  {
    weak.reset();
    shared.reset(t);
  }

  void reset()
  {
    weak.reset();
    shared.reset();
  }

  arc<T> getWeak()
  {
    arc<T> rtn = *this;

    if(rtn.get() != NULL)
    {
      rtn.weak = rtn.shared;
      rtn.shared.reset();
    }

    return rtn;
  }

  arc<T> getStrong()
  {
    arc<T> rtn = *this;

    if(rtn.weak.lock().get() != NULL)
    {
      rtn.shared = rtn.weak.lock();
      rtn.weak.reset();
    }

    return rtn;
  }

  T* get()
  {
    if(shared.get() != NULL)
    {
      return shared.get();
    }
    else
    {
      return weak.lock().get();
    }
  }

/*
  T& operator* ()
  {
    if(shared.get() != NULL)
    {
      return *shared;
    }
    else
    {
      return *weak.lock();
    }
  }
*/

  T* operator->()
  {
    if(shared.get() != NULL)
    {
      return shared.get();
    }
    else
    {
      return weak.lock().get();
    }
  }

// TODO: Solve dynamic cast of private
//private:
#ifdef HAS_TR1_NAMESPACE
  std::tr1::shared_ptr<T> shared;
  std::tr1::weak_ptr<T> weak;
#else
  std::shared_ptr<T> shared;
  std::weak_ptr<T> weak;
#endif

private:
  static void _arc(T* t)
  {
    t->~T();
    free(t);
    //delete t;
  }

  static std::vector<arc<T>*>* arcs;

};

template <class T> std::vector<arc<T>*>* arc<T>::arcs = NULL;

#endif
