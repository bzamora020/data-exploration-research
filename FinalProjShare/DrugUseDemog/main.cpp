#include <iostream>
#include <iterator>
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
    //read in the demographic data
    read_csv(pileOfData, "drugs.csv", DRUG);

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

    // //mixed data use 'sample'
    // cout << "**State data over 65  and number Hospitals: " << endl;
    // statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopOver65, &comboHospitalData::getNumH);
    // cout << "County data over 65 and number Hospitals: " << endl;
    // statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboHospitalData::getNumH);

    //demogxdemog sample
    // cout << "State data Pop under 5 and BA up: " << endl;
    // statTool::computeStatsDemogRegionData(&theStates, &fillStates, &demogData::getpopUnder5, &demogData::getBAup,
    //     &demogData::getpopUnder5Count, &demogData::getBAupCount);
    // cout << "County data Pop under 5 and BA up: " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder5, &demogData::getBAup,
    //     &demogData::getpopUnder5Count, &demogData::getBAupCount);

    //std::map<string, comboDemogData*> stateMap = theStates.stateHmap();
    std::map<string, comboHospitalData*> stateHmap = theStates.stateHmap();
    

    std::map<string, comboDemogData*> countyMap = theCounties.countyDmap();
    // std::map<string, comboHospitalData*> countyMap = theCounties.countyHmap();

    std::map<string, drugData*> stateDrugMap = theStates.stateDrugmap();



    std::map<string, comboDemogData*>::iterator it;
    // std::map<string, comboHospitalData*>::iterator it;

    std::vector<double> nums;

    cout << endl;

    cout << "PopUnder18 and Cocaine Corr: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopUnder18, &drugData::getCocaine);
    cout << endl;

    cout << "PopUnder18 and Alcohol Corr: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopUnder18, &drugData::getAlcohol);
    cout << endl;

    cout << "Pain Medication and Overall Hospital Rate: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &drugData::getPain, &hospitalData::getOverallRate);
    cout << endl;

    cout << "PopUnder18 and Pain Medication Corr: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopUnder18, &drugData::getPain);
    cout << endl;

    cout << "PopUnder18 and Weed Corr: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopUnder18, &drugData::getWeed);
    cout << endl;

    cout << "Cocaine and Weed Corr: " << endl;
    statTool::computeStatsDrugRegionData(&theStates, &fillStates, &drugData::getCocaine, &drugData::getWeed, &drugData::getCocaineCount, &drugData::getWeedCount);
    cout << endl;

    cout << "Alcohol and Pain Corr: " << endl;
    statTool::computeStatsDrugRegionData(&theStates, &fillStates, &drugData::getAlcohol, &drugData::getPain, &drugData::getAlcoholCount, &drugData::getPainCount);
    cout << endl;

    cout << "Alcohol and Weed Corr: " << endl;
    statTool::computeStatsDrugRegionData(&theStates, &fillStates, &drugData::getAlcohol, &drugData::getWeed, &drugData::getAlcoholCount, &drugData::getWeedCount);
    cout << endl;

    cout << "PopOver65 and Alcohol Corr: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopOver65, &drugData::getAlcohol);
    cout << endl;
    
    cout << "PopOver65 and Weed Corr: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopOver65, &drugData::getWeed);
    cout << endl;

    cout << "Poverty-level and Weed Corr: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getBelowPoverty, &drugData::getWeed);
    cout << endl;

    cout << "Poverty-level and Alcohol Corr: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getBelowPoverty, &drugData::getAlcohol);
    cout << endl;

    for(auto i: stateDrugMap){
        cout << *i.second << endl;
        cout << endl;
    }
        
    // for (it = stateMap.begin(); it != stateMap.end(); it++) {
    //     nums.push_back(it->second->getNumH());
    // }

    // int countyTotalPop = 0;

    // for (it = countyMap.begin(); it != countyMap.end(); it++) {
    //     nums.push_back(it->second->getBelowPoverty() / 100);
    //     countyTotalPop += it->second->getPop();
    // }

    // cout << "QUESTION 3" << endl;
    // //cout << stats::computePopMean(nums, countyTotalPop) << endl;
    // cout << stats::computeStdDevPop(nums, 0.15) << endl;


    // cout << "QUESTION 4" << endl;
    // cout << "state: overall hospital rating and population over 65: " << endl;
    // statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopOver65, &comboHospitalData::getOverallRate);
 
    // cout << "\n\n" << endl;

    // cout << "Counties: number of hospitals and population with BA or higher " << endl;
    // statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboHospitalData::getNumH);

    // cout << "\n\n" << endl;

    // cout << "Counties: population with BA or higher and population below poverty " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getBAup, &demogData::getBelowPoverty, &demogData::getBAupCount,
    //     &demogData::getBelowPovertyCount);

    // cout << "\n\n" << endl;

    // cout << "Counties: population with high school or higher and population below poverty" << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getHSup, &demogData::getBelowPoverty, &demogData::getHSupCount,
    //     &demogData::getBelowPovertyCount);

    // cout << "\n\n" << endl;

    // cout << "Counties: population younger than 18 and population younger than 5" << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder18, &demogData::getpopUnder5, &demogData::getpopUnder18Count,
    //     &demogData::getpopUnder5Count);

    // cout << "\n\n" << endl;

    // cout << "Counties: population younger than 18 and population over 65" << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder18, &demogData::getpopOver65, &demogData::getpopUnder18Count,
    //     &demogData::getpopOver65Count);

    

    return 0;
}



