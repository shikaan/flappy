#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/ResourceManager.h>

#include <sstream>
#include "../characters/Bird.cpp"
#include "../environment/Floor.cpp"

using namespace lb;

class GameScene : public Object {
private:
  Bird *bird = new Bird();
  Floor *floor = new Floor();

public:
  GameScene() {
    // The scene is a container object for all the objects that will be drawn on
    // the screen.
    // Setting the type will allow you to retrieve the scene later on and to
    // identify it in the logs.
    setType("GameScene");

    // The Display Manager (DM) is responsible for drawing everything on the
    // screen. Here you can set the background color of the scene for example.
    DM.setBackground(Color::BLUE);

    const auto music = RM.getMusic("music");
    if (music != nullptr) {
      music->play(true);
    }

    // In the following block we are placing objects in the scene.
    const auto center =
        Vector(DM.getHorizontalCells() / 2.0, DM.getVerticalCells() / 2.0);

    const auto birdBox = this->bird->getBox();
    this->bird->setPosition(
        center - Vector(birdBox.getWidth() / 2, 32 - birdBox.getHeight() / 2));

    const auto floorPosition = Vector(0, DM.getVerticalCells() - this->floor->getBox().getHeight());
    this->floor->setPosition(floorPosition);
  }

  ~GameScene() {
    WM.removeObject(this->bird);
    WM.removeObject(this->floor);
  };
};