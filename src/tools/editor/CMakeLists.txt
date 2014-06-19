add_executable(editor
  SelectProjectScreen.cpp
  ProjectScreen.cpp
  main.cpp
  SceneManager.cpp
  Header.cpp
  FilesPanel.cpp
  HierarchyPanel.cpp
  InspectorPanel.cpp
  ScenePanel.cpp
  EditorWindow.cpp
  AuthorCamera.cpp
  EditorGuiUtil.cpp
  FileTree.cpp
  LogPanel.cpp
  DropdownLayer.cpp
  Util.cpp
  InspectorCamera.cpp
)

target_link_libraries(editor mutiny)
