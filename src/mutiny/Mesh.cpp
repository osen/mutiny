#include "Mesh.h"
#include "Application.h"
#include "Color.h"
#include "Debug.h"

#include "internal/WavefrontParser.h"

#include <iostream>
#include <memory>
#include <functional>

namespace mutiny
{

namespace engine
{

Mesh* Mesh::load(std::string path)
{
  internal::WavefrontParser parser(path + ".obj");
  internal::ModelData* modelData = parser.getModelData();
  std::vector<Vector3> vertices;
  std::vector<Vector3> normals;
  std::vector<Vector2> uv;
  std::vector<Color> colors;
  std::vector<std::vector<int> > triangles;
  int currentSubmesh = 0;

  for(int p = 0; p < modelData->parts.size(); p++)
  {
    internal::PartData* part = modelData->parts.at(p).get();

    for(int m = 0; m < part->materialGroups.size(); m++)
    {
      internal::MaterialGroupData* materialGroup = part->materialGroups.at(m).get();
      triangles.push_back(std::vector<int>());

      for(int f = 0; f < materialGroup->faces.size(); f++)
      {
        internal::FaceData* face = materialGroup->faces.at(f).get();

        triangles.at(currentSubmesh).push_back(vertices.size());
        vertices.push_back(Vector3(face->a.position.x, face->a.position.y, face->a.position.z));
        triangles.at(currentSubmesh).push_back(vertices.size());
        vertices.push_back(Vector3(face->b.position.x, face->b.position.y, face->b.position.z));
        triangles.at(currentSubmesh).push_back(vertices.size());
        vertices.push_back(Vector3(face->c.position.x, face->c.position.y, face->c.position.z));

        normals.push_back(Vector3(face->a.normal.x, face->a.normal.y, face->a.normal.z));
        normals.push_back(Vector3(face->b.normal.x, face->b.normal.y, face->b.normal.z));
        normals.push_back(Vector3(face->c.normal.x, face->c.normal.y, face->c.normal.z));

        uv.push_back(Vector2(face->a.coord.x, face->a.coord.y));
        uv.push_back(Vector2(face->b.coord.x, face->b.coord.y));
        uv.push_back(Vector2(face->c.coord.x, face->c.coord.y));

        colors.push_back(Color(materialGroup->material->color.x,
                               materialGroup->material->color.y,
                               materialGroup->material->color.z));

        colors.push_back(Color(materialGroup->material->color.x,
                               materialGroup->material->color.y,
                               materialGroup->material->color.z));

        colors.push_back(Color(materialGroup->material->color.x,
                               materialGroup->material->color.y,
                               materialGroup->material->color.z));
      }

      currentSubmesh++;
    }
  }


  Mesh* mesh = new Mesh();
  mesh->setVertices(vertices);
  mesh->setNormals(normals);
  mesh->setUv(uv);
  mesh->setColors(colors);

  for(int i = 0; i < triangles.size(); i++)
  {
    mesh->setTriangles(triangles.at(i), i);
  }

  Debug::log("Loading mesh");

  return mesh;
}

void Mesh::freeBuffer(GLuint bufferId)
{
  glDeleteBuffers(1, &bufferId);
}

Mesh::Mesh() : bounds(Vector3(), Vector3())
{
  //glGenBuffers(1, &positionBufferId);
  //_positionBufferId.reset(&positionBufferId, std::bind(glDeleteBuffers, 1, &positionBufferId));
  //glGenBuffers(1, &uvBufferId);
  //_uvBufferId.reset(&uvBufferId, std::bind(glDeleteBuffers, 1, &uvBufferId));
  //glGenBuffers(1, &normalBufferId);
  //_normalBufferId.reset(&normalBufferId, std::bind(glDeleteBuffers, 1, &normalBufferId));
}

Mesh::~Mesh()
{

}

void Mesh::setVertices(std::vector<Vector3> vertices)
{
  this->vertices = vertices;
}

void Mesh::setColors(std::vector<Color> colors)
{
  this->colors = colors;
}

void Mesh::setTriangles(std::vector<int> triangles, int submesh)
{
  if(submesh > positionBufferIds.size())
  {
    throw std::exception();
  }

  if(submesh == positionBufferIds.size())
  {
    this->triangles.push_back(triangles);
  }

  if(normals.size() > 0)
  {
    std::cout << normals.size() << std::endl;
  }

  recalculateBounds();

  std::vector<float> values;

  for(int i = 0; i < triangles.size(); i++)
  {
    values.push_back(vertices.at(triangles.at(i)).x);
    values.push_back(vertices.at(triangles.at(i)).y);
    values.push_back(vertices.at(triangles.at(i)).z);
  }

  GLuint positionBufferId = 0;
  glGenBuffers(1, &positionBufferId);
  positionBufferIds.push_back(positionBufferId);
  _positionBufferIds.push_back(std::shared_ptr<GLuint>(&positionBufferId, std::bind(freeBuffer, positionBufferId)));

  glBindBuffer(GL_ARRAY_BUFFER, positionBufferId);
  glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(values[0]), &values[0], GL_STATIC_DRAW);

// Normals

  if(normals.size() > 0)
  {
    values.clear();

    for(int i = 0; i < triangles.size(); i++)
    {
      values.push_back(normals.at(triangles.at(i)).x);
      values.push_back(normals.at(triangles.at(i)).y);
      values.push_back(normals.at(triangles.at(i)).z);
    }

    GLuint normalBufferId = 0;
    glGenBuffers(1, &normalBufferId);
    normalBufferIds.push_back(normalBufferId);
    _normalBufferIds.push_back(std::shared_ptr<GLuint>(&normalBufferId, std::bind(freeBuffer, normalBufferId)));

    glBindBuffer(GL_ARRAY_BUFFER, normalBufferId);
    glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(values[0]), &values[0], GL_STATIC_DRAW);
  }

// UVs

  values.clear();

  for(int i = 0; i < triangles.size(); i++)
  {
    values.push_back(uv.at(triangles.at(i)).x);
    values.push_back(uv.at(triangles.at(i)).y);
  }

  GLuint uvBufferId = 0;
  glGenBuffers(1, &uvBufferId);
  uvBufferIds.push_back(uvBufferId);
  _uvBufferIds.push_back(std::shared_ptr<GLuint>(&uvBufferId, std::bind(freeBuffer, uvBufferId)));

  glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
  glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(values[0]), &values[0], GL_STATIC_DRAW);
}

void Mesh::setUv(std::vector<Vector2> uv)
{
  this->uv = uv;
}

void Mesh::setNormals(std::vector<Vector3> normals)
{
  this->normals = normals;
}

std::vector<Vector3>* Mesh::getVertices()
{
  return &vertices;
}

std::vector<int>* Mesh::getTriangles(int submesh)
{
  return &triangles.at(submesh);
}

std::vector<Vector2>* Mesh::getUv()
{
  return &uv;
}

std::vector<Vector3>* Mesh::getNormals()
{
  return &normals;
}

std::vector<Color>* Mesh::getColors()
{
  return &colors;
}

void Mesh::recalculateBounds()
{
  if(vertices.size() < 1)
  {
    bounds = Bounds(Vector3(), Vector3());
  }

  float minX = vertices.at(0).x; float maxX = vertices.at(0).x;
  float minY = vertices.at(0).y; float maxY = vertices.at(0).y;
  float minZ = vertices.at(0).z; float maxZ = vertices.at(0).z;

  for(int i = 0; i < vertices.size(); i++)
  {
    if(vertices.at(i).x < minX)
    {
      minX = vertices.at(i).x;
    }

    if(vertices.at(i).x > maxX)
    {
      maxX = vertices.at(i).x;
    }

    if(vertices.at(i).y < minY)
    {
      minY = vertices.at(i).y;
    }

    if(vertices.at(i).y > maxY)
    {
      maxY = vertices.at(i).y;
    }

    if(vertices.at(i).z < minZ)
    {
      minZ = vertices.at(i).z;
    }

    if(vertices.at(i).z > maxZ)
    {
      maxZ = vertices.at(i).z;
    }
  }

  float midX = (maxX + minX) / 2.0f;
  float midY = (maxY + minY) / 2.0f;
  float midZ = (maxZ + minZ) / 2.0f;

  float sizeX = maxX - minX;
  float sizeY = maxY - minY;
  float sizeZ = maxZ - minZ;

  bounds = Bounds(Vector3(midX, midY, midZ), Vector3(sizeX, sizeY, sizeZ));
}

Bounds Mesh::getBounds()
{
  return bounds;
}

int Mesh::getSubmeshCount()
{
  return triangles.size();
}

}

}
