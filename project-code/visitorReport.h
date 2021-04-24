#ifndef VISITREP_H
#define VISITREP_H

#include "comboShootingData.h"
#include "demogData.h"
#include "hospitalData.h"
#include "shootingData.h"
#include "visitor.h"
#include <memory>
#include <string>

class visitorReport : public Visitor // TODO fill in
{
public:
  virtual void visit(demogData *e) {
    cout << "Special report demog Data:" << endl;
    cout << "Demographics Info (State): " << e->getState() << endl;
    cout << "Education info:" << endl;
    cout << "(% Bachelor degree or more): " << e->getBAup() << endl;
    cout << "(% high school or more): " << e->getHSup() << endl;
    cout << "% below poverty: " << e->getBelowPoverty() << endl;
  }

  virtual void visit(hospitalData *e) {
    cout << "Special report hospital data:" << endl;
    cout << "Hospital Info: " << e->getState() << endl;
    cout << "Overall rating (out of 5): "
         << ((comboHospitalData *)e)->getOverallRate() << endl;
  }

  virtual void visit(shootingData *e) {
    cout << "Special report Shooting Data: " << endl;
    cout << "Number of cases: " << ((comboShootingData *)e)->getNumberOfCases()
         << endl;
  }
};

#endif