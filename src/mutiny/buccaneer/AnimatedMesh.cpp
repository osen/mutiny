#include "AnimatedMesh.h"
#include "../Debug.h"

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
    animatedMesh->textures.push_back(std::vector<std::string>());
    animatedMesh->meshNames.push_back(part->name);

    for(int m = 0; m < part->materialGroups.size(); m++)
    {
      internal::MaterialGroupData* materialGroup = part->materialGroups.at(m).get();
      //Debug::log(materialGroup->material->texture);
      std::string texName = materialGroup->material->texture;
      texName = texName.substr(0, texName.length() - 4);
      animatedMesh->textures.at(animatedMesh->textures.size() - 1).push_back(texName);
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

        uv.push_back(Vector2(face->a.coord.x, face->a.coord.y));
        uv.push_back(Vector2(face->b.coord.x, face->b.coord.y));
        uv.push_back(Vector2(face->c.coord.x, face->c.coord.y));
      }

      currentSubmesh++;
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

    Debug::log("Loaded part");
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

std::string AnimatedMesh::getTexture(int mesh, int submesh)
{
  return textures.at(mesh).at(submesh);
}

std::string AnimatedMesh::getMeshName(int mesh)
{
  return meshNames.at(mesh);
}

}

}
