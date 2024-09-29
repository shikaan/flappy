#include <latebit/core/objects/Object.h>
#include <latebit/core/events/EventOut.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/utils/Logger.h>
#include <latebit/utils/Math.h>

using namespace lb;

class TopPipe : public Object {
public:
  TopPipe(): Object("TopPipe") {
    setSprite("top-pipe");
    setSolidness(Solidness::SOFT);
  }
};

class BottomPipe : public Object {
public:
  BottomPipe(): Object("BottomPipe") {
    setSprite("bottom-pipe");
    setSolidness(Solidness::SOFT);
  }
};

class Pipe : public Object {
public:
  const int GAP = 36;

  Pipe(): Object("Pipe") {
    subscribe(OUT_EVENT);
    setPosition(Vector());
    setSolidness(Solidness::SOFT);
    
    const auto pipeHeight = topPipe.getBox().getHeight();
    const auto totalPipeHeight = 2*pipeHeight + GAP;
    const auto pipeWidth = topPipe.getBox().getWidth();
    halfPipeHeight = pipeHeight / 2;

    setBox(Box(Vector(pipeWidth/2, 0), 1, totalPipeHeight));
  }

  int eventHandler(const Event *e) override {
    if (e->getType() == OUT_EVENT) {
      return handleOut(); 
    }
    return 0;
  }

  int setPosition(const Vector &position) {
    topPipe.setPosition(position);
    bottomPipe.setPosition(Vector(position.getX(), position.getY() + topPipe.getBox().getHeight() + GAP));
    Object::setPosition(position);
    return 1;
  }

  int setVelocity(const Vector &velocity) {
    topPipe.setVelocity(velocity);
    bottomPipe.setVelocity(velocity);
    Object::setVelocity(velocity);
    return 1;
  }

  void setAltitude(int altitude) {
    topPipe.setAltitude(altitude);
    bottomPipe.setAltitude(altitude);
    Object::setAltitude(altitude);
  }

private:
  TopPipe topPipe = TopPipe();
  BottomPipe bottomPipe = BottomPipe();
  int halfPipeHeight = 0;

  int handleOut() {
    const auto position = getPosition();
    const auto random = rand();
    const int y = position.getY() + (random % 10) * (random % 2 == 0 ? 1 : -1);
    setPosition(Vector(DM.getHorizontalCells(), clamp(y, -halfPipeHeight, 0)));
    return 1;
  }
};