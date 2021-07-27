#pragma once

#include "../util/vectors.h"

class Entity
{
public:
    Entity() {}

    Entity(const RealPos &mPos) : m_pos(mPos) {}

    inline const RealPos& getPos() const {return m_pos; }
    inline void setPos(const RealPos& pos) {m_pos = pos; }
    inline void changePos(const RealPos& pos) {m_pos += pos; }
    inline RealPos getDims() const { return RealPos(getWidth(), getHeight()); };
    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;
private:
    RealPos m_pos;
};
