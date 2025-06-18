/**
 * @file Delay.h
 * @author Owen McManus
 * @date 2025/5/18
 */
#pragma once
#include "Component.h"

#include <functional>

namespace OEngine {
class Delay : public Component {
  public:
    Delay(uint32_t delay, std::function<void()> cb);
    ~Delay() override = default;

    void Update(double deltaTime) override;

  private:
    uint32_t delay;
    uint32_t startTime;
    std::function<void()> cb;
    bool complete = false;
};

} // namespace OEngine
