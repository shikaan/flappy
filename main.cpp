#include "src/scenes/GameScene.cpp"

#include <latebit/core/configuration/Configuration.h>
#include <latebit/core/GameManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/utils/Logger.h>

using namespace lb;

int main() {
  Configuration::fromFile("latebit.cfg");
  GM.startUp();

  RM.loadTextSprite("assets/sprites/bird.lbspr", "bird");
  RM.loadImageSprite("assets/sprites/logo.png", "logo");
  RM.loadMusic("assets/audio/music.lbmus", "music");
  RM.loadSound("assets/audio/sound.lbsfx", "sound");

  auto scene = new GameScene();

  GM.run();
  delete scene;

  return 0;
}
