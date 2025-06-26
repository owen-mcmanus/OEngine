/**
 * @file MultiSprite.cpp
 * @author Owen McManus
 * @date 2025-09-16
 */
#include "MultiSprite.h"

#include "Core/GameObject.h"
#include "Transform.h"

#include <algorithm>
#include <utility>

using namespace OEngine;

MultiSprite::MultiSprite() = default;

template <typename Vec, typename Entry> void MultiSprite::InsertOrdered(Vec& vec, Entry&& e) {
    auto it = std::upper_bound(
        vec.begin(), vec.end(), e.layer, [](int lhs, const auto& rhs) { return lhs < rhs.layer; });
    vec.insert(it, std::forward<Entry>(e));
}

void MultiSprite::AddSprite(std::unique_ptr<Sprite> s, glm::vec2 offset, int layer) {
    if (!s)
        return;

    auto t = std::make_unique<Transform>(offset);
    t->SetParent(owner->GetCacheableComponent<Transform>());

    InsertOrdered(sprites, LayerEntry<Sprite>{layer, std::move(s), std::move(t)});
}

void MultiSprite::AddPrimitiveSprite(
    std::unique_ptr<PrimitiveSprite> ps,
    glm::vec2 offset,
    int layer) {
    if (!ps)
        return;

    auto t = std::make_unique<Transform>(offset);
    t->SetParent(owner->GetCacheableComponent<Transform>());

    InsertOrdered(pSprites, LayerEntry<PrimitiveSprite>{layer, std::move(ps), std::move(t)});
}

void MultiSprite::RemoveSprite(Sprite* s) {
    if (!s)
        return;
    std::erase_if(sprites, [s](const auto& e) { return e.drawable.get() == s; });
}

void MultiSprite::RemovePrimitiveSprite(PrimitiveSprite* ps) {
    if (!ps)
        return;
    std::erase_if(pSprites, [ps](const auto& e) { return e.drawable.get() == ps; });
}

Sprite* MultiSprite::GetSprite(int i) const {
    return (i >= 0 && i < static_cast<int>(sprites.size())) ? sprites[i].drawable.get() : nullptr;
}

PrimitiveSprite* MultiSprite::GetPrimitiveSprite(int i) const {
    return (i >= 0 && i < static_cast<int>(pSprites.size())) ? pSprites[i].drawable.get() : nullptr;
}

Transform* MultiSprite::GetSpriteOffset(int i) const {
    return (i >= 0 && i < static_cast<int>(sprites.size())) ? sprites[i].transform.get() : nullptr;
}

Transform* MultiSprite::GetPrimitiveSpriteOffset(int i) const {
    return (i >= 0 && i < static_cast<int>(pSprites.size())) ? pSprites[i].transform.get()
                                                             : nullptr;
}

int MultiSprite::GetSpriteLayer(int i) const {
    return (i >= 0 && i < static_cast<int>(sprites.size())) ? sprites[i].layer : 0;
}

int MultiSprite::GetPrimitiveSpriteLayer(int i) const {
    return (i >= 0 && i < static_cast<int>(pSprites.size())) ? pSprites[i].layer : 0;
}

int MultiSprite::GetNumSprites() const { return static_cast<int>(sprites.size()); }

int MultiSprite::GetNumPrimitiveSprites() const { return static_cast<int>(pSprites.size()); }
