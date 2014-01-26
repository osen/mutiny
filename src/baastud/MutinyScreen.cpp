#include "MutinyScreen.h"

using namespace mutiny::engine;

GameObject* MutinyScreen::create()
{
  GameObject* mainGo = new GameObject("MutinyScreen");
  mainGo->addComponent<MutinyScreen>();

  return mainGo;
}

void MutinyScreen::onAwake()
{
  background = Resources::load<Texture2d>("textures/white");
  mutinyLogo = Resources::load<Texture2d>("textures/ggj14");
  timeout = 3;
}

void MutinyScreen::onGui()
{
  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), background);
  Gui::drawTexture(Rect((Screen::getWidth() / 2) - (mutinyLogo->getWidth() / 2),
                        (Screen::getHeight() / 2) - (mutinyLogo->getHeight() / 2),
                        mutinyLogo->getWidth(), mutinyLogo->getHeight()), mutinyLogo);

  timeout -= Time::getDeltaTime();

  if(timeout <= 0)
    Application::loadLevel("introduction");
}
