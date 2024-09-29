#include "State.h"

#define STATE State::getInstance()

void State::increment() {
  score++;
  if (score > highScore) {
    highScore = score;
  }
}

int State::getScore() { return score; }

int State::getHighScore() { return highScore; }

void State::reset() { score = 0; }

auto State::getInstance() -> State & {
  static State instance;
  return instance;
}