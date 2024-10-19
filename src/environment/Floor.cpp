#include <latebit/core/world/Object.h>
#include <latebit/core/world/ObjectUtils.h>
#include <latebit/core/world/WorldManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/utils/Logger.h>

using namespace lb;

class Tile : public Object {
public:
  Tile(const Vector position): Object("Tile") {
    setSprite("floor");
    setSolidness(Solidness::SOFT);
    setPosition(position);
  }
};

class Floor : public Object {
private:
  int tileWidth = 0;
  vector<Object*> tiles = {};

public:
  Floor(const Vector position, Scene* scene): Object("Floor") {
    this->setSolidness(Solidness::SOFT);
    this->setPosition(position);
    auto tile = WM.createObject<Tile>(scene, position);
    insert(this->tiles, tile);

    tileWidth = tile->getBox().getWidth();
    const auto tileHeight = tile->getBox().getHeight();
    const auto tiles = int(WINDOW_WIDTH / tileWidth) + 1;

    for (int i = 1; i <= tiles; i++) {
      auto t = WM.createObject<Tile>(scene, Vector(i * tileWidth + position.getX(), position.getY()));
      insert(this->tiles, t);
    }
    
    setBox(Box(WINDOW_WIDTH*2, tileHeight));
    subscribe(STEP_EVENT);
  }

  auto eventHandler(const Event *e) -> int override {
    if (e->getType() == STEP_EVENT) {
      return reposition();
    }

    return 0;
  }

  void setPosition(Vector position) {
    int count = 0;
    float x = position.getX(), y = position.getY();
    for (auto &tile : this->tiles) {
      tile->setPosition(Vector(count * tileWidth + x, y));
      count++;
    }
    Object::setPosition(position);
  }

  void setAltitude(int altitude) {
    for (auto &tile : this->tiles) {
      tile->setAltitude(altitude);
    }
    Object::setAltitude(altitude);
  }

  void teardown() override {
    auto tiles = WM.getAllObjectsByType("Tile");
    for (auto &tile : tiles) {
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
    } else {
      setPosition(position);
    }

    return 0;
  }
};