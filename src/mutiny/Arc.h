#ifndef MUTINY_ENGINE_ARC_H
#define MUTINY_ENGINE_ARC_H

#include <vector>
#include <cstdlib>

namespace mutiny
{

namespace engine
{

class ArcBase
{
public:
  ArcBase()
  {
    all.push_back(this);
  }

  virtual ~ArcBase()
  {
    for(size_t i = 0; i < all.size(); i++)
    {
      if(all.at(i) == this)
      {
        all.erase(all.begin() + i);
        break;
      }
    }
  }
//protected:
  static std::vector<ArcBase*> all;

  virtual void* getGeneric() = 0;
  virtual void(*getGenericDeleter())(void*) = 0;

};

template <class T>
class Arc : public ArcBase
{
public:
  Arc()
  {
    data = NULL;
    deleter = NULL;
  }

  Arc(T* data)
  {
    this->data = data;
    deleter = NULL;
  }

  Arc(const Arc& other)
  {
    data = other.data;
    deleter = other.deleter;
  }

  Arc& operator=(const Arc& other)
  {
    reset(other.data, other.deleter);
    return *this;
  }

  T* operator->()
  {
    return data;
  }

  T& operator* ()
  {
    return *data;
  }

  virtual ~Arc()
  {
    reset();
  }

  void recover(T* data)
  {
    T* _data = NULL;
    void(*_deleter)(T*) = NULL;

    if(data != NULL)
    {
      // Fetch the deleter function from another shared entry
      for(size_t i = 0; i < all.size(); i++)
      {
        if(all.at(i)->getGeneric() == data)
        {
          _data = data;
          _deleter = (void(*)(T*))all.at(i)->getGenericDeleter();
          break;
        }
      }
    }

    reset(_data, _deleter);
  }

  void reset()
  {
    reset(NULL);
  }

  void reset(T* data)
  {
    reset(data, NULL);
  }

  void reset(T* data, void (*deleter)(T*))
  {
    if(this->data != NULL)
    {
      // Check to make sure the data being reset with isnt already this data
      if(this->data == data)
      {
        this->deleter = deleter;
        return;
      }

      // Look through all the other entries to check if another entry has a reference
      // If so, just replace the data in this container
      for(size_t i = 0; i < all.size(); i++)
      {
        if(all.at(i) != this && all.at(i)->getGeneric() == this->data)
        {
          this->data = data;
          this->deleter = deleter;

          return;
        }
      }

      if(this->deleter == NULL)
      {
        delete this->data;
      }
      else
      {
        this->deleter(this->data);
      }
    }

    this->data = data;
    this->deleter = deleter;
  }

  T* get()
  {
    return data;
  }

protected:
  void* getGeneric()
  {
    return data;
  }

  void(*getGenericDeleter())(void*)
  {
    return (void(*)(void*))deleter;
  }

private:
  T* data;
  void(*deleter)(T*);

};

}

}

#endif

