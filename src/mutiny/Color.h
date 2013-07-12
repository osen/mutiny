#ifndef MUTINY_ENGINE_COLOR_H
#define MUTINY_ENGINE_COLOR_H

namespace mutiny
{

namespace engine
{

class Color
{
public:
  float r;
  float g;
  float b;
  float a;

  Color();
  Color(float r, float g, float b);
  Color(float r, float g, float b, float a);

};

}

}

#endif

