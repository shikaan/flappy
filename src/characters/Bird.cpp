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
  Bird() {
    setType("Bird");
    setSprite("bird");
    setVelocity(VELOCITY);
  
    subscribe(INPUT_EVENT);
    subscribe(STEP_EVENT);
    subscribe(COLLISION_EVENT);
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == INPUT_EVENT) {
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (inputEvent->getKey() == InputKey::A && inputEvent->getAction() == InputAction::PRESSED) {
        this->sfx->play();
        isDashing = true;
        dashingStep = DASH_DURATION;

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
  const Vector VELOCITY = Vector(0, 0.8);
  const int DASH_DURATION = 12;

  bool isDashing = false;
  int dashingStep = -1;

  bool isScoring = false;
  const Pipe* scoringPipe = nullptr;

  int handleStep() {
    const auto velocity = getVelocity();
    
    if (isDashing) {
      if (dashingStep == DASH_DURATION) {
        setVelocity(Vector(0));
      } else if (dashingStep >= DASH_DURATION*2/3) {
        setVelocity(velocity + Vector(0, -1));
      } else if (dashingStep >= DASH_DURATION/3) {
        setVelocity(velocity + Vector(0, 1));
      } else if (dashingStep == 0) {
        isDashing = false;
        setVelocity(VELOCITY);
      }

      dashingStep--;
      return 1;
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