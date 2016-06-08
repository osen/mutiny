#ifndef PLAYER_H
#define PLAYER_H

#include <mutiny/mutiny.h>

using namespace mutiny::engine;

class GameScreen;
class QuickNumber;

class Player : public Behaviour
{
public:
  static ref<GameObject> create(ref<GameScreen> gameScreen);

  virtual void onAwake();
  virtual void onUpdate();
  virtual void onGui();

private:
  ref<GameScreen> gameScreen;
  ref<AnimatedMeshRenderer> mr;
  ref<Animation> walkAnimation;
  ref<Animation> idleAnimation;
  ref<Animation> sprintAnimation;
  ref<Animation> humpAnimation;
  ref<Texture2d> censoredTexture;
  ref<Texture2d> sheepIconTexture;
  shared<QuickNumber> quickNumber;


  bool firstTime;
  int score;
  int state;
  float hTimeout;
  float speed;
  ref<GameObject> hTarget;

};

#endif

