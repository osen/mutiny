#include "Canvas.h"
#include "../Gui.h"
#include "../Vector2.h"
#include "../Vector3.h"
#include "../Mesh.h"
#include "../Material.h"
#include "../Shader.h"
#include "../Texture2d.h"
#include "../Resources.h"
#include "../Matrix4x4.h"
#include "../Graphics.h"
#include "../Screen.h"
#include "../Exception.h"
#include "../Color.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../Input.h"

#include <GL/glew.h>

namespace mutiny
{

namespace engine
{

void Canvas::awake()
{
  texture.reset(new Texture2d(128, 128));
  texture->apply();

  std::vector<Vector3> vertices;
  std::vector<Vector2> uv;
  std::vector<int> triangles;

  getGameObject()->getTransform()->setLocalPosition(Vector3(100, 100, 0));
  getGameObject()->getTransform()->setLocalScale(Vector3(128, 128, 0));

  float x = 0;
  float y = 0;
  float xw = x + 1;
  float yh = y + 1;

  triangles.push_back(0);
  triangles.push_back(1);
  triangles.push_back(2);
  triangles.push_back(3);
  triangles.push_back(4);
  triangles.push_back(5);

  vertices.push_back(Vector3(x, y, 0));
  vertices.push_back(Vector3(x, yh, 0));
  vertices.push_back(Vector3(xw, yh, 0));
  vertices.push_back(Vector3(xw, yh, 0));
  vertices.push_back(Vector3(xw, y, 0));
  vertices.push_back(Vector3(x, y, 0));

  uv.push_back(Vector2(0, 0));
  uv.push_back(Vector2(0, 1));
  uv.push_back(Vector2(1, 1));
  uv.push_back(Vector2(1, 1));
  uv.push_back(Vector2(1, 0));
  uv.push_back(Vector2(0, 0));

  mesh = arc<Mesh>::alloc();
  mesh->setVertices(vertices);
  mesh->setUv(uv);
  mesh->setTriangles(triangles, 0);

  arc<Shader> shader = Resources::load<Shader>("shaders/internal-gui-texture");

  if(shader.get() == NULL)
  {
    throw Exception("Failed to load GUI shader");
  }

  material.reset(new Material(shader));

}

bool Canvas::isHovering()
{
  return hovering;
}

bool Canvas::hasHoveringChanged()
{
  return hoveringChanged;
}

bool Canvas::isPressed()
{
  return pressed;
}

bool Canvas::hasPressedChanged()
{
  return pressedChanged;
}

bool Canvas::isReleased()
{
  return released;
}

bool Canvas::hasReleasedChanged()
{
  return releasedChanged;
}

void Canvas::update()
{
  hoveringChanged = false;
  pressedChanged = false;
  releasedChanged = false;
  released = false;

  Vector3 pos = getGameObject()->getTransform()->getPosition();
  Vector3 scale = getGameObject()->getTransform()->getScale();
  Rect bounds(pos.x, pos.y, scale.x, scale.y);

  if(bounds.contains(Input::getMousePosition()) == true)
  {
    if(hovering == false) hoveringChanged = true;
    hovering = true;

    if(Input::getMouseButtonDown(0) == true)
    {
      if(pressed == false) pressedChanged = true;
      pressed = true;
    }
    else if(Input::getMouseButton(0) == false)
    {
      if(pressed == true)
      {
        pressedChanged = true;
        pressed = false;
        releasedChanged = true;
        released = true;
      }
    }
  }
  else
  {
    if(hovering == true) hoveringChanged = true;
    hovering = false;

    if(Input::getMouseButton(0) == false)
    {
      if(pressed == true)
      {
        pressedChanged = true;
        pressed = false;
      }
    }
  }
}

void Canvas::gui()
{
  material->setMainTexture(texture.cast<Texture>());

  material->setMatrix("in_Projection", Matrix4x4::ortho(
    0, Screen::getWidth(), Screen::getHeight(), 0, -1, 1));

  material->setMatrix("in_View", Matrix4x4::getIdentity());
  material->setPass(0, material);

  Matrix4x4 modelMat = Matrix4x4::getIdentity();
  modelMat = modelMat.translate(getGameObject()->getTransform()->getPosition());
  modelMat = modelMat.scale(getGameObject()->getTransform()->getScale());

  glDisable(GL_DEPTH_TEST);
  glCullFace(GL_BACK);
  Graphics::drawMeshNow(mesh, modelMat, 0);
  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);
}

void Canvas::setPosition(int x, int y)
{
  getGameObject()->getTransform()->setLocalPosition(Vector3(x, y, 0));
}

void Canvas::setSize(int width, int height)
{
  getGameObject()->getTransform()->setLocalScale(Vector3(width, height, 0));
  texture->resize(width, height);
}

void Canvas::fillRectangle(Rect rect, Color color)
{
  for(int y = rect.y; y < rect.y + rect.height; y++)
  {
    for(int x = rect.x; x < rect.x + rect.width; x++)
    {
      texture->setPixel(x, y, color);
    }
  }

  texture->apply();
}

}

}
