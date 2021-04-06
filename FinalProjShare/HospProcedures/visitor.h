#ifndef VISITOR_H
#define VISITOR_H

#include "hospitalData.h"
#include "demogData.h"

class Visitor {
  public:
    virtual void visit(hospitalData* e) = 0;
    virtual void visit(demogData* e) = 0;
};

#endif
