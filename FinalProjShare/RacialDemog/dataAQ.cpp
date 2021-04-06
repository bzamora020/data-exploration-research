/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include <iostream>
#include <algorithm>
#include "placeData.h"
#include "comboDemogData.h"

dataAQ::dataAQ() {}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */
void dataAQ::createStateDemogData(std::vector<shared_ptr<demogData> > theData) {
	    //process the vector in our county data aggregate 
    for (const auto &obj : theData) {
        // cout << obj->getName() << endl;
        // shared_ptr<demogData> comboData = static_pointer_cast<demogData>(obj);
        string stateName = obj->getState();
        //if first state entry, create it
        if (allStateDemogData.count(stateName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allStateDemogData[stateName] = new comboDemogData(stateName);
        }
        //either way now add this county info 
        //this keeps a running total
        allStateDemogData[stateName]->addCountytoState(obj);

    }
    //call average 
    for (const auto &elem: allStateDemogData){
        elem.second->average();
    }


}

void dataAQ::createStateHospData(std::vector<shared_ptr<hospitalData>> theData) {
	//TODO fill in
    for (const auto &obj: theData) {
        //get name for county data and put into combo data
        shared_ptr<hospitalData> comboData = static_pointer_cast<hospitalData>(obj);
        string stateName = obj->getState();
        if(allStateHospData.count(stateName) < 1) {
            allStateHospData[stateName] = new comboHospitalData(stateName, "", "state");
        }
        allStateHospData[stateName]->addCountytoState(comboData);
    }
    for (const auto &elem: allStateHospData){
        // if(elem.first == "AL"){
        //     cout << elem.first << endl;
        //     cout << elem.second->getOverallRate() << endl;
        // }
        elem.second->average();
    }
}

void dataAQ::createCountyHospData(std::vector<shared_ptr<hospitalData>> theData) {
	//TODO fill in
    for (const auto &obj: theData) {
        //get name for county data and put into combo data
        shared_ptr<hospitalData> comboData = static_pointer_cast<hospitalData>(obj);
        shared_ptr<cityHospitalData> cityData = static_pointer_cast<cityHospitalData>(obj);
        string stateName = obj->getState();
        string countyName = cityToCounty[cityData->getCity() + stateName];
        if(allCountyHData.count(countyName) < 1) {
            allCountyHData[countyName] = new comboHospitalData(stateName, countyName, "county");
        }
        allCountyHData[countyName]->addCountytoState(comboData);
    }
    for (const auto &elem: allCountyHData){
        elem.second->average();
    }
}

//compare predicate on teen population (on map entry)
bool compareTeen(std::pair<std::string, comboDemogData *> left, std::pair<std::string, comboDemogData *> right) {
        return left.second->getpopUnder18() < right.second->getpopUnder18();
}

//predicate version
//return the name of the state with the largest population under age 18
string dataAQ::teenPop()  {
  std::pair<std::string, comboDemogData *> min 
      = *max_element(allStateDemogData.begin(), allStateDemogData.end(), compareTeen);
  return min.first; 
}

bool compareHospRating(std::pair<std::string, comboHospitalData *> left, std::pair<std::string, comboHospitalData *> right){
    return left.second->getOverallRate() < right.second->getOverallRate();
}

bool compareMortRating(std::pair<std::string, comboHospitalData *> left, std::pair<std::string, comboHospitalData *> right){
    return left.second->getMortality() < right.second->getMortality();
}

bool compareReadmitRating(std::pair<std::string, comboHospitalData *> left, std::pair<std::string, comboHospitalData *> right){
    return left.second->getReadmit() < right.second->getReadmit();
}

/* Lab03 fill in */

string dataAQ::LowHospRating() {
    std::pair<std::string, comboHospitalData *> min
        = *min_element(allStateHospData.begin(), allStateHospData.end(), compareHospRating);
    return min.first;
}

string dataAQ::HighHospRating() {
    std::pair<std::string, comboHospitalData *> max
        = *max_element(allStateHospData.begin(), allStateHospData.end(), compareHospRating);
    return max.first;
}

string dataAQ::HighMortHospRating(){
    std::pair<std::string, comboHospitalData *> max
        = *max_element(allStateHospData.begin(), allStateHospData.end(), compareMortRating);
    return max.first;
}

string dataAQ::HighReadmitHospRating() {
    std::pair<std::string, comboHospitalData *> max
        = *max_element(allStateHospData.begin(), allStateHospData.end(), compareReadmitRating);
    return max.first;
}

bool compHospRating(comboHospitalData* left, comboHospitalData* right){
    return left->getOverallRate() < right->getOverallRate();
}

bool compHospRatingHighToLow(comboHospitalData* left, comboHospitalData* right){
    if(left->getOverallRate().getRatingNum() == right->getOverallRate().getRatingNum()){
        return left->getCounty() < right->getCounty();
    }
    return left->getOverallRate() > right->getOverallRate();
}

void dataAQ::sortHospRatingHighLow(std::vector<comboHospitalData *>& hospHighToLow, string regionType) {
    if(regionType == "state"){
        for (auto const& elem: allStateHospData){
            hospHighToLow.push_back(elem.second);
        }
    }
    else{
        for (auto const& elem: allCountyHData){
            hospHighToLow.push_back(elem.second);
        }
    }
    sort(hospHighToLow.begin(), hospHighToLow.end(), compHospRatingHighToLow);
}

void dataAQ::sortHospRatingLowHigh(std::vector<comboHospitalData *>& hospLowToHigh, string regionType) {
    if(regionType == "state"){
        for (auto const& elem: allStateHospData){
            hospLowToHigh.push_back(elem.second);
        }
    }
    else{
        for (auto const& elem: allCountyHData){
            hospLowToHigh.push_back(elem.second);
        }
    }
    sort(hospLowToHigh.begin(), hospLowToHigh.end(), compHospRating);
}

bool comparePovLevel(demogData* left, demogData* right){
    return left->getBelowPoverty() < right->getBelowPoverty();
}

bool comparePovLevelHightoLow(demogData* left, demogData* right){
    return left->getBelowPoverty() > right->getBelowPoverty();
}
void dataAQ::sortDemogPovLevelLowHigh(std::vector<demogData*>& incomeHighLow) {
    for (auto const& elem: allStateDemogData){
        incomeHighLow.push_back(elem.second);
    }
    sort(incomeHighLow.begin(), incomeHighLow.end(), comparePovLevel);
}

void dataAQ::sortDemogPovLevelHighLow(std::vector<demogData*>& povLevelHighLow) {
    for (auto const& elem: allStateDemogData){
        povLevelHighLow.push_back(elem.second);
    }
    sort(povLevelHighLow.begin(), povLevelHighLow.end(), comparePovLevelHightoLow);
}

// bool compAlphabetical(comboHospitalData* left, comboHospitalData* right){
//     if(left->getOverallRate().getRatingNum() == right->getOverallRate().getRatingNum()){
//         return left->getCounty() < right->getCounty();
//     }
// }

void dataAQ::sortHospRatingHighLowForState(std::vector<comboHospitalData *>& hospHighToLow, string state){
    for(auto const& elem: allCountyHData){
        if(elem.second->getState() == state){
            hospHighToLow.push_back(elem.second);
        }
    }
    sort(hospHighToLow.begin(), hospHighToLow.end(), compHospRatingHighToLow);
    // for(int i = 0; i < hospHighToLow.size() - 1; i++){
    //     if(hospHighToLow[i]->getOverallRate().getRatingNum() == hospHighToLow[i]->getOverallRate().getRatingNum()){
    //         if(hospHighToLow[i]->getCounty() > hospHighToLow[i+1]->getCounty()){
    //             comboHospitalData* temp = hospHighToLow[i];
    //             hospHighToLow[i] = hospHighToLow[i+1];
    //             hospHighToLow[i+1] = temp;
    //         }
    //     }
    // }
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
    visitorReport vr;
    thresh = thresh/100.0;
    int counter = 0;
    for (auto const& elem: allStateDemogData){
        if(elem.second->getBelowPoverty() > thresh){
            elem.second->accept(vr);
            allStateHospData[elem.first]->accept(vr);
            counter++;
        }
    }
    cout << "\nGenerated a report for a total of: " << counter << "\n";
}
