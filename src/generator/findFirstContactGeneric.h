#pragma once

#include <tuple>
#include <functional>
#include <optional>

template <typename LineIterator, typename ContactData>
std::pair<LineIterator, ContactData> findFirstContactGeneric
    (LineIterator begin, LineIterator end, std::function<std::optional<ContactData>(LineIterator)>& contactFunc)
{
    auto optFrontContact = contactFunc(begin);
    //does front have contact?
    //yes:
    if (optFrontContact.has_value())
    {
        auto& frontContact = optFrontContact.value();
        auto optBackContact = contactFunc(end);

        //is there contact at the back?
        //yes
        if(optBackContact.has_value())
        {
            auto& contactInfo = optBackContact.value();
            //if there is a contact at the end, keep going back the chain of contacts until you find a contactless line
            auto envelopeItr = end;
            while (1)
            {
                //go to previous
                envelopeItr--;
                //check for contact info
                auto nextBackContactInfo = contactFunc(envelopeItr);

                if (!nextBackContactInfo.has_value())
                    break;
                else
                    contactInfo = nextBackContactInfo.value();

            }

            envelopeItr++;

            return {envelopeItr, contactInfo};


        //no contact at the back
        } else {
            //return front
            return {begin, frontContact};
        }
    }
    //no contact at the front
    else {
        auto envelopeItr = begin;
        envelopeItr++;
        //start from second
        while (true)
        {
            //if it contacts, stop
            auto optContact = contactFunc(envelopeItr);
            if(optContact.has_value())
            {
                auto& contact = optContact.value();
                return {envelopeItr, contact};
            }
            envelopeItr++;
        }
    }

}
