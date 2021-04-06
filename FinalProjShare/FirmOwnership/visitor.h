#ifndef VISITOR_H
#define VISITOR_H

#include "hospitalData.h"
#include "demogData.h"
#include <memory>

/* a visitor can visit any of my specific data types */
class Visitor {
public:
	virtual void visit(shared_ptr<hospitalData> h)=0;
	virtual void visit(shared_ptr<demogData> d)= 0;

	virtual ~Visitor(){}
};
#endif

