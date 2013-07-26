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

std::shared_ptr<Material> Material::defaultMaterial;
std::shared_ptr<Material> Material::guiMaterial;
std::shared_ptr<Material> Material::particleMaterial;

Material* Material::load(std::string path)
{
  Shader* shader = Resources::load<Shader>(path);

  if(shader == NULL)
  {
    return NULL;
  }

  Material* material = new Material(shader);

  return material;
}

Material::Material(std::string vertContents, std::string fragContents)
{
  shader.reset(new Shader(vertContents, fragContents));
}

Material::Material(Shader* shader)
{
  this->shader.reset(shader, std::bind(dummyDeleter));
}

void Material::dummyDeleter()
{

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
  this->shader.reset(shader, std::bind(dummyDeleter));
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

