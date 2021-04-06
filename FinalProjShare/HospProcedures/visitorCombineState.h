#ifndef VCOMBOS_H
#define VCOMBOS_H

#include <memory>
#include <map>

#include "hospitalData.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "visitor.h"


class visitorCombineState : public Visitor {
  public:
    //required because normal pointers are used instead of smart ones.
    ~visitorCombineState(){
      for (auto key : allStateDemogData){
        delete key.second;
      }
      for (auto key : allStateHospData){
        delete key.second;
      }
    }

    std::map<string, comboDemogData*>& stateDmap() { return allStateDemogData; }
    comboDemogData* stateDmapEntry(string stateN) {
      if (allStateDemogData.count(stateN) < 1){
        return NULL;
      } else {
        return allStateDemogData[stateN];
      }
    }


    std::map<string, comboHospitalData*> stateHmap() const { return allStateHospData; }
    comboHospitalData* stateHmapEntry(string stateN) {
      if (allStateHospData.count(stateN) < 1){
        return NULL;
      } else {
        return allStateHospData[stateN];
      }
    }

    virtual void visit(demogData* e){
      string regionName = e->getRegion();
      if (allStateDemogData.count(regionName) < 1) {
         //cout << "Making a new state entry: " << regionName << endl;
         allStateDemogData[regionName] = new comboDemogData(regionName);
      }
      //either way now add this county info
      //this keeps a running total
      allStateDemogData[regionName]->addDemogtoRegion(e);
    }

    //This will need its ratings updated after aggreagating all data!!!
    virtual void visit(hospitalData* e){
      string regionName = e->getRegion();
      if (allStateHospData.count(regionName) < 1) {
         //cout << "Making a new state entry: " << regionName << endl;
         allStateHospData[regionName] = new comboHospitalData(regionName);
      }
      //either way now add this county info
      //this keeps a running total
      allStateHospData[regionName]->addHospitaltoRegion(e);
    }

    void updateRatings() {
      for (auto &i : allStateHospData){
        i.second->updateRegionRatings();

      }
    }


    std::map<string, comboDemogData*> allStateDemogData;
  private:

    std::map<string, comboHospitalData*> allStateHospData;
};

#endif
