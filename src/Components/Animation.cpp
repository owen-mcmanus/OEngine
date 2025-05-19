/**
 * @file Animation.cpp
 * @author Owen McManus
 * @date 2025/5/18
 */

#include "Animation.h"

OEngine::Sprite* OEngine::Animation::GetFrame() {
    if (currentFrame >= frameCount || frameCount == 0) {
        return nullptr;
    }
    return frames[currentFrame].get();
}

OEngine::Sprite* OEngine::Animation::GetFrame(int frame) {
    if (frame >= frameCount || frameCount == 0) {
        return nullptr;
    }
    return frames[frame].get();
}

void OEngine::Animation::AddFrame(const std::string& texturesheet, int width, int height) {
    frames.push_back(std::make_unique<Sprite>(texturesheet, width, height));
}