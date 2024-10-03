#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/events/EventInput.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/utils/Logger.h>

#include "../events/events.h"
#include "../State.h"
#include "Scene.h"

using namespace lb;

class GameOverScene : public Scene {
private:
  int stepsSinceStart = 0;

public:
  GameOverScene(): Scene("GameOverScene") {
    subscribe(INPUT_EVENT);
    subscribe(STEP_EVENT);
  }

  void play() override {
    DM::setBackground(Color::DARK_BLUE);
    stepsSinceStart = 0;
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == INPUT_EVENT && stepsSinceStart > 60) {
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (inputEvent->getKey() == InputKey::START && inputEvent->getAction() == InputAction::PRESSED) {
        WM.onEvent(new EventGameStart());
        return 1;
      }
    }

    if (event->getType() == STEP_EVENT) {
      stepsSinceStart++;
    }

    return 0;
  }

  int draw() override {
    const auto center = Vector(DM::WINDOW_WIDTH / 2.0, DM::WINDOW_HEIGHT / 2.0);
    const auto message = "GAME OVER";
    int result = 0;

    const auto delta = Vector(0, -64);

    result += DM::drawString(center + delta, message, TextAlignment::CENTER, Color::BLACK, TextSize::XXLARGE);
    result += DM::drawString(center + delta + Vector(3,3), message, TextAlignment::CENTER, Color::WHITE, TextSize::XXLARGE);

    result += DM::drawRectangle(center - Vector(64, 8), 128, 56, Color::INDIGO, Color::INDIGO);
    
    const auto score = "SCORE: " + to_string(STATE.getScore());
    result += DM::drawString(center, score, TextAlignment::CENTER, Color::DARK_BLUE, TextSize::LARGE);
    result += DM::drawString(center + Vector(1,1), score, TextAlignment::CENTER, Color::WHITE, TextSize::LARGE);

    const auto highScore = " HIGH: " + to_string(STATE.getHighScore());
    result += DM::drawString(center + Vector(0, 24), highScore, TextAlignment::CENTER, Color::DARK_BLUE, TextSize::LARGE);
    result += DM::drawString(center + Vector(0, 24) + Vector(1,1), highScore, TextAlignment::CENTER, Color::WHITE, TextSize::LARGE);

    if (stepsSinceStart > 60) {
      result += DM::drawString(center + Vector(0, 56), "Press START to restart", TextAlignment::CENTER, Color::WHITE, TextSize::NORMAL);
    }

    return result;
  }

  void cleanup() override {}
};