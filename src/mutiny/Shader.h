#ifndef MUTINY_ENGINE_SHADER_H
#define MUTINY_ENGINE_SHADER_H

#include "Object.h"

#include <GL/glew.h>

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

class Shader : public Object
{
  friend class mutiny::engine::Material;
  friend class mutiny::engine::MeshRenderer;
  friend class mutiny::engine::Gui;
  friend class mutiny::engine::Graphics;
  friend class mutiny::engine::ParticleRenderer;

private:
  GLuint vertexShaderId; std::shared_ptr<void> _vertexShaderId;
  GLuint fragmentShaderId; std::shared_ptr<void> _fragmentShaderId;
  GLuint programId; std::shared_ptr<void> _programId;

};

}

}

#endif

