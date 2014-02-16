add_executable(drunken
  SceneManager.cpp
  main.cpp
  GameScreen.cpp
  GameCamera.cpp
  Terrain.cpp
  SkyBox.cpp
  Player.cpp
  Pickup.cpp
)

target_link_libraries(drunken mutiny)
