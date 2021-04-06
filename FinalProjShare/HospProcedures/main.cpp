
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

#include "stats.h"
#include "statTool.h"
#include "statGatherer.h"

#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"

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
    cout << "STATE" << endl;
    statTool::createStateData(pileOfData, theStates);
    //theStates.printAllStates();
    cout << "COUNTY" << endl;
    //create a visitor to combine the county data (need aux map city-> county)
    visitorCombineCounty theCounties("simple_uscities.csv");
    statTool::createCountyData(pileOfData, theCounties);
    //theCounties.printAllCounties();

    //create statGathers to help make the data one for states one for counties
    stateGather fillStates;
    countyGather fillCounties;

    cout << "----COUNTY----" << endl;
    //COUNTY
    cout << "--County data (x = popOver65) and (y = Heat Attack Quality): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboHospitalData::getHeart_attack_q_Num);
    cout << endl;

    cout << "--County data (x = BAup) and (y = Heat Attack Quality): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboHospitalData::getHeart_attack_q_Num);
    cout << endl;

    cout << "--County data (x = BAup) and (y = Heart Attack Value): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboHospitalData::getHeart_attack_v_Num);
    cout << endl;

    cout << "--County data (x = belowPov) and (y = Heart Attack Value): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboHospitalData::getHeart_attack_v_Num);
    cout << endl;

    cout << "--County data (x = popOver65) and (y = Heart Failure Quality): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboHospitalData::getHeart_failure_q_Num);
    cout << endl;

    cout << "--County data (x = BAup) and (y = Heart Failure Quality): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboHospitalData::getHeart_failure_q_Num);
    cout << endl;

    cout << "--County data (x = getBAup) and (y = Heart Failure Value): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboHospitalData::getHeart_failure_v_Num);
    cout << endl;

    cout << "--County data (x = popOver65) and (y = Pneumonia Quality): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboHospitalData::getPneumonia_q_Num);
    cout << endl;

    cout << "--County data (x = BAup) and (y = Pneumonia Quality): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboHospitalData::getPneumonia_q_Num);
    cout << endl;

    cout << "--County data (x = belowPov) and (y = Pneumonia Quality): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboHospitalData::getPneumonia_q_Num);
    cout << endl;

    cout << "--County data (x = popUnder18) and (y = Pneumonia Quality): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopUnder18, &comboHospitalData::getPneumonia_q_Num);
    cout << endl;


    cout << "----STATE----" << endl;
    //STATE
    cout << "--State data (x = BAup) and (y = Heart Attack Quality): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillCounties, &demogData::getBAup, &comboHospitalData::getHeart_attack_q_Num);
    cout << endl;

    cout << "--State data (x = BAup) and (y = Heart Attack Value): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillCounties, &demogData::getBAup, &comboHospitalData::getHeart_attack_v_Num);
    cout << endl;

    cout << "--State data (x = popOver65) and (y = Heart Attack Quality): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillCounties, &demogData::getpopOver65, &comboHospitalData::getHeart_attack_q_Num);
    cout << endl;

    cout << "--State data (x = popOver65) and (y = Heart Failure Quality): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillCounties, &demogData::getpopOver65, &comboHospitalData::getHeart_failure_q_Num);
    cout << endl;

    cout << "--State data (x = BAup) and (y = Heart Failure Value): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillCounties, &demogData::getBAup, &comboHospitalData::getHeart_failure_v_Num);
    cout << endl;

    cout << "--State data (x = popOver65) and (y = Pneumonia Quality): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillCounties, &demogData::getpopOver65, &comboHospitalData::getPneumonia_q_Num);
    cout << endl;

    cout << "--State data (x = belowPov) and (y = Pneumonia Quality): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillCounties, &demogData::getBelowPoverty, &comboHospitalData::getPneumonia_q_Num);
    cout << endl;

    cout << "--State data (x = popUnder5) and (y = Pneumonia Quality): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillCounties, &demogData::getpopUnder5, &comboHospitalData::getPneumonia_q_Num);
    cout << endl;




    return 0;
}
