#ifndef VCOMBOS_H
#define VCOMBOS_H

#include "hospitalData.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "visitor.h"
#include <memory>

using namespace std;

class visitorCombineState : public Visitor {

public:

    virtual void visit(shared_ptr<demogData> e){
        shared_ptr<demogData> comboData = static_pointer_cast<demogData>(e);
        string stateName = e->getState();
        //if first state entry, create it
        if (allStateDemogData.count(stateName) < 1) {
        //cout << "Making a new state entry: " << stateName << endl;
            allStateDemogData[stateName] = new comboDemogData(stateName);
        }
        //either way now add this county info 
        //this keeps a running total
        // shared_ptr<demogData> comboDemog = static_pointer_cast<demogData>(e);
        allStateDemogData[stateName]->addCountytoState(comboData);

        //remember to average at end

    }

    virtual void visit(shared_ptr<hospitalData> e){
        shared_ptr<hospitalData> comboData = static_pointer_cast<hospitalData>(e);
        string stateName = e->getState();
        if(allStateHospData.count(stateName) < 1) {
            allStateHospData[stateName] = new comboHospitalData(stateName, "", "state");
        }
        allStateHospData[stateName]->addCountytoState(e);
    }

    map<string, comboDemogData*> stateDmap(){
        return allStateDemogData;
    }
    comboDemogData* stateDmapEntry(string stateN){
        return allStateDemogData[stateN];
    }

    map<string, comboHospitalData*> stateHmap(){
        return allStateHospData;
    }
    comboHospitalData* stateHmapEntry(string stateN){
        return allStateHospData[stateN];
    }

    void printAllStates(){
        for (auto entry: allStateDemogData){
            cout << "state: " << entry.first << endl;
            cout << "popOver65: " << entry.second->getpopOver65() << endl;
        }
        for (auto entry: allStateHospData){
            cout << "state: "<< entry.first << endl;
            cout << "overall Rate: " << entry.second->getOverallRate() << endl;
        }
    }

private:
    map<string, comboHospitalData*> allStateHospData;
    std::map<string, comboDemogData*> allStateDemogData;

};

#endif
