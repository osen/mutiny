#ifndef MUTINY_ENGINE_GRAPHICS_H
#define MUTINY_ENGINE_GRAPHICS_H

#include "Rect.h"
#include "Color.h"

#include <GL/glew.h>

namespace mutiny
{

namespace engine
{

class Texture;
class Material;
class RenderTexture;
class Matrix4x4;
class Mesh;
class Camera;
class Gui;

class Graphics
{
  friend class mutiny::engine::Gui;

public:
  static void setRenderTarget(RenderTexture* renderTarget);
  static void drawTexture(Rect rect, Texture* texture, Material* material);
  static void drawTexture(Rect rect, Texture* texture, Rect sourceRect, Material* material);
  static void drawTexture(Rect rect, Texture* texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Color color, Material* material = NULL);
  static void drawTexture(Rect rect, Texture* texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Material* material = NULL);

  static void drawMeshNow(Mesh* mesh, Matrix4x4 matrix, int materialIndex);

private:
  static void drawMeshNow(Mesh* mesh, int materialIndex);

};

}

}

#endif

