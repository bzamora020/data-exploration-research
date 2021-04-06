#include "demogData.h"
#include "visitor.h"
#include <sstream>

/* print county demographic data */
void demogData::accept(class Visitor &v){
	v.visit(static_pointer_cast<demogData>(this->getptr()));
}
