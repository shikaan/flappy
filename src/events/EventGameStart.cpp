#include "latebit/core/events/Event.h"

const string GAME_START_EVENT = "GameStart";

class EventGameStart : public lb::Event {
public:
  EventGameStart(): lb::Event(GAME_START_EVENT) {}
};