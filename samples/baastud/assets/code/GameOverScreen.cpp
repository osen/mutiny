#include "GameOverScreen.h"
#include "QuickNumber.h"
#include "Audio.h"

using namespace mutiny::engine;

int GameOverScreen::score = 0;

ref<GameObject> GameOverScreen::create()
{
  ref<GameObject> mainGo = GameObject::create("GameOverScreen");
  mainGo->addComponent<GameOverScreen>();

  return mainGo;
}

void GameOverScreen::onAwake()
{
  Audio::playSound(23);
  qn.reset(new QuickNumber());
  background = Resources::load<Texture2d>("textures/failScreen");
  timeout = 5;
}

void GameOverScreen::onGui()
{
  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), background.get());
  qn->drawW(score, Screen::getWidth() * 0.3f, Screen::getHeight() * 0.05f);

  timeout -= Time::getDeltaTime();

  if(timeout <= 0)
    Application::loadLevel("introduction");
}
