#include "WavefrontParser.h"
#include "Util.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace mutiny
{

namespace engine
{

namespace internal
{

WavefrontParser::WavefrontParser(std::string path)
{
  std::string line;
  std::vector<std::string> splitLine;
  std::vector<std::string> subSplit;
  std::vector<Vector3> vertexPositions;
  std::vector<Vector3> vertexNormals;
  std::vector<Vector2> vertexCoords;
  std::ifstream file;

  arc<MaterialData> currentMaterial;
  arc<PartData> currentPart;
  arc<MaterialGroupData> currentMaterialGroup;
  arc<FaceData> currentFace;

  _hasCoords = false;
  _hasNormals = false;
  filename = Util::getFilename(path);
  foldername = Util::getFoldername(path);

  //std::cout << foldername << " " << filename << std::endl;

  // Setup defaults

  currentPart = arc<PartData>::alloc();
  modelData.parts.push_back(currentPart);
  currentPart->name = "";

  currentMaterial = arc<MaterialData>::alloc();
  modelData.materials.push_back(currentMaterial);
  currentMaterial->name = "";
  currentMaterial->color = Vector4(1, 1, 1, 1);
  currentMaterial->texture = "";

  currentMaterialGroup = arc<MaterialGroupData>::alloc();
  currentPart->materialGroups.push_back(currentMaterialGroup);
  currentMaterialGroup->material = currentMaterial;

  // Start parsing file

  file.open(path.c_str());

  if(file.is_open() == false)
  {
    //std::cout << "Error: Failed to open \"" << path << "\"" << std::endl;
    throw std::exception();
  }

  while(file.eof() == false)
  {
    getline(file, line);
    splitLine.clear();
    Util::splitStringWhitespace(line, &splitLine);

    if(splitLine.size() < 1)
    {
      continue;
    }

    if(splitLine.at(0) == "mtllib")
    {
      parseMtl(splitLine.at(1));
    }
    else if(splitLine.at(0) == "v")
    {
      vertexPositions.push_back(Vector3(-atof(splitLine.at(1).c_str()),
        atof(splitLine.at(2).c_str()),
        atof(splitLine.at(3).c_str())));
    }
    else if(splitLine.at(0) == "vn")
    {
      vertexNormals.push_back(Vector3(atof(splitLine.at(1).c_str()),
        atof(splitLine.at(2).c_str()),
        atof(splitLine.at(3).c_str())));
    }
    else if(splitLine.at(0) == "vt")
    {
      vertexCoords.push_back(Vector2(atof(splitLine.at(1).c_str()),
        -atof(splitLine.at(2).c_str())));
    }
    else if(splitLine.at(0) == "g" || splitLine.at(0) == "o")
    {
      currentPart = new PartData();
      modelData.parts.push_back(currentPart);

      if(splitLine.size() >= 2)
      {
        currentPart->name = splitLine.at(1);
      }

      currentMaterialGroup = new MaterialGroupData();
      currentPart->materialGroups.push_back(currentMaterialGroup);
      currentMaterialGroup->material = currentMaterial;
    }
    else if(splitLine.at(0) == "usemtl")
    {
      if(splitLine.size() > 1)
      {
        currentMaterial = getMaterialData(splitLine.at(1));
      }
      else
      {
        currentMaterial = getMaterialData("noname");
      }

      currentMaterialGroup = new MaterialGroupData();
      currentPart->materialGroups.push_back(currentMaterialGroup);
      currentMaterialGroup->material = currentMaterial;
    }
    else if(splitLine.at(0) == "f")
    {
      splitLine = mungeSplitLine(splitLine);
      currentFace = arc<FaceData>::alloc();
      currentMaterialGroup->faces.push_back(currentFace);
      subSplit.clear(); Util::splitString(splitLine.at(1), '/', &subSplit);

      currentFace->a.position = Vector3(vertexPositions.at(atoi(subSplit.at(0).c_str()) - 1));

      if(subSplit.size() > 1 && subSplit.at(1) != "")
      {
        _hasCoords = true;
        currentFace->a.coord = Vector2(vertexCoords.at(atoi(subSplit.at(1).c_str()) - 1));
      }

      if(subSplit.size() > 2)
      {
        _hasNormals = true;
        currentFace->a.normal = Vector3(vertexNormals.at(atoi(subSplit.at(2).c_str()) - 1));
      }

      subSplit.clear(); Util::splitString(splitLine.at(2), '/', &subSplit);

      currentFace->b.position = Vector3(vertexPositions.at(atoi(subSplit.at(0).c_str()) - 1));

      if(subSplit.size() > 1 && subSplit.at(1) != "")
      {
        currentFace->b.coord = Vector2(vertexCoords.at(atoi(subSplit.at(1).c_str()) - 1));
      }

      if(subSplit.size() > 2)
      {
        currentFace->b.normal = Vector3(vertexNormals.at(atoi(subSplit.at(2).c_str()) - 1));
      }

      subSplit.clear(); Util::splitString(splitLine.at(3), '/', &subSplit);

      currentFace->c.position = Vector3(vertexPositions.at(atoi(subSplit.at(0).c_str()) - 1));

      if(subSplit.size() > 1 && subSplit.at(1) != "")
      {
        currentFace->c.coord = Vector2(vertexCoords.at(atoi(subSplit.at(1).c_str()) - 1));
      }

      if(subSplit.size() > 2)
      {
        currentFace->c.normal = Vector3(vertexNormals.at(atoi(subSplit.at(2).c_str()) - 1));
      }

      if(splitLine.size() >= 5)
      {
        currentFace = new FaceData();
        currentMaterialGroup->faces.push_back(currentFace);
        subSplit.clear(); Util::splitString(splitLine.at(3), '/', &subSplit);

        currentFace->a.position = Vector3(vertexPositions.at(atoi(subSplit.at(0).c_str()) - 1));

        if(subSplit.size() > 1 && subSplit.at(1) != "")
        {
          currentFace->a.coord = Vector2(vertexCoords.at(atoi(subSplit.at(1).c_str()) - 1));
        }

        if(subSplit.size() > 2)
        {
          currentFace->a.normal = Vector3(vertexNormals.at(atoi(subSplit.at(2).c_str()) - 1));
        }

        subSplit.clear(); Util::splitString(splitLine.at(4), '/', &subSplit);

        currentFace->b.position = Vector3(vertexPositions.at(atoi(subSplit.at(0).c_str()) - 1));

        if(subSplit.size() > 1 && subSplit.at(1) != "")
        {
          currentFace->b.coord = Vector2(vertexCoords.at(atoi(subSplit.at(1).c_str()) - 1));
        }

        if(subSplit.size() > 2)
        {
          currentFace->b.normal = Vector3(vertexNormals.at(atoi(subSplit.at(2).c_str()) - 1));
        }

        subSplit.clear(); Util::splitString(splitLine.at(1), '/', &subSplit);

        currentFace->c.position = Vector3(vertexPositions.at(atoi(subSplit.at(0).c_str()) - 1));

        if(subSplit.size() > 1 && subSplit.at(1) != "")
        {
          currentFace->c.coord = Vector2(vertexCoords.at(atoi(subSplit.at(1).c_str()) - 1));
        }

        if(subSplit.size() > 2)
        {
          currentFace->c.normal = Vector3(vertexNormals.at(atoi(subSplit.at(2).c_str()) - 1));
        }
      }
    }
  }

  for(int a = 0; a < modelData.parts.size(); a++)
  {
    for(int b = 0; b < modelData.parts.at(a)->materialGroups.size(); b++)
    {
      if(modelData.parts.at(a)->materialGroups.at(b)->faces.size() < 1)
      {
        modelData.parts.at(a)->materialGroups.erase(modelData.parts.at(a)->materialGroups.begin() + b);
        b--;
      }
    }

    if(modelData.parts.at(a)->materialGroups.size() < 1)
    {
      modelData.parts.erase(modelData.parts.begin() + a);
      a--;
    }
  }

  // TODO: Go through each part and get max / min.
  // work out size and offset from 0, 0 so we can rotate around center of part.
  obtainSizes();
}

bool WavefrontParser::hasNormals()
{
  return _hasNormals;
}

bool WavefrontParser::hasCoords()
{
  return _hasCoords;
}

void WavefrontParser::obtainSizes()
{
  PartData* part = NULL;
  MaterialGroupData* materialGroup = NULL;
  float maxX = 0; float minX = 0;
  float maxY = 0; float minY = 0;
  float maxZ = 0; float minZ = 0;
  float modelMaxX = 0; float modelMinX = 0;
  float modelMaxY = 0; float modelMinY = 0;
  float modelMaxZ = 0; float modelMinZ = 0;
  bool initialSet = false;
  bool modelInitialSet = false;
  Vector3* current = NULL;

  for(int a = 0; a < modelData.parts.size(); a++)
  {
    part = modelData.parts.at(a).get();
    initialSet = false;

    for(int b = 0; b < part->materialGroups.size(); b++)
    {
      materialGroup = part->materialGroups.at(b).get();

      for(int c = 0; c < materialGroup->faces.size(); c++)
      {
        for(int d = 0; d < 3; d++)
        {
          if(d == 0)
          {
            current = &materialGroup->faces.at(c)->a.position;
          }
          else if(d == 1)
          {
            current = &materialGroup->faces.at(c)->b.position;
          }
          else
          {
            current = &materialGroup->faces.at(c)->c.position;
          }
        }

        if(initialSet == false)
        {
          maxX = current->x;
          minX = current->x;
          maxY = current->y;
          minY = current->y;
          maxZ = current->z;
          minZ = current->z;
          initialSet = true;
        }
        else
        {
          if(current->x > maxX) maxX = current->x;
          if(current->x < minX) minX = current->x;
          if(current->y > maxY) maxY = current->y;
          if(current->y < minY) minY = current->y;
          if(current->z > maxZ) maxZ = current->z;
          if(current->z < minZ) minZ = current->z;
        }
      }
    }

    part->size = absVec3(Vector3(maxX - minX, maxY - minY, maxZ - minZ));
    part->center.x = (maxX + minX) / 2;
    part->center.y = (maxY + minY) / 2;
    part->center.z = (maxZ + minZ) / 2;
    //std::cout << part->name << std::endl;
    //std::cout << " " << part->size.x << " " << part->size.y << " " << part->size.z << std::endl;
    //std::cout << " " << part->center.x << " " << part->center.y << " " << part->center.z << std::endl;

    if(modelInitialSet == false)
    {
      modelMaxX = maxX; modelMinX = minX;
      modelMaxY = maxY; modelMinY = minY;
      modelMaxZ = maxZ; modelMinZ = minZ;
      modelInitialSet = true;
    }
    else
    {
      if(maxX > modelMaxX) modelMaxX = maxX;
      if(minX < modelMinX) modelMinX = minX;
      if(maxY > modelMaxY) modelMaxY = maxY;
      if(minY < modelMinY) modelMinY = minY;
      if(maxZ > modelMaxZ) modelMaxZ = maxZ;
      if(minZ < modelMinZ) modelMinZ = minZ;
    }
  }

  modelData.size = absVec3(Vector3(modelMaxX - modelMinX, modelMaxY - modelMinY, modelMaxZ - modelMinZ));
  modelData.center.x = (modelMaxX + modelMinX) / 2;
  modelData.center.y = (modelMaxY + modelMinY) / 2;
  modelData.center.z = (modelMaxZ + modelMinZ) / 2;
  //std::cout << modelData.size.x << " " << modelData.size.y << " " << modelData.size.z << std::endl;
  //std::cout << modelData.center.x << " " << modelData.center.y << " " << modelData.center.z << std::endl;
}

Vector3 WavefrontParser::absVec3(Vector3 input)
{
  Vector3 output;

  if(input.x < 0)
  {
    output.x = input.x * -1;
  }
  else
  {
    output.x = input.x;
  }

  if(input.y < 0)
  {
    output.y = input.y * -1;
  }
  else
  {
    output.y = input.y;
  }

  if(input.z < 0)
  {
    output.z = input.z * -1;
  }
  else
  {
    output.z = input.z;
  }

  return output;
}

void WavefrontParser::parseMtl(std::string filename)
{
  MaterialData* currentMaterial = NULL;
  std::string line;
  std::vector<std::string> splitLine;
  std::vector<std::string> subSplit;
  std::string path = foldername + "/" + filename;
  char buffer[256];
  std::ifstream file;

  file.open(path.c_str());

  if(file.is_open() == false)
  {
    throw std::exception();
    std::cout << "Failed to open \"" + path + "\"" << std::endl;
  }

  while(file.eof() == false)
  {
    getline(file, line);
    splitLine.clear();
    Util::splitStringWhitespace(line, &splitLine);

    if(splitLine.size() < 1)
    {
      continue;
    }

    if(splitLine.at(0) == "newmtl")
    {
      currentMaterial = new MaterialData();
      modelData.materials.push_back(currentMaterial);

      if(splitLine.size() > 1)
      {
        currentMaterial->name = splitLine.at(1);
      }
      else
      {
        currentMaterial->name = "noname";
      }

      currentMaterial->color = Vector4(1);
    }
    else if(splitLine.at(0) == "Kd")
    {
      currentMaterial->color.x = atof(splitLine.at(1).c_str());
      currentMaterial->color.y = atof(splitLine.at(2).c_str());
      currentMaterial->color.z = atof(splitLine.at(3).c_str());
    }
    else if(splitLine.at(0) == "map_Kd")
    {
      currentMaterial->texture = foldername + "/" + splitLine.at(1);
    }
  }
}

ModelData* WavefrontParser::getModelData()
{
  return &modelData;
}

void WavefrontParser::output()
{
  std::cout << "Materials: " << modelData.materials.size() << std::endl;

  for(int a = 0; a < modelData.materials.size(); a++)
  {
    std::cout << "  Material: " << modelData.materials.at(a)->name << std::endl;
    std::cout << "    R: " << modelData.materials.at(a)->color.x << std::endl;
    std::cout << "    G: " << modelData.materials.at(a)->color.y << std::endl;
    std::cout << "    B: " << modelData.materials.at(a)->color.z << std::endl;
    std::cout << "    A: " << modelData.materials.at(a)->color.w << std::endl;

    if(modelData.materials.at(a)->texture != "")
    {
      std::cout << "    Texture: " << modelData.materials.at(a)->texture << std::endl;
    }
    else
    {
      std::cout << "    No Texture" << std::endl;
    }
  }

  std::cout << "Parts: " << modelData.parts.size() << std::endl;

/*
  for(int a = 0; a < modelData.parts.size(); a++)
  {
    std::cout << "  Part: " << modelData.parts.at(a)->name << std::endl;
    std::cout << "    Material Groups: " << modelData.parts.at(a)->materialGroups.size() << std::endl;

    for(int b = 0; b < modelData.parts.at(a)->materialGroups.size(); b++)
    {
      std::cout << "      Material Group: " << b << std::endl;
      std::cout << "        Faces: " << modelData.parts.at(a)->materialGroups.at(b)->faces.size() << std::endl;
      std::cout << "        Material: " << modelData.parts.at(a)->materialGroups.at(b)->material->name << std::endl;

      //if(modelData.parts.at(a)->materialGroups.at(b)->faces.size() > 0)
      //{

      //}
    }
  }
*/
}

arc<MaterialData> WavefrontParser::getMaterialData(std::string name)
{
  for(int i = 0; i < modelData.materials.size(); i++)
  {
    if(modelData.materials.at(i)->name == name)
    {
      return modelData.materials.at(i).get();
    }
  }

  //throw Exception("Failed to obtain material \"" + name + "\"");
  std::cout << "Warning: Failed to obtain material \"" << name << "\"" << std::endl;
  return modelData.materials.at(0);
}

std::vector<std::string> WavefrontParser::mungeSplitLine(std::vector<std::string> splitLine)
{
  std::vector<std::string> rtn;

  rtn.push_back(splitLine.at(0));
  rtn.push_back(splitLine.at(3));
  rtn.push_back(splitLine.at(2));
  rtn.push_back(splitLine.at(1));

  if(splitLine.size() > 4)
  {
    rtn.push_back(splitLine.at(4));
  }

  return rtn;
}

}

}

}
