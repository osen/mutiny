#include "Shader.h"
#include "Application.h"
#include "Matrix4x4.h"
#include "Texture.h"
#include "Debug.h"
#include "Exception.h"

#include <memory>
#include <functional>

#include <iostream>
#include <fstream>

namespace mutiny
{

namespace engine
{

void Shader::deleteVertexArray(GLuint id)
{
  glDeleteVertexArrays(1, &id);
}

Shader* Shader::load(std::string path)
{
  std::string vertPath = path + ".vert";
  std::string fragPath = path + ".frag";

  std::string vertContents;
  std::string fragContents;

  std::ifstream file;
  std::string line;
  file.open(vertPath.c_str());

  if(file.is_open() == false)
  {
    throw Exception("Failed to read vertex shader file '" + path + "'");
  }

  while(file.eof() == false)
  {
    getline(file, line);
    vertContents += line + '\n';
  }

  file.close();
  file.open(fragPath.c_str());

  if(file.is_open() == false)
  {
    throw Exception("Failed to read fragment shader file");
  }

  while(file.eof() == false)
  {
    getline(file, line);
    fragContents += line + '\n';
  }

  Shader* shader = Shader::create(vertContents, fragContents);

  return shader;
}

Shader* Shader::create(std::string vertContents, std::string fragContents)
{
  Shader* rtn = Application::getGC()->gc_new<Shader>();

  const char* vertSrc = NULL;
  const char* fragSrc = NULL;
  GLint isCompiled = GL_FALSE;

  rtn->vertexShaderId = gl::Uint::createVertexShader();
  vertSrc = vertContents.c_str();
  glShaderSource(rtn->vertexShaderId->getGLuint(), 1, &vertSrc, NULL);
  glCompileShader(rtn->vertexShaderId->getGLuint());
  glGetShaderiv(rtn->vertexShaderId->getGLuint(), GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(rtn->vertexShaderId->getGLuint(), GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(rtn->vertexShaderId->getGLuint(), maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    throw Exception("Failed to compile vertex shader: \n" + std::string(log));
  }

  rtn->fragmentShaderId = gl::Uint::createFragmentShader();
  fragSrc = fragContents.c_str();
  glShaderSource(rtn->fragmentShaderId->getGLuint(), 1, &fragSrc, NULL);
  glCompileShader(rtn->fragmentShaderId->getGLuint());
  glGetShaderiv(rtn->fragmentShaderId->getGLuint(), GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(rtn->fragmentShaderId->getGLuint(), GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(rtn->fragmentShaderId->getGLuint(), maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    throw Exception("Failed to compile fragment shader: \n" + std::string(log));
  }

  rtn->programId = gl::Uint::createProgram();
  glAttachShader(rtn->programId->getGLuint(), rtn->vertexShaderId->getGLuint());
  glAttachShader(rtn->programId->getGLuint(), rtn->fragmentShaderId->getGLuint());
  glLinkProgram(rtn->programId->getGLuint());

  GLint isLinked = 0;
  glGetProgramiv(rtn->programId->getGLuint(), GL_LINK_STATUS, (int *)&isLinked);

  if(isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(rtn->programId->getGLuint(), GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(rtn->programId->getGLuint(), maxLength, &maxLength, &infoLog[0]);
 
    char* log = &infoLog[0];
 
    throw Exception("Failed to compile fragment shader: \n" + std::string(log));
  }
 
  //Always detach shaders after a successful link.
  //glDetachShader(programId, vertexShaderId);
  //glDetachShader(programId, fragmentShaderId);

  return rtn;
}

}

}
