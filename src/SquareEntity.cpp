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
    /*auto xLim = 0.49f;//getWidth() / 2.f;
    auto yLim = 0.49f;//getHeight() / 2.f;
    RealPos clampedDelta(std::clamp(delta.x, -xLim, xLim), std::clamp(delta.y, -yLim, yLim));*/
    auto finalDelta = getCollisionResolutionDelta(*MainTileMap::get(), *this, delta);
    changePos(finalDelta);
}
