/**
 * @file MultiSprite.h
 * @author Owen McManus
 * @date 2025-09-16
 */
#pragma once

#include "Component.h"
#include "PrimitiveSprite.h"
#include "Sprite.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

namespace OEngine {

class Transform;

template <typename Drawable> struct LayerEntry {
    int layer;
    std::unique_ptr<Drawable> drawable;
    std::unique_ptr<Transform> transform;
};

class MultiSprite : public Component {
  public:
    MultiSprite();
    ~MultiSprite() override = default;

    /* forbid copying, allow moving */
    MultiSprite(const MultiSprite&) = delete;
    MultiSprite& operator=(const MultiSprite&) = delete;
    MultiSprite(MultiSprite&&) noexcept = default;
    MultiSprite& operator=(MultiSprite&&) noexcept = default;

    void AddSprite(std::unique_ptr<Sprite> s, glm::vec2 offset, int layer = 0);
    void AddSprite(std::unique_ptr<Sprite> s, glm::vec3 offset, int layer = 0);
    void AddPrimitiveSprite(std::unique_ptr<PrimitiveSprite> ps, glm::vec2 offset, int layer = 0);
    void AddPrimitiveSprite(std::unique_ptr<PrimitiveSprite> ps, glm::vec3 offset, int layer = 0);

    void RemoveSprite(Sprite* s);
    void RemovePrimitiveSprite(PrimitiveSprite* ps);

    Sprite* GetSprite(int i) const;
    PrimitiveSprite* GetPrimitiveSprite(int i) const;
    Transform* GetSpriteOffset(int i) const;
    Transform* GetPrimitiveSpriteOffset(int i) const;
    int GetSpriteLayer(int i) const;
    int GetPrimitiveSpriteLayer(int i) const;

    int GetNumSprites() const;
    int GetNumPrimitiveSprites() const;

  private:
    std::vector<LayerEntry<Sprite>> sprites;
    std::vector<LayerEntry<PrimitiveSprite>> pSprites;

    template <typename Vec, typename Entry> void InsertOrdered(Vec& vec, Entry&& e);
};

} // namespace OEngine
