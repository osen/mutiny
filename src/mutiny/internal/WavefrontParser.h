#ifndef MUTINY_ENGINE_INTERNAL_WAVEFRONTPARSER_H
#define MUTINY_ENGINE_INTERNAL_WAVEFRONTPARSER_H

#include "../Vector2.h"
#include "../Vector3.h"
#include "../Vector4.h"
#include "../arc.h"

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
  arc<MaterialData> material;
  std::vector<arc<FaceData> > faces;
  
};

struct PartData
{
  std::vector<arc<MaterialGroupData> > materialGroups;
  std::string name;
  Vector3 size;
  Vector3 center;

};

struct ModelData
{
  std::vector<arc<PartData> > parts;
  std::vector<arc<MaterialData> > materials;
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

  arc<MaterialData> getMaterialData(std::string name);
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

