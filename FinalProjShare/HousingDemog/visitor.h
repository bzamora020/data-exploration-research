#ifndef VISITOR_H
#define VISITOR_H

#include "hospitalData.h"
#include "demogData.h"

/* a visitor can visit any of my specific data types */ //(hospitalData and demogData)
class Visitor {
public:
    //virtual void visit(demogData *d) = 0;
    //virtual void visit(hospitalData *h) = 0;
    virtual void visit(placeData *p) = 0;
};
#endif
