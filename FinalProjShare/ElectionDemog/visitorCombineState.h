#ifndef VCOMBOS_H
#define VCOMBOS_H

#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "comboElectionData.h"
#include "visitor.h"
#include <map>
#include <memory>

using namespace std;

class visitorCombineState : public Visitor {
public:
    void visit(demogData* e) {
        string name = e->getName();
        string stateName = e->getState();
        //if first state entry, create it
            
        if (allStateDemogData.count(stateName) < 1) {
            //cout << "Making a new state entry: " << stateName << endl;
            allStateDemogData[stateName] = new comboDemogData(name, stateName);
        }
        //either way now add this county info 
        //this keeps a running total
    
        shared_ptr<demogData> p(&(*e));
        allStateDemogData[stateName]->addDemogtoRegion(p);

    }

    void visit(hospitalData* e) {
        string state = "";
        state = e->getState();
        //if true, key is not found
        if (allStateHospData.count(state) == 0) {
            comboHospitalData* p = new comboHospitalData("state", state);
            allStateHospData.insert(make_pair(state, p)); //state and region names are the same
        }
        shared_ptr<hospitalData> p(&(*e));
        allStateHospData.at(state)->addHospitaltoRegion(p);
    }

    void visit(electionData* e) {
        string name = e->getName();
        string stateName = e->getState();
        //if first state entry, create it
        if (allStateElecData.count(stateName) < 1) {
            //cout << "Making a new state entry: " << stateName << endl;
            comboElectionData* p = new comboElectionData("state", stateName);
            allStateElecData[stateName] = p;
        }
        //either way now add this county info 
        //this keeps a running total
        //shared_ptr<electionData> h(&(*e));
        
        allStateElecData[stateName]->addElectoRegion(e);
    
    }

    map<string, comboDemogData*> stateDmap() { return allStateDemogData; }
    comboDemogData* stateDmapEntry(string stateN) { return allStateDemogData[stateN]; }
    map<string, comboHospitalData*> stateHmap() const { return allStateHospData; }
    comboHospitalData* stateHmapEntry(string stateN) { return allStateHospData[stateN]; }
    map<string, comboElectionData*> stateEmap() const { return allStateElecData; }
    comboElectionData* stateEmapEntry(string stateN) { return allStateElecData[stateN]; }


private:
    map<string, comboDemogData*> allStateDemogData;
    map<string, comboHospitalData*> allStateHospData;
    map<string, comboElectionData*> allStateElecData;
};

#endif
