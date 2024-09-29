#include <latebit/core/objects/Object.h>
#include <latebit/core/graphics/DisplayManager.h>
#include "../events/events.h"

using namespace lb;

class Score : public Object {
  int currentScore = 0;

  public:
  Score(): Object("Score") {
    subscribe(SCORE_EVENT);
    init();
  }

  int eventHandler(const lb::Event *event) override {
    if (event->getType() == SCORE_EVENT) {
      currentScore++;
    }

    return 0;
  }

  int draw() override {
    DM.drawString(getPosition() + Vector(1,1),to_string(currentScore), TextAlignment::CENTER, Color::BLACK, TextSize::XLARGE);
    DM.drawString(getPosition(),to_string(currentScore), TextAlignment::CENTER, Color::WHITE, TextSize::XLARGE);
    return 0;
  }
  
  void init() {
    currentScore = 0;
  }
};