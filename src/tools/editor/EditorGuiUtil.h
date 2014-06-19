#ifndef EDITORGUIUTIL_H
#define EDITORGUIUTIL_H

#include <mutiny/mutiny.h>

#include <vector>
#include <string>

using namespace mutiny::engine;

class DropdownLayer;

class EditorGuiUtil
{
  friend class DropdownLayer;

public:
  static std::string tabs(Rect rect, std::vector<std::string>* names,
    std::string current);

  static void dropDown(Rect rect, std::string caption, std::string items,
    void(*callback)(std::string));

private:
  static DropdownLayer* dropdownLayer;
  static Texture2d* tabTexture;
  static Texture2d* noTabTexture;

};

#endif

