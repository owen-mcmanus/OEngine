/**
 * @file Animation.h
 * @author Owen McManus
 * @date 2025/5/18
 */
#pragma once
#include "Component.h"
#include "Sprite.h"

#include <memory>
#include <vector>

namespace OEngine {
typedef enum { linear, easeIn, easeOut, ease, easeInOut, spring } AnimationCurve;

typedef struct {
    uint32_t time;
    float value;
    AnimationCurve curve;
    int keyId;
    int frequency = 1;
    int damping = 1;
} KeyFrame;

class Animation : public Component {
  public:
    Animation() = default;
    ~Animation() override = default;

    void Update(double deltaTime) override;
    virtual void HandleFrame(std::vector<KeyFrame> keys) = 0;
    void AddKeyFrame(const std::vector<KeyFrame>& kf);
    void StartAnimation();

  private:
    uint32_t startTime = 0;
    uint32_t animationTime = 0;
    bool running;
    std::vector<std::vector<KeyFrame>> keyFrames;
};

} // namespace OEngine
