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

/*     theCounties.sortRacialDemogDemogCounties();
    theCounties.mostShootingsCounty(); */
    theCounties.mostShootingsCounty();
/*     theCounties.mostShootingsCountyCA();
    theCounties.mostShootingsCountyTX();
    theCounties.mostShootingsCountyAZ();
    theCounties.mostShootingsCountyHI();
    theCounties.mostShootingsCountyAK();
    theCounties.mostShootingsCountyDC();
    theStates.mostShootingsState(); */
    // theCounties.mostShootingsCounty();

 /*     cout << "Stats per County" << endl;

    theCounties.mostShootingsCounty();

    auto demogCA = theStates.stateDmapEntry("CA");
    auto demogTX = theStates.stateDmapEntry("TX");
    auto demogAZ = theStates.stateDmapEntry("AZ");

    cout << "Num Shootings\n" << theStates.stateSmapEntry("CA")->getNumCases() << endl;
    cout << theStates.stateSmapEntry("TX")->getNumCases() << endl;
    cout << theStates.stateSmapEntry("AZ")->getNumCases() << endl;

    cout << "Racial Demog: Black Perc\n";
    cout << demogCA->getBlackPerc() << "%" << endl;
    cout << demogTX->getBlackPerc() << "%" << endl;
    cout << demogAZ->getBlackPerc() << "%" << endl;
    
    cout << "Racial Demog: White Perc\n";
    cout << demogCA->getWhitePerc() << "%" << endl;
    cout << demogTX->getWhitePerc() << "%" << endl;
    cout << demogAZ->getWhitePerc() << "%" << endl;

    cout << "Racial Demog: Hispanic Perc\n";
    cout << demogCA->getHispanicPerc() << "%" << endl;
    cout << demogTX->getHispanicPerc() << "%" << endl;
    cout << demogAZ->getHispanicPerc() << "%" << endl; */





    // statTool::computeStatsMixRegionData3(&theCounties, &fillCounties, &demogData::getWhitePerc, &comboShootingData::getPerArmedUnknown);

    //cout << endl;

    /*     cout << "Shooting compared with shooting: " << endl;

    statTool::computeStatsShootingRegionData(&theCounties, &fillCounties, &shootingData::getPerAfricanAme, &shootingData::getPerMI);


    statTool::computeStatsShootingRegionData(&theCounties, &fillCounties, &shootingData::getPerWhite, &shootingData::getPerMI);

    statTool::computeStatsShootingRegionData(&theCounties, &fillCounties, &shootingData::getPerWhite, &shootingData::getPerMen);
 */

    //Printing out the number of shooting cases per State

/*     int whiteTot = 0;
    int hispTot = 0;
    int blackTot = 0;
    int asianTot = 0;
    int nativeTot = 0;
    int otherTot = 0;
    int tot = 0;

    for (auto entry : theCounties.countySmap())
    {
        if (entry.first.find("Unknown") != std::string::npos)
        {
            auto temp = entry.second->getRaceData();
            cout << entry.first << "\nNumber of cases: " << entry.second->getNumCases()
                 << "\nPercentage that were White: " << entry.second->getPerWhite()
                 << "\nPercentage that were Hispanic: " << entry.second->getPerHispanics()
                 << "\nPercentage that were Black: " << entry.second->getPerAfricanAme()
                 << "\nPercentage that were Native American: " << entry.second->getPerNativeAme()
                 << "\nPercentage that were Asian: " << entry.second->getPerAsians()
                 << "\nPercentage that were Other: " << entry.second->getPerOther()
                 << "\nPercentage that were Body Cam off: " << entry.second->getPerBodyCamOff()
                 << "\nPercentage that were Fleeing: " << entry.second->getPerFleeing()
                 << "\nPercentage that were reported with a mental illness: " << entry.second->getPerMentalI()
                 << endl;
            whiteTot += temp.getNumWhite();
            hispTot += temp.getNumHispanics();
            blackTot += temp.getNumAsians();
            asianTot += temp.getNumAsians();
            nativeTot += temp.getNumNative();
            otherTot += temp.getnumOther();
        }
    }
    tot = whiteTot + hispTot + blackTot + asianTot + nativeTot + otherTot;
    cout << "Totals per category: " << endl;
    cout << "Whites: " << whiteTot << "\nHispanics: " << hispTot << "\nBlacks: " << blackTot << "\nAsians: " << asianTot << "\nNatives: " << nativeTot << "\nOthers: " << otherTot << endl;
    cout << "total: " << tot << endl;
    cout << "white per: " << (whiteTot / (double)tot) << endl;
    int counter = 0;
    for (auto entry : theCounties.countySmap())
    {
        cout << "County name? " << entry.second->getRegionType() << " State: " << entry.second->getState() << " Cases: " << entry.second->getNumCases() << endl;
        counter++;
    }

    // int whiteTot = 0;
    // int hispTot = 0;
    // int blackTot = 0;
    // int asianTot = 0;
    // int nativeTot = 0;
    // int otherTot = 0;
    // int tot = 0;

    // for (auto entry : theCounties.countySmap())
    // {
    //     if (entry.first.find("Unknown") != std::string::npos)
    //     {
    //         auto temp = entry.second->getRaceData();
    //         cout << entry.first << "\nNumber of cases: " << entry.second->getNumCases()
    //              << "\nPercentage that were White: " << entry.second->getPerWhite()
    //              << "\nPercentage that were Hispanic: " << entry.second->getPerHispanics()
    //              << "\nPercentage that were Black: " << entry.second->getPerAfricanAme()
    //              << "\nPercentage that were Native American: " << entry.second->getPerNativeAme()
    //              << "\nPercentage that were Asian: " << entry.second->getPerAsians()
    //              << "\nPercentage that were Other: " << entry.second->getPerOther()
    //              << "\nPercentage that were Body Cam off: " << entry.second->getPerBodyCamOff()
    //              << "\nPercentage that were Fleeing: " << entry.second->getPerFleeing()
    //              << "\nPercentage that were reported with a mental illness: " << entry.second->getPerMentalI()
    //              << endl;
    //         whiteTot += temp.getNumWhite();
    //         hispTot += temp.getNumHispanics();
    //         blackTot += temp.getNumAsians();
    //         asianTot += temp.getNumAsians();
    //         nativeTot += temp.getNumNative();
    //         otherTot += temp.getnumOther();
    //     }
    // }
    // tot = whiteTot + hispTot + blackTot + asianTot + nativeTot + otherTot;
    // cout << "Totals per category: " << endl;
    // cout << "Whites: " << whiteTot << "\nHispanics: " << hispTot << "\nBlacks: " << blackTot << "\nAsians: " << asianTot << "\nNatives: " << nativeTot << "\nOthers: " << otherTot << endl;
    // cout << "total: " << tot << endl;
    // cout << "white per: " << (whiteTot / (double)tot) << endl;
    // int counter = 0;
    // for (auto entry : theCounties.countySmap())
    // {
    //     cout << "County name? " << entry.second->getRegionType() << " State: " << entry.second->getState() << " Cases: " << entry.second->getNumCases() << endl;
    //     counter++;
    // }


    cout << "Number of counties: " << counter << endl;
        cout << "*** Low Income Levels ***: " << "\n" << endl;

    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Hispanic" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerHispanics);
    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as White" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerWhite);
    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as African American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerAfricanAme);
    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Asian" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerAsians);

    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Natice American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerNativeAme);

        cout << "*** HS Levels ***: " << "\n" << endl;

    cout << "*** Percentage HS degree compared to percentage of fatal police shootings where the victim was classified as Hispanic" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getHSup, &shootingData::getPerHispanics);
    cout << "*** Percentage HS degree compared to percentage of fatal police shootings where the victim was classified as White" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getHSup, &shootingData::getPerWhite);
    cout << "*** Percentage HS degree compared to percentage of fatal police shootings where the victim was classified as African American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getHSup, &shootingData::getPerAfricanAme);
    cout << "*** Percentage HS degree compared to percentage of fatal police shootings where the victim was classified as Asian" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getHSup, &shootingData::getPerAsians);

    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Natice American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getHSup, &shootingData::getPerNativeAme); 

    cout << "*** Age Levels ***: " << "\n" << endl;

    cout << "*** Pop Under 5 compared to percentage of fatal police shootings where the victim was classified as Hispanic" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder5, &shootingData::getPerHispanics);
    cout << "***  Pop Under 5  compared to percentage of fatal police shootings where the victim was classified as White" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder5, &shootingData::getPerWhite);
    cout << "***  Pop Under 5 compared to percentage of fatal police shootings where the victim was classified as African American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder5, &shootingData::getPerAfricanAme);
    cout << "***  Pop Under 5 compared to percentage of fatal police shootings where the victim was classified as Asian" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder5, &shootingData::getPerAsians);
    cout << "***  Pop Under 5 compared to percentage of fatal police shootings where the victim was classified as Natice American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder5, &shootingData::getPerNativeAme); 

    cout << "*** Pop Under 18 compared to percentage of fatal police shootings where the victim was classified as Hispanic" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder18, &shootingData::getPerHispanics);
    cout << "***  Pop Under 18 compared to percentage of fatal police shootings where the victim was classified as White" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder18, &shootingData::getPerWhite);
    cout << "***  Pop Under 18 compared to percentage of fatal police shootings where the victim was classified as African American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder18, &shootingData::getPerAfricanAme);
    cout << "***  Pop Under 18 compared to percentage of fatal police shootings where the victim was classified as Asian" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder18, &shootingData::getPerAsians);
    cout << "***  Pop Under 18 compared to percentage of fatal police shootings where the victim was classified as Natice American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopUnder18, &shootingData::getPerNativeAme); 

    cout << "*** Pop Over 65 compared to percentage of fatal police shootings where the victim was classified as Hispanic" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopOver65, &shootingData::getPerHispanics);
    cout << "***  Pop Over 65 compared to percentage of fatal police shootings where the victim was classified as White" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopOver65, &shootingData::getPerWhite);
    cout << "***  Pop Over 65 compared to percentage of fatal police shootings where the victim was classified as African American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopOver65, &shootingData::getPerAfricanAme);
    cout << "***  Pop Over 65 compared to percentage of fatal police shootings where the victim was classified as Asian" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopOver65, &shootingData::getPerAsians);
    cout << "***  Pop Over 65 compared to percentage of fatal police shootings where the victim was classified as Natice American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getpopOver65, &shootingData::getPerNativeAme); 

    cout << "*** Low Income Levels ***: " << "\n" << endl;

    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Hispanic" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerHispanics);
    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as White" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerWhite);
    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as African American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerAfricanAme);
    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Asian" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerAsians);

    cout << "*** Below Poverty compared to percentage of fatal police shootings where the victim was classified as Natice American" << "\n" << endl;
    statTool::computeStatsMixRegionData2(&theCounties, &fillCounties, &demogData::getBelowPoverty, &shootingData::getPerNativeAme); 

    cout << endl;

    cout << "*** cases of fatal police shootings compared to percentage of Below Poverty " << "\n" << endl;
    statTool::computeStatsMixRegionData3(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboShootingData::getPerHispanics);




    cout << "Stats per County" << endl;

    theCounties.mostShootingsCounty();
    cout << theCounties.countySmapEntry("Los AngelesCA")->getPerWhite() << endl;

    cout << theCounties.countySmapEntry("MaricopaAZ")->getPerWhite() << endl;
    
    cout << theCounties.countySmapEntry("HarrisTX")->getPerWhite() << endl;

        cout << endl;
    theCounties.leastShootingsCounty();

    theCounties.leastHSGraduates();
        cout << endl;

    theCounties.highestPovLevels();
        cout << endl;

    cout << "TESTSSSSSS: \n";

   statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder5, &demogData::getBAup,
                                          &demogData::getpopUnder5Count, &demogData::getBAupCount);  */



    return 0;
}
