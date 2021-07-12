#pragma once

#include <cstdlib>
#include <ctime>

#include "Fraction.h"
#include "singleton.h"

class Random
{
    Random(unsigned int seed) {srand(seed);}
public:


    inline int randInt(int low, int high)
    {
        return low + rand() % ( high - low + 1);
    }
    
    inline bool fractionChance(Fraction fraction)
    {
        int choice = randInt(0, fraction.denominator);
        if(choice <= fraction.numerator) return true;
        return false;
        
    }
    
    inline bool fiftyFifty()
    {
        return rand() % 2;
    }

    float ranFloat(float maxOffset, int resolution)
    {
        return (maxOffset * randInt(0, resolution)) / resolution;
    }

    inline float ranFloat(float l, float h, int resolution)
    {
        return l + ranFloat(h - l, resolution);
    }


    SINGLETON(Random)
    static void init(unsigned int seed) {
        instance = new Random(seed);
    }
};
