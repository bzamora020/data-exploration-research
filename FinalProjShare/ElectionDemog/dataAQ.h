#ifndef DATAAQ_H
#define DATAAQ_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "visitorReport.h"


using namespace std;
class dataAQ {
  public:
    dataAQ() {}
    void createStateDemogData(vector< shared_ptr<demogData> > theData);
    void createStateHospData(std::vector<shared_ptr<hospitalData> > theData);
    void createCountyHospData(std::vector<shared_ptr<hospitalData>>& theHospitalData);

    void sortDemogPovLevelLowHigh(vector<demogData*>& povLevelLowHigh);
    void sortDemogPovLevelHighLow(vector<demogData*>& povLevelHighLow);

    void sortHospRatingHighLow(vector<comboHospitalData*>& hospHighToLow, string regionType);
    void sortHospRatingLowHigh(vector<comboHospitalData*>& hospLowToHigh, string regionType);
    void sortHospRatingHighLowForState(vector<comboHospitalData*>& hospHighToLow, string state);

    void stateReport(double thresh);

    void read_csvCityCounty(string filename);

    friend ostream& operator<<(ostream& out, const dataAQ& allStateData);

    map<string, shared_ptr<comboDemogData>> allStateDemogData;
    map<string, shared_ptr<comboHospitalData>> allStateHospData;

    //map, pointing county name key to all the county
    map<string, shared_ptr<comboHospitalData>> allCountyHData;

    //helper to create aggregates from city -> county
    map<string, string> cityToCounty;
 };
 #endif