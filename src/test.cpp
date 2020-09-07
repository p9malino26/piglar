#include <iostream>
#include "util/rangeFor.h"

int findFirstContact(bool* contacts, int length)
{
    bool checkingBack = false;
    int i = 0;
    while (true)
    {
        if (contacts[i])
        {
            if(i == 0)
            {
                if (!checkingBack)
                {
                    i = length - 1;
                    checkingBack = true;
                    continue;
                }
            }
            
            return i;
        }

        if (i == length - 1)
        {
            if (checkingBack)
            {
                i = 0;
                continue;
            }
            else
                return -1;
        }

        i++;
    }
}

int main()
{
    bool contacts[] {0,1, 0, 0,1};
    std::cout << findFirstContact(contacts, 5) << std::endl;
    return 0;
}
