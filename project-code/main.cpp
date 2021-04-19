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

#include "shootingData.h"
#include "cityShootingData.h"
#include "comboShootingData.h"

#include "parse.h"

#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "stats.h"
#include "statTool.h"
#include "statGatherer.h"

using namespace std;

int main()
{

    std::vector<shared_ptr<placeData>> pileOfData;

    //set up outpout format
    cout << std::setprecision(2) << std::fixed;

    //read in the hospital data
    read_csv(pileOfData, "hospitals.csv", HOSPITAL);
    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG);
    //read in the shooting data
    read_csv(pileOfData, "police_shootings_cleaned.csv", SHOOTING);

    //create a visitor to combine the state data
    visitorCombineState theStates;
    //create the state demographic data
    statTool::createStateData(pileOfData, theStates);
    //theStates.printAllStates();

    //create a visitor to combine the county data (need aux map city-> county)
    visitorCombineCounty theCounties("simple_uscities.csv");
    statTool::createCountyData(pileOfData, theCounties);
    //theCounties.printAllCounties();

    //create statGathers to help make the data one for states one for counties
    stateGather fillStates;
    countyGather fillCounties;

    //Do stats work here these are examples...

    //mixed data use 'sample'

    //cout << "PROFFESSOR'S EXAMPLES" << endl;

    cout << endl;

    /* cout << "**State data over 65  and number Hospitals: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopOver65, &comboHospitalData::getNumH);

    cout << endl;

    cout << "County data over 65 and number Hospitals: " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboHospitalData::getNumH);

    cout << endl;

    //demogxdemog sample
    cout << "State data Pop under 5 and BA up: " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &fillStates, &demogData::getpopUnder5, &demogData::getBAup,
                                          &demogData::getpopUnder5Count, &demogData::getBAupCount); // Use of function pointers right here

    cout << endl;
    */
    cout << "County data Pop under 5 and BA up: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder5, &demogData::getBAup,
                                          &demogData::getpopUnder5Count, &demogData::getBAupCount); 

    cout << endl;
    cout << "***** OUR COMPUTATIONS *****" << endl;
    
    cout << endl;

    statTool::computeStatsShootingRegionData(&theCounties, &fillCounties, &shootingData::getPerAfricanAme, &shootingData::getPerFleeing);
    statTool::computeStatsShootingRegionData(&theCounties, &fillCounties, &shootingData::getPerAfricanAme, &shootingData::getPerMI);

    
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getHispanicPerc, &shootingData::getPerHispanics);
    /*
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerAfricanAme);

    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerMen);
    */
    return 0;
}
