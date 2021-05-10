#ifndef VCOMBOS_H
#define VCOMBOS_H

#include "hospitalData.h"
#include "cityHospitalData.h"
#include "demogData.h"
#include "countyDemogData.h"
#include "shootingData.h"
#include "cityShootingData.h"
#include "visitor.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include "comboShootingData.h"

class visitorCombineState : public Visitor
{

public:
    void visit(hospitalData *e) // This was a raw ptr
    {
        //process the vector in our county data aggregate
        string stateName = e->getState();
        //if first state entry, create it
        if (allStateHospData.count(stateName) < 1)
        {

            allStateHospData[stateName] = new comboHospitalData("state", stateName);
        }
        //either way now add this county info
        //this keeps a running total
        allStateHospData[stateName]->addHospitaltoRegion(e); // This function takes in a share_ptr not a raw ptr
    }

    void visit(demogData *e)
    {
        string stateName = e->getState();
        //if first state entry, create it
        if (allStateDemogData.count(stateName) < 1)
        {

            allStateDemogData[stateName] = new comboDemogData("state", stateName);
        }
        //either way now add this county info
        //this keeps a running total
        allStateDemogData[stateName]->addDemogtoRegion(e);
    }

    void visit(shootingData *e)
    {
        string stateName = e->getState();

        if(allStateShootingData.count(stateName) < 1)
        {
            allStateShootingData[stateName] = new comboShootingData("state", stateName);
        }

        allStateShootingData[stateName]->addShootingtoRegion(e);

    }

    // Getters
    std::map<string, comboDemogData *> stateDmap() const
    {
        return allStateDemogData;
    }

    std::map<string, comboHospitalData *> stateHmap() const
    {
        return allStateHospData;
    }

    std::map<string, comboShootingData *> stateSmap() const
    {
        return allStateShootingData;
    }

    comboDemogData *stateDmapEntry(string stateN)
    {
        return allStateDemogData[stateN];
    }

    comboHospitalData *stateHmapEntry(string stateN)
    {
        return allStateHospData[stateN];
    }



    comboShootingData *stateSmapEntry(string stateN)
    {
        return allStateShootingData[stateN];
    }

  void mostShootingsState()
  {
    std::vector<comboShootingData *> theStates;
    for (const auto entry : allStateShootingData)
    {
      theStates.push_back(entry.second);
    }
    std::sort(theStates.begin(), theStates.end(), compareNumShootings);

    cout << "Counties with most police shootings: \n"
         << "1.) " << theStates[0]->getRegionType() << " in this state ->" << theStates[0]->getState() << " had this many fatal police shootings ->" << theStates[0]->getNumCases() << endl
         << "2.) " << theStates[1]->getRegionType() << " in this state ->" << theStates[1]->getState() << " had this many fatal police shootings ->" << theStates[1]->getNumCases() << endl
         << "3.) " << theStates[2]->getRegionType() << " in this state ->" << theStates[2]->getState() << " had this many fatal police shootings ->" << theStates[2]->getNumCases() << endl;
  }

  void leastShootingsState()
  {
    std::vector<comboShootingData *> theStates;
    for (const auto entry : allStateShootingData)
    {
      theStates.push_back(entry.second);
    }
    std::sort(theStates.begin(), theStates.end(), compareLeastNumShootings);

    cout << "Counties with least police shootings: \n"
         << "1.) " << theStates[0]->getRegionType() << " in this state ->" << theStates[0]->getState() << " had this many fatal police shootings ->" << theStates[0]->getNumCases() << endl
         << "2.) " << theStates[1]->getRegionType() << " in this state ->" << theStates[1]->getState() << " had this many fatal police shootings ->" << theStates[1]->getNumCases() << endl
         << "3.) " << theStates[2]->getRegionType() << " in this state ->" << theStates[2]->getState() << " had this many fatal police shootings ->" << theStates[2]->getNumCases() << endl;
  }


private:
    // Private data like maps and stuff

    //state maps
    std::map<string, comboDemogData *> allStateDemogData;
    std::map<string, comboHospitalData *> allStateHospData;
    std::map<string, comboShootingData *> allStateShootingData;

  static bool compareNumShootings(comboShootingData *a, comboShootingData *b)
  {
    return (a->getNumCases() > b->getNumCases());
  }

  static bool compareLeastNumShootings(comboShootingData *a, comboShootingData *b)
  {
    return (a->getNumCases() < b->getNumCases());
  }

};

#endif
