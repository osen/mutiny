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
  MutinyScreen.cpp
  GameOverScreen.cpp
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
target_link_libraries(baastud mutiny)
else()
target_link_libraries(baastud mutiny SDL_mixer)
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")
