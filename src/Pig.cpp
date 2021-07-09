//
// Created by patryk on 06/07/2021.
//

#include "Pig.h"
#include "util/Random.h"
#include "Player.h"
#include "MainTileMap.h"
#include "TimeManager.h"

float Pig::speed;
float Pig::detectionRange;


Pig::Pig(const RealPos &startPos)
    : SquareEntity(startPos, 0.7f), m_minPlayerDistance(Random::get()->ranFloat(0.1f, 0.3f, 5)) {}

void Pig::update()
{
    auto pig2player = Player::get()->getPos() - this->getPos();
    float distance = glm::length(pig2player);
    if (distance > detectionRange || distance < m_minPlayerDistance) return;
    auto pig2playerU = glm::normalize(pig2player);
    auto pigMove = getCollisionResolutionDelta(*MainTileMap::get(), *this, pig2playerU * speed * TimeManager::get()->deltaTime());
    changePos(pigMove);
}

void Pig::init(float playerSpeedRatio, float detectionRange)
{
    speed = playerSpeedRatio * Player::get()->getSpeed();
    Pig::detectionRange = detectionRange;
}

