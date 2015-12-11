#include "Shader.h"
#include "Application.h"
#include "Matrix4x4.h"
#include "Texture.h"
#include "Debug.h"

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
    //Debug::logError("Failed to read vertex shader file '" + path + "'");
    throw std::exception();
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
    //Debug::logError("Failed to read fragment shader file");
    throw std::exception();
  }

  while(file.eof() == false)
  {
    getline(file, line);
    fragContents += line + '\n';
  }

  Shader* shader = new Shader(vertContents, fragContents);

  return shader;
}

Shader::Shader(std::string vertContents, std::string fragContents)
{
  const char* vertSrc = NULL;
  const char* fragSrc = NULL;
  GLint isCompiled = GL_FALSE;

  //glGenVertexArrays(1, &vertexArrayId);
  //_vertexArrayId.reset(&vertexArrayId, std::bind(deleteVertexArray, vertexArrayId));

  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  // TODO:
  //_vertexShaderId.reset(&vertexShaderId, std::bind(glDeleteShader, vertexShaderId));
  vertSrc = vertContents.c_str();
  glShaderSource(vertexShaderId, 1, &vertSrc, NULL);
  glCompileShader(vertexShaderId);

  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(vertexShaderId, maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    Debug::logError("Failed to compile vertex shader: \n" + std::string(log));
    throw std::exception();
  }

  fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  // TODO:
  //_fragmentShaderId.reset(&fragmentShaderId, std::bind(glDeleteShader, fragmentShaderId));
  fragSrc = fragContents.c_str();
  glShaderSource(fragmentShaderId, 1, &fragSrc, NULL);
  glCompileShader(fragmentShaderId);

  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(fragmentShaderId, maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    Debug::logError("Failed to compile fragment shader: \n" + std::string(log));
    throw std::exception();
  }

  programId = glCreateProgram();
  // TODO:
  //_programId.reset(&programId, std::bind(glDeleteProgram, programId));
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);

  GLint isLinked = 0;
  glGetProgramiv(programId, GL_LINK_STATUS, (int *)&isLinked);

  if(isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]);
 
    char* log = &infoLog[0];
 
    Debug::logError("Failed to compile fragment shader: \n" + std::string(log));
    throw std::exception();
  }
 
  //Always detach shaders after a successful link.
  //glDetachShader(programId, vertexShaderId);
  //glDetachShader(programId, fragmentShaderId);
}

}

}
