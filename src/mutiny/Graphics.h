#ifndef MUTINY_ENGINE_GRAPHICS_H
#define MUTINY_ENGINE_GRAPHICS_H

#include "Rect.h"
#include "Color.h"
#include "arc.h"

#include <GL/glew.h>

#include <string>
#include <vector>

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
class Application;

class Graphics
{
  friend class mutiny::engine::Gui;
  friend class mutiny::engine::Application;

public:
  static void setRenderTarget(arc<RenderTexture> renderTarget);
  static void drawTexture(Rect rect, arc<Texture> texture, arc<Material> material);
  static void drawTexture(Rect rect, arc<Texture> texture, Rect sourceRect, arc<Material> material);
  static void drawTexture(Rect rect, arc<Texture> texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Color color, arc<Material> material);
  static void drawTexture(Rect rect, arc<Texture> texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, arc<Material> material);

  static void drawMeshNow(arc<Mesh> mesh, Matrix4x4 matrix, int materialIndex);

private:
  static arc<Material> defaultMaterial;
  static arc<RenderTexture> renderTarget;

  static void drawTextureBatch(std::vector<Rect> rects, arc<Texture> texture, std::vector<Rect> sourceRects, arc<Material> material);

};

}

}

#endif

