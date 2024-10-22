#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/world/Object.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/GameManager.h>
#include <latebit/core/world/WorldManager.h>

#include "../characters/characters.h"
#include "../environment/environment.h"
#include "../ui/ui.h"
#include "../State.h"

using namespace lb;

class GameScene : public Scene {
public:
  const Vector CENTER = Vector(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
  const Vector GAME_VELOCITY = Vector(-1, 0);
    int stepsSinceStart = 0;
  const Sound* scoreSfx = RM.getSound("score");
  const Sound* gameOverSfx = RM.getSound("game-over");

  Bird* bird = nullptr;
  Score* score = nullptr;
  array<Pipe*, 3> pipes = {nullptr, nullptr, nullptr};
  Background* background = nullptr;
  Floor* floor = nullptr;

  GameScene() {
    subscribe(GAME_OVER_EVENT);
    subscribe(SCORE_EVENT);

    auto floorSprite = RM.getSprite("floor");
    auto backgroundSprite = RM.getSprite("background");
    bird = this->createObject<Bird>();
    bird->setActive(false);
    score = this->createObject<Score>();
    pipes[0] = this->createObject<Pipe>(this);
    pipes[1] = this->createObject<Pipe>(this);
    pipes[2] = this->createObject<Pipe>(this);
    background = this->createObject<Background>(Vector(0, WINDOW_HEIGHT - backgroundSprite->getHeight() - floorSprite->getHeight()), this);
    floor = this->createObject<Floor>(Vector(0, WINDOW_HEIGHT - floorSprite->getHeight()), this);
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == GAME_OVER_EVENT) {
      this->gameOverSfx->play();
      WM.switchToScene("GameOverScene");
      return 1;
    }

    if (event->getType() == SCORE_EVENT) {
      this->scoreSfx->play();
      STATE.increment();
      return 1;
    }

    return 0;
  }

  void makeScore() {
    STATE.reset();
    score->setPosition(Vector(WINDOW_WIDTH / 2.0, 8));
    score->setAltitude(4);
  }

  void makeBird() {
    auto birdBox = bird->getBox();
    bird->setPosition(
        CENTER - Vector(birdBox.getWidth() / 2, 32 - birdBox.getHeight() / 2));
    bird->setAltitude(3);
    bird->setAcceleration(Vector(0, 0.1));
    bird->setVelocity({});
  }

  const int PIPE_DISTANCE = WINDOW_WIDTH / 3;
  void makePipe(int index) {
    auto pipe = pipes[index];
    const auto pipeWidth = pipe->getBox().getWidth();
    const auto pipePosition = Vector(WINDOW_WIDTH + index * (PIPE_DISTANCE + pipeWidth / 3), -16);
    pipe->setPosition(pipePosition);
    pipe->setVelocity(GAME_VELOCITY);
    pipe->setAltitude(1);
  }

  void makeFloor() {
    floor->setVelocity(GAME_VELOCITY);
    floor->setAltitude(2);
  }

  void makeBackground() {
    background->setVelocity(Vector(-0.1, 0));
    background->setAltitude(0);
  }

  void onActivated() override {
    DM.setBackground(Color::BLUE);
    makePipe(0);
    makePipe(1);
    makePipe(2);
    makeScore();
    makeBird();
    makeFloor();
    makeBackground();
    bird->setActive(true);
  }

  void onDeactivated() override {
    bird->setActive(false);
  };
};