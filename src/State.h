#pragma once

#define STATE State::getInstance()

class State {
private:
  int score = 0;
  int highScore = 0;

  static State* instance;
  State() = default;

public:
  void increment();
  void reset();
  int getScore();
  int getHighScore();

  State(State const &) = delete;
  void operator=(State const &) = delete;
  static auto getInstance() -> State &;
};