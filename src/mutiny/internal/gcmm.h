#ifndef MUTINY_ENGINE_INTERNAL_GCMM_H
#define MUTINY_ENGINE_INTERNAL_GCMM_H

#include "gc.h"

#include <cstdlib>

namespace mutiny
{

namespace engine
{

namespace internal
{

namespace gc
{

class context;

template <class T>
class list
{
  friend class mutiny::engine::internal::gc::context;

public:
  void push_back(T t)
  {
    if(actualSize < _size + 1)
    {
      size_t newSize = (_size * 10) + 1;
      T* newData = (T*)gc_alloc(ctx, sizeof(t) * newSize);

      if(data != NULL)
      {
        //memcpy(newData, data, sizeof(t) * size);
        for(size_t i = 0; i < _size; i++)
        {
          newData[i] = data[i];
        }
      }

      data = newData;
      actualSize = newSize;
    }

    data[_size] = t;
    _size++;
  }

  void remove_at(size_t idx)
  {
    if(idx >= _size)
    {
      // Error
      exit(1);
    }

    for(size_t i = idx + 1; i < _size; i++)
    {
      data[i-1] = data[i];
    }

    _size--;
  }

  T& at(size_t idx)
  {
    if(idx >= _size)
    {
      // Error
      exit(1);
    }

    return data[idx];
  }

  void clear()
  {
    data = NULL;
    _size = 0;
    actualSize = 0;
  }

  size_t size()
  {
    return _size;
  }

private:
  T* data;
  size_t _size;
  size_t actualSize;
  GcContext* ctx;

};

class context
{
public:
  context()
  {
    gc_ctx = gc_context();
  }

  ~context()
  {
    gc_destroy(gc_ctx);
  }

  void gc_collect()
  {
    ::gc_collect(gc_ctx);
  }

  template <class N>
  N* gc_new()
  {
    void* data = NULL;
    N* rtn = NULL;

    data = gc_alloc(gc_ctx, sizeof(*rtn));
    rtn = new(data) N;
    gc_finalizer(gc_ctx, rtn, gc_delete<N>);

    return rtn;
  }

  template <class N>
  list<N>* gc_list()
  {
    list<N>* rtn = NULL;

    rtn = gc_new<list<N> >();
    rtn->ctx = gc_ctx;

    return rtn;
  }

private:
  GcContext* gc_ctx;

  template <class D>
  static void gc_delete(void* ptr)
  {
    D* d = (D*)ptr;
    d->~D();
  }

  context(const context&)
  {

  }

  context& operator=(const context&)
  {
    return *this;
  }

};

}

}

}

}

#endif