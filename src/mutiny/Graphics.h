#ifndef MUTINY_ENGINE_GRAPHICS_H
#define MUTINY_ENGINE_GRAPHICS_H

#include "ref.h"
#include "Rect.h"
#include "Color.h"

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

class GraphicsCacheEntry : public enable_ref
{
  friend class mutiny::engine::GraphicsCache;

private:
  static shared<GraphicsCacheEntry> create();

  std::vector<Rect> rects;
  std::vector<Rect> sourceRects;
  shared<Mesh> mesh;
  int useCount;

};

class GraphicsCache : public enable_ref
{
  friend class mutiny::engine::Graphics;
  friend class mutiny::engine::Application;

private:
  static shared<GraphicsCache> create();
  shared<Mesh> matchMesh(std::vector<Rect>& rects, std::vector<Rect>& sourceRects);
  void addMesh(std::vector<Rect>& rects, std::vector<Rect>& sourceRects, shared<Mesh> mesh);
  void sweepUnused();

  std::vector<shared<GraphicsCacheEntry> > entries;

};

class Graphics
{
  friend class mutiny::engine::Gui;
  friend class mutiny::engine::Application;

public:
  static void setRenderTarget(ref<RenderTexture> renderTarget);
  static void drawTexture(Rect rect, ref<Texture> texture, ref<Material> material);
  static void drawTexture(Rect rect, ref<Texture> texture, Rect sourceRect, ref<Material> material);
  static void drawTexture(Rect rect, ref<Texture> texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, Color color, ref<Material> material);
  static void drawTexture(Rect rect, ref<Texture> texture, Rect sourceRect, int leftBorder, int rightBorder, int topBorder, int bottomBorder, ref<Material> material);

  static void drawMeshNow(ref<Mesh> mesh, Matrix4x4 matrix, int materialIndex);

private:
  static void drawTextureBatch(std::vector<Rect> rects, ref<Texture> texture, std::vector<Rect> sourceRects, ref<Material> material);

};

}

}

#endif

