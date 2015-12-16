#ifndef MUTINY_ENGINE_CANVAS_H
#define MUTINY_ENGINE_CANVAS_H

#include "../Behaviour.h"
#include "../Vector2.h"
#include "../Color.h"
#include "../Rect.h"
#include "../arc.h"

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
  void setSize(int width, int height);
  void setPosition(int x, int y);

  void fillRectangle(Rect rect, Color color);

  bool isHovering();
  bool isPressed();
  bool isReleased();
  bool needsRepaint();

private:
  arc<Texture2d> texture;
  arc<Mesh> mesh;
  arc<Material> material;

  bool needsApply;

  bool repaint;
  bool hovering;
  bool pressed;
  bool released;

  virtual void awake();
  virtual void update();
  virtual void gui();

};

}

}

#endif
