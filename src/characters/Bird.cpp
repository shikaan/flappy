#include <array>

#include <latebit/core/events/EventStep.h>
#include <latebit/core/events/EventInput.h>
#include <latebit/core/events/EventCollision.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/utils/Logger.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/core/utils/utils.h>

#include "../events/events.h"
#include "../environment/environment.h"

using namespace lb;

class Bird : public Object {
public:
  Vector ACCELERATION = Vector(0, 0.15);

  Bird() {
    setType("Bird");
    setSprite("bird");
  
    subscribe(INPUT_EVENT);
    subscribe(STEP_EVENT);
    subscribe(COLLISION_EVENT);

    const auto width = getBox().getWidth();
    const auto height = getBox().getHeight();

    setBox(Box(Vector(3, 3), width-6, height-6));
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == INPUT_EVENT) {
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (dashStep < 0 && DASH_COOLDOWN > 0 && inputEvent->getKey() == InputKey::A && inputEvent->getAction() == InputAction::PRESSED) {
        this->sfx->play();
        dashStep = DASH_DURATION;

        return 1;
      }
    }

    if (event->getType() == STEP_EVENT) {
      return handleStep();
    }

    if (event->getType() == COLLISION_EVENT) {
      return handleCollision(static_cast<const EventCollision*>(event));
    }

    return 0;
  }

private:
  const Sound* sfx = RM.getSound("dash");
  const int DASH_DURATION = 2;
  const int DASH_COOLDOWN = 40;

  int dashStep = -1;
  int dashCooldown = 0;

  bool isScoring = false;
  const Pipe* scoringPipe = nullptr;

  int handleStep() {
    if (getPosition().getY() < 24) {
      setPosition(Vector(getPosition().getX(), 24));
      setVelocity(Vector(getVelocity().getX(), 0));
      setAcceleration(ACCELERATION);
      dashCooldown = DASH_COOLDOWN;
    }

    if (dashStep >= 0) {
      if (dashStep == DASH_DURATION) {
        setVelocity(Vector());
        setAcceleration(Vector(0, -1));
      } else if (dashStep == 0) {
        dashStep = -1;
        dashCooldown = DASH_COOLDOWN;
        setAcceleration(ACCELERATION);
      }

      dashStep--;
      return 1;
    } else {
      dashCooldown--;
    }

    if (isScoring && scoringPipe && !intersects(getWorldBox(), scoringPipe->getWorldBox())) {
      isScoring = false;
      scoringPipe = nullptr;
      WM.onEvent(new EventScore());
      return 1;
    }

    return 0;
  }

  array<string, 3> DEADLY_OBJECTS = {"Floor", "TopPipe", "BottomPipe"};
  int handleCollision(const EventCollision* event) {
    auto other = event->getFirstObject() == this ? event->getSecondObject() : event->getFirstObject();

    if (other->getType() == "Pipe") {
      isScoring = true;
      scoringPipe = static_cast<const Pipe*>(other);
      return 1;
    }

    for (const auto& deadlyObject : DEADLY_OBJECTS) {
      if (other->getType() == deadlyObject) {
        WM.onEvent(new EventGameOver());
        return 1;
      }
    }

    return 0;
  }
};