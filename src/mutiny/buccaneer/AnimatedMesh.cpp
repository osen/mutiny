#include "AnimatedMesh.h"
#include "../Debug.h"
#include "../Resources.h"
#include "../Texture2d.h"

#include "../internal/WavefrontParser.h"

namespace mutiny
{

namespace engine
{

AnimatedMesh* AnimatedMesh::load(std::string path)
{
  internal::WavefrontParser parser(path + ".obj");
  internal::ModelData* modelData = parser.getModelData();
  std::vector<Vector3> vertices;
  std::vector<Vector2> uv;
  std::vector<std::vector<int> > triangles;
  int currentSubmesh = 0;
  std::unique_ptr<AnimatedMesh> animatedMesh(new AnimatedMesh());

  for(int p = 0; p < modelData->parts.size(); p++)
  {
    internal::PartData* part = modelData->parts.at(p).get();
    animatedMesh->textures.push_back(std::vector<Texture2d*>());
    animatedMesh->meshNames.push_back(part->name);
    Vector3 max;
    Vector3 min;
    bool mmSet = false;

    for(int m = 0; m < part->materialGroups.size(); m++)
    {
      internal::MaterialGroupData* materialGroup = part->materialGroups.at(m).get();
      //Debug::log(materialGroup->material->texture);
      std::string texName = materialGroup->material->texture;
      texName = texName.substr(0, texName.length() - 4);

      Texture2d* tex = Resources::load<Texture2d>(texName);

      if(tex == NULL)
      {
        //Debug::logError("Texture is null " + texName);
        //throw std::exception();
      }

      animatedMesh->textures.at(animatedMesh->textures.size() - 1).push_back(tex);
      triangles.push_back(std::vector<int>());

      for(int f = 0; f < materialGroup->faces.size(); f++)
      {
        internal::FaceData* face = materialGroup->faces.at(f).get();

        if(mmSet == false) { max.x = face->a.position.x; max.y = face->a.position.y; max.z = face->a.position.z;
                             min.x = face->a.position.x; min.y = face->a.position.y; min.z = face->a.position.z;
                             mmSet = true; }

        if(face->a.position.x > max.x) { max.x = face->a.position.x; }
        if(face->a.position.y > max.y) { max.y = face->a.position.y; }
        if(face->a.position.z > max.z) { max.z = face->a.position.z; }

        if(face->a.position.x < min.x) { min.x = face->a.position.x; }
        if(face->a.position.y < min.y) { min.y = face->a.position.y; }
        if(face->a.position.z < min.z) { min.z = face->a.position.z; }

        if(face->b.position.x > max.x) { max.x = face->b.position.x; }
        if(face->b.position.y > max.y) { max.y = face->b.position.y; }
        if(face->b.position.z > max.z) { max.z = face->b.position.z; }

        if(face->b.position.x < min.x) { min.x = face->b.position.x; }
        if(face->b.position.y < min.y) { min.y = face->b.position.y; }
        if(face->b.position.z < min.z) { min.z = face->b.position.z; }

        if(face->c.position.x > max.x) { max.x = face->c.position.x; }
        if(face->c.position.y > max.y) { max.y = face->c.position.y; }
        if(face->c.position.z > max.z) { max.z = face->c.position.z; }

        if(face->c.position.x < min.x) { min.x = face->c.position.x; }
        if(face->c.position.y < min.y) { min.y = face->c.position.y; }
        if(face->c.position.z < min.z) { min.z = face->c.position.z; }

        triangles.at(currentSubmesh).push_back(vertices.size());
        vertices.push_back(Vector3(face->a.position.x, face->a.position.y, face->a.position.z));
        triangles.at(currentSubmesh).push_back(vertices.size());
        vertices.push_back(Vector3(face->b.position.x, face->b.position.y, face->b.position.z));
        triangles.at(currentSubmesh).push_back(vertices.size());
        vertices.push_back(Vector3(face->c.position.x, face->c.position.y, face->c.position.z));

        uv.push_back(Vector2(face->a.coord.x, face->a.coord.y));
        uv.push_back(Vector2(face->b.coord.x, face->b.coord.y));
        uv.push_back(Vector2(face->c.coord.x, face->c.coord.y));
      }

      currentSubmesh++;
    }

    Vector3 offset = (max + min) / 2.0f;
    animatedMesh->meshOffsets.push_back(offset);

    for(int i = 0; i < vertices.size(); i++)
    {
      vertices[i] = vertices[i] - offset;
    }

    Mesh* mesh = new Mesh();
    animatedMesh->meshes.push_back(std::shared_ptr<Mesh>(mesh));
    mesh->setVertices(vertices);
    mesh->setUv(uv);

    for(int i = 0; i < triangles.size(); i++)
    {
      mesh->setTriangles(triangles.at(i), i);
    }

    vertices.clear();
    uv.clear();
    triangles.clear();
    currentSubmesh = 0;

    //Debug::log("Loaded part");
  }

  return animatedMesh.release();
}

AnimatedMesh::AnimatedMesh() : bounds(Vector3(), Vector3())
{

}

Mesh* AnimatedMesh::getMesh(int index)
{
  return meshes.at(index).get();
}

void AnimatedMesh::recalculateBounds()
{

}

Bounds AnimatedMesh::getBounds()
{
  return bounds;
}

int AnimatedMesh::getMeshCount()
{
  return meshes.size();
}

Texture2d* AnimatedMesh::getTexture(int mesh, int submesh)
{
  return textures.at(mesh).at(submesh);
}

Vector3 AnimatedMesh::getMeshOffset(int mesh)
{
  return meshOffsets.at(mesh);
}

std::string AnimatedMesh::getMeshName(int mesh)
{
  return meshNames.at(mesh);
}

}

}
