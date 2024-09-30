#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/GameManager.h>

#include <sstream>
#include "../characters/characters.h"
#include "../environment/environment.h"
#include "../ui/ui.h"
#include "../State.h"
#include "Scene.h"

using namespace lb;

class GameScene : public Scene {
private:
  const int HORIZONTAL_CELLS = DM.getHorizontalCells();
  const int VERTICAL_CELLS = DM.getVerticalCells();
  const Vector CENTER = Vector(HORIZONTAL_CELLS / 2.0, VERTICAL_CELLS / 2.0);
  const Vector GAME_VELOCITY = Vector(-1, 0);

  const Sound* scoreSfx = RM.getSound("score");
  const Sound* gameOverSfx = RM.getSound("game-over");

  void makeScore() {
    auto score = new Score();
    STATE.reset();
    score->setPosition(Vector(HORIZONTAL_CELLS / 2, 8));
    score->setAltitude(4);
  }

  void makeBird() {
    auto bird = new Bird();
    const auto birdBox = bird->getBox();
    bird->setPosition(
        CENTER - Vector(birdBox.getWidth() / 2, 32 - birdBox.getHeight() / 2));
    bird->setAltitude(3);
  }

  const int PIPE_DISTANCE = HORIZONTAL_CELLS / 3;
  void makePipe(int index) {
    auto pipe = new Pipe();
    const auto pipeWidth = pipe->getBox().getWidth();
    const auto pipePosition = Vector(HORIZONTAL_CELLS + index * (PIPE_DISTANCE + pipeWidth / 3), -32);
    pipe->setPosition(pipePosition);
    pipe->setVelocity(GAME_VELOCITY);
    pipe->setAltitude(1);
  }

  void makeFloor() {
    auto floors = WM.objectsOfType("Floor");
    auto it = ObjectListIterator(&floors);
    auto floor = static_cast<Floor*>(it.currentObject());

    if (floor == nullptr) {
      auto floorSprite = RM.getSprite("floor");
      floor = new Floor(Vector(0, VERTICAL_CELLS - floorSprite->getHeight()));
    }

    floor->setVelocity(GAME_VELOCITY);
    floor->setAltitude(2);
  }

  void makeBackground() {
    auto backgrounds = WM.objectsOfType("Background");
    auto it = ObjectListIterator(&backgrounds);
    auto background = static_cast<Background*>(it.currentObject());

    if (background == nullptr) {
      auto floorSprite = RM.getSprite("floor");
      auto backgroundSprite = RM.getSprite("background");
      background = new Background(Vector(0, VERTICAL_CELLS - backgroundSprite->getHeight() - floorSprite->getHeight()));
    }

    background->setVelocity(Vector(-0.1, 0));
    background->setAltitude(0);
  }

  void play() override{
    DM.setBackground(Color::BLUE);
    makePipe(0);
    makePipe(1);
    makePipe(2);
    makeScore();
    makeBird();
    makeFloor();
    makeBackground();
  }

public:
  GameScene(): Scene("GameScene") {
    subscribe(GAME_OVER_EVENT);
    subscribe(SCORE_EVENT);
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == GAME_OVER_EVENT) {
      this->gameOverSfx->play();
      return 1;
    }

    if (event->getType() == SCORE_EVENT) {
      this->scoreSfx->play();
      STATE.increment();
      return 1;
    }

    return 0;
  }

  array<string, 5> CLEANUP_TYPES = {"Bird", "Floor", "Pipe", "Score", "Background"};
  void cleanup() override {
    auto os = WM.getAllObjects();
    auto it = ObjectListIterator(&os);
    for (it.first(); !it.isDone(); it.next()) {
      auto o = it.currentObject();
      for (auto type : CLEANUP_TYPES) {
        if (o->getType() == type) {
          WM.markForDelete(o);
        }
      }
    }
  };
};