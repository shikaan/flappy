#include <latebit/core/events/EventOut.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/events/EventInput.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/core/ResourceManager.h>

using namespace lb;

class Bird : public Object {
private:
  const Sound* sfx = RM.getSound("sound");
public:
  Bird() {
    setType("Bird");
    setSprite("bird");
  
    subscribe(INPUT_EVENT);
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == INPUT_EVENT) {
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (inputEvent->getKey() == InputKey::A && inputEvent->getAction() == InputAction::PRESSED) {
        this->sfx->play();

        return 1;
      }
    }

    return 0;
  }
};