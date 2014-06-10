add_executable(editor
  SelectProjectScreen.cpp
  ProjectScreen.cpp
  main.cpp
  SceneManager.cpp
  Header.cpp
  FilesPanel.cpp
  HierarchyPanel.cpp
  InspectorPanel.cpp
  EditorWindow.cpp
#  AuthorCamera.cpp
)

target_link_libraries(editor mutiny)
