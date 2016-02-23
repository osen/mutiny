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

  //glGenVertexArrays(1, &vertexArrayId);
  //_vertexArrayId.reset(&vertexArrayId, std::bind(deleteVertexArray, vertexArrayId));

  rtn->vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  // TODO:
  //_vertexShaderId.reset(&vertexShaderId, std::bind(glDeleteShader, vertexShaderId));
  vertSrc = vertContents.c_str();
  glShaderSource(rtn->vertexShaderId, 1, &vertSrc, NULL);
  glCompileShader(rtn->vertexShaderId);

  glGetShaderiv(rtn->vertexShaderId, GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(rtn->vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(rtn->vertexShaderId, maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    throw Exception("Failed to compile vertex shader: \n" + std::string(log));
  }

  rtn->fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  // TODO:
  //_fragmentShaderId.reset(&fragmentShaderId, std::bind(glDeleteShader, fragmentShaderId));
  fragSrc = fragContents.c_str();
  glShaderSource(rtn->fragmentShaderId, 1, &fragSrc, NULL);
  glCompileShader(rtn->fragmentShaderId);

  glGetShaderiv(rtn->fragmentShaderId, GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(rtn->fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(rtn->fragmentShaderId, maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    throw Exception("Failed to compile fragment shader: \n" + std::string(log));
  }

  rtn->programId = glCreateProgram();
  // TODO:
  //_programId.reset(&programId, std::bind(glDeleteProgram, programId));
  glAttachShader(rtn->programId, rtn->vertexShaderId);
  glAttachShader(rtn->programId, rtn->fragmentShaderId);
  glLinkProgram(rtn->programId);

  GLint isLinked = 0;
  glGetProgramiv(rtn->programId, GL_LINK_STATUS, (int *)&isLinked);

  if(isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(rtn->programId, GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(rtn->programId, maxLength, &maxLength, &infoLog[0]);
 
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
