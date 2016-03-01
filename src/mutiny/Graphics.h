#ifndef MUTINY_ENGINE_GRAPHICS_H
#define MUTINY_ENGINE_GRAPHICS_H

#include "Rect.h"
#include "Color.h"
#include "internal/gcmm.h"

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
class GraphicsCache;
class Graphics;

class GraphicsCacheEntry
{
  friend class mutiny::engine::GraphicsCache;

private:
  static GraphicsCacheEntry* create();

  std::vector<Rect> rects;
  std::vector<Rect> sourceRects;
  Mesh* mesh;
  int useCount;

};

class GraphicsCache
{
  friend class mutiny::engine::Graphics;
  friend class mutiny::engine::Application;

private:
  static GraphicsCache* create();
  Mesh* matchMesh(std::vector<Rect>& rects, std::vector<Rect>& sourceRects);
  void addMesh(std::vector<Rect>& rects, std::vector<Rect>& sourceRects, Mesh* mesh);
  void sweepUnused();

  internal::gc::list<GraphicsCacheEntry*>* entries;

};

class Graphics
{
  friend class mutiny::engine::Gui;
  friend class mutiny::engine::Application;

public:
  static void setRenderTarget(RenderTexture* renderTarget);
  static void drawTexture(Rect rect, Texture* texture, Material* material);
  static void drawTexture(Rect rect, Texture* texture, Rect sourceRect, Material* material);
  static void drawTexture(Rect rect, Texture* texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Color color, Material* material);
  static void drawTexture(Rect rect, Texture* texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Material* material);

  static void drawMeshNow(Mesh* mesh, Matrix4x4 matrix, int materialIndex);

private:
  static void drawTextureBatch(std::vector<Rect> rects, Texture* texture, std::vector<Rect> sourceRects, Material* material);

};

}

}

#endif

