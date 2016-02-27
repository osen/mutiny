#ifndef MUTINY_ENGINE_INTERNAL_WAVEFRONTPARSER_H
#define MUTINY_ENGINE_INTERNAL_WAVEFRONTPARSER_H

#include "gcmm.h"
#include "../Vector2.h"
#include "../Vector3.h"
#include "../Vector4.h"

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
  Vector4 color;
  std::string texture;
  std::string name;

};

struct VertexData
{
  Vector3 position;
  Vector3 normal;
  Vector2 coord;

};

struct FaceData
{
  VertexData a;
  VertexData b;
  VertexData c;

};

struct MaterialGroupData
{
  MaterialGroupData();

  MaterialData* material;
  std::vector<FaceData> faces;
  
};

struct PartData
{
  PartData();

  internal::gc::list<MaterialGroupData*>* materialGroups;
  std::string name;
  Vector3 size;
  Vector3 center;

};

struct ModelData
{
  ModelData();

  internal::gc::list<PartData*>* parts;
  internal::gc::list<MaterialData*>* materials;
  Vector3 size;
  Vector3 center;

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
  Vector3 absVec3(Vector3 input);
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

