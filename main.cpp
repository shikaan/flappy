#include "src/scenes/GameScene.cpp"

#include <latebit/core/configuration/Configuration.h>
#include <latebit/core/GameManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/utils/Logger.h>

using namespace lb;

int main() {
  // Log.setLevel(LogLevel::DEBUG);
  Log.setDestination(LogDestination::STDOUT);
  Configuration::fromFile("latebit.cfg");
  GM.startUp();

  RM.loadTextSprite("assets/sprites/bird.lbspr", "bird");
  RM.loadTextSprite("assets/sprites/floor.lbspr", "floor");
  RM.loadTextSprite("assets/sprites/bottom-pipe.lbspr", "bottom-pipe");
  RM.loadTextSprite("assets/sprites/top-pipe.lbspr", "top-pipe");
  RM.loadSound("assets/audio/dash.lbsfx", "dash");

  auto scene = new GameScene();

  GM.run();
  delete scene;

  return 0;
}
