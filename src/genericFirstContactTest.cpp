#include "generator/findFirstContactGeneric.h"

#include <iostream>


int main()
{
    bool contactInfo[]{1, 1, 0, 1, 0};
    std::function checkContact = [] (bool* contactPtr) -> std::optional<int> {
        if (*contactPtr)
            return std::optional(5);
        return {};
    };
    auto contact = findFirstContactGeneric<bool*, int>(contactInfo, contactInfo + 4, checkContact);
    printf("Start: %x, first contact: %x, difference: %d\n", contactInfo, contact.first, contact.first - contactInfo);
    return 0;
}
