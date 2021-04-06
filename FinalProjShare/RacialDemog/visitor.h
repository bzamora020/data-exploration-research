#ifndef VISITOR_H
#define VISITOR_H

#include "hospitalData.h"
#include "demogData.h"

/* a visitor can visit any of my specific data types */
class Visitor {
//TODO fill in
public:
    virtual void visit(shared_ptr<demogData> e) = 0;
    virtual void visit(shared_ptr<hospitalData> h) = 0;
};
#endif

