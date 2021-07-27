//
// Created by patryk on 21/06/2021.
//
#include "tileMapUtil.h"
#include "Entity.h"
#include "util/compassUtil.h"


struct Boundary
{
    char orientation;
    int coord;
};

RealPos getShiftToBoundaryDelta(const RealPos& pos, const Boundary& b)
{
    return b.orientation == 'h' ? RealPos (0.f, b.coord - pos.y) : RealPos (b.coord - pos.x, 0.f);
}

std::vector<RealPos> getEntityVertices(Entity& entity, const RealPos& delta)
{
    std::vector<RealPos> entityVertices = {{0.f,0.f}, {1.f, 0.f}, {0.f, 1.f}, {1.f, 1.f}};
    for (auto& vertex: entityVertices)
    {
        vertex *= RealPos {entity.getWidth(), entity.getHeight()};
        vertex += entity.getPos() + delta;
    }
    return entityVertices;

}


template<typename VecList>
std::vector<RealPos*> getIllegalVertices(const TileMap& tileMap, VecList& vertices)
{
    std::vector<RealPos*> illegalVertices;
    illegalVertices.reserve(4);
    for (auto& v: vertices) //wasbug
    {
        if (!isOnRoad(tileMap,v))
            illegalVertices.push_back(&v);
    }

    return illegalVertices;
}

//inline int round(float f) {return static_cast<int>(f + 0.5f);};



inline std::vector<Boundary> getCloseBoundariesForPoint(const TileMap& tileMap, const RealPos& pos)
{
    std::vector<Boundary> toReturn;

    BoardPos onTile = realToTile(pos);
    BoardPos clampedPoint = clampToNearestTile(pos);

    //check horizontal boundaries
    if(clampedPoint.y == onTile.y)
    {
        if (isOnRoad(tileMap, onTile + SOUTH_VEC) == 1) // if boundary southward
        {
            toReturn.push_back({'h', onTile.y});
        }
    } else
    {
        if (isOnRoad(tileMap, onTile + NORTH_VEC) == 1) // if boundary northward
        {
            toReturn.push_back({'h', onTile.y + 1});
        }
    }

    //check vertical boundaries
    if(clampedPoint.x == onTile.x)
    {
        if (isOnRoad(tileMap, onTile + WEST_VEC) == 1) // if boundary westwards
        {
            toReturn.push_back({'v', onTile.x});
        }

    } else
    {
        if (isOnRoad(tileMap, onTile + EAST_VEC) == 1) // if boundary eastwards
        {
            toReturn.push_back({'v', onTile.x + 1});
        }
    }

    return toReturn;
}

inline float getBoundaryDistanceFromPoint(const RealPos& pos, Boundary& b)
{
    auto& component = (b.orientation == 'v') ? pos.x : pos.y;
    return std::abs(b.coord - component);
}

Boundary& getCloserBoundaryToPoint(const RealPos& point, Boundary& b1, Boundary& b2)
{
    float b1_distance = getBoundaryDistanceFromPoint(point, b1);
    float b2_distance = getBoundaryDistanceFromPoint(point, b2);

    return (b1_distance > b2_distance) ? b2 : b1;//wasbug
}

Boundary& getBoundaryWithOrientation(std::vector<Boundary>& boundaries, char orientation)
{
    for(auto& b: boundaries)
        if (b.orientation == orientation) return b;
}

char getOrientationOfPoints(const RealPos& p1, const RealPos& p2)
{
    if (p1.x == p2.x) return 'v';
    else if (p1.y == p2.y) return 'h';
    //else assert(false);
}

RealPos getCollisionResolutionDelta(const TileMap& tileMap, Entity& entity, const RealPos& initialDelta)
{
    std::vector<RealPos> entityVertices = getEntityVertices(entity, initialDelta);

    std::vector<RealPos*> illegalVertices = getIllegalVertices(tileMap, entityVertices);
    int illegalCount = illegalVertices.size();
    if (illegalCount == 0 || illegalCount == 4) return initialDelta;
    if (illegalCount == 3) return RealPos(0.f);
    RealPos& lastIllegalPoint = **illegalVertices.data();

    std::vector<Boundary> closeBoundaries = getCloseBoundariesForPoint(tileMap, lastIllegalPoint);
    if (closeBoundaries.empty()) return RealPos (0.f);

    Boundary* boundaryToShift = nullptr;

    switch (illegalCount) {
        case 1:
            boundaryToShift = &getCloserBoundaryToPoint(lastIllegalPoint, closeBoundaries[0], closeBoundaries[1]);
            break;
        case 2:
            if (closeBoundaries.size() == 1)
                boundaryToShift = closeBoundaries.data();
            else
                boundaryToShift = &getBoundaryWithOrientation(closeBoundaries, getOrientationOfPoints(*illegalVertices[0], *illegalVertices[1]));
            break;

    }

    return initialDelta + getShiftToBoundaryDelta(lastIllegalPoint, *boundaryToShift);

}
