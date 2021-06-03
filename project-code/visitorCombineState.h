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
#include <algorithm>
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
    std::vector<comboShootingData *> theStatesShootingData;
    std::vector<comboDemogData*> theStatesDemogData;
    for (const auto entry : allStateShootingData)
    {
        if((entry.first == "CA")||(entry.first == "AZ")||(entry.first == "TX")||(entry.first == "HI")||(entry.first == "AK")||(entry.first == "DC")){
            theStatesShootingData.push_back(entry.second);
        }
        
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
    myFile.open ("statesSortedOnNumshootingsSelected2018_2020.csv"); 
    // Header Line
    myFile << "State, JanShooting18, FebShooting18, MarShooting18, AprShooting18, MayShooting18, JunShooting18, JulShooting18, AugShooting18, SepShooting18, OctShooting18, NovShooting18, DecShooting18,"
            <<" JanShooting19, FebShooting19, MarShooting19, AprShooting19, MayShooting19, JunShooting19, JulShooting19, AugShooting19, SepShooting19, OctShooting19, NovShooting19, DecShooting19,"
            <<" JanShooting20, FebShooting20, MarShooting20, AprShooting20, MayShooting20, JunShooting20, JulShooting20, AugShooting20, SepShooting20, OctShooting20, NovShooting20, DecShooting20\n";
    myFile << std::setprecision(2) << std::fixed;

    for(int i = 0; i < theStatesShootingData.size(); i++){
        auto shootingObj = theStatesShootingData[i];
        auto demogObj = theStatesDemogData[i];
        if(shootingObj->getName() == demogObj->getName()){
              myFile<< shootingObj->getName() << ","

                    << shootingObj->getDateData().getNumShootingsJan2018() << "," 
                    << shootingObj->getDateData().getNumShootingsFeb2018() << "," 
                    << shootingObj->getDateData().getNumShootingsMar2018() << "," 
                    << shootingObj->getDateData().getNumShootingsApr2018() << "," 
                    << shootingObj->getDateData().getNumShootingsMay2018() << "," 
                    << shootingObj->getDateData().getNumShootingsJun2018() << "," 
                    << shootingObj->getDateData().getNumShootingsJul2018() << "," 
                    << shootingObj->getDateData().getNumShootingsAug2018() << "," 
                    << shootingObj->getDateData().getNumShootingsSep2018() << "," 
                    << shootingObj->getDateData().getNumShootingsOct2018() << "," 
                    << shootingObj->getDateData().getNumShootingsNov2018() << "," 
                    << shootingObj->getDateData().getNumShootingsDec2015() << ","
                    << shootingObj->getDateData().getNumShootingsJan2019() << "," 
                    << shootingObj->getDateData().getNumShootingsFeb2019() << "," 
                    << shootingObj->getDateData().getNumShootingsMar2019() << "," 
                    << shootingObj->getDateData().getNumShootingsApr2019() << "," 
                    << shootingObj->getDateData().getNumShootingsMay2019() << "," 
                    << shootingObj->getDateData().getNumShootingsJun2019() << "," 
                    << shootingObj->getDateData().getNumShootingsJul2019() << "," 
                    << shootingObj->getDateData().getNumShootingsAug2019() << "," 
                    << shootingObj->getDateData().getNumShootingsSep2019() << "," 
                    << shootingObj->getDateData().getNumShootingsOct2019() << "," 
                    << shootingObj->getDateData().getNumShootingsNov2019() << "," 
                    << shootingObj->getDateData().getNumShootingsDec2019() << ","                    
                    << shootingObj->getDateData().getNumShootingsJan2020() << "," 
                    << shootingObj->getDateData().getNumShootingsFeb2020() << "," 
                    << shootingObj->getDateData().getNumShootingsMar2020() << "," 
                    << shootingObj->getDateData().getNumShootingsApr2020() << "," 
                    << shootingObj->getDateData().getNumShootingsMay2020() << "," 
                    << shootingObj->getDateData().getNumShootingsJun2020() << "," 
                    << shootingObj->getDateData().getNumShootingsJul2020() << "," 
                    << shootingObj->getDateData().getNumShootingsAug2020() << "," 
                    << shootingObj->getDateData().getNumShootingsSep2020() << "," 
                    << shootingObj->getDateData().getNumShootingsOct2020() << "," 
                    << shootingObj->getDateData().getNumShootingsNov2020() << "," 
                    << shootingObj->getDateData().getNumShootingsDec2020()
                    << "\n";
        }
    }
    myFile.close();
  }

  void leastShootingsState()
  {
    std::vector<comboShootingData *> theStates;
    std::vector<comboDemogData *> theStatesD;
    for (const auto entry : allStateShootingData)
    {
      theStates.push_back(entry.second);
    }
    std::sort(theStates.begin(), theStates.end(), compareLeastNumShootings);

    for(auto entry : theStates){
      theStatesD.push_back(stateDmapEntry(entry->getState()));
    }

    cout << "Counties with least police shootings: \n";
    for(int i = 0; i < theStates.size(); i++){
         cout << i+1 << ".) " <<"This state ->" << theStates[i]->getState() << " had this many fatal police shootings ->" << theStates[i]->getNumCases() 
         << "\nBlack Demog Perc: " << theStatesD[i]->getBlackPerc() 
         << "\nHispanic Demog Perc: " << theStatesD[i]->getHispanicPerc() 
         << "\nWhite Demog Perc: " << theStatesD[i]->getWhitePerc() 
         << "\nNative Demog Perc: " << theStatesD[i]->getNativePerc() 
         << "\nAsian Demog Perc: " << theStatesD[i]->getAsianPerc() 
         << endl;
    }
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
