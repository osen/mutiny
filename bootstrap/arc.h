#ifndef ARC_H
#define ARC_H

#include <memory>

template <class T>
class arc
{
public:
  static arc<T> alloc()
  {
    arc<T> rtn(new(calloc(1, sizeof(T))) T());

    return rtn;
  }

  arc(){}

  arc(T* t)
  {
    reset(t);
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

    rtn.shared = std::dynamic_pointer_cast<R>(shared);
    rtn.weak = std::dynamic_pointer_cast<R>(weak.lock());

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

  arc<T> makeWeak()
  {
    arc<T> rtn = *this;

    if(rtn.get() != NULL)
    {
      rtn.weak = rtn.shared;
      rtn.shared.reset();
    }

    return rtn;
  }

  arc<T> makeStrong()
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

//private:
  std::shared_ptr<T> shared;
  std::weak_ptr<T> weak;

};

#endif
