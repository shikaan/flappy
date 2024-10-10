#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/ObjectUtils.h>
#include <latebit/core/world/WorldManager.h>
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
  vector<Object*> tiles = {};

public:
  Background(const Vector position): Object("Background") {
    this->setPosition(position);
    const auto tile = WM::create<BackgroundTile>(position);
    insert(this->tiles, tile);

    tileWidth = tile->getBox().getWidth();
    const auto tileHeight = tile->getBox().getHeight();
    const auto tiles = int(DM::WINDOW_WIDTH / tileWidth) + 1;

    for (int i = 1; i <= tiles; i++) {
      auto t = WM::create<BackgroundTile>(Vector(i * tileWidth + position.getX(), position.getY()));
      insert(this->tiles, t);
    }
    
    setBox(Box(DM::WINDOW_HEIGHT*2, tileHeight));
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

    for (auto tile : this->tiles) {
      tile->setPosition(Vector(count * tileWidth + x, y));
      result += tile->draw();
      count++;
    }

    return this->Object::draw() + result;
  }

  void setAltitude(int altitude) {
    for (auto tile : this->tiles) {
      tile->setAltitude(altitude);
    }
    Object::setAltitude(altitude);
  }

  void teardown () override {
    for (auto tile : this->tiles) {
      WM::markForDelete(tile);
    }
    tiles.clear();
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