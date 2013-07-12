#ifndef MUTINY_ENGINE_MATERIAL_H
#define MUTINY_ENGINE_MATERIAL_H

#include "Object.h"

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
class Matrix4x4;
class Gui;
class Texture;
class ParticleRenderer;

class Material : public Object
{
  friend class mutiny::engine::Resources;
  friend class mutiny::engine::Application;
  friend class mutiny::engine::MeshRenderer;
  friend class mutiny::engine::Gui;
  friend class mutiny::engine::ParticleRenderer;

public:
  Material(std::string vertContents, std::string fragContents);

  Shader* getShader();
  void setShader(Shader* shader);
  void setMatrix(std::string propertyName, Matrix4x4 matrix);
  void setFloat(std::string propertyName, float value);
  void setTexture(std::string propertyName, Texture* texture);
  void setMainTexture(Texture* texture);

  void setPass(int pass);

private:
  static std::shared_ptr<Material> defaultMaterial;
  static std::shared_ptr<Material> guiMaterial;
  static std::shared_ptr<Material> particleMaterial;

  static Material* load(std::string path);

  std::vector<Matrix4x4> matrices; std::vector<GLuint> matrixIndexes; std::vector<std::string> matrixNames;
  std::vector<float> floats; std::vector<GLuint> floatIndexes; std::vector<std::string> floatNames;
  std::vector<Texture*> textures; std::vector<GLuint> textureIndexes; std::vector<std::string> textureNames;

  std::shared_ptr<Shader> shader;
  Texture* mainTexture;

  void refreshIndexes();

};

}

}

#endif

