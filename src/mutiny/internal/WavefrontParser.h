#ifndef MUTINY_ENGINE_INTERNAL_WAVEFRONTPARSER_H
#define MUTINY_ENGINE_INTERNAL_WAVEFRONTPARSER_H

#include "../Vector2.h"
#include "../Vector3.h"
#include "../Vector4.h"
#include "../ref.h"

#include <string>
#include <vector>
#include <memory>

namespace mutiny
{

namespace engine
{

namespace internal
{

struct MaterialData : public enable_ref
{
  Vector4 color;
  std::string texture;
  std::string name;

};

struct VertexData : public enable_ref
{
  Vector3 position;
  Vector3 normal;
  Vector2 coord;

};

struct FaceData : public enable_ref
{
  VertexData a;
  VertexData b;
  VertexData c;

};

struct MaterialGroupData : public enable_ref
{
  ref<MaterialData> material;
  std::vector<shared<FaceData> > faces;
  
};

struct PartData : public enable_ref
{
  std::vector<shared<MaterialGroupData> > materialGroups;
  std::string name;
  Vector3 size;
  Vector3 center;

};

struct ModelData : public enable_ref
{
  std::vector<shared<PartData> > parts;
  std::vector<shared<MaterialData> > materials;
  Vector3 size;
  Vector3 center;

};

class WavefrontParser : public enable_ref
{
private:
  shared<ModelData> modelData;
  std::string filename;
  std::string foldername;
  bool _hasNormals;
  bool _hasCoords;

  shared<MaterialData> getMaterialData(std::string name);
  void parseMtl(std::string filename);
  void obtainSizes();
  Vector3 absVec3(Vector3 input);
  std::vector<std::string> mungeSplitLine(std::vector<std::string> splitLine);

public:
  WavefrontParser(std::string path);

  ref<ModelData> getModelData();
  void output();

  bool hasCoords();
  bool hasNormals();

};

}

}

}

#endif

