#include "Entity.h"

template <typename T> bool between(T a, T b, T x) {return x >= a && x < b; };

bool entitiesTouch(const Entity& e1, const Entity& e2) //TODO make const
{
    const auto& pos1 = e1.getPos(), pos2 = e2.getPos();
    return (between(pos1.x, pos1.x + e1.getWidth(), pos2.x) || between(pos2.x, pos2.x + e2.getWidth(), pos1.x))
        && (between(pos1.y, pos1.y + e1.getHeight(), pos2.y) || between(pos2.y, pos2.y + e2.getHeight(), pos1.y));
}