#ifndef VISITOR_H
#define VISITOR_H

#include "hospitalData.h"
#include "demogData.h"
#include "placeData.h"
#include "shootingData.h"

/* a visitor can visit any of my specific data types */
class Visitor
{
public:
    virtual void visit(demogData *e) = 0;
    virtual void visit(hospitalData *e) = 0;
    virtual void visit(shootingData *e) = 0;
};
#endif
