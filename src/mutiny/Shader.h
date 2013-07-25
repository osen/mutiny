#ifndef MUTINY_ENGINE_SHADER_H
#define MUTINY_ENGINE_SHADER_H

#include "Object.h"

#include <GL/glew.h>

#include <string>
#include <memory>

namespace mutiny
{

namespace engine
{

class Material;
class MeshRenderer;
class Shader;
class ParticleRenderer;
class Gui;
class Graphics;
class Resources;

class Shader : public Object
{
  friend class mutiny::engine::Material;
  friend class mutiny::engine::MeshRenderer;
  friend class mutiny::engine::Gui;
  friend class mutiny::engine::Graphics;
  friend class mutiny::engine::ParticleRenderer;
  friend class mutiny::engine::Resources;

private:
  static Shader* load(std::string path);

  GLuint vertexShaderId; std::shared_ptr<void> _vertexShaderId;
  GLuint fragmentShaderId; std::shared_ptr<void> _fragmentShaderId;
  GLuint programId; std::shared_ptr<void> _programId;

  Shader(std::string vertContents, std::string fragContents);

};

}

}

#endif

