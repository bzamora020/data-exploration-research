#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <math.h>
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"
#include "dataAQ.h"

#include "stats.h"
#include "statTool.h"
#include "statGatherer.h"

using namespace std;

/*
* Things we did
can potentially support variable amount of candidates
wrote a new parse, wrote reading the candidate names
extended electionData from placeData
made candidates in electionData protected so it's visible to comboElectionData
overloaded the operator + to add the data of candidates.
made copy constructors for electionData and comboElectionData as a fast way to duplicate data
we gathered data into counties and states
*/

int main() {

    vector<shared_ptr<placeData>> pileOfData;

    //set up outpout format
    cout << setprecision(2) << std::fixed;

    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG);
    //read in the hospital data
    read_csv(pileOfData, "hospitals.csv", HOSPITAL);
    //read in the election data
    read_csv(pileOfData, "election.csv", ELECTION);

    //create a visitor to combine the state data
    visitorCombineState theStates;
    //create the state demographic data
    
    statTool::createStateData(pileOfData, theStates);
    //theStates.printAllStates();
    
    //create a visitor to combine the county data (need aux map city-> county)
    visitorCombineCounty theCounties("simple_uscities.csv");
    statTool::createCountyData(pileOfData, theCounties);
    //theCounties.printAllCounties();

    countyGather fillCounties;

    cout << "Relationship between Poverty Rate and Democrat Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboElectionData::getDemocratVotes);
    cout << "Relationship between Poverty Rate and Republican Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboElectionData::getRepublicanVotes);

    cout << "Relationship between Poverty Rate and Bernie Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboElectionData::getBernieVotes);
    cout << "Relationship between Poverty Rate and Hillary Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboElectionData::getHillaryVotes);

    cout << "Relationship between Poverty Rate and Trump Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboElectionData::getTrumpVotes);
    cout << "Relationship between Poverty Rate and Cruz Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboElectionData::getCruzVotes);

    cout << "Relationship between Population over 65 and Bernie Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboElectionData::getBernieVotes);
    cout << "Relationship between Population over 65 and Hillary Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboElectionData::getHillaryVotes);
    
    cout << "Relationship between Population over 65 and Trump Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboElectionData::getTrumpVotes);
    cout << "Relationship between Population over 65 and Cruz Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboElectionData::getCruzVotes);

    cout << "Relationship between Population and Democrat Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getPopDouble, &comboElectionData::getDemocratVotes);
    cout << "Relationship between Population and Republican Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getPopDouble, &comboElectionData::getRepublicanVotes);

    cout << "Relationship between college education and Bernie Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboElectionData::getBernieVotes);
    cout << "Relationship between college education and Hillary Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboElectionData::getHillaryVotes);
    
    cout << "Relationship between college education and Trump Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboElectionData::getTrumpVotes);
    cout << "Relationship between college education and Cruz Votes: \n";
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboElectionData::getCruzVotes);



    
    /*
    computeStatsMixRegionData(Visitor* theRegions, statGatherer* fillCounties, 
        double (demogData::*f1)() const, double (comboElectionData::*f2)() const)
    */

    

    //shared_ptr<electionData> elecD = static_pointer_cast<electionData>(theElectionData.at(0)); //first county election data.
    
    //create the state demographic data
    //theAnswers.createStateDemogData((std::vector<shared_ptr<demogData>>&)theCountyDemogData);

    //create the state hospital data
    //theAnswers.createStateHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);
    return 0;
}
