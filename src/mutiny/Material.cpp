#include "Material.h"
#include "Application.h"
#include "Shader.h"
#include "Matrix4x4.h"
#include "Texture.h"
#include "Resources.h"
#include "Debug.h"

#include <memory>
#include <functional>

#include <iostream>
#include <fstream>

namespace mutiny
{

namespace engine
{

Material* Material::current = NULL;
Material* Material::defaultMaterial = NULL;
Material* Material::guiMaterial = NULL;
Material* Material::particleMaterial = NULL;

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
  shader.reset(new Shader(vertContents, fragContents));
}

Material::Material(Material* material)
{
  shader.reset(material->shader.get(), std::bind(dummyDeleter));
}

Material::Material(Shader* shader)
{
  this->shader.reset(shader, std::bind(dummyDeleter));
}

void Material::dummyDeleter()
{

}

Texture* Material::getTexture(std::string propertyName)
{
  for(int i = 0; i < textureNames.size(); i++)
  {
    if(textureNames.at(i) == propertyName)
    {
      return textures.at(i);
    }
  }

  return NULL;
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
    //glUniform1i(uniformId, i);
    //glActiveTexture(GL_TEXTURE0 + i);
    //glBindTexture(GL_TEXTURE_2D, textures[i]->getNativeTexture());
  }
}

Texture* Material::getMainTexture()
{
  return getTexture("in_Texture");
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
  this->shader.reset(shader, std::bind(dummyDeleter));
  refreshIndexes();
}

void Material::setPass(int pass)
{
  Material::current = this;
  glUseProgram(shader->programId);
}

void Material::apply()
{
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

