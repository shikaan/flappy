#include <latebit/core/objects/Object.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/graphics/DisplayManager.h>

using namespace lb;

class Floor : public Object {
private:
  const Sprite* sprite;

public:
  Floor(): Object("Floor") {
    setSprite("floor");
    sprite = getAnimation().getSprite();

    setBox(Box(DM.getHorizontalCells(), sprite->getHeight()));
  }

  auto draw() -> int override {
    auto result = 0;
    const auto tiles = (DM.getHorizontalCells() / sprite->getWidth()) + 1;
    const auto position = getPosition(); 

    for (int i = 0; i < tiles; i++ ) {
      result += sprite->draw(0, position + Vector(i * sprite->getWidth(), 0));
    }

    return result;
  }
};