#include "latebit/core/events/Event.h"

const string SCORE_EVENT = "Score";

class EventScore : public lb::Event {
public:
  EventScore(): lb::Event(SCORE_EVENT) {}
};