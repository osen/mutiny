add_executable(editor
  SelectProjectScreen.cpp
  ProjectScreen.cpp
  main.cpp
  SceneManager.cpp
#  AuthorCamera.cpp
)

target_link_libraries(editor mutiny)
