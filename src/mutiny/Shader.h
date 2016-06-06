#ifndef MUTINY_ENGINE_SHADER_H
#define MUTINY_ENGINE_SHADER_H

#include "ref.h"
#include "Object.h"
#include "internal/glmm.h"

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
  static void deleteVertexArray(GLuint id);
  static Shader* load(std::string path);

  shared<gl::Uint> vertexShaderId;
  shared<gl::Uint> fragmentShaderId;
  shared<gl::Uint> programId;

  static Shader* create(std::string vertContents, std::string fragContents);

};

}

}

#endif

