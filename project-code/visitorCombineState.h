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
#include <algorithm>

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
    std::vector<comboShootingData *> theStatesShootingData;
    std::vector<comboDemogData*> theStatesDemogData;
    for (const auto entry : allStateShootingData)
    {
      theStatesShootingData.push_back(entry.second);
    }
    std::sort(theStatesShootingData.begin(), theStatesShootingData.end(), compareNumShootings);

    for(const auto entry : theStatesShootingData){
        theStatesDemogData.push_back(stateDmapEntry(entry->getName()));
    }

    std::ofstream myFile;
    myFile.open ("statesSortedOnNumShootings.csv");
    // Header Line
    myFile << "State,NUmber of Shootings,Percentage of Armed Shootings,Percentage of Shootings on Black,Percentage of Shootings on Hispanic,Percentage of Shootings on White,Percentage ofS hootings on Native,Percentage of Shootings on Asian,Percentage of Demog is Black,Percentage of Demog is White,Percentage of Demog is Hispanic,Percentage of Demog is Native,Percentage of Demog is Asian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theStatesShootingData.size(); i++){
        auto shootingObj = theStatesShootingData[i];
        auto demogObj = theStatesDemogData[i];
        if(shootingObj->getName() == demogObj->getName()){
            myFile <<  shootingObj->getName() << "," 
                   << shootingObj->getNumCases() << "," 
                   << shootingObj->getPerArmed() << "," 
                   << shootingObj->getPerAfricanAme() << "," 
                   << shootingObj->getPerHispanics() << "," 
                   << shootingObj->getPerWhite() << "," 
                   << shootingObj->getPerNativeAme() << "," 
                   << shootingObj->getPerAsians() << "," 
                   << demogObj->getBlackPerc() << "," 
                   << demogObj->getOnlyWhitePerc() << ","
                   << demogObj->getHispanicPerc() << ","
                   << demogObj->getNativePerc() << ","
                   << demogObj->getAsianPerc() 
                   << "\n";
        }
    }
    myFile.close();

/*     myFile.open("statesBlackPercShooting.csv");
    myFile << "State" */

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
};

#endif
