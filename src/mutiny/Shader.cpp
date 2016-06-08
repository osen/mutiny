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

ref<Shader> Shader::load(std::string path)
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

  ref<Shader> shader = new Shader(vertContents, fragContents);

  return shader;
}
shared<Shader> Shader::create(std::string vertContents, std::string fragContents)
{
  shared<Shader> rtn(new Shader(vertContents, fragContents));

  return rtn;
}

Shader::Shader(std::string vertContents, std::string fragContents)
{
  const char* vertSrc = NULL;
  const char* fragSrc = NULL;
  GLint isCompiled = GL_FALSE;

  vertexShaderId = gl::Uint::createVertexShader();
  vertSrc = vertContents.c_str();
  glShaderSource(vertexShaderId->getGLuint(), 1, &vertSrc, NULL);
  glCompileShader(vertexShaderId->getGLuint());
  glGetShaderiv(vertexShaderId->getGLuint(), GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(vertexShaderId->getGLuint(), GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(vertexShaderId->getGLuint(), maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    throw Exception("Failed to compile vertex shader: \n" + std::string(log));
  }

  fragmentShaderId = gl::Uint::createFragmentShader();
  fragSrc = fragContents.c_str();
  glShaderSource(fragmentShaderId->getGLuint(), 1, &fragSrc, NULL);
  glCompileShader(fragmentShaderId->getGLuint());
  glGetShaderiv(fragmentShaderId->getGLuint(), GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(fragmentShaderId->getGLuint(), GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShaderId->getGLuint(), maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    throw Exception("Failed to compile fragment shader: \n" + std::string(log));
  }

  programId = gl::Uint::createProgram();
  glAttachShader(programId->getGLuint(), vertexShaderId->getGLuint());
  glAttachShader(programId->getGLuint(), fragmentShaderId->getGLuint());
  glLinkProgram(programId->getGLuint());

  GLint isLinked = 0;
  glGetProgramiv(programId->getGLuint(), GL_LINK_STATUS, (int *)&isLinked);

  if(isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(programId->getGLuint(), GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(programId->getGLuint(), maxLength, &maxLength, &infoLog[0]);
 
    char* log = &infoLog[0];
 
    throw Exception("Failed to compile fragment shader: \n" + std::string(log));
  }
 
  //Always detach shaders after a successful link.
  //glDetachShader(programId, vertexShaderId);
  //glDetachShader(programId, fragmentShaderId);
}

}

}
