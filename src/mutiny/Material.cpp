#include "Material.h"
#include "Application.h"
#include "Shader.h"
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

std::shared_ptr<Material> Material::defaultMaterial;
std::shared_ptr<Material> Material::guiMaterial;
std::shared_ptr<Material> Material::particleMaterial;

Material* Material::load(std::string path)
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

  Material* material = new Material(vertContents, fragContents);

  return material;
}

Material::Material(std::string vertContents, std::string fragContents)
{
  const char* vertSrc = NULL;
  const char* fragSrc = NULL;
  GLint isCompiled = GL_FALSE;

  shader.reset(new Shader());

  shader->vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  shader->_vertexShaderId.reset(&shader->vertexShaderId, std::bind(glDeleteShader, shader->fragmentShaderId));
  vertSrc = vertContents.c_str();
  glShaderSource(shader->vertexShaderId, 1, &vertSrc, NULL);
  glCompileShader(shader->vertexShaderId);

  glGetShaderiv(shader->vertexShaderId, GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(shader->vertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(shader->vertexShaderId, maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    Debug::logError("Failed to compile vertex shader: \n" + std::string(log));
    throw std::exception();
  }

  shader->fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  shader->_fragmentShaderId.reset(&shader->fragmentShaderId, std::bind(glDeleteShader, shader->fragmentShaderId));
  fragSrc = fragContents.c_str();
  glShaderSource(shader->fragmentShaderId, 1, &fragSrc, NULL);
  glCompileShader(shader->fragmentShaderId);

  glGetShaderiv(shader->fragmentShaderId, GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(shader->fragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetShaderInfoLog(shader->fragmentShaderId, maxLength, &maxLength, &infoLog[0]);

    char* log = &infoLog[0];
 
    Debug::logError("Failed to compile fragment shader: \n" + std::string(log));
    throw std::exception();
  }

  shader->programId = glCreateProgram();
  shader->_programId.reset(&shader->programId, std::bind(glDeleteProgram, shader->programId));
  glAttachShader(shader->programId, shader->vertexShaderId);
  glAttachShader(shader->programId, shader->fragmentShaderId);
  glLinkProgram(shader->programId);

  GLint isLinked = 0;
  glGetProgramiv(shader->programId, GL_LINK_STATUS, (int *)&isLinked);

  if(isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(shader->programId, GL_INFO_LOG_LENGTH, &maxLength);
 
    //The maxLength includes the NULL character
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(shader->programId, maxLength, &maxLength, &infoLog[0]);
 
    char* log = &infoLog[0];
 
    Debug::logError("Failed to compile fragment shader: \n" + std::string(log));
    throw std::exception();
  }
 
  //Always detach shaders after a successful link.
  //glDetachShader(shader->programId, shader->vertexShaderId);
  //glDetachShader(shader->programId, shader->fragmentShaderId);
}

void Material::setTexture(std::string propertyName, Texture* texture)
{
  for(int i = 0; i < textureNames.size(); i++)
  {
    if(textureNames.at(i) == propertyName)
    {
      textures[i] = texture;
      return;
    }
  }

  textures.push_back(texture);
  textureIndexes.push_back(-1);
  textureNames.push_back(propertyName);
  refreshIndexes();
}

void Material::setFloat(std::string propertyName, float value)
{
  for(int i = 0; i < floatNames.size(); i++)
  {
    if(floatNames.at(i) == propertyName)
    {
      floats[i] = value;
      return;
    }
  }

  floats.push_back(value);
  floatIndexes.push_back(-1);
  floatNames.push_back(propertyName);
  refreshIndexes();
}

void Material::setMatrix(std::string propertyName, Matrix4x4 matrix)
{
  for(int i = 0; i < matrixNames.size(); i++)
  {
    if(matrixNames.at(i) == propertyName)
    {
      matrices[i] = matrix;
      return;
    }
  }

  matrices.push_back(matrix);
  matrixIndexes.push_back(-1);
  matrixNames.push_back(propertyName);
  refreshIndexes();
}

void Material::refreshIndexes()
{
  glUseProgram(shader->programId);

  for(int i = 0; i < matrixNames.size(); i++)
  {
    GLuint uniformId = glGetUniformLocation(shader->programId, matrixNames.at(i).c_str());

    if(uniformId == -1)
    {
      Debug::logWarning("The specified matrix name was not found in the shader");
      continue;
    }

    matrixIndexes[i] = uniformId;
  }

  for(int i = 0; i < floatNames.size(); i++)
  {
    GLuint uniformId = glGetUniformLocation(shader->programId, floatNames.at(i).c_str());

    if(uniformId == -1)
    {
      Debug::logWarning("The specified float name was not found in the shader");
      continue;
    }

    floatIndexes[i] = uniformId;
  }

  for(int i = 0; i < textureNames.size(); i++)
  {
    GLint uniformId = glGetUniformLocation(shader->programId, textureNames.at(i).c_str());

    if(uniformId == -1)
    {
      Debug::logWarning("The specified sampler name was not found in the shader");
      continue;
    }

    textureIndexes[i] = uniformId;
    glUniform1i(uniformId, i);
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, textures[i]->getNativeTexture());
  }
}

void Material::setMainTexture(Texture* texture)
{
  setTexture("in_Texture", texture);
}

Shader* Material::getShader()
{
  return shader.get();
}

void Material::setShader(Shader* shader)
{
  // Should set deleter func to do nothing.
  this->shader.reset(shader);
  refreshIndexes();
}

void Material::setPass(int pass)
{
  glUseProgram(shader->programId);

  for(int i = 0; i < matrixNames.size(); i++)
  {
    glUniformMatrix4fv(matrixIndexes[i], 1, GL_FALSE, matrices[i].getValue());
  }

  for(int i = 0; i < floatNames.size(); i++)
  {
    glUniform1f(floatIndexes[i], floats[i]);
  }

  for(int i = 0; i < textureNames.size(); i++)
  {
    glUniform1i(textureIndexes[i], i);
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, textures[i]->getNativeTexture());
  }
}

}

}

