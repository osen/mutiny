add_executable(baastud
  MenuScreen.cpp
  SceneManager.cpp
  main.cpp
  GameScreen.cpp
  Sheep.cpp
  GameCamera.cpp
  Fence.cpp
  Player.cpp
  FencePanel.cpp
  Terrain.cpp
  SkyBox.cpp
  AudioTest.cpp
  Audio.cpp
  QuickNumber.cpp
)

target_link_libraries(baastud mutiny SDL_mixer)
