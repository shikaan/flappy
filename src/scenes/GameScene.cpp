#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/GameManager.h>
#include <latebit/core/world/WorldManager.h>

#include "../characters/characters.h"
#include "../environment/environment.h"
#include "../ui/ui.h"
#include "../State.h"
#include "Scene.h"

using namespace lb;

class GameScene : public Scene {
public:
  const Vector CENTER = Vector(DM::WINDOW_WIDTH / 2.0, DM::WINDOW_HEIGHT / 2.0);
  const Vector GAME_VELOCITY = Vector(-1, 0);

  const Sound* scoreSfx = RM.getSound("score");
  const Sound* gameOverSfx = RM.getSound("game-over");

  void makeScore() {
    auto score = WM::create<Score>();
    STATE.reset();
    score->setPosition(Vector(DM::WINDOW_WIDTH / 2, 8));
    score->setAltitude(4);
  }

  void makeBird() {
    Bird* bird = WM::create<Bird>();
    auto birdBox = bird->getBox();
    bird->setPosition(
        CENTER - Vector(birdBox.getWidth() / 2, 32 - birdBox.getHeight() / 2));
    bird->setAltitude(3);
    bird->setAcceleration(Vector(0, 0.1));
  }

  const int PIPE_DISTANCE = DM::WINDOW_WIDTH / 3;
  void makePipe(int index) {
    auto pipe = WM::create<Pipe>();
    const auto pipeWidth = pipe->getBox().getWidth();
    const auto pipePosition = Vector(DM::WINDOW_WIDTH + index * (PIPE_DISTANCE + pipeWidth / 3), -16);
    pipe->setPosition(pipePosition);
    pipe->setVelocity(GAME_VELOCITY);
    pipe->setAltitude(1);
  }

  void makeFloor() {
    auto floors = WM::getAllObjectsByType("Floor");
    Floor* floor = nullptr;
    
    if (floors.empty()) {
      auto floorSprite = RM.getSprite("floor");
      floor = WM::create<Floor>(Vector(0, DM::WINDOW_HEIGHT - floorSprite->getHeight()));
    } else {
      floor = static_cast<Floor*>(floors[0]);
    }

    floor->setVelocity(GAME_VELOCITY);
    floor->setAltitude(2);
  }

  void makeBackground() {
    auto backgrounds = WM::getAllObjectsByType("Background");
    Background* background = nullptr;

    if (backgrounds.empty()) {
      auto floorSprite = RM.getSprite("floor");
      auto backgroundSprite = RM.getSprite("background");
      background = WM::create<Background>(Vector(0, DM::WINDOW_HEIGHT - backgroundSprite->getHeight() - floorSprite->getHeight()));
    } else {
      background = static_cast<Background*>(backgrounds[0]);
    }

    background->setVelocity(Vector(-0.1, 0));
    background->setAltitude(0);
  }

  void play() override {
    DM::setBackground(Color::BLUE);
    makePipe(0);
    makePipe(1);
    makePipe(2);
    makeScore();
    makeBird();
    makeFloor();
    makeBackground();
  }

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
    auto os = WM::getAllObjects();
    for (auto& o : os) {
      for (auto type : CLEANUP_TYPES) {
        if (o->getType() == type) {
          WM::markForDelete(o);
        }
      }
    }
  };
};