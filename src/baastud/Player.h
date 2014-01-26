#ifndef PLAYER_H
#define PLAYER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;
class QuickNumber;

class Player : public Behaviour
{
public:
  static GameObject* create(GameScreen* gameScreen);

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  GameScreen* gameScreen;
  AnimatedMeshRenderer* mr;
  Animation* walkAnimation;
  Animation* idleAnimation;
  Animation* sprintAnimation;
  Animation* humpAnimation;
  Texture2d* censoredTexture;
  Texture2d* heartTexture;
  std::unique_ptr<QuickNumber> quickNumber;

  float speed;
  int state;
  float hTimeout;
  GameObject* hTarget;
  int score;

};

#endif

