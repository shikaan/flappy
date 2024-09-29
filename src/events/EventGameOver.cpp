#include "latebit/core/events/Event.h"

const string GAME_OVER_EVENT = "GameOver";

class EventGameOver : public lb::Event {
public:
  EventGameOver(): lb::Event(GAME_OVER_EVENT) {}
};