#pragma once

#include <latebit/core/objects/Object.h>

class Scene : public lb::Object {
  public:
    Scene(const std::string &type) : lb::Object(type) {}
    virtual void play() = 0;
    virtual void cleanup() = 0;
};