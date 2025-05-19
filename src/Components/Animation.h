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
class Animation : public Component {
  public:
    Animation();
    ~Animation() = default;

    Sprite* GetFrame();
    Sprite* GetFrame(int frame);

    void AddFrame(const std::string& texturesheet, int width, int height);

  private:
    int currentFrame = 0;
    int frameCount = 0;
    std::vector<std::unique_ptr<Sprite>> frames;
};

} // namespace OEngine
