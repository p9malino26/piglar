#pragma once

#include <tuple>
#include <optional>

template <typename LineIterator, typename ContactData>
std::pair<LineIterator, ContactData> getFirstPointOfContact
    (LineIterator begin, LineIterator end, std::optional<ContactData> (*contactFunc)(LineIterator))
{
    bool checkingBack = false;
    LineIterator mainLineIterator = mainLineFirst;

    while (true)
    {
        if (contactFunc(mainLineIterator).has_value())
        {

            if (mainLineIterator == mainLineFirst)
            {
                if (!checkingBack)
                {
                    mainLineIterator = mainLineLast;
                    checkingBack = true;
                    continue;
                }
            }

            onReturnCallback();
            return mainLineIterator;

        }

        if(mainLineIterator == mainLineLast)
        {
            if(checkingBack)
            {
                mainLineIterator = mainLineFirst;
                continue;
            } else {
                assert(false);
            }

        }
    }
}
