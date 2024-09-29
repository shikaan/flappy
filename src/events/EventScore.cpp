#include "latebit/core/events/Event.h"

class EventScore : public lb::Event {
public:
  EventScore(): lb::Event("Score") {}
};