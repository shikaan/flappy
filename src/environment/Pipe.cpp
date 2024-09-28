#include <latebit/core/objects/Object.h>
#include <latebit/core/events/EventOut.h>
#include <latebit/core/graphics/DisplayManager.h>

using namespace lb;

class Pipe : public Object {
public:
  Pipe(): Object("Pipe") {
    setSprite("pipe");
    subscribe(OUT_EVENT);
    setSolidness(Solidness::SOFT);
  }

  int eventHandler(const Event *e) override {
    if (e->getType() == OUT_EVENT) {
      return handleOut(); 
    }
    return 0;
  }

private:
  int handleOut() {
    const auto position = getPosition();
    setPosition(Vector(DM.getHorizontalCells(), position.getY()));
    return 1;
  }
};