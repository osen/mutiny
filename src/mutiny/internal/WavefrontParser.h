#ifndef MUTINY_ENGINE_INTERNAL_WAVEFRONTPARSER_H
#define MUTINY_ENGINE_INTERNAL_WAVEFRONTPARSER_H

#include "../glm/glm.hpp"

#include <string>
#include <vector>
#include <memory>

namespace mutiny
{

namespace engine
{

namespace internal
{

struct MaterialData
{
  glm::vec4 color;
  std::string texture;
  std::string name;

};

struct VertexData
{
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 coord;

};

struct FaceData
{
  VertexData a;
  VertexData b;
  VertexData c;

};

struct MaterialGroupData
{
  MaterialData* material;
  std::vector<std::shared_ptr<FaceData> > faces;
  
};

struct PartData
{
  std::vector<std::shared_ptr<MaterialGroupData> > materialGroups;
  std::string name;
  glm::vec3 size;
  glm::vec3 center;

};

struct ModelData
{
  std::vector<std::shared_ptr<PartData> > parts;
  std::vector<std::shared_ptr<MaterialData> > materials;
  glm::vec3 size;
  glm::vec3 center;

};

class WavefrontParser
{
private:
  ModelData modelData;
  std::string filename;
  std::string foldername;
  bool _hasNormals;
  bool _hasCoords;

  MaterialData* getMaterialData(std::string name);
  void parseMtl(std::string filename);
  void obtainSizes();
  glm::vec3 absVec3(glm::vec3 input);
  std::vector<std::string> mungeSplitLine(std::vector<std::string> splitLine);

public:
  WavefrontParser(std::string path);

  ModelData* getModelData();
  void output();

  bool hasCoords();
  bool hasNormals();

};

}

}

}

#endif

