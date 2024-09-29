#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/GameManager.h>

#include <sstream>
#include "../characters/Bird.cpp"
#include "../environment/environment.h"

using namespace lb;

class GameScene : public Object {
private:
  const int HORIZONTAL_CELLS = DM.getHorizontalCells();
  const int VERTICAL_CELLS = DM.getVerticalCells();
  const Vector GAME_VELOCITY = Vector(-1, 0);

  Bird *bird = new Bird();
  Floor *floor = new Floor();
  array<Pipe*, 3> pipes = { new Pipe(), new Pipe(), new Pipe() };
  const Sound* scoreSfx = RM.getSound("score");
  const Sound* gameOverSfx = RM.getSound("game-over");

  int currentScore = 0; 

  void init() {
    DM.setBackground(Color::BLUE);
    currentScore = 0;

    // In the following block we are placing objects in the scene.
    const auto center =
        Vector(HORIZONTAL_CELLS / 2.0, VERTICAL_CELLS / 2.0);

    const auto birdBox = this->bird->getBox();
    this->bird->setPosition(
        center - Vector(birdBox.getWidth() / 2, 32 - birdBox.getHeight() / 2));
    this->bird->setAltitude(3);

    const auto DISTANCE = HORIZONTAL_CELLS / 3;
    for (int i = 0; i < 3; i++) {
      const auto pipe = this->pipes[i];
      const auto pipeWidth = pipe->getBox().getWidth();
      const auto pipePosition = Vector(HORIZONTAL_CELLS + i * (DISTANCE + pipeWidth/3), -32);
      pipe->setPosition(pipePosition);
      pipe->setVelocity(GAME_VELOCITY);
      pipe->setAltitude(1);
    }

    const auto floorPosition = Vector(0, VERTICAL_CELLS - this->floor->getBox().getHeight());
    this->floor->setPosition(floorPosition);
    this->floor->setVelocity(GAME_VELOCITY);
    this->floor->setAltitude(2);
  }

public:
  GameScene(): Object("GameScene") {
    setType("GameScene");
    subscribe("GameOver");
    subscribe("Score");
    init();
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == "GameOver") {
      DM.setBackground(Color::RED);
      this->gameOverSfx->play();
      GM.pause();
      return 1;
    }

    if (event->getType() == "Score") {
      this->scoreSfx->play();
      this->currentScore++;
      Log.info("Score: " + to_string(this->currentScore));
    }

    return 0;
  }

  ~GameScene() {
    WM.removeObject(this->bird);
    WM.removeObject(this->floor);
    for (auto pipe : this->pipes) {
      WM.removeObject(pipe);
    }
  };
};