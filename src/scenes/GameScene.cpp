#include <latebit/core/graphics/Colors.h>
#include <latebit/core/graphics/DisplayManager.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/ResourceManager.h>

#include <sstream>
#include "../characters/Fish.cpp"

using namespace lb;

class WelcomeText : public Object {
public:
  WelcomeText() { this->setType("WelcomeText"); }

  // The draw method is called every frame to draw the object on the screen.
  int draw() override {
    int result = 0;

    // This comes from the CMakeLists.txt file, don't mind it.
    std::string version = LATEBIT_VERSION;

    // Here we are using the Display Manager (DM) to draw text on the screen at
    // a given position.
    result += DM.drawString(this->getPosition() + Vector(0, 30), version,
                            TextAlignment::CENTER, Color::WHITE);
    
    // You can use special glyphs to represent input buttons. This is useful
    // for on-screen instructions and settings.
    char msg[26];
    sprintf(msg, "Press %c to play a sound", InputGlyph::A);
    result += DM.drawString(this->getPosition() + Vector(0, 50), msg, TextAlignment::CENTER, Color::PEACH);

    return result;
  }
};

class Logo : public Object {
public:
  Logo() {
    // This is the simplest object you can create: you give it a type and a
    // sprite, and, by using `setPosition` you can place it on the screen.
    this->setType("Logo");
    this->setSprite("logo");
  }
};

class GameScene : public Object {
private:
  // Here we are defining child objects of our GameScene. In other words, this
  // defines the objects that will appear in this scene.
  // The GameScene owns the objects and is therefore responsibile for cleaning
  // them up. You can check the ~GameScene destructor to see how.
  //
  // Head to the GameScene constructor to see how to set up a scene!
  WelcomeText *welcomeText = new WelcomeText();
  Fish *fish = new Fish();
  Logo *logo = new Logo();

public:
  GameScene() {
    // The scene is a container object for all the objects that will be drawn on
    // the screen.
    // Setting the type will allow you to retrieve the scene later on and to
    // identify it in the logs.
    setType("GameScene");

    // The Display Manager (DM) is responsible for drawing everything on the
    // screen. Here you can set the background color of the scene for example.
    DM.setBackground(Color::BLUE);

    // Here we are retrieving the music we loaded in the main.cpp from the
    // ResourceManager (RM) and playing it.
    const auto music = RM.getMusic("music");
    if (music != nullptr) {
      music->play(true);
    }

    // In the following block we are placing objects in the scene.
    const auto center =
        Vector(DM.getHorizontalCells() / 2.0, DM.getVerticalCells() / 2.0);

    // To place objects in the screen we need to know how "big" they are.
    // A box is a simplified, rectangular representation of an object's boundaries. 
    // It defines the minimum and maximum extents of the object along each axis,
    // providing an efficient way to perform collision detection and spatial queries.
    const auto fishBox = this->fish->getBox();
    const auto logoBox = this->logo->getBox();

    // Positions are defined by bidimensional vectors. You can perform standard
    // vector operations on them. Take a look at the header for the Vector class
    // for more information.
    this->welcomeText->setPosition(center - Vector(0, 5));

    this->fish->setPosition(
        center - Vector(fishBox.getWidth() / 2, 32 - fishBox.getHeight() / 2));

    this->logo->setPosition(center - Vector(logoBox.getWidth() / 2, 0));

    // Now you are ready to see how the objects we have manipulated are defined.
    // Go check the WelcomeText, Logo, and Fish to start implementing your first objects.
  }

  ~GameScene() {
    // GameScene owns our mascotte, the text, and the logo, therefore it's responsible
    // for cleaning them up once it gets detroyed.
    WM.removeObject(this->logo);
    WM.removeObject(this->fish);
    WM.removeObject(this->welcomeText);
  };
};