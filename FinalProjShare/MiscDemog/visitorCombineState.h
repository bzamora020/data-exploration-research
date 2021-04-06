#ifndef VCOMBOS_H
#define VCOMBOS_H

#include "hospitalData.h"
#include "demogData.h"
#include "visitor.h"
#include <memory>

class visitorCombineState : public Visitor {
    public:
        virtual void visit(demogData *d) override {
            string stateName = d->getState();
            if (allStateDemogData.count(stateName) < 1) {
                allStateDemogData[stateName] = new comboDemogData("state", stateName);
            }
            allStateDemogData[stateName]->addDemogtoRegion(d);
        }

        virtual void visit(hospitalData *h) override {
            string stateName = h->getState();
            if (allStateHospData.count(stateName) < 1) {
                allStateHospData[stateName] = new comboHospitalData("state", stateName);
            }
            allStateHospData[stateName]->addHospitaltoRegion(h);
        }
        void getHMsizes() override {
            cout << allStateHospData.size() << " " << allStateDemogData.size() << endl;
        }
        std::map<string, comboDemogData*> stateDmap() const { return allStateDemogData; }
        comboDemogData* stateDmapEntry(string stateN) { return allStateDemogData[stateN]; }
        std::map<string, comboHospitalData*> stateHmap() const { return allStateHospData; }
        comboHospitalData* stateHmapEntry(string stateN) { return allStateHospData[stateN]; }

    private:
        std::map<string, comboDemogData*> allStateDemogData;
        std::map<string, comboHospitalData*> allStateHospData;
};

#endif
