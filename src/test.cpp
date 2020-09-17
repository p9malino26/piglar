#include <iostream>

int findFirstContact(bool* contacts, int length)
{
    int index;
    if (contacts[0]){
        index = length;
        while (contacts[index - 1] == 1)
        {
            index--;
        }


        return index % length;
    } else
    {
        index = 1;
        for(; index < length; index++)
        {
            if (contacts[index])
                return index;
        }
    }

    return -1;
}

int main()
{
    bool contactInfo[]{1, 0, 0, 1, 1};
    std::cout << findFirstContact(contactInfo, 5) << std::endl;
    return 0;
}
