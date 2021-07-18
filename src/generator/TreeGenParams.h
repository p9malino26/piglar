//
// Created by patryk on 08/07/2021.
//

#pragma once

#include "../util/Fraction.h"

namespace Generator {
//structs
    struct TreeGenParams {
        std::pair<int, int> mainRoadLengthRange = {7,11}
        , branchRoadLengthRange= {5, 7}, branchStepRange= {2, 4};

        Fraction houseProbability{1, 3};
    };
}