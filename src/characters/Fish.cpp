#include <latebit/core/events/EventOut.h>
#include <latebit/core/events/EventStep.h>
#include <latebit/core/events/EventInput.h>
#include <latebit/core/objects/Object.h>
#include <latebit/core/objects/WorldManager.h>
#include <latebit/core/ResourceManager.h>

using namespace lb;

class Bubbles : public Object {
public:
  Bubbles(Vector position) {
    // This tiny object is a bubble that floats up the screen and disappears
    // when it reaches the top. We give it a type and assign it a sprite that we
    // have loaded in the main.cpp. Again you can pick the sprites by their
    // label ("bubbles" in this case)
    setType("Bubbles");
    setSprite("bubbles");

    // latebit supports collisions between objects. Marking this object as
    // SPECTRAL means that it will not collide with other objects. You can read
    // more about solidness in latebit/core/objects/Object.h
    setSolidness(Solidness::SPECTRAL);

    // We set the velocity of the bubble to float up the screen
    setVelocity(Vector(0, -1));

    // Altitude is a property of the object that determines the order in which
    // objects are drawn on the screen. The higher the altitude, the later the
    // object is drawn. This is useful when you want to draw objects on top of
    // others.
    setAltitude(2);

    // We set the position of the bubble to the position we received in the
    // constructor
    setPosition(position);

    // We subscribe to the OUT_EVENT here, to mark the bubble for deletion when
    // it goes out of the screen. We will handle this in the eventHandler()
    subscribe(OUT_EVENT);
  }

  // This is where we handle the events we subscribed to.
  // In this case, we are only interested in the OUT_EVENT, which we use to mark
  // the bubble for deletion when it goes out of the screen.
  int eventHandler(const Event *event) override {
    if (event->getType() == OUT_EVENT) {
      WM.markForDelete(this);
      return 1;
    }

    return 0;
  }
};

class Fish : public Object {
private:
  const Sound* sfx = RM.getSound("sound");
public:
  Fish() {
    // This is your first character!
    // It is a fish that swims in the middle of the screen and honestly does not
    // do much. We give it a type and assign it a sprite that we have loaded in
    // the main.cpp. You can pick the sprites by their label ("fish" in this
    // case)
    //
    // Head over to assets/sprites/fish.lbspr to see what a sprite looks like.
    // If you have the Latebit Studio Visual Studio Code extension installed, you
    // will also get a nice Sprite Editor to easily update it.
    setType("Fish");
    setSprite("fish");

    // This is how you can make your game objects interactive.
    // By subscribing to events, you can make your objects react to them.
    // Here we are subscribing to the STEP_EVENT, which is triggered every
    // frame. We are using it to spawn bubbles every now and then (see
    // eventHandler())
    subscribe(STEP_EVENT);
    
    // Here instead we are subscribing to an input event, this is how the
    // players can interact with our game
    subscribe(INPUT_EVENT);
  }

  // This is where we handle the events we subscribed to.
  // In this case, we are only interested in the STEP_EVENT, which we use to
  // spawn bubbles from time to time.
  int eventHandler(const Event *event) override {
    if (event->getType() == STEP_EVENT) {
      if (rand() % 100 == 0) {
        // The Bubbles clean up themselves once they get out of the screen (see
        // the implementation above). In other circumstances you may want the
        // Fish to own them.
        // Go check how Bubbles are implemented at the top of this file!
        new Bubbles(getPosition() + Vector(16, 0));
      }
      // Returning 1 means the event was handled and it won't cascade
      return 1;
    }

    if (event->getType() == INPUT_EVENT) {
      // While handling the input events, is important to understand what what button
      // was pressed. Fortunately, the event holds this information, but only after it's
      const EventInput* inputEvent = static_cast<const EventInput*>(event);

      if (inputEvent->getKey() == InputKey::A && inputEvent->getAction() == InputAction::PRESSED) {
        // As promised in the GameScene, we are now playing the sound when A is pressed
        this->sfx->play();

        // And we are returning 1 again to signal that the event was handled
        return 1;
      }
    }

    return 0;
  }
};