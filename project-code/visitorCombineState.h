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
        //if((entry.first == "CA")||(entry.first == "AZ")||(entry.first == "TX")||(entry.first == "HI")||(entry.first == "AK")||(entry.first == "DC")){
            theStatesShootingData.push_back(entry.second);
        //}
        
    }
    std::sort(theStatesShootingData.begin(), theStatesShootingData.end(), compareNumShootings);

    for(const auto entry : theStatesShootingData){
        theStatesDemogData.push_back(stateDmapEntry(entry->getName()));
    }

    /*
    CSVs to get:
        - DC, AK, HI, CA, TX, AZ
        Racial Demog and Shootings race identification
    */

    std::ofstream myFile;

    myFile.open("statesPerBodyCamRaceSpecified.csv");

    myFile << "State,NumBlackBodyCamOn,NumNativeBodyCamOn,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theStatesShootingData.size(); i++){
        auto shootingObj = theStatesShootingData[i];
        auto demogObj = theStatesDemogData[i];

            if(shootingObj->getName() == demogObj->getName()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getCountBlackBodyCamOn() << "," 
                   << shootingObj->getCountNativeBodyCamOn() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();

    myFile.open("statesPerMIRaceSpecified.csv");

    myFile << "State,NumBlackMI,NumNativeMI,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theStatesShootingData.size(); i++){
        auto shootingObj = theStatesShootingData[i];
        auto demogObj = theStatesDemogData[i];

            if(shootingObj->getName() == demogObj->getName()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getCountBlackMI() << "," 
                   << shootingObj->getCountNativeMI() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();

    myFile.open("statesPerWasFleeingRaceSpecified.csv");

    myFile << "State,NumBlackFleeing,NumNativeFleeing,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theStatesShootingData.size(); i++){
        auto shootingObj = theStatesShootingData[i];
        auto demogObj = theStatesDemogData[i];

            if(shootingObj->getName() == demogObj->getName()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getCountBlackFleeing() << "," 
                   << shootingObj->getCountNativeFleeing() << "," 
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();

    myFile.open ("statesPerArmedRaceSelected.csv"); 
    // Header Line
     myFile << "State,NumBlackArmed,NumNativeArmed,NumShootingsOnBlack,NumShootingsOnHispanic,NumShootingsOnWhite,NumShootingsOnNative,NumShootingsOnAsian\n";
    myFile << std::setprecision(2) << std::fixed;
    for(int i = 0; i < theStatesShootingData.size(); i++){
        auto shootingObj = theStatesShootingData[i];
        auto demogObj = theStatesDemogData[i];

            if(shootingObj->getRegionType() == demogObj->getRegionType()){
            myFile <<  shootingObj->getRegionType() << "," 
                   << shootingObj->getCountBlackArmed() << ","
                   << shootingObj->getCountNativeArmed() << ","
                   << shootingObj->getRaceData().getNumAfricanAme() << "," 
                   << shootingObj->getRaceData().getNumHispanics() << "," 
                   << shootingObj->getRaceData().getNumNative() << "," 
                   << shootingObj->getRaceData().getNumWhite() << "," 
                   << shootingObj->getRaceData().getNumAsians() 
                   << "\n";
        }
    }
    myFile.close();

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