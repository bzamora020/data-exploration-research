#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "visitorReport.h"


/*
  data aggregator and query for testing
*/
class dataAQ {
  public:
    dataAQ();

    /* function to aggregate demographic  data at a state level */
    void createStateDemogData(std::vector<shared_ptr<demogData>>& theData);

    /* function to aggregate hospital data at a state level */
    void createStateHospData(std::vector<shared_ptr<hospitalData>>& theData);

    /* function to aggregate hospital data at a county level */
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

  // State report using the visitor class depending on the poverty level
    void stateReport(double thresh);

    //state maps
    std::map<string, comboDemogData*> allStateDemogData;

    std::map<string, comboHospitalData*> allStateHospData;

    //map for county hospital data
    std::map<string, comboHospitalData*> allCountyHData;

    //helper to create aggregates from city -> county
    std::map<string, string> cityToCounty;



};
#endif
