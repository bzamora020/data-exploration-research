#include "hospitalData.h"
#include "visitor.h"
#include <iostream>
#include <memory>
using namespace std;

/* print hospital data */
void hospitalData::accept(class Visitor &v){
	v.visit(static_pointer_cast<hospitalData>(this->getptr()));
}
