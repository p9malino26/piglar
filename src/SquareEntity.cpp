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
    auto finalDelta = getCollisionResolutionDelta(*MainTileMap::get(), *this, delta);
    //pigMove = glm::normalize(pigMove) * moveDistance;
    changePos(finalDelta);

}
