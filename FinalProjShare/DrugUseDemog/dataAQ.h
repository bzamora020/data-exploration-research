#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "comboDemogData.h"
#include "comboHospitalData.h"


/*
  data aggregator and query for testing
*/
class dataAQ {
  public:
    dataAQ();

    /* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
    void createStateDemogData(std::vector<shared_ptr<demogData>>& theData);

    void createStateHospData(std::vector<shared_ptr<hospitalData>>& theData);

    void createCountyHospData(std::vector<shared_ptr<hospitalData>>& theHospitalData);

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

    void sortHospRatingHighLow(std::vector<comboHospitalData *>& hospHighToLow,  string regionType);
    void sortHospRatingLowHigh(std::vector<comboHospitalData  *>& hospLowToHigh,  string regionType);

    void sortHospRatingHighLowForState(std::vector<comboHospitalData *>& hospHighToLow, string state);
   
    void sortDemogPovLevelLowHigh(std::vector<demogData *>& incomeHighLow);
    void sortDemogPovLevelHighLow(std::vector<demogData *>& povLevelHighLow);
    
    friend std::ostream& operator<<(std::ostream &out, const dataAQ &allStateData);

    //not in parser because this is helper data
    void read_csvCityCounty(std::string filename);

    void createComboDemogVector(std::vector<demogData*>& vec);
    void createComboHospVector(std::vector<comboHospitalData *>& vec, string regionType, string name);

    //state maps
    std::map<string, comboDemogData*> allStateDemogData;

    std::map<string, comboHospitalData*> allStateHospData;

    //map for county hospital data
    std::map<string, comboHospitalData*> allCountyHData;

    //helper to create aggregates from city -> county
    std::map<string, string> cityToCounty;


    // reports
    void stateReport(double thresh);
};
#endif
