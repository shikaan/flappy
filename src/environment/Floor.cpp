#include <latebit/core/objects/Object.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/utils/Logger.h>

using namespace lb;

class Tile : public Object {
public:
  Tile(): Object("Tile") {
    setSprite("floor");
    setSolidness(Solidness::SOFT);
    setDebug(true);
  }
};

class Floor : public Object {
private:
  vector<Tile> tiles = {};
  int tileWidth = 0;

public:
  Floor(): Object("Floor") {
    const auto tile = Tile();
    tileWidth = tile.getBox().getWidth();
    const auto tileHeight = tile.getBox().getHeight();
    const auto tiles = int(DM.getHorizontalCells() / tileWidth) + 1;

    this->tiles.resize(tiles);
    this->tiles.push_back(tile);

    for (int i = 1; i < tiles; i++) this->tiles.push_back(Tile());

    setBox(Box(DM.getHorizontalCells()*2, tileHeight));

    subscribe(STEP_EVENT);
    setDebug(true);
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
    auto count = 0;

    for (auto &tile : this->tiles) {
      tile.setPosition(Vector(count * tileWidth + x, y));
      result += tile.draw();
      count++;
    }

    return this->Object::draw() + result;
  }

  void setAltitude(int altitude) {
    for (auto &tile : this->tiles) tile.setAltitude(altitude);
    Object::setAltitude(altitude);
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