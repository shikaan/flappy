#include <latebit/core/geometry/Vector.h>
#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/graphics/Font.h>
#include <latebit/core/world/Object.h>
#include <latebit/core/events/EventInput.h>
#include <latebit/core/world/WorldManager.h>
#include <latebit/utils/Logger.h>
#include <latebit/ui/Text.h>
#include <latebit/ui/Rectangle.h>
#include <latebit/ui/utils.h>
#include <sstream>

#include "../events/events.h"
#include "../ui/ui.h"
#include "../characters/characters.h"

using namespace lbui;

class GameStartScene : public Scene {
public:
  Floor *floor = nullptr;
  Background *background = nullptr;
  Logo *logo = nullptr;
  Bird *bird = nullptr;

  Rectangle *box = nullptr;
  Text *start = nullptr;
  Text *instructions = nullptr;

  GameStartScene() {
    subscribe(INPUT_EVENT);
    auto floorSprite = RM.getSprite("floor");
    auto backgroundSprite = RM.getSprite("background");

    floor = this->createObject<Floor>(Vector(0, WINDOW_HEIGHT - floorSprite->getHeight()), this);
    background = this->createObject<Background>(Vector(0, WINDOW_HEIGHT - backgroundSprite->getHeight() - floorSprite->getHeight()), this);
    logo = this->createObject<Logo>();
    bird = this->createObject<Bird>();

    box = this->createObject<Rectangle>(RectangleOptions{
      .height = 32,
      .width = 104,
      .fill = Color::BROWN,
      .stroke = {Color::BROWN, Color::BROWN, Color::WHITE},
    });

    stringstream ss;
    ss << (char)InputGlyph::START << ": START GAME";
    start = this->createObject<Text>("Start", ss.str(), TextOptions{
      .color = Color::WHITE,
    });

    ss.str("");
    ss << (char)InputGlyph::A << ": FLAP      ";
    instructions = this->createObject<Text>("Instructions", ss.str(), TextOptions{
      .color = Color::WHITE,
    });
  }
  
  int eventHandler(const Event *event) override {
    if (event->getType() == INPUT_EVENT) {
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (inputEvent->getKey() == InputKey::START && inputEvent->getAction() == InputAction::PRESSED) {
        WM.switchToScene("GameScene");
        WM.broadcast(make_unique<EventGameStart>().get());
        return 1;
      }
    }

    return 0;
  }

  void onActivated() override {
    DM.setBackground(Color::BLUE);

    // logo->setPosition(Vector(WINDOW_WIDTH / 2.0 - logo->getBox().getWidth() / 2, 16));
    bird->setPosition(Vector(WINDOW_WIDTH / 2.0 - bird->getBox().getWidth() / 2, 64));
    setPositionOnScreen(logo, ScreenPosition::TOP_CENTER, Vector{0, 16});
    setPositionOnScreen(box, ScreenPosition::MIDDLE_CENTER, Vector{0 , 28});
    setPositionOnScreen(start, ScreenPosition::MIDDLE_CENTER, Vector{0 , 22});
    setPositionOnScreen(instructions, ScreenPosition::MIDDLE_CENTER, Vector{0 , 34});

    background->setAltitude(0);
    bird->setAltitude(1);
    floor->setAltitude(1);
    start->setAltitude(2);
    instructions->setAltitude(2);
    box->setAltitude(1);

    bird->setActive(false);
  }

  void onDeactivated() override {
    WM.markForDelete(bird);
  }
};