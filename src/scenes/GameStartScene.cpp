#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/ObjectList.h>
#include <latebit/core/objects/ObjectListIterator.h>
#include <latebit/core/events/EventInput.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/utils/Logger.h>

#include "../events/events.h"
#include "../ui/ui.h"
#include "../characters/characters.h"
#include "Scene.h"

using namespace lb;

class GameStartScene : public Scene {
private:
public:
  GameStartScene(): Scene("GameStartScene") {
    subscribe(INPUT_EVENT);
  }

  void play() override {
    DM::setBackground(Color::BLUE);
    auto floorSprite = RM.getSprite("floor");
    new Floor(Vector(0, DM::WINDOW_HEIGHT - floorSprite->getHeight()));

    auto backgroundSprite = RM.getSprite("background");
    auto background = new Background(Vector(0, DM::WINDOW_HEIGHT - backgroundSprite->getHeight() - floorSprite->getHeight()));
    background->setAltitude(0);

    auto logo = new Logo();
    const auto logoBox = logo->getBox();
    logo->setPosition(Vector(DM::WINDOW_WIDTH / 2 - logoBox.getWidth() / 2, 24));

    auto bird = new Bird();
    const auto birdBox = bird->getBox();
    bird->setPosition(Vector(DM::WINDOW_WIDTH / 2 - birdBox.getWidth() / 2, 72));

    (new Text("Start", "Press START", TextOptions{
      .alignment = TextAlignment::CENTER,
      .color = Color::WHITE,
      .background = Color::DARK_BLUE,
      .shadow = Color::BLACK
    }))->setPosition(Vector(DM::WINDOW_WIDTH / 2, 96));
  }

  int eventHandler(const Event *event) override {
    if (event->getType() == INPUT_EVENT) {
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (inputEvent->getKey() == InputKey::START && inputEvent->getAction() == InputAction::PRESSED) {
        WM.onEvent(new EventGameStart());
        return 1;
      }
    }

    return 0;
  }

  void cleanup() override {
    auto os = WM.getAllObjects();
    auto it = ObjectListIterator(&os);
    for (it.first(); !it.isDone(); it.next()) {
      auto o = it.currentObject();
      if (o->getType() == "Logo" || o->getType() == "Bird" || o->getType() == "Start") {
        WM.markForDelete(o);
      }
    }
  }
};