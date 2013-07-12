#include "Mesh.h"
#include "Application.h"
#include "Debug.h"

#include "internal/WavefrontParser.h"

#include <iostream>

namespace mutiny
{

namespace engine
{

Mesh* Mesh::load(std::string path)
{
  internal::WavefrontParser parser(path + ".obj");
  internal::ModelData* modelData = parser.getModelData();
  std::vector<Vector3> vertices;
  std::vector<Vector2> uv;
  std::vector<int> triangles;

  for(int p = 0; p < modelData->parts.size(); p++)
  {
    internal::PartData* part = modelData->parts.at(p).get();

    for(int m = 0; m < part->materialGroups.size(); m++)
    {
      internal::MaterialGroupData* materialGroup = part->materialGroups.at(m).get();

      for(int f = 0; f < materialGroup->faces.size(); f++)
      {
        internal::FaceData* face = materialGroup->faces.at(f).get();

        triangles.push_back(vertices.size());
        vertices.push_back(Vector3(face->a.position.x, face->a.position.y, face->a.position.z));
        triangles.push_back(vertices.size());
        vertices.push_back(Vector3(face->b.position.x, face->b.position.y, face->b.position.z));
        triangles.push_back(vertices.size());
        vertices.push_back(Vector3(face->c.position.x, face->c.position.y, face->c.position.z));
        uv.push_back(Vector2(face->a.coord.x, face->a.coord.y));
        uv.push_back(Vector2(face->b.coord.x, face->b.coord.y));
        uv.push_back(Vector2(face->c.coord.x, face->c.coord.y));
      }
    }
  }


  Mesh* mesh = new Mesh();
  mesh->setVertices(vertices);
  mesh->setUv(uv);
  mesh->setTriangles(triangles);

  Debug::log("Loading mesh");

  return mesh;
}

Mesh::Mesh() : bounds(Vector3(), Vector3())
{
  glGenBuffers(1, &positionBufferId);
  _positionBufferId.reset(&positionBufferId, std::bind(glDeleteBuffers, 1, &positionBufferId));
  glGenBuffers(1, &uvBufferId);
  _uvBufferId.reset(&uvBufferId, std::bind(glDeleteBuffers, 1, &uvBufferId));
  glGenBuffers(1, &normalBufferId);
  _normalBufferId.reset(&normalBufferId, std::bind(glDeleteBuffers, 1, &normalBufferId));
}

void Mesh::setVertices(std::vector<Vector3> vertices)
{
  this->vertices = vertices;
}

void Mesh::setTriangles(std::vector<int> triangles)
{
  this->triangles = triangles;
  recalculateBounds();
  //Debug::log("Sending mesh to gfx card");

  std::vector<float> values;

  for(int i = 0; i < vertices.size(); i++)
  {
    values.push_back(vertices.at(i).x);
    values.push_back(vertices.at(i).y);
    values.push_back(vertices.at(i).z);
  }

  glBindBuffer(GL_ARRAY_BUFFER, positionBufferId);
  glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(values[0]), &values[0], GL_STATIC_DRAW);

  values.clear();

  for(int i = 0; i < uv.size(); i++)
  {
    values.push_back(uv.at(i).x);
    values.push_back(uv.at(i).y);
  }

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

std::vector<int>* Mesh::getTriangles()
{
  return &triangles;
}

std::vector<Vector2>* Mesh::getUv()
{
  return &uv;
}

std::vector<Vector3>* Mesh::getNormals()
{
  return &normals;
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

}

}
