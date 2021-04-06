#ifndef VISITREP_H
#define VISITREP_H

#include "hospitalData.h"
#include "demogData.h"
#include "visitor.h"

class visitorReport : public Visitor {
    virtual void visit(demogData* d) {
        cout << "\nSpecial report demog Data:";
        cout << *d;
    }
    virtual void visit(hospitalData* h) {
        cout << "\nSpecial report hospital data:" ;
        cout << *h;
     }
};

#endif
