add_library(mutiny STATIC 
  internal/Util.cpp
  internal/tribox.cpp
  internal/WavefrontParser.cpp
  internal/lodepng.cpp
  buccaneer/AnimatedMeshRenderer.cpp
  buccaneer/AnimatedMesh.cpp
  buccaneer/Animation.cpp
  Time.cpp
  Mathf.cpp
  Texture.cpp
  Component.cpp
  GuiSkin.cpp
  Resources.cpp
  Behaviour.cpp
  Debug.cpp
  Camera.cpp
  ParticleRenderer.cpp
  Bounds.cpp
  ParticleEmitter.cpp
  Input.cpp
  CharacterController.cpp
  GameObject.cpp
  MeshFilter.cpp
  Matrix4x4.cpp
  Object.cpp
  GuiStyleState.cpp
  Font.cpp
  Color.cpp
  Vector2.cpp
  Vector3.cpp
  Vector4.cpp
  Rect.cpp
  Material.cpp
  RenderTexture.cpp
  GuiStyle.cpp
  Shader.cpp
  MeshRenderer.cpp
  Texture2d.cpp
  Mesh.cpp
  Collider.cpp
  Graphics.cpp
  Application.cpp
  RectOffset.cpp
  MeshCollider.cpp
  Transform.cpp
  Screen.cpp
  Gui.cpp
  AudioClip.cpp
  AudioSource.cpp
  Random.cpp
  GuiUtility.cpp
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
target_link_libraries(mutiny GLEW32s opengl32 SDL SDLmain SDL_mixer)
else()
target_link_libraries(mutiny GLEW GL png SDL SDL_image SDL_gfx SDL_mixer)
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")
