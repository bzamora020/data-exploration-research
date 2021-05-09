#include "mental.h"

mental &mental::operator+=(const mental &m)
{
    mentalI += m.mentalI;
    countedMI += m.countedMI;
    return *(this);
};