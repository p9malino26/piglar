//
// Created by patryk on 21/06/2021.
//

#include "SquareEntity.h"
#include "MainTileMap.h"

float SquareEntity::getWidth() const {
    return m_sideLength;
}

float SquareEntity::getHeight() const {
    return m_sideLength;
}

void SquareEntity::move(const RealPos& delta) {
    RealPos clampedDelta(std::clamp(delta.x, 0.f, getWidth() / 2), std::clamp(delta.y, 0.f, getHeight() / 2));
    auto finalDelta = getCollisionResolutionDelta(*MainTileMap::get(), *this, delta);
    changePos(finalDelta);
}
