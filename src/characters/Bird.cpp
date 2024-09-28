#include <latebit/core/events/EventStep.h>
#include <latebit/core/events/EventInput.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/core/ResourceManager.h>

using namespace lb;

class Bird : public Object {
public:
  Bird() {
    setType("Bird");
    setSprite("bird");
  
    subscribe(INPUT_EVENT);
    subscribe(STEP_EVENT);
    setDebug(true);
    setVelocity(VELOCITY);
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == INPUT_EVENT) {
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (isDashing) {
        return 1;
      }

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

    return 0;
  }

private:
  const Sound* sfx = RM.getSound("dash");
  const Vector VELOCITY = Vector(0, 0.8);
  const Vector DASH_VELOCITY = Vector(0, -1.6);
  const int DASH_DURATION = 10;

  int isDashing = false;
  int dashingStep = -1;

  int handleStep() {
    const auto velocity = getVelocity();
    
    if (isDashing) {
      setVelocity(DASH_VELOCITY + Vector(0, 0.05));
      dashingStep--;

      if (dashingStep == 0) {
        isDashing = false;
        setVelocity(VELOCITY);
      }

      return 1;
    }

    return 0;
  }
};