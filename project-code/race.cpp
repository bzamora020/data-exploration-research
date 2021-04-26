#include "race.h"

race &race::operator+=(const race &r)
{
    raceCount += r.raceCount;
    numAsians += r.numAsians;
    numAfricanAme += r.numAfricanAme;
    numWhite += r.numWhite;
    numNativeAmer += r.numNativeAmer;
    numHispanics += r.numHispanics;
    numOther += r.numOther;
    return *(this);
};