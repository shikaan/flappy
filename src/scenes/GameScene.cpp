#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/ResourceManager.h>

#include <sstream>
#include "../characters/Bird.cpp"
#include "../environment/environment.h"

using namespace lb;

class GameScene : public Object {
private:
  Bird *bird = new Bird();
  Floor *floor = new Floor();

  Pipe *pipe = new Pipe();

public:
  GameScene(): Object("GameScene") {
    setType("GameScene");
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

    const auto pipeHeight = DM.getVerticalCells() - this->floor->getBox().getHeight() - this->pipe->getBox().getHeight();
    this->pipe->setPosition(Vector(DM.getHorizontalCells() - 24, pipeHeight));
  }

  ~GameScene() {
    WM.removeObject(this->bird);
    WM.removeObject(this->floor);
    WM.removeObject(this->pipe);
  };
};