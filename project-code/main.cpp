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
    read_csv(pileOfData, "county_demographics_cleaned.csv", DEMOG);
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

    // cleaning, removed the end of some of the county names, like Parish, city, stuff like dat, so there might be conflicts with something CountyNCA and CountyNCA


    cout << "***** OUR COMPUTATIONS *****" << endl;
    
    cout << endl;

/*     cout << "Shooting compared with shooting: " << endl;

    statTool::computeStatsShootingRegionData(&theCounties, &fillCounties, &shootingData::getPerAfricanAme, &shootingData::getPerMI);


    statTool::computeStatsShootingRegionData(&theCounties, &fillCounties, &shootingData::getPerWhite, &shootingData::getPerMI);

    statTool::computeStatsShootingRegionData(&theCounties, &fillCounties, &shootingData::getPerWhite, &shootingData::getPerMen);
 */


    //Printing out the number of shooting cases per State
 /* or(auto entry : theStates.stateSmap())
 {
     cout << "Number of cases: " << entry.second->getNumCases() << " State: " << entry.second->getState() << endl;
    
 } */
    
    // int counter = 0;
    // for (auto entry : theCounties.countySmap())
    // {
    //     cout << "County name? " << entry.second->getRegionType() << " State: " << entry.second->getState() << " Cases: " << entry.second->getNumCases() << endl;
    //     counter++;
    // }

    // cout << "Number of counties: " << counter << endl;
/*     cout << "*** Low Income Levels ***: " << "\n" << endl;

    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Hispanic" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerHispanics);
    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as White" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerWhite);
    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as African American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerAfricanAme);
    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Asian" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerAsians);

    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Natice American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerNativeAme); */

    cout << "*** Percentage of hispanics compared to percentage of cases of body cams on" << "\n" << endl;

    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getHispanicPerc, &shootingData::getPerBodyCamOn);
  
    cout << "*** Below Poverty compared to percentage of cases of fatal police shootings" << "\n" << endl;
    statTool::computeStatsMixRegionData3(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboShootingData::getPerNumberCases);

    cout << "*** cases of fatal police shootings compared to percentage of Below Poverty " << "\n" << endl;
    statTool::computeStatsMixRegionData3(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboShootingData::getPerHispanics);


    // cout << "Stats per County" << endl;


    /* cout << "Stats per County" << endl; */

    /* theCounties.mostShootingsCounty();
        cout << endl;
    // theCounties.leastShootingsCounty();

    theCounties.leastHSGraduates();
        cout << endl;

    theCounties.highestPovLevels();
        cout << endl;



    // cout << "TESTSSSSSS: \n";

    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder5, &demogData::getBAup,
                                          &demogData::getpopUnder5Count, &demogData::getBAupCount);
 */
    return 0;
}

