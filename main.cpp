#include "src/scenes/GameScene.cpp"

#include <latebit/core/configuration/Configuration.h>
#include <latebit/core/GameManager.h>
#include <latebit/core/ResourceManager.h>
#include <latebit/utils/Logger.h>

using namespace lb;

int main() {
  // A configuration file allows to customize certain aspects of the game
  // without recompiling. The path is relative to the binary file.
  //
  // The configuration is optional, the engine will run with sensible defaults
  // otherwise, but if you want to use it, you need to load it before starting
  // the game.
  Configuration::fromFile("latebit.cfg");

  // The GameManager (GM) is the main class of the engine. It is responsible for
  // initialising all the subsystems, running the game loop, and cleaning up the
  // resources when the game ends.
  //
  // The startUp() method initializes the engine, without starting the game
  // loop.
  GM.startUp();

  // Load resources
  // Resources are managed by the ResourceManager (RM). Below you can see how to
  // load sprites and audio files. To retrieve loaded resources, you can use the
  // get* methods of the RM.

  // latebit supports two types of sprites: text and image.
  // Text sprites are in a proprietary format. They are as powerful as images,
  // but you can work with them directly in your IDE.
  // Image sprites are loaded from 16-colors PNG files. That's the only image
  // format latebit supports. If the 16 colors of the image are not in the
  // latebit palette, the image will be remapped to latebit colors.
  //
  // No matter what type of sprite you use, you can use them in the same way and
  // they abide by the same rules: they can only display the 16 colors of the
  // latebit palette.
  RM.loadTextSprite("assets/sprites/fish.lbspr", "fish");
  RM.loadTextSprite("assets/sprites/bubbles.lbspr", "bubbles");
  RM.loadImageSprite("assets/sprites/logo.png", "logo");

  // latebit supports two types audio: music and sound effects.
  // Loading them is as simple as loading sprites, except that to hear them you
  // need to play() them.
  RM.loadMusic("assets/audio/music.lbmus", "music");
  RM.loadSound("assets/audio/sound.lbsfx", "sound");

  // Go check the src/scenes/GameScene.cpp file to see how to create a scene and
  // make your first game!
  auto scene = new GameScene();

  // The GM will run the game loop until GM.setGameOver(true) is called. Every
  // iteration of the loop loosely represents a frame in the game.
  GM.run();
  delete scene;

  return 0;
}
