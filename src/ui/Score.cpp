#include <latebit/core/objects/Object.h>
#include <latebit/core/graphics/DisplayManager.h>
#include "../events/events.h"
#include "../State.h"

using namespace lb;

class Score : public Object {
  public:
  Score(): Object("Score") {
    subscribe(SCORE_EVENT);
  }

  int draw() override {
    const int currentScore = STATE.getScore();
    int result = 0;
    result += DM.drawString(getPosition() + Vector(1,1),to_string(currentScore), TextAlignment::CENTER, Color::BLACK, TextSize::XLARGE);
    result += DM.drawString(getPosition(),to_string(currentScore), TextAlignment::CENTER, Color::WHITE, TextSize::XLARGE);
    return result;
  }
};