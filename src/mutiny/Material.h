#ifndef MUTINY_ENGINE_MATERIAL_H
#define MUTINY_ENGINE_MATERIAL_H

#include "Object.h"
#include "Matrix4x4.h"

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
  Material(std::string vertContents, std::string fragContents);
  Material(Shader* shader);
  Material(Material* material);

  Shader* getShader();
  void setShader(Shader* shader);
  void setMatrix(std::string propertyName, Matrix4x4 matrix);
  void setFloat(std::string propertyName, float value);
  void setTexture(std::string propertyName, Texture* texture);
  Texture* getTexture(std::string propertyName);
  void setMainTexture(Texture* texture);
  Texture* getMainTexture();

  int getPassCount();
  void setPass(int pass);

private:
  static Material* current;
  static Material* defaultMaterial;
  static Material* guiMaterial;
  static Material* particleMaterial;

  static Material* load(std::string path);

  std::vector<Matrix4x4> matrices; std::vector<GLuint> matrixIndexes; std::vector<std::string> matrixNames;
  std::vector<float> floats; std::vector<GLuint> floatIndexes; std::vector<std::string> floatNames;
  std::vector<Texture*> textures; std::vector<GLuint> textureIndexes; std::vector<std::string> textureNames;

  std::shared_ptr<Shader> shader;

  bool indexesDirty;
  void refreshIndexes();
  static void dummyDeleter();

};

}

}

#endif

