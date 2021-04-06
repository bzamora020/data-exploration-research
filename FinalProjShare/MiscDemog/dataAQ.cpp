/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"
#include "visitor.h"
#include "visitorReport.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#define DEBUG false

dataAQ::dataAQ() {}

/* function to aggregate demographic  data at a state level */
void dataAQ::createStateDemogData(std::vector<shared_ptr<demogData>>& theData) {
	    //process the vector in our county data aggregate 
    for (const auto &obj : theData) {
        string stateName = obj->getState();
        //if first state entry, create it
        if (allStateDemogData.count(stateName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allStateDemogData[stateName] = new comboDemogData("state", stateName);
        }
        //either way now add this county info 
        //this keeps a running total
        allStateDemogData[stateName]->addDemogtoRegion(obj);
    }
}

/* function to aggregate hospital data at a state level */
void dataAQ::createStateHospData(std::vector<shared_ptr<hospitalData>>& theData) {
      //process the vector in our county data aggregate 
    for (const auto &obj : theData) {
        string stateName = obj->getState();
        //if first state entry, create it
        if (allStateHospData.count(stateName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allStateHospData[stateName] = new comboHospitalData("state", stateName);
        }
        //either way now add this county info 
        //this keeps a running total
        allStateHospData[stateName]->addHospitaltoRegion(obj);
    }
}

/* function to aggregate hospital data at a county level */
void dataAQ::createCountyHospData(std::vector<shared_ptr<hospitalData>>& theHospitalData) {
  //some error logging for dev
  int cityError = 0;
  int loggedCity = 0;
  int numCountyH = 0;
  /* make county hospital data */
  for (const auto &obj : theHospitalData) {
        std::shared_ptr<cityHospitalData > hInfo = std::static_pointer_cast<cityHospitalData >(obj);
        if(hInfo) { 
            string city = hInfo->getCity();
            //city names can be redundent
            string cityKey = city+hInfo->getState();
            string county = "";
            string countyKey= "";
            //figure out the county
            if (cityToCounty.count(cityKey) >= 1) {
              county = cityToCounty[cityKey];
            } else {
                county = "unknown " + hInfo->getState();
                if (DEBUG ) {
                  cout << "hospital with unknown city: ";// << city << ", " << hInfo->getState() << endl;
                  cout << "citykey: " << cityKey <<endl;
                }
                cityError++;
            }
            countyKey = county+hInfo->getState();
            //if first county entry, create it
            if (allCountyHData.count(countyKey) < 1) {
                //cout << "Making a new county entry (hospital): " << countyKey << endl;
                //make the new data
                allCountyHData[countyKey] = new comboHospitalData(county +" County", hInfo->getState());
                numCountyH++;
            } 
            //either way now add this city hospital to the right county
            comboHospitalData* chInfo = allCountyHData[countyKey];
            if(chInfo) { 
                chInfo->addHospitaltoRegion(hInfo);
                loggedCity++;
            } else {
                cout << "Error should not happen - allCounty data map fail" << endl;
            }
        } else {
            cout << "Error should not happen - hospital dynamic cast fail" << endl;
        } 
  }  
  //DEBUG for figuring out city->county map weakness
  //cout << "Num unfound: " << cityError << " numfound " << numCountyH << endl; 
}



bool compareHospRating(comboHospitalData * left, comboHospitalData * right) {
        if (left->getOverallRate() == right->getOverallRate()) {
          return left->getRegion() < right->getRegion();
        }
        return left->getOverallRate() > right->getOverallRate();
}

bool compareHospRatingInv(comboHospitalData * left, comboHospitalData* right) {
        if (left->getOverallRate() == right->getOverallRate()) {
          return left->getRegion() < right->getRegion();
        }
        return left->getOverallRate() < right->getOverallRate();
}


/* kind of redudant but we are playing with these ideas */
void dataAQ::sortHospRatingLowHigh(std::vector<comboHospitalData *>& hospLowToHigh, 
  string regionType) {

  if (regionType.compare("state")==0) {
    for (auto entry : allStateHospData){
      hospLowToHigh.push_back((comboHospitalData *)entry.second);
    }
  } else {
    for (auto entry : allCountyHData){
      hospLowToHigh.push_back((comboHospitalData *)entry.second);
    }
  }
  sort(hospLowToHigh.begin(), hospLowToHigh.end(), compareHospRatingInv);
}


void dataAQ::sortHospRatingHighLow(std::vector<comboHospitalData *>& hospHighToLow, 
  string regionType) {

  if (regionType.compare("state")==0) {
    for (auto entry : allStateHospData){
      hospHighToLow.push_back((comboHospitalData *)entry.second);
    }
  } else {
    for (auto entry : allCountyHData){
      hospHighToLow.push_back((comboHospitalData *)entry.second);
    }
  }
  sort(hospHighToLow.begin(), hospHighToLow.end(), compareHospRating);
}


/* getting  a bit excessive with the number of these... */
void dataAQ::sortHospRatingHighLowForState(std::vector<comboHospitalData *>& hospHighToLow, string state) {

  for (auto entry : allCountyHData){
    string curState = entry.second->getState();
    if (curState.compare(state) == 0) {
        hospHighToLow.push_back((comboHospitalData *)entry.second);
    }
  }
  sort(hospHighToLow.begin(), hospHighToLow.end(), compareHospRating);
}


bool comparePovLevel(demogData * left, demogData * right) {
        return left->getBelowPoverty() < right->getBelowPoverty();
}

 void dataAQ::sortDemogPovLevelLowHigh(std::vector<demogData *>& povLevelLowHigh) {

  for (auto entry : allStateDemogData){
    povLevelLowHigh.push_back(entry.second);
  }

  sort(povLevelLowHigh.begin(), povLevelLowHigh.end(), comparePovLevel);

}


bool comparePovLevelInv(demogData * left, demogData * right) {
        return left->getBelowPoverty() > right->getBelowPoverty();
}

 void dataAQ::sortDemogPovLevelHighLow(std::vector<demogData *>& povLevelHighLow) {

  for (auto entry : allStateDemogData){
    povLevelHighLow.push_back(entry.second);
  }

  sort(povLevelHighLow.begin(), povLevelHighLow.end(), comparePovLevelInv);

}


/* DEBUG print all state data */
std::ostream& operator<<(std::ostream &out, const dataAQ &theAnswers) {
	for (auto const& entry : theAnswers.allStateDemogData) {
    	out << "State Info: " << entry.first << "\n  data: ";
    	out << *(entry.second) << "\n";
	}
  for (auto const& entry : theAnswers.allStateHospData) {
      out << "State Info: " << entry.first << "\n  data: ";
      out << *(entry.second) << "\n";
  }
    return out;
}


/*functions to parse city to county helper map */
void dataAQ::read_csvCityCounty(std::string filename) {

    // Create an input filestream
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

void dataAQ::stateReport(double thresh){
    int count = 0;
    visitorReport stateVisitor;
    for(auto state : allStateDemogData){
        if(state.second->getBelowPoverty() >= thresh){
            state.second->accept(stateVisitor);
            allStateHospData[state.first]->accept(stateVisitor);
            count++;
        }
    }

    cout << "\nGenerated a report for a total of: " << count << endl;   
}
