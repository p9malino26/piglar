#include <iostream>
#include "../../TileMap.h"
#include "../../util/Random.h"
#include "treeGenData.h"
#include "TreeGenerator.h"
#include "../../TreeGenParams.h"
#include "../../tileMapUtil.h"

#define CONSTANT(EXPR) \
static constexpr EXPR;


    void genHouses(TileMap& tileMap, const BoardPos& startPos, CompassDirection direction, int length, Fraction houseProbability)
    {
        std::function<void(TileState&)> makeHouse = [&houseProbability] (TileState& tile) { if (Random::get()->fractionChance(houseProbability)) tile = HOUSE; };
        forEachOnLine(tileMap, startPos, direction, length, makeHouse);
    }

    TreeGenData generateTree(TileMap& roadmap, const BoardPos& startpos, const TreeGenParams& params)
    {
        assert(!roadmap.isPositionOutside(startpos));

        int mainRoadLength = Random::get()->randInt(params.mainRoadLengthRange.first, params.mainRoadLengthRange.second);
        BoardPos endPos = startpos;
        endPos.y += mainRoadLength - 1;
        assert(!roadmap.isPositionOutside(endPos));


        //for initial line:
        setLine(roadmap, startpos, CompassDirection::NORTH, mainRoadLength);

        int maxLHouseLine=0, maxRHouseLine=0;

        auto genBranch = [&roadmap, &params, &maxLHouseLine, &maxRHouseLine](bool leftBranch, const BoardPos& pos) -> int{

            int linelength = Random::get()->randInt(params.branchRoadLengthRange.first, params.branchRoadLengthRange.second); // branch length
            auto startPos = pos;
            startPos.x += leftBranch ? 1 : -1;
            CompassDirection direction =leftBranch ? CompassDirection::EAST : CompassDirection::WEST;
            setLine(roadmap, startPos, direction, linelength);

            //generate houses
            int& maxHouseLineThisSide = leftBranch ? maxLHouseLine: maxRHouseLine;

            auto genHousesSp = [&roadmap, &startPos, &params, linelength, direction] (bool isBelow) {
                genHouses(roadmap, BoardPos(startPos.x, startPos.y + (isBelow ? -1 : 1)), direction, linelength, params.houseProbability);
            };
            if (startPos.y - 1 > maxHouseLineThisSide)
                if (Random::get()->fiftyFifty()) genHousesSp(true);

            if (pos.y >= roadmap.getHeight() && Random::get()->fiftyFifty()) {
                genHousesSp(false);
                maxHouseLineThisSide = startPos.y + 1;
            }
            return linelength;

        };

        int maxLBranchLength = 0, maxRBranchLength = 0;
        //for branches:
        for (BoardPos pos = startpos; pos.y <= endPos.y ;)
        {
            int junctionChoice = Random::get()->randInt(0,2);
            /*
                0: left
                1: right
                2: both left and right
            */
            if (junctionChoice == 0 || junctionChoice == 2) {// left
                int branchLength = genBranch(0, pos);
                maxLBranchLength = std::max(branchLength, maxLBranchLength);
            }

            if(junctionChoice == 1 || junctionChoice == 2) {// right
                int branchLength = genBranch(1, pos);
                maxRBranchLength = std::max(branchLength, maxRBranchLength);
            }

            int maxHouseLine = std::max(maxLHouseLine, maxRHouseLine);
            //end steps:
            pos.y += Random::get()->randInt(std::max(maxHouseLine + 1 - pos.y, params.branchStepRange.first), params.branchStepRange.second);
        }

        TreeGenData returnData;
        returnData.dims = {maxLBranchLength + 1 + maxRBranchLength, mainRoadLength};
        returnData.maxLBranchLength = maxLBranchLength;
        returnData.maxRBranchLength = maxRBranchLength;
        return returnData;

    }

    std::pair<BoardPos, BoardPos> treePosToBufferAndGlobal(
            bool orientation,
            const BoardPos& placePos,
            const BoardPos& treePos,
            int treeWidth,
            int bufferMaxBranchLength,
            int maxLBranchLength)
    {
        BoardPos bufferPos = treePos;
        bufferPos.x += bufferMaxBranchLength - maxLBranchLength;

        BoardPos globalPos;
        if(orientation == 1) // horizontal
        {
            globalPos = {treePos.y, -treePos.x + treeWidth - 1};
            globalPos += placePos;
        } else {//vertical
            globalPos = treePos + placePos;
        }

        return {bufferPos, globalPos};
    }


    TreeGenerator::TreeGenerator(const TreeGenParams &params)
    :treeData(std::make_unique<TileMap>(1 + 2 * params.branchRoadLengthRange.second, params.mainRoadLengthRange.second)), params(&params),
          lastGenData(std::make_unique<TreeGenData>())
    {}


    BoardPos TreeGenerator::generate()
    {
        *lastGenData = generateTree(*treeData, {params->branchRoadLengthRange.second, 0}, *params);
        return lastGenData->dims;
    }



    void TreeGenerator::writeTo(TileMap& roadMap, BoardPos startPos, bool flip)
    {
        //write#


        //go through every logical tree position
        const BoardPos& dims = lastGenData->dims;
        BoardPos treePos{0,0};
        for (; treePos.x < dims.x; treePos.x++)
        {
            for(treePos.y = 0; treePos.y < dims.y; treePos.y++)
            {
                //find out different coordinates
                auto tmp = treePosToBufferAndGlobal(flip, startPos, treePos, dims.x, params->branchRoadLengthRange.second, lastGenData->maxLBranchLength);
                BoardPos& bufferPos = tmp.first;
                BoardPos& globalPos = tmp.second;

                auto srcState = treeData->getTileState(bufferPos);
                auto destState = srcState;
                if (flip) {
                    if (destState == HORIZONTAL)
                        destState = VERTICAL;
                    else if (destState == VERTICAL)
                        destState = HORIZONTAL;
                }
                roadMap.setTileState(globalPos, destState);
            }
        }
        treeData->clear();

    }

    TreeGenerator::~TreeGenerator() {};
