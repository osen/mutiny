#include "GameOverScreen.h"
#include "QuickNumber.h"

using namespace mutiny::engine;

int GameOverScreen::score = 0;

GameObject* GameOverScreen::create()
{
  GameObject* mainGo = new GameObject("GameOverScreen");
  mainGo->addComponent<GameOverScreen>();

  return mainGo;
}

void GameOverScreen::onAwake()
{
  qn.reset(new QuickNumber());
  background = Resources::load<Texture2d>("textures/failScreen");
  timeout = 5;
}

void GameOverScreen::onGui()
{
  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), background);

  qn->drawW(score, Screen::getWidth() * 0.3f, Screen::getHeight() * 0.05f);

  timeout -= Time::getDeltaTime();

  if(timeout <= 0)
  {
    Application::loadLevel("introduction");
  }
}
