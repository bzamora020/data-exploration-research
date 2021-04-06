#ifndef VISITOR_H
#define VISITOR_H

#include "hospitalData.h"
#include "demogData.h"

class Visitor {
    public:
        virtual void visit(demogData *d) = 0;
        virtual void visit(hospitalData *h) = 0;
        virtual void getHMsizes() = 0;
};

#endif