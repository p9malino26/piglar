#pragma once

#include <cstdlib>
#include <ctime>

#include "Fraction.h"
#include "singleton.h"

class Random
{
    Random() {srand(3);}
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
        if(rand() % 2 == 0) return true;
        return false;
    }

    SINGLETON(Random)
    static void init() {
        instance = new Random();
    }
};
