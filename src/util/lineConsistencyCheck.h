#pragma once

#include "lineFunc.h"

template<class InputIt>
void lineConsistencyCheck(InputIt first, InputIt end)
{
    InputIt linePtr = first;
    InputIt last = --end;
    if (linePtr == last) return;
    do {
        auto prev = linePtr++;
        std::cout << "Analysing: " << &(*prev) << std::endl;
        assert(tip(*prev) == (linePtr)->pos);
    } while (linePtr != last);
}
