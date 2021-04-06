#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "hospitalData.h"
#include "cityHospitalData.h"
#include "demogData.h"
#include "countyDemogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "visitor.h"
#include "parse.h"
#include <memory>
#include <fstream>

using namespace std;

class visitorCombineCounty : public Visitor {

public:
    visitorCombineCounty(string filename){ 
        std::ifstream myFile(filename);

        // Make sure the file is open
        if(!myFile.is_open()) {
            throw std::runtime_error("Could not open file");
        }

        if(myFile.good()) {
            consumeColumnNames(myFile);

            // Helper vars
            std::string line, state, junk;

            // Now read data, line by line and enter into the map
            while(std::getline(myFile, line)) {

                std::stringstream ss(line);

                string city = getFieldNQ(ss);
                state = getFieldNQ(ss);
                junk = getFieldNQ(ss);
                string county = getFieldNQ(ss);

                string cityKey = city+state;

                cityToCounty[cityKey] = county;

            //cout << "line: " << line << endl;
            //cout << "pair (city, county): " << city << ", " << county << " state " << junk << endl;
            }

            // Close file
            myFile.close();
        }
    }
    virtual void visit(shared_ptr<demogData> e){
        shared_ptr<demogData> comboData = static_pointer_cast<demogData>(e);
        shared_ptr<countyDemogData> countyData = static_pointer_cast<countyDemogData>(comboData);
        string countyName = countyData->getCountyName();
        if (countyName.find(" County") != string::npos){
            countyName.erase(countyName.find(" County"), 7);
        }
        countyName += countyData->getState();
        if(allCountyDemogData.count(countyName) < 1) {
            allCountyDemogData[countyName] = new comboDemogData(countyName);
        }
        allCountyDemogData[countyName]->addCountytoState(comboData);
    }

    virtual void visit(shared_ptr<hospitalData> e){
        shared_ptr<hospitalData> s_ptr = static_pointer_cast<hospitalData>(e);
        shared_ptr<cityHospitalData> cityData = static_pointer_cast<cityHospitalData>(e);
        string stateName = s_ptr->getState();
        if(cityToCounty[cityData->getCity() + stateName] != ""){
            string countyName = cityToCounty[cityData->getCity() + stateName] + stateName;
        
            if(allCountyHData.count(countyName) < 1) {
                allCountyHData[countyName] = new comboHospitalData(stateName, countyName, "county");
            }
            allCountyHData[countyName]->addCountytoState(s_ptr);
        }
    }

    map<string, comboDemogData*> countyDmap(){
        return allCountyDemogData;
    }

    map<string, comboHospitalData*> countyHmap(){
        return allCountyHData;
    }

    comboDemogData* countyDmapEntry(string countyN){
        return allCountyDemogData[countyN];
    }

    comboHospitalData* countyHmapEntry(string countyN){
        return allCountyHData[countyN];
    }

    void printAllCounties(){
        for (auto entry: allCountyDemogData){
            cout << "county: " << entry.first << endl;
            cout << "popOver65: " << entry.second->getpopOver65() << endl;
        }
        // for (auto entry: allCountyHData){
        //     cout << "county: "<< entry.first << endl;
        //     cout << "overall Rate: " << entry.second->getOverallRate() << endl;
        // }
    }

private:
    std::map<string, comboHospitalData*> allCountyHData;
    std::map<string, comboDemogData*> allCountyDemogData;

    std::map<string, string> cityToCounty;
};

#endif
