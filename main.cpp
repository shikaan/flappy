#include "src/scenes/scenes.h"

#include <latebit/core/configuration/Configuration.h>
#include <latebit/core/GameManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/utils/Logger.h>

using namespace lb;

int main() {
  Log.setLevel(LogLevel::ERROR);
  Log.setDestination(LogDestination::STDOUT);
  Configuration::fromFile("latebit.cfg");
  GM.startUp();

  RM.loadTextSprite("assets/sprites/bird.lbspr", "bird");
  RM.loadTextSprite("assets/sprites/floor.lbspr", "floor");
  RM.loadTextSprite("assets/sprites/bottom-pipe.lbspr", "bottom-pipe");
  RM.loadTextSprite("assets/sprites/top-pipe.lbspr", "top-pipe");
  RM.loadTextSprite("assets/sprites/logo.lbspr", "logo");
  RM.loadTextSprite("assets/sprites/background.lbspr", "background");
  RM.loadSound("assets/audio/dash.lbsfx", "dash");
  RM.loadSound("assets/audio/score.lbsfx", "score");
  RM.loadSound("assets/audio/gameover.lbsfx", "game-over");

  WM.createScene<GameStartScene>("GameStartScene");
  WM.createScene<GameScene>("GameScene");
  WM.createScene<GameOverScene>("GameOverScene");
  WM.activateScene("GameStartScene");
  GM.run();

  return 0;
}
