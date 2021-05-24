#ifndef ARMED_H
#define ARMED_H

#include "string"
#include <iostream>

using namespace std;

class armed
{
public:
    armed(string inArmed) : strArmed(inArmed)
    {
        armedCount = 0;
        wasArmed = 0;
        notArmed = 0;
        armedGun = 0;
        armedUnknown = 0;

        if ((inArmed.compare("") != 0) && (inArmed.compare("undetermined") != 0))
        {
            if (inArmed.compare("gun") == 0)
            {
                armedGun++;
                wasArmed++;
            }
            else if (inArmed.compare("unarmed") == 0)
            {
                notArmed++;
            }
            else
            {
                wasArmed++;
            }
            armedCount++;
        }

    }

private:
    string strArmed;
    int armedCount;
    int wasArmed;
    int notArmed;
    int armedGun;
    int armedUnknown;
};

#endif