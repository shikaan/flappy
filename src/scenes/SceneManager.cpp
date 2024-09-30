#include <latebit/core/objects/Object.h>
#include "../events/events.h"

#include "GameScene.cpp"
#include "GameOverScene.cpp"
#include "GameStartScene.cpp"

using namespace lb;

class SceneManager : public Object {
public:

  GameScene *game = new GameScene();
  GameOverScene *gameOver = new GameOverScene();
  GameStartScene *gameStart = new GameStartScene();
  Scene *currentScene = nullptr;

  SceneManager(): Object("SceneManager") {
    subscribe(GAME_START_EVENT);
    subscribe(GAME_OVER_EVENT);

    game->setActive(false);
    gameOver->setActive(false);
    switchScene(gameStart);
  }

  int eventHandler(const Event *e) {
    if (e->getType() == GAME_START_EVENT) {
      return switchScene(game);
    } else if (e->getType() == GAME_OVER_EVENT) {
      return switchScene(gameOver);
    }
    return 0;
  }

  int switchScene(Scene *scene) {
    if (this->currentScene == scene) return 0;

    if (this->currentScene) {
      this->currentScene->setActive(false);
      this->currentScene->cleanup();
    }
    scene->setActive(true);
    scene->play();
    this->currentScene = scene;
    return 1;
  }
};