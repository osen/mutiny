#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <mutiny/mutiny.h>

#include <memory>
#include <string>

using namespace mutiny::engine;

class EditorWindow
{
public:
  Rect position;

  EditorWindow();
  virtual ~EditorWindow();

  void gui();
  void setTitle(std::string title);

private:
  std::shared_ptr<Texture2d> headerTexture;
  std::string title;

  virtual void onGui();

};

#endif

