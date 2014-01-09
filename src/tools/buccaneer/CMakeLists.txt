add_executable(buccaneer
  MainScreen.cpp
  main.cpp
  SceneManager.cpp
  MainCamera.cpp
  MenuScreen.cpp
  Timeline.cpp
  menus/SelectAnimationScreen.cpp
  menus/SelectModelScreen.cpp
  Util.cpp
)

target_link_libraries(buccaneer mutiny)
