#ifndef VISIT_REPORT_H
#define VISIT_REPORT_H

#include "visitor.h"
#include <iostream>
#include <memory>
#include <ostream>



class VisitorReport : public Visitor {

    private:
        void visit(std::shared_ptr<hospitalData> hosp) override {
            cout << "\nSpecial report hospital data:";
            cout << "\nHospital Info: " << hosp->getState();
            cout << "\nOverall rating (out of 5): " << hosp->getOverallRate();
        }

        void visit(demogData &demog) override {
            cout << "\nSpecial report demog Data:";
            cout << "\nDemographics Info (State): " << demog.getState();
            cout << "\nEducation info:";
            cout << "\n(% Bachelor degree or more): " << demog.getBAup();
            cout << "\n(% high school or more): " << demog.getHSup();
            cout << "\n% below poverty: " << demog.getBelowPoverty();
        }
};


#endif