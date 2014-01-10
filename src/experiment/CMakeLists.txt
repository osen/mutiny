add_executable(experiment
  model/ModelScreen.cpp
  introduction/IntroductionScreen.cpp
  main.cpp
  SceneManager.cpp
  transform/TransformScreen.cpp

  collision/CollisionScreen.cpp
  collision/Level.cpp
  collision/Player.cpp
  collision/SkyBox.cpp
  collision/SplashScreen.cpp

  post/MainCamera.cpp
  post/PostScreen.cpp

  bloom/BloomCamera.cpp
  bloom/BloomScreen.cpp
)

target_link_libraries(experiment mutiny)
