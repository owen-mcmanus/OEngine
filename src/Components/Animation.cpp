/**
 * @file Animation.cpp
 * @author Owen McManus
 * @date 2025/5/18
 */

#include "Animation.h"

#include <absl/strings/internal/str_format/extension.h>
#include <absl/strings/str_format.h>
#include <algorithm>
#include <iostream>

using namespace OEngine;

inline float linearInterpolation(uint32_t time, uint32_t t0, uint32_t t1, float v0, float v1) {
    const float m = (v1 - v0) / (t1 - t0);
    return m * (time - t0) + v0;
}

inline float easeInInterpolation(float delta, float t0, float t1, float v0, float v1) {
    float t = std::clamp((delta - t0) / (t1 - t0), 0.0f, 1.0f);
    float s = t * t;
    return v0 + (v1 - v0) * s;
}

inline float easeOutInterpolation(float delta, float t0, float t1, float v0, float v1) {
    float t = std::clamp((delta - t0) / (t1 - t0), 0.0f, 1.0f);
    // quadratic ease-out
    float s = 1.0f - (1.0f - t) * (1.0f - t);
    return v0 + (v1 - v0) * s;
}

inline float easeInOutInterpolation(float delta, float t0, float t1, float v0, float v1) {
    float t = std::clamp((delta - t0) / (t1 - t0), 0.0f, 1.0f);
    // piecewise quadratic in/out
    float s = (t < 0.5f) ? 2.0f * t * t : 1.0f - 2.0f * (1.0f - t) * (1.0f - t);
    return v0 + (v1 - v0) * s;
}

inline float easeInterpolation(float delta, float t0, float t1, float v0, float v1) {
    float t = std::clamp((delta - t0) / (t1 - t0), 0.0f, 1.0f);
    // smooth-step (3t² – 2t³) – a good general-purpose ease
    float s = t * t * (3.0f - 2.0f * t);
    return v0 + (v1 - v0) * s;
}

void Animation::Update(double deltaTime) {
    if (!running)
        return;

    uint32_t delta = SDL_GetTicks() - startTime;
    std::vector<KeyFrame> frames;
    if (delta >= animationTime) {
        running = false;
        for (auto keyFrame : keyFrames) {
            frames.push_back(keyFrame.back());
        }
        HandleFrame(frames);
        return;
    }

    for (auto keyFrame : keyFrames) {
        for (int i = 1; i < keyFrame.size(); i++) {
            if (keyFrame[i].time > delta && keyFrame[i - 1].time <= delta) {
                float value;
                switch (keyFrame[i - 1].curve) {
                case linear:
                    value = linearInterpolation(
                        delta, keyFrame[i - 1].time, keyFrame[i].time, keyFrame[i - 1].value,
                        keyFrame[i].value);
                    break;
                case easeIn:
                    value = easeInInterpolation(
                        delta, keyFrame[i - 1].time, keyFrame[i].time, keyFrame[i - 1].value,
                        keyFrame[i].value);
                    break;
                case easeOut:
                    value = easeOutInterpolation(
                        delta, keyFrame[i - 1].time, keyFrame[i].time, keyFrame[i - 1].value,
                        keyFrame[i].value);
                    break;
                case ease:
                    value = easeInterpolation(
                        delta, keyFrame[i - 1].time, keyFrame[i].time, keyFrame[i - 1].value,
                        keyFrame[i].value);
                    break;
                case easeInOut:
                    value = easeInOutInterpolation(
                        delta, keyFrame[i - 1].time, keyFrame[i].time, keyFrame[i - 1].value,
                        keyFrame[i].value);
                    break;
                default:
                    value = keyFrame[i - 1].value;
                }

                frames.emplace_back(delta, value, keyFrame[i - 1].curve, keyFrame[i - 1].keyId);
                break;
            }
        }
    }

    HandleFrame(frames);
}

void Animation::AddKeyFrame(const std::vector<KeyFrame>& kf) {
    if (kf[0].time != 0)
        throw std::runtime_error("Keyframe must start at time 0");
    if (kf.size() <= 1)
        throw std::runtime_error("Keyframe must have at least 2 elements");
    for (int i = 1; i < kf.size(); i++) {
        if (kf[i].time <= kf[i - 1].time) {
            throw std::runtime_error("Keyframe times must always increase");
        }
    }
    animationTime = std::max(animationTime, kf.back().time);
    keyFrames.push_back(kf);
}

void Animation::StartAnimation() {
    running = true;
    startTime = SDL_GetTicks();
}
