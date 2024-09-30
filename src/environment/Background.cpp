#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/ObjectList.h>
#include <latebit/core/objects/ObjectListIterator.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/utils/Logger.h>

using namespace lb;

class BackgroundTile : public Object {
public:
  BackgroundTile(const Vector position): Object("BackgroundTile") {
    setSprite("background");
    setSolidness(Solidness::SPECTRAL);
    setPosition(position);
  }
};

class Background : public Object {
private:
  int tileWidth = 0;
  ObjectList tiles = {};

public:
  Background(const Vector position): Object("Background") {
    this->setPosition(position);
    const auto tile = new BackgroundTile(position);
    this->tiles.insert(tile);

    tileWidth = tile->getBox().getWidth();
    const auto tileHeight = tile->getBox().getHeight();
    const auto tiles = int(DM.getHorizontalCells() / tileWidth) + 1;

    for (int i = 1; i <= tiles; i++) {
      auto t = new BackgroundTile(Vector(i * tileWidth + position.getX(), position.getY()));
      this->tiles.insert(t);
    }
    
    setBox(Box(DM.getHorizontalCells()*2, tileHeight));
    subscribe(STEP_EVENT);
    setSolidness(Solidness::SPECTRAL);
  }

  auto eventHandler(const Event *e) -> int override {
    if (e->getType() == STEP_EVENT) {
      return reposition();
    }

    return 0;
  }

  auto draw() -> int override {
    const auto position = getPosition();
    const auto y = position.getY();
    const auto x = position.getX();
    auto result = 0;
    int count = 0;

    auto tiles = ObjectListIterator(&this->tiles);
    for (tiles.first(), count = 0; !tiles.isDone(); tiles.next(), count++) {
      auto tile = tiles.currentObject();
      tile->setPosition(Vector(count * tileWidth + x, y));
      result += tile->draw();
    }

    return this->Object::draw() + result;
  }

  void setAltitude(int altitude) {
    auto tiles = ObjectListIterator(&this->tiles);
    for (tiles.first(); !tiles.isDone(); tiles.next()) {
      tiles.currentObject()->setAltitude(altitude);
    }
    Object::setAltitude(altitude);
  }

  ~Background() {
    auto tiles = ObjectListIterator(&this->tiles);
    for (tiles.first(); !tiles.isDone(); tiles.next()) {
      auto tile = tiles.currentObject();
      WM.markForDelete(tile);
    }
  }

private:
  int reposition() {
    const auto position = getPosition();
    const auto y = position.getY();
    const auto x = position.getX();
    
    if (x + this->tileWidth <= 0) {
      setPosition(Vector(0, y));
      return 1;
    }

    return 0;
  }
};