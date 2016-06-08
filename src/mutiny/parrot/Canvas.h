#ifndef MUTINY_ENGINE_CANVAS_H
#define MUTINY_ENGINE_CANVAS_H

#include "../Behaviour.h"
#include "../Vector2.h"
#include "../Color.h"
#include "../Rect.h"
#include "../Font.h"

#include <string>

namespace mutiny
{

namespace engine
{

class Texture2d;
class Mesh;
class Material;

class Canvas : public Behaviour
{
public:
  virtual ~Canvas();
  void setSize(int width, int height);
  void setPosition(int x, int y);

  void fillRectangle(Rect rect, Color color);
  void drawText(Vector2 position, Font* font, std::string text);

  bool isHovering();
  bool isPressed();
  bool isReleased();
  bool needsRepaint();
  bool isActive();

private:
  static Canvas* currentActive;

  shared<Texture2d> texture;
  Mesh* mesh;
  ref<Material> material;

  bool needsApply;

  bool repaint;
  bool hovering;
  bool pressed;
  bool released;
  bool active;

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

};

}

}

#endif
