#ifndef VCOMBOS_H
#define VCOMBOS_H

#include "hospitalData.h"
#include "demogData.h"
#include "visitor.h"
#include <memory>

class visitorCombineState : public Visitor {
    public:
    virtual void visit(placeData *p) {
        if(dynamic_cast<demogData*>(p)) {
            demogData* d = static_cast<demogData*>(p);
            string stateName = d->getState();
            //if first state entry, create it
            if (allStateDemogData.count(stateName) < 1) {
                allStateDemogData[stateName] = new comboDemogData("State", stateName);
            }
            //either way now add this county info 
            //this keeps a running total
            allStateDemogData[stateName]->addDemogtoRegion(d);
        } else {
            hospitalData* h = static_cast<hospitalData*>(p);
            string stateName = h->getState();
            //if first state entry, create it
            if (allStateHospData.count(stateName) < 1) {
                allStateHospData[stateName] = new comboHospitalData("State", stateName);
            }
            // either way add hospital data to the state
            allStateHospData[stateName]->addHospitaltoRegion(h);
        }
    }

    std::map<string, comboDemogData*> stateDmap() {return allStateDemogData;}
    comboDemogData* stateDmapEntry(string stateN)  {return allStateDemogData[stateN];}

    std::map<string, comboHospitalData*> stateHmap() const {return allStateHospData;}
    comboHospitalData* stateHmapEntry(string stateN) {return allStateHospData[stateN];}
  
    private:
    	//state maps
        std::map<string, comboDemogData*> allStateDemogData;
        std::map<string, comboHospitalData*> allStateHospData;

};

#endif
