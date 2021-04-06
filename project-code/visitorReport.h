#ifndef VISITREP_H
#define VISITREP_H

#include <memory>
#include <string>
#include "visitor.h"
#include "hospitalData.h"
#include "demogData.h"

class visitorReport : public Visitor //TODO fill in
{
public:
    virtual void visit(demogData *e)
    {
        cout << "Special report demog Data:" << endl;
        cout << "Demographics Info (State): " << e->getState() << endl;
        cout << "Education info:" << endl;
        cout << "(% Bachelor degree or more): " << e->getBAup() << endl;
        cout << "(% high school or more): " << e->getHSup() << endl;
        cout << "% below poverty: " << e->getBelowPoverty() << endl;
    }

    virtual void visit(hospitalData *e)
    {
        cout << "Special report hospital data:" << endl;
        cout << "Hospital Info: " << e->getState() << endl;
        cout << "Overall rating (out of 5): " << ((comboHospitalData *)e)->getOverallRate() << endl;
    }
};

#endif