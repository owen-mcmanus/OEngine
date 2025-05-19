/**
 * @file Collider.h
 * @author Owen McManus
 * @date 2025/5/6
 */
#pragma once
#include "../Events/Event.h"
#include "Component.h"

namespace OEngine {
class CollisionEvent : public Event {
  public:
};

class Collider : public Component {};

class RectangleCollider : public Collider {};

class CircleCollider : public Collider {};
} // namespace OEngine