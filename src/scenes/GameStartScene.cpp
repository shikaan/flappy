#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/world/Object.h>
#include <latebit/core/events/EventInput.h>
#include <latebit/core/world/WorldManager.h>
#include <latebit/utils/Logger.h>

#include "../events/events.h"
#include "../ui/ui.h"
#include "../characters/characters.h"

class GameStartScene : public Scene {
public:
  Floor *floor = nullptr;
  Background *background = nullptr;
  Logo *logo = nullptr;
  Bird *bird = nullptr;
  Text *text = nullptr;

  GameStartScene() {
    subscribe(INPUT_EVENT);
    auto floorSprite = RM.getSprite("floor");
    auto backgroundSprite = RM.getSprite("background");

    floor = WM.createObject<Floor>(this, Vector(0, WINDOW_HEIGHT - floorSprite->getHeight()), this);
    background = WM.createObject<Background>(this, Vector(0, WINDOW_HEIGHT - backgroundSprite->getHeight() - floorSprite->getHeight()), this);
    logo = WM.createObject<Logo>(this);
    bird = WM.createObject<Bird>(this);
    text = WM.createObject<Text>(this, "Start", "Press START", TextOptions{
      .alignment = TextAlignment::CENTER,
      .color = Color::WHITE,
      .background = Color::DARK_BLUE,
      .shadow = Color::BLACK
    });
  }
  
  int eventHandler(const Event *event) override {
    if (event->getType() == INPUT_EVENT) {
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (inputEvent->getKey() == InputKey::START && inputEvent->getAction() == InputAction::PRESSED) {
        WM.switchToScene("GameScene");
        WM.onEvent(make_unique<EventGameStart>().get());
        return 1;
      }
    }

    return 0;
  }

  void onActivated() override {
    DM.setBackground(Color::BLUE);

    logo->setPosition(Vector(WINDOW_WIDTH / 2.0 - logo->getBox().getWidth() / 2, 24));
    bird->setPosition(Vector(WINDOW_WIDTH / 2.0 - bird->getBox().getWidth() / 2, 72));
    text->setPosition(Vector(WINDOW_WIDTH / 2.0, 96));
    
    background->setAltitude(0);
    bird->setAltitude(1);
    floor->setAltitude(1);
    text->setAltitude(1);
  }

  void onDeactivated() override {
  }
};