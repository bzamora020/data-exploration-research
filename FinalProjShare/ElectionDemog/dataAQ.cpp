#include "dataAQ.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#define DEBUG false

using namespace std;
/*
Questions:
What's the deal with region? Why do we need it? Is there a special input for region/county in parse?
What is up with countyDemogData and cityHospitalData?
How are we supposed to store our data in the maps? By region or state? How do we store the data in comboHospData?
*/
//function to aggregate the data - this CAN and SHOULD vary per student - depends on how they map
void dataAQ::createStateDemogData(vector< shared_ptr<demogData> > theData) {
    string state = "";
    for (shared_ptr<demogData> county : theData) {
        state = county->getState();
        //if true, key is not found
        if (allStateDemogData.count(state) == 0) {
            allStateDemogData.insert(make_pair(state, make_shared<comboDemogData>(state, state))); //state and region names are the same
        }
        allStateDemogData.at(state)->addDemogtoRegion(county);
    }
}

void dataAQ::createStateHospData(std::vector<shared_ptr<hospitalData> > theData) {
    string state = "";
    for (shared_ptr<hospitalData> hosp : theData) {
        state = hosp->getState();
        //if true, key is not found
        if (allStateHospData.count(state) == 0) {
            allStateHospData.insert(make_pair(state, make_shared<comboHospitalData>("state", state))); //state and region names are the same
        }
        allStateHospData.at(state)->addHospitaltoRegion(hosp);
    }
}

void dataAQ::createCountyHospData(std::vector<shared_ptr<hospitalData>>& theHospitalData) {
    string cityKey = "";
    string county = "";
    string state = "";
    for (shared_ptr<hospitalData> hosp : theHospitalData) {
        state = hosp->getState();
        cityKey = hosp->getCity() + state;
        county = cityToCounty[cityKey];
        county += " County"; //added cause the tester tests for the exytra "County"
        //if true, key is not found
        if (allCountyHData.count(county) == 0) {
            allCountyHData.insert(make_pair(county, make_shared<comboHospitalData>(county, state)));
        }
        allCountyHData.at(county)->addHospitaltoRegion(hosp);
    }
}

void dataAQ::sortHospRatingHighLow(vector<comboHospitalData*>& hospHighToLow, string regionType) {
    //adding elements from the hashmap to the vector
    for (map<string, shared_ptr<comboHospitalData>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); i++) {
        hospHighToLow.push_back(&(*i->second));
    }
    sort(hospHighToLow.begin(), hospHighToLow.end(), &hospitalData::compareOV);
    //reverse
    reverse(hospHighToLow.begin(), hospHighToLow.end());
}

void dataAQ::sortHospRatingLowHigh(vector<comboHospitalData*>& hospLowToHigh, string regionType) {
    for (map<string, shared_ptr<comboHospitalData>>::iterator i = allStateHospData.begin(); i != allStateHospData.end(); i++) {
        hospLowToHigh.push_back(&(*i->second));
    }
    sort(hospLowToHigh.begin(), hospLowToHigh.end(), &hospitalData::compareOV);
}

void dataAQ::sortDemogPovLevelLowHigh(vector<demogData*>& povLevelLowHigh) {
    for (map<string, shared_ptr<comboDemogData>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++) {
        povLevelLowHigh.push_back(&(*i->second));
    }
    sort(povLevelLowHigh.begin(), povLevelLowHigh.end(), &demogData::compareP);
    reverse(povLevelLowHigh.begin(), povLevelLowHigh.end());
}

void dataAQ::sortDemogPovLevelHighLow(vector<demogData*>& povLevelHighLow) {
    for (map<string, shared_ptr<comboDemogData>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++) {
        povLevelHighLow.push_back(&(*i->second));
    }
    sort(povLevelHighLow.begin(), povLevelHighLow.end(), &demogData::compareP);
}

//sorting counties
void dataAQ::sortHospRatingHighLowForState(vector<comboHospitalData*>& hospHighToLow, string state) {
    for (map<string, shared_ptr<comboHospitalData>>::iterator i = allCountyHData.begin(); i != allCountyHData.end(); i++) {
        if(i->second->getState().compare(state) == 0)
            hospHighToLow.push_back(&(*i->second));
    }
    sort(hospHighToLow.begin(), hospHighToLow.end(), &hospitalData::compareOV);
    reverse(hospHighToLow.begin(), hospHighToLow.end());
}

//prints every state with a poverty level above the threshold
void dataAQ::stateReport(double thresh) {
    visitorReport VR;
    int total = 0;
    for (map<string, shared_ptr<comboDemogData>>::iterator i = allStateDemogData.begin(); i != allStateDemogData.end(); i++) {
        cout << endl;
        if (i->second->getBelowPoverty() / i->second->getPop() > thresh / 100) {
            cout << "Special report demog Data : \n";
            allStateDemogData[i->first]->accept(VR);
            cout << "Special report hospital data : \n";
            allStateHospData[i->first]->accept(VR);
            total++;
        }
    }
    cout << "Generated a report for a total of : " << total << "\n";
//Expected: \nSpecial report demog Data : \nDemographics Info(State) : MS\nEducation info : \n(% Bachelor degree or more) : 20.43\n(% high school or more) : 81.62\n % below poverty : 22.63\nSpecial report hospital data : \nHospital Info : MS\nOverall rating(out of 5) : 2.57\nGenerated a report for a total of : 1\n
//aActual : \nSpecial report demog Data : \nDemographics Info(State) : MS\nEducation info : \n(% bachelor degree or more) : 20.43\n(% high school or more) : 81.62\n % below poverty : 22.63\nSpecial report hospital data : \nHospital Info : MS\nOverall rating(out of 5) : 2.57\nGenerated a report for a total of : 1'
//Expected: \nSpecial report demog Data : \nDemographics Info(State) : MS\nEducation info : \n(% Bachelor degree or more) : 20.43\n(% high school or more) : 81.62\n % below poverty : 22.63\nSpecial report hospital data : \nHospital Info : MS\nOverall rating(out of 5) : 2.57\nSpecial report demog Data : \nDemographics Info(State) : NM\nEducation info : \n(% Bachelor degree or more) : 25.58\n(% high school or more) : 83.39\n % below poverty : 20.40\nSpecial report hospital data : \nHospital Info : NM\nOverall rating(out of 5) : 2.73\nGenerated a report for a total of : 2\n
//Actusal : \nSpecial report demog Data : \nDemographics Info(State) : MS\nEducation info : \n(% bachelor degree or more) : 20.43\n(% high school or more) : 81.62\n % below poverty : 22.63\nSpecial report hospital data : \nHospital Info : MS\nOverall rating(out of 5) : 2.57\nSpecial report demog Data : \nDemographics Info(State) : NM\nEducation info : \n(% bachelor degree or more) : 25.58\n(% high school or more) : 83.39\n % below poverty : 20.40\nSpecial report hospital data : \nHospital Info : NM\nOverall rating(out of 5) : 2.73\nGenerated a report for a total of : 2
}
ostream& operator<<(ostream &out, const dataAQ &AQ) {
    out << "bruh";
    return out;
}

void dataAQ::read_csvCityCounty(string filename) {
    // Create an input filestream
    ifstream myFile(filename);
    // Make sure the file is open
    if (!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if (myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        string line, state, junk;

        // Now read data, line by line and enter into the map
        while (getline(myFile, line)) {

            stringstream ss(line);

            string city = getFieldNQ(ss);
            state = getFieldNQ(ss);
            junk = getFieldNQ(ss);
            string county = getFieldNQ(ss);

            string cityKey = city + state;

            cityToCounty[cityKey] = county;

            //cout << "line: " << line << endl;
            //cout << "pair (city, county): " << city << ", " << county << " state " << junk << endl;
        }

        // Close file
        myFile.close();
    }
}
 