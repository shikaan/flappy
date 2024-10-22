#include <latebit/core/world/Object.h>
#include <latebit/core/graphics/DisplayManager.h>

using namespace lb;

class Logo : public Object {
public:
  Logo(): Object("Logo") {
    setSprite("logo");
    auto box = getBox();
    setBox(Box(box.getWidth() * 3, box.getHeight() * 3));
    this->setScale(3);
  }
};
