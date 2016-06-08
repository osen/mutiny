#ifndef MUTINY_ENGINE_MATERIAL_H
#define MUTINY_ENGINE_MATERIAL_H

#include "Object.h"
#include "Matrix4x4.h"
#include "Vector2.h"

#include <GL/glew.h>

#include <memory>
#include <vector>
#include <string>

namespace mutiny
{

namespace engine
{

class Resources;
class Application;
class Shader;
class MeshRenderer;
class Gui;
class Texture;
class Texture2d;
class ParticleRenderer;
class Graphics;

class Material : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::Application;
  friend class mutiny::engine::MeshRenderer;
  friend class mutiny::engine::Gui;
  friend class mutiny::engine::ParticleRenderer;
  friend class mutiny::engine::Graphics;

public:
  Material();
  Material(std::string vertContents, std::string fragContents);
  Material(ref<Shader> shader);
  Material(ref<Material> material);

  static shared<Material> create(ref<Shader> shader);
  static shared<Material> create(std::string vertContents, std::string fragContents);

  ref<Shader> getShader();
  void setShader(ref<Shader> shader);
  void setMatrix(std::string propertyName, Matrix4x4 matrix);
  Matrix4x4 getMatrix(std::string propertyName);
  void setFloat(std::string propertyName, float value);
  void setVector(std::string propertyName, Vector2 value);
  void setTexture(std::string propertyName, ref<Texture> texture);
  void setTexture(std::string propertyName, ref<Texture2d> texture);
  ref<Texture> getTexture(std::string propertyName);
  void setMainTexture(ref<Texture> texture);
  void setMainTexture(ref<Texture2d> texture);
  ref<Texture> getMainTexture();

  int getPassCount();
  void setPass(int pass, ref<Material> _this);

private:
  static ref<Material> load(std::string path);

  std::vector<Matrix4x4> matrices; std::vector<GLuint> matrixIndexes; std::vector<std::string> matrixNames;
  std::vector<float> floats; std::vector<GLuint> floatIndexes; std::vector<std::string> floatNames;
  std::vector<Vector2> vector2s; std::vector<GLuint> vector2Indexes; std::vector<std::string> vector2Names;
  std::vector<ref<Texture> > textures; std::vector<GLuint> textureIndexes; std::vector<std::string> textureNames;

  GLint positionId;
  GLint uvId;
  GLint normalId;
  GLint modelUniformId;

  shared<Shader> managedShader;
  ref<Shader> shader;

  bool indexesDirty;
  void refreshIndexes();
  void refreshIds();

};

}

}

#endif

