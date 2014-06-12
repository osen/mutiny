#ifndef EDITORGUIUTIL_H
#define EDITORGUIUTIL_H

#include <mutiny/mutiny.h>

#include <vector>
#include <string>

using namespace mutiny::engine;

class EditorGuiUtil
{
public:
  static std::string tabs(Rect rect, std::vector<std::string>* names,
    std::string current);

private:
  static Texture2d* tabTexture;
  static Texture2d* noTabTexture;

};

#endif

