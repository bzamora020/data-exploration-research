#include "visitor.h"
#include "placeData.h"


void placeData::accept(class Visitor &v){
    v.visit(this);
}