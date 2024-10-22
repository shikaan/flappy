#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/world/Object.h>
#include <latebit/core/events/EventInput.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/world/Scene.h>
#include <latebit/core/world/WorldManager.h>
#include <latebit/utils/Logger.h>

#include "../events/events.h"
#include "../ui/ui.h"

using namespace lb;

class GameOverScene : public Scene {
private:
  const int RESTART_DELAY_STEPS = 60;
public:
  int stepsSinceStart = 0;
  Text* start = nullptr;
  Text* score = nullptr;
  Text* highScore = nullptr;

  GameOverScene() {
    const auto center = Vector(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
    auto gameOver = this->createObject<Text>("GameOver", "GAME OVER", TextOptions{
      .size = TextSize::XXLARGE,
      .alignment = TextAlignment::CENTER,
      .color = Color::WHITE,
      .shadow = Color::BLACK
    });
    gameOver->setPosition(center + Vector(0, -64));

    score = this->createObject<Text>("Score", "SCORE: 0", TextOptions{
      .size = TextSize::LARGE,
      .alignment = TextAlignment::CENTER,
      .color = Color::WHITE,
      .shadow = Color::BLACK
    });
    score->setPosition(center);

    highScore = this->createObject<Text>("HighScore", "HIGH: 0", TextOptions{
      .size = TextSize::LARGE,
      .alignment = TextAlignment::CENTER,
      .color = Color::WHITE,
      .shadow = Color::BLACK
    });
    highScore->setPosition(center + Vector(0, 24));

    start = this->createObject<Text>("Start", "Press START", TextOptions{
      .size = TextSize::NORMAL,
      .alignment = TextAlignment::CENTER,
      .color = Color::WHITE,
      .shadow = Color::BLACK
    });
    start->setPosition(center + Vector(0, 48));
    
    subscribe(INPUT_EVENT);
    subscribe(STEP_EVENT);
  }

  void onActivated() override {
    DM.setBackground(Color::DARK_BLUE);
    stepsSinceStart = 0;
    start->setVisible(false);
    score->setText("SCORE: " + to_string(STATE.getScore()));
    highScore->setText("HIGH: " + to_string(STATE.getHighScore()));
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == INPUT_EVENT && stepsSinceStart > RESTART_DELAY_STEPS) {
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (inputEvent->getKey() == InputKey::START && inputEvent->getAction() == InputAction::PRESSED) {
        WM.broadcast(make_unique<EventGameStart>().get());
        WM.switchToScene("GameScene");
        return 1;
      }
    }

    if (event->getType() == STEP_EVENT) {
      stepsSinceStart++;
      if (stepsSinceStart > RESTART_DELAY_STEPS) {
        start->setVisible(true);
      }
    }

    return 0;
  }
};