#ifndef VISITORREPORT_H
#define VISITORREPORT_H

#include "demogData.h"
#include "hospitalData.h"
#include "visitor.h"

class visitorReport : public Visitor {
    public:
        virtual void visit(demogData *d){
            cout << "\nSpecial report demog Data:";
            cout << "\nDemographics Info (State): " << d->getState();
            cout << "\nEducation info:";
            cout << "\n(% Bachelor degree or more): " << d->getBAup();
            cout << "\n(% high school or more): " << d->getHSup();
            cout << "\n% below poverty: " << d->getBelowPoverty();
        }

        virtual void visit(hospitalData *h){
            comboHospitalData* HD = dynamic_cast<comboHospitalData*>(h);
            cout << "\nSpecial report hospital data:";
            cout << "\nHospital Info: " << HD->getState();
            cout << "\nOverall rating (out of 5): " << HD->getOverallRate();
        }
};

#endif