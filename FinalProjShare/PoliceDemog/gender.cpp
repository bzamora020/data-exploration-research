#include "gender.h"

gender &gender::operator+=(const gender &g)
{
    countedGender += g.countedGender;
    numWomen += g.numWomen;
    numMen += g.numMen;
    return *(this);
};