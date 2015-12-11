#ifndef MUTINY_ENGINE_SHADER_H
#define MUTINY_ENGINE_SHADER_H

#include "Object.h"
#include "arc.h"

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

  GLuint vertexShaderId; arc<GLuint> _vertexShaderId;
  GLuint fragmentShaderId; arc<GLuint> _fragmentShaderId;
  GLuint programId; arc<GLuint> _programId;
  GLuint vertexArrayId; arc<GLuint> _vertexArrayId;

  Shader(std::string vertContents, std::string fragContents);

};

}

}

#endif

