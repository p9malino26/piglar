#pragma once

#include "vectors.h"

class Entity
{
public:
    Entity() {}

    Entity(const RealPos &mPos) : m_pos(mPos) {}

    inline RealPos& getPos() {return m_pos; }
    inline void setPos(const RealPos& pos) {m_pos = pos; }
    inline void changePos(const RealPos& pos) {m_pos += pos; }
    virtual float getWidth() = 0;
    virtual float getHeight() = 0;
private:
    RealPos m_pos;
};
