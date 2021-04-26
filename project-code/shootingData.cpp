#include "shootingData.h"
#include "visitor.h"

void shootingData::accept(class Visitor &v) 
{
    v.visit(this);
}
