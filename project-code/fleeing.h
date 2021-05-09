#ifndef FLEEING_H
#define FLEEING_H

#include <string>

using namespace std;

class fleeing
{
public:
    fleeing(string inFleeing)
    {
        fleeingCases = 0;
        triedFleeing = 0;
        notFleeing = 0;

        if ((inFleeing.compare("Foot") == 0) || (inFleeing.compare("Car") == 0) || (inFleeing.compare("Other") == 0))
        {
            triedFleeing++;
            fleeingCases++;
        }
        else
        {
            fleeingCases++;
            notFleeing++;
        }
    }

    int getFleeingCases() const { return fleeingCases; }
    int getTriedFleeing() const { return triedFleeing; }
    int getNotTriedFleeing() const { return notFleeing; }

    fleeing &operator+=(const fleeing &f);

private:
    int fleeingCases;
    int triedFleeing;
    int notFleeing;
};

#endif