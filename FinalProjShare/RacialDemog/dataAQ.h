#ifndef DATAAQ_H
#define DATAAQ_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include "comboHospitalData.h"
#include "comboDemogData.h"
#include "placeData.h"
#include "cityHospitalData.h"
#include "hospitalData.h"
#include "demogData.h"
#include "parse.h"
#include "visitorReport.h"
#include <algorithm>
#include <sstream>

/*
  data aggregator and query for testing
*/
class dataAQ {
  public:
    dataAQ();

    /* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
    void createStateDemogData(std::vector<shared_ptr<demogData> > theData);

    void createStateHospData(std::vector<shared_ptr<hospitalData> > theData);

    void createCountyHospData(std::vector<shared_ptr<hospitalData> > theData);
    //return the name of the state with the largest population under age 5
    string youngestPop();
    //return the name of the state with the largest population under age 18
    string teenPop();
    //return the name of the state with the largest population over age 65
    string wisePop();
    //return the name of the state with the largest population who did not finish high school
    string underServeHS();
    //return the name of the state with the largest population who completed college
    string collegeGrads();

    string getMinTeenPop();


    string LowHospRating();
    string HighHospRating();
    string HighMortHospRating();
    string HighReadmitHospRating();

    void sortHospRatingHighLow(std::vector<comboHospitalData *>& hospHighToLow, string regionType);
    void sortHospRatingLowHigh(std::vector<comboHospitalData *>& hospLowToHigh, string regionType);
    
    void sortDemogPovLevelLowHigh(std::vector<demogData*>& incomeHighLow);
    void sortDemogPovLevelHighLow(std::vector<demogData*>& povLevelHighLow);

    void sortHospRatingHighLowForState(std::vector<comboHospitalData*>& hospHighToLow, string state);
    
    friend std::ostream& operator<<(std::ostream &out, const dataAQ &allStateData);


    void read_csvCityCounty(std::string filename);

    void stateReport(double thresh);

    //For lab02 solution... 
    std::map<string, comboDemogData*> allStateDemogData;

    //For lab03 use a similar structure....
    std::map<string, comboHospitalData*> allStateHospData;
    //map for county hospital data
    std::map<string, comboHospitalData*> allCountyHData;

    //helper to create aggregates from city -> county
    std::map<string, string> cityToCounty;

};
#endif
