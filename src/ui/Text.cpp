#include <latebit/core/world/Object.h>
#include <latebit/core/graphics/DisplayManager.h>

using namespace lb;

class TextOptions {
  public:
    TextSize::TextSize size = TextSize::NORMAL;
    TextAlignment::TextAlignment alignment = TextAlignment::LEFT;
    Color::Color color = Color::WHITE;
    Color::Color background = Color::UNDEFINED_COLOR;
    Color::Color shadow = Color::UNDEFINED_COLOR;
};

class Text : public Object {
  string text;
  TextOptions options;
public:
  Text(const string label, const string text, const TextOptions options = TextOptions()): Object(label) {
    this->text = text;
    this->options = options;
    setSolidness(Solidness::SPECTRAL);
  }

  int draw() override {
    int result = 0;

    if (options.background != Color::UNDEFINED_COLOR) {
      auto offset = (int)options.size;
      auto size = DM.measureString(text, options.size);
      size.setHeight(size.getHeight() + offset*4);
      size.setWidth(size.getWidth() + offset*8);

      auto position = getPosition();
      if (options.alignment == TextAlignment::CENTER) {
        position.setX(position.getX() - size.getWidth() / 2);
      } else if (options.alignment == TextAlignment::RIGHT) {
        position.setX(position.getX() - size.getWidth());
      }

      position.setY(position.getY() - offset*2);

      result += DM.drawRectangle(position, size.getWidth(), size.getHeight(), options.background, options.background);
    }

    if (options.shadow != Color::UNDEFINED_COLOR) {
      result += DM.drawString(getPosition() + Vector(options.size, options.size), text, options.alignment, options.shadow, options.size);
    }

    return DM.drawString(getPosition(), text, options.alignment, options.color, options.size) + result;
  }

  void setText(const string text) {
    this->text = text;
  }
};