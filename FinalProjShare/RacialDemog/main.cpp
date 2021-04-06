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

#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "stats.h"
#include "statTool.h"
#include "statGatherer.h"

using namespace std;


int main() {

    std::vector<shared_ptr<placeData>> pileOfData;

    //set up outpout format
    cout << std::setprecision(2) << std::fixed;

    //read in the hospital data
    read_csv(pileOfData, "hospitals.csv", HOSPITAL);
    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG); 

    //create a visitor to combine the state data
    visitorCombineState theStates;
    //create the state demographic data
    statTool::createStateData(pileOfData, theStates);
    // theStates.printAllStates();

    //create a visitor to combine the county data (need aux map city-> county)
    visitorCombineCounty theCounties("simple_uscities.csv");
    statTool::createCountyData(pileOfData, theCounties);
    // theCounties.printAllCounties();

    //create statGathers to help make the data one for states one for counties
    stateGather fillStates;
    countyGather fillCounties;

    //Do stats work here these are examples...

    // //mixed data use 'sample'
    // cout << "\n**State data over 65  and overall Hospital Rating: " << endl;
    // statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopOver65, &comboHospitalData::getOverallRate);
    // cout << "\nCounty data overall HS and up and over Hospital Rating: " << endl;
    // statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getHSup, &comboHospitalData::getOverallRate);

    // cout << "\n**State data over 65 and num Hospitals: " << endl;
    // statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopOver65, &comboHospitalData::getNumH);

    // cout << "\nCounty data overall Below Poverty and over Hospital Rating: " << endl;
    // statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboHospitalData::getOverallRate);

    // cout << "\nCounty data popWithBA or Higher and num Hospitals: " << endl;
    // statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboHospitalData::getNumH);
    
    
    
    // //demogxdemog sample
    // cout << "\nCounty data Pop below poverty and BA up: " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &demogData::getBAup,
    //     &demogData::getBelowPovertyCount, &demogData::getBAupCount);
    // cout << "\nCounty data Pop w HS or Higher and pop below poverty: " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getHSup, &demogData::getBelowPoverty,
    //     &demogData::getHSupCount, &demogData::getBelowPovertyCount);

    // cout << "\nCounty data Pop younger than 18 and pop under 5: " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder18, &demogData::getpopUnder5,
    //     &demogData::getpopUnder18Count, &demogData::getpopUnder5Count);

    cout << "\nCounty data only white and pop below poverty: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getOnlyWhitePerc, &demogData::getBelowPoverty,
        &demogData::getOnlyWhiteCount, &demogData::getBelowPovertyCount);

    return 0;
}



