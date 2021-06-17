#pragma once

#include <cstdlib>
#include <ctime>

#include "Fraction.h"

class Random
{
public:
    static inline void init()
    {
        srand(3);
    }

    static inline int randInt(int low, int high)
    {
        return low + rand() % ( high - low + 1);
    }
    
    static inline bool fractionChance(Fraction fraction)
    {
        int choice = randInt(0, fraction.denominator);
        if(choice <= fraction.numerator) return true;
        return false;
        
    }
    
    static inline bool fiftyFifty()
    {
        if(rand() % 2 == 0) return true;
        return false;
    }
};
