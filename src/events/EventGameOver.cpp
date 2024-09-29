#include "latebit/core/events/Event.h"

class EventGameOver : public lb::Event {
public:
  EventGameOver(): lb::Event("GameOver") {}
};