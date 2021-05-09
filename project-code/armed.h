#ifndef ARMED_H
#define ARMED_H

#include <iostream>
#include <string>

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

    int getArmedCount() const { return armedCount; }
    int getWasArmed() const { return wasArmed; }
    int getNotArmed() const { return notArmed; }
    int getArmedGun() const { return armedGun; }
    string getArmedStr() const { return strArmed; }

    armed &operator+=(const armed &a);

private:
    //String holding the raw values
    string strArmed;

    //Counts of the raw values
    int armedGun;
    int notArmed;
    int wasArmed;
    int armedCount;
    int armedUnknown;
};

#endif