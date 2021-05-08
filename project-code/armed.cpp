#include "armed.h"

armed &armed::operator+=(const armed &a)
{

    armedGun += a.armedGun;
    notArmed += a.notArmed;
    wasArmed += a.wasArmed;
    armedCount += a.armedCount;
    armedUnknown += a.armedUnknown;

    return *(this);
};