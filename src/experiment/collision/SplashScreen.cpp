#include "SplashScreen.h"

using namespace mutiny::engine;

void SplashScreen::onAwake()
{
  splashLogo = Resources::load<Texture2d>("images/loading");
  background.reset(new Texture2d(1, 1));
  background->setPixel(0, 0, Color(1, 1, 1, 1));
  background->apply();
  timeout = 3;
}

void SplashScreen::onGui()
{
  Gui::drawTexture(Rect(0, 0, Screen::getWidth(), Screen::getHeight()), background.get());

  Gui::drawTexture(Rect((Screen::getWidth() / 2) - (splashLogo->getWidth() / 2),
                        (Screen::getHeight() / 2) - (splashLogo->getHeight() / 2),
                        splashLogo->getWidth(), splashLogo->getHeight()), splashLogo);

  timeout -= Time::getDeltaTime();

  if(timeout <= 0)
  {
    Application::loadLevel("CollisionTest");
  }
}

