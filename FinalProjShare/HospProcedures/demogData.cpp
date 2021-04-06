#include "demogData.h"
#include <sstream>
#include "visitor.h"

void demogData::accept(class Visitor &v){
  v.visit(this);
}
