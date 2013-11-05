#include "Mathf.h"

namespace mutiny
{

namespace engine
{

float Mathf::pi = 3.14159265358979f;

int Mathf::nextPowerOfTwo(int value)
{
  if( value != 0 )
  {
    value--;
    value |= (value >> 1); //Or first 2 bits
    value |= (value >> 2); //Or next 2 bits
    value |= (value >> 4); //Or next 4 bits
    value |= (value >> 8); //Or next 8 bits
    value |= (value >> 16); //Or next 16 bits
    value++;
  }

  return value;
}

float Mathf::deg2Rad(float degrees)
{
  return (degrees / 180) * Mathf::pi;
}

}

}

