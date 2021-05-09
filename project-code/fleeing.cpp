#include "fleeing.h"

fleeing &fleeing::operator+=(const fleeing &f)
{
    fleeingCases += f.fleeingCases;
    notFleeing += f.notFleeing;
    triedFleeing += f.triedFleeing;
    return *(this);
};
