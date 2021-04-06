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
    
    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG); 

    //create a visitor to combine the county data (need aux map city-> county)
    visitorCombineCounty theCounties("simple_uscities.csv");
    statTool::createCountyData(pileOfData, theCounties);

    //create statGathers to help make the data- one for counties
    countyGather fillCounties;
    
    cout << "** County data BA or Higher and Housing Median Value: " << endl;
    statTool::computeStatsDemogHouseRegionData(&theCounties, &fillCounties, 
        &demogData::getBAup, &housingData::getMedianVal);

    cout << "** County data Poverty Level and Home Ownership: " << endl;
    statTool::computeStatsDemogHouseRegionData(&theCounties, &fillCounties, 
        &demogData::getBelowPoverty, &housingData::getHomeOwnership);


    return 0;
}

