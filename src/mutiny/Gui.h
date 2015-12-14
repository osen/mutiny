#ifndef MUTINY_ENGINE_GUI_H
#define MUTINY_ENGINE_GUI_H

#include "Rect.h"
#include "Matrix4x4.h"
#include "arc.h"

#include <GL/glew.h>

#include <string>
#include <vector>

namespace mutiny
{

namespace engine
{

class GuiSkin;
class Texture;
class GuiStyle;
class Application;

class Gui
{
  friend class mutiny::engine::Application;

public:
  static Matrix4x4 getMatrix();
  static void setMatrix(Matrix4x4 matrix);
  static GuiSkin* getSkin();

  static void label(Rect rect, std::string text);
  static bool button(Rect rect, std::string text);
  static bool button(Rect rect, Texture* image);
  static void box(Rect rect, std::string text);
  static void drawTexture(Rect rect, arc<Texture> texture);
  static void drawTextureWithTexCoords(Rect position, arc<Texture> texture, Rect texCoords);

private:
  static GuiSkin* skin;
  static Matrix4x4 matrix;

  static void drawUi(Rect rect, arc<Texture> texture, arc<GuiStyle> style);
  static void drawTextureWithTexCoords(std::vector<Rect> positions, arc<Texture> texture, std::vector<Rect> texCoords);

};

}

}

#endif

