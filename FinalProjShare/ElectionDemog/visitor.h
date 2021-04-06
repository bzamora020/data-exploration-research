#ifndef VISITOR_H
#define VISITOR_H

#include "demogData.h"
#include "hospitalData.h"
#include "electionData.h"

/* a visitor can visit any of my specific data types */
class Visitor {
public:
    virtual void visit(demogData* e) = 0;
    virtual void visit(hospitalData* e) = 0;
    virtual void visit(electionData* e) = 0;
};
#endif


