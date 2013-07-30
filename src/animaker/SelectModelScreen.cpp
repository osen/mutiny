#include "SelectModelScreen.h"

#include <sys/types.h>
#include <dirent.h>

using namespace mutiny::engine;

std::string SelectModelScreen::choice;

void SelectModelScreen::scanDir(std::string directory, std::vector<std::string>* files)
{
  DIR* dp = NULL;
  struct dirent* ep = NULL;

  dp = opendir (directory.c_str());

  if(dp != NULL)
  {
    while(ep = readdir(dp))
    {
      std::string filename = ep->d_name;

      if(filename == "." || filename == "..")
      {
        continue;
      }

      scanDir(directory + "/" + filename, files);
      files->push_back(directory + "/" + filename);
    }

    closedir (dp);
  }
}

void SelectModelScreen::onAwake()
{
  titleFont = Resources::load<Font>("fonts/default");

  scanDir(".", &files);

  for(int i = 0; i < files.size(); i++)
  {
    std::string curr = files.at(i);

    if(curr.length() <= 4 || curr.substr(curr.length() - 4) != ".obj")
    {
      files.erase(files.begin() + i);
      i--;
    }
  }
}

void SelectModelScreen::onUpdate()
{

}

void SelectModelScreen::onGui()
{
  Gui::label(Rect(100, 100, 100, 100), "select a model");

  for(int i = 0; i < files.size(); i++)
  {
    if(Gui::button(Rect(50, 50 + i * 40, 200, 30), files.at(i)) == true)
    {
      choice = files.at(i);
      Application::loadLevel("Main");
    }
  }

  if(Gui::button(Rect(200, 200, 100, 30), "load") == true)
  {
    Application::loadLevel("Main");
  }

  if(Gui::button(Rect(Screen::getWidth() - 110, Screen::getHeight() - 40, 100, 30), "close") == true)
  {
    Application::quit();
  }
}

