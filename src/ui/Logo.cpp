#include <latebit/core/objects/Object.h>

using namespace lb;

class Logo : public Object {
public:
  Logo(): Object("Logo") {
    setSprite("logo");
    auto box = getBox();
    setBox(Box(box.getWidth() * 3, box.getHeight() * 3));  
  }

  int draw() override {
    auto animation = getAnimation();
    auto frame = animation.getSprite()->getFrame(0);
    return DM.drawFrame(getPosition(), &frame, 3);
  }
};
