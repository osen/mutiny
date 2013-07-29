#ifndef MUTINY_ENGINE_GUI_H
#define MUTINY_ENGINE_GUI_H

#include "Rect.h"
#include "Matrix4x4.h"

#include <GL/glew.h>

#include <string>

namespace mutiny
{

namespace engine
{

class GuiSkin;
class Texture;

class Gui
{
public:
  static Matrix4x4 getMatrix();
  static void label(Rect rect, std::string text);
  static bool button(Rect rect, std::string text);
  static void box(Rect rect, std::string text);
  static void drawTexture(Rect rect, Texture* texture);

private:
  static GuiSkin* skin;

};

}

}

#endif

