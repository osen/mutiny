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

class Graphics
{
public:
  static void setRenderTarget(RenderTexture* renderTarget);
  static void drawTexture(Rect rect, Texture* texture, Material* material);
  static void drawTexture(Rect rect, Texture* texture, Rect sourceRect, Material* material);
  static void drawTexture(Rect rect, Texture* texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Color color, Material* material);

private:
  static GLuint positionBufferId;
  static GLuint uvBufferId;
  static RenderTexture* renderTarget;

};

}

}

#endif

